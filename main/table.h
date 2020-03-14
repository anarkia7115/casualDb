#ifndef TABLE_H_
#define TABLE_H_

#include <cstdint>

#include <string>

#include "main/row.h"
#include "main/state.h"

namespace casualdb
{


const uint32_t kPageSize = 4096;
#define kTableMaxPages 100
const uint32_t kRowsPerPage = kPageSize / Row::kRowSize;
const uint32_t kTableMaxRows = kRowsPerPage * kTableMaxPages;

class Pager {
public:
  uint32_t file_length;
  int file_descriptor;
  void* pages[kTableMaxPages];
  Pager(std::string db_file);
  ~Pager();
  void* GetPage(std::uint32_t page_number);
  void Flush(uint32_t i, uint32_t size);
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
  
} // namespace casualdb

#endif // TABLE_H_
