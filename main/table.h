#ifndef TABLE_H_
#define TABLE_H_

#include <cstdint>

#include <string>

#include "main/row.h"

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
  Pager();
  ~Pager();

  void Load(std::string db_file);
  void* GetPage(std::uint32_t page_number);
  void Flush(uint32_t i, uint32_t size);
};

class Table {

  public:
    Pager* pager;
    uint32_t num_rows;

    Table();
    ~Table();
    void Load(std::string db_file);
    void Close();
};
  
} // namespace casualdb

#endif // TABLE_H_
