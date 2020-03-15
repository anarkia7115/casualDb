#ifndef CURSOR_H_
#define CURSOR_H_

#include "main/table.h"
#include "main/state.h"

namespace casualdb
{

enum TablePos {
    kTableStart, 
    kTableEnd
};

class Cursor {
public:
    Table* table;
    uint32_t row_num;
    bool end_of_table;
    Cursor(Table* table, TablePos table_pos);

    Row* Value();
    ExecuteResult Insert(Row row);
    Row Select();
    void Advance();
};
    
} // namespace casualdb

#endif // CURSOR_H_