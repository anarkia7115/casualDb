#ifndef TABLE_CC_
#define TABLE_CC_

#include "table.h"

#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>

#include "row.h"
#include "logging.h"

Pager::Pager(std::string db_file) {
    int fd = open(
        db_file.c_str(), 
        O_RDWR |
            O_CREAT, 
        S_IWUSR |
            S_IRUSR
    );

    if (fd == -1) {
        std::cout << "Unable to open file"
            << std::endl;
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    this->file_descriptor = fd;
    this->file_length = file_length;

    for (uint32_t i=0; i< kTableMaxPages; i++) {
        this->pages[i] = NULL;
    }
}

Pager::~Pager() {
    for (uint32_t i=0; i<kTableMaxPages; i++) {
        void* page = pages[i];
        if (page) {
            free(page);
            pages[i] = NULL;
        }
    }
}

void* 
Pager::GetPage(uint32_t page_num) {
    if (page_num > kTableMaxPages) {
        std::cout << "Tried to fetch page number out of max" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (this->pages[page_num] == NULL) {
        void* page = malloc(kPageSize);
        uint32_t num_pages = file_length / kPageSize;

        if ((file_length % kPageSize) != 0) {
            num_pages += 1;
        }

        // read if not new
        if (page_num <= num_pages) {
            lseek(this->file_descriptor, page_num*kPageSize, SEEK_SET);
            ssize_t bytes_read = read(this->file_descriptor, page, kPageSize);
            if (bytes_read == -1) {
                std::cout << "Error reading file: " << this->file_descriptor
                    << errno << std::endl;
            }
        }

        this->pages[page_num] = page;
    }
    return this->pages[page_num];
}

void
Pager::Flush(uint32_t page_num, uint32_t size) {
    if (this->pages[page_num] == NULL) {
        Log().Get(kLogError) << "Tried to flush null page.";
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(this->file_descriptor, page_num * kPageSize, SEEK_SET);

    if (offset == -1) {
        Log().Get(kLogError) << "Error seeking: " << errno;
        
    }
}

Table::Table(std::string db_file) {
    Pager pager(db_file);
    this->num_rows_ = pager.file_length / Row::kRowSize;
}

Table::Table() {
    Table(".casual_db");
}

Table::~Table() {
    uint32_t num_full_pages = 
        this->num_rows_ / kRowsPerPage;

    // flush all pages
    for (uint32_t i=0; i < num_full_pages; i++) {
        // skip if empty page
        if (pager_->pages[i] == NULL) {
            continue;
        }
        pager_->Flush(i, kPageSize);
        free(pager_->pages[i]);
        // TODO is this necessary? 
        pager_->pages[i] = NULL;
    }

    // There may be a partial page to write 
    // at the end of file
    uint32_t num_additional_rows = 
        this->num_rows_ % kRowsPerPage;
    if(num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;
        if(pager_->pages[page_num] != NULL) {
            pager_->Flush(page_num, num_additional_rows);
            free(pager_->pages[page_num]);
            pager_->pages[page_num] = NULL;
        }
    }

    int result = close(pager_->file_descriptor);
    if (result == -1) {
        std::cout << "Error closing db file."
            << std::endl;
        exit(EXIT_FAILURE);
    }
    // free all pages
    // move this to ~Pager()
    free(pager_);
}

void* 
Table::RowSlot(uint32_t row_num) {
    uint32_t page_num = row_num / kRowsPerPage;
    void* page = this->pager_->GetPage(page_num);
    uint32_t row_offset = row_num % kRowsPerPage;
    uint32_t byte_offset = row_offset * Row::kRowSize;
    return page + byte_offset;
}

ExecuteResult
Table::Insert(Row row_to_insert) {
    if (this->num_rows_ >= kTableMaxRows) {
        return kExecuteTableFull;
    }

    row_to_insert.Serialize(RowSlot(this->num_rows_));
    this->num_rows_ += 1;

    return kExecuteSuccess;
}

ExecuteResult
Table::Select() {
    Row row;
    for (uint32_t i = 0; i < this->num_rows_; i++) {
        row.Deserialize(RowSlot(i));
        row.Print();
    }
    return kExecuteSuccess;
}

#endif // TABLE_CC_