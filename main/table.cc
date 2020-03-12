#ifndef TABLE_CC_
#define TABLE_CC_

#include <iostream>
#include <cstdlib>
#include "fcntl.h"
#include "unistd.h"

#include "table.h"
#include "row.h"

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
        this->pages_[i] = NULL;
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
    for (int i=0; this->pages_[i]; i++) {
        free(this->pages_[i]);
    }
}

void* 
Pager::GetPage(uint32_t page_num) {
    if (page_num > kTableMaxPages) {
        std::cout << "Tried to fetch page number out of max" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (this->pages_[page_num] == NULL) {
        void* page = malloc(kPageSize);
        uint32_t num_pages = file_length / kPageSize;

        // TODO: save a partial page
        if (file_length % kPageSize) {
            num_pages += 1;
        }

        // read if not new
        if (page_num <= num_pages)

    }

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