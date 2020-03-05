#ifndef TABLE_H_
#define TABLE_H_

#include <cstdint>
#include "row.h"
#include "state.h"

const uint32_t kPageSize = 4096;
#define kTableMaxPages 100
const uint32_t kRowsPerPage = kPageSize / Row::kRowSize;
const uint32_t kTableMaxRows = kRowsPerPage * kTableMaxPages;

class Table {
    uint32_t num_rows_;
    void* pages_[kTableMaxPages];
    void* RowSlot(std::uint32_t row_num);

  public:
    Table();
    ~Table();
    ExecuteResult Insert(Row row);
    ExecuteResult Select();
};

#endif // TABLE_H_
