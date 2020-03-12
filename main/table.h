#ifndef TABLE_H_
#define TABLE_H_

#include <string>
#include <cstdint>
#include "row.h"
#include "state.h"

const uint32_t kPageSize = 4096;
#define kTableMaxPages 100
const uint32_t kRowsPerPage = kPageSize / Row::kRowSize;
const uint32_t kTableMaxRows = kRowsPerPage * kTableMaxPages;

class Pager {
  int file_descriptor;
  void* pages_[kTableMaxPages];
public:
  uint32_t file_length;
  Pager(std::string db_file);
  void* GetPage(std::uint32_t page_number);
  ~Pager();
};

class Table {
    uint32_t num_rows_;
    Pager* pager_;
    void* RowSlot(std::uint32_t row_num);

  public:
    Table(std::string db_file);
    Table();
    ~Table();
    ExecuteResult Insert(Row row);
    ExecuteResult Select();
};

#endif // TABLE_H_
