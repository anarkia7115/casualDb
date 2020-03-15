#ifndef TABLE_CC_
#define TABLE_CC_

#include "table.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>

#include "main/row.h"
#include "main/logging.h"

namespace casualdb
{

Pager::Pager() {}

void Pager::Load(std::string db_file) {
    int fd = open(
        db_file.c_str(), 
        O_RDWR |
            O_CREAT, 
        S_IWUSR |
            S_IRUSR
    );

    if (fd == -1) {
        throw std::runtime_error("Unable to open file.\n");
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
        void* page(pages[i]);
        if (page) {
            free(page);
            pages[i] = NULL;
        }
    }
}

void*
Pager::GetPage(uint32_t page_num) {
    if (page_num > kTableMaxPages) {
        throw std::out_of_range("Tried to fetch page number out of max.\n");
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

/** Write page to file */
void
Pager::Flush(uint32_t page_num, uint32_t size) {
    if (this->pages[page_num] == NULL) {
        throw std::runtime_error("Tried to flush null page.\n");
    }

    off_t offset = lseek(this->file_descriptor, page_num * kPageSize, SEEK_SET);

    if (offset == -1) {
        throw std::runtime_error("Error seeking: " + std::to_string(errno) + "\n");
    }

    ssize_t bytes_written = 
        write(this->file_descriptor, this->pages[page_num], size);

    if (bytes_written == -1) {
        throw std::runtime_error("Error writing: " + std::to_string(errno) + "\n");
    }
}

Table::Table() {
    this->pager = new Pager();
}

void Table::Load(std::string db_file) {
    this->pager->Load(db_file);
    this->num_rows = this->pager->file_length / Row::kRowSize;
}

Table::~Table() {
}

void
Table::Close() {
    uint32_t num_full_pages = 
        this->num_rows / kRowsPerPage;

    // flush all pages to file
    for (uint32_t i=0; i < num_full_pages; i++) {
        // skip if empty page
        if (pager->pages[i] == NULL) {
            continue;
        }
        pager->Flush(i, kPageSize);
        free(pager->pages[i]);
        // TODO: is this necessary? 
        pager->pages[i] = NULL;
    }

    // Last page
    uint32_t num_additional_rows = 
        this->num_rows % kRowsPerPage;
    if(num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;
        if(pager->pages[page_num] != NULL) {
            pager->Flush(page_num, num_additional_rows*Row::kRowSize);
            free(pager->pages[page_num]);
            pager->pages[page_num] = NULL;
        }
    }

    int result = close(pager->file_descriptor);
    if (result == -1) {
        throw std::runtime_error("Error closing db file.\n");
    }
}
} // namespace casualdb

#endif // TABLE_CC_