#ifndef TABLE_CC_
#define TABLE_CC_

#include "table.h"
#include <cstdlib>

Table::Table() {
    this->num_rows_ = 0;
    for (uint32_t i=0; i < kTableMaxPages; i++) {
        this->pages_[i] = NULL;
    }
}

Table::~Table() {
    for (int i=0; this->pages_[i]; i++) {
        free(this->pages_[i]);
    }
}

void* 
Table::RowSlot(uint32_t row_num) {
    uint32_t page_num = row_num / kRowsPerPage;
    void* page = this->pages_[page_num];
    if (page == NULL) {
        // Allocate memory only when we try to access page
        page = this->pages_[page_num] = malloc(kPageSize);
    }
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