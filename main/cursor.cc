#include "main/cursor.h"

namespace casualdb
{

Cursor::Cursor(Table* table, TablePos table_pos) {
    this->table = table;
    this->row_num = table_pos == kTableEnd ? table->num_rows : 0;
    this->end_of_table = table_pos == kTableEnd ? true : (table->num_rows == 0);
}

Row*
Cursor::Value() {
    uint32_t row_num = this->row_num;
    uint32_t page_num = row_num / kRowsPerPage;
    void* page = this->table->pager->GetPage(page_num);
    uint32_t row_offset = row_num % kRowsPerPage;
    uint32_t byte_offset = row_offset * Row::kRowSize;
    return reinterpret_cast<Row*>((uint8_t*)page + byte_offset);
}

ExecuteResult
Cursor::Insert(Row row_to_insert) {
    if (this->table->num_rows >= kTableMaxRows) {
        return kExecuteTableFull;
    }

    row_to_insert.Serialize(this->Value());
    this->table->num_rows += 1;

    return kExecuteSuccess;
}

Row
Cursor::Select() {
    Row row;
    row.Deserialize(Value());
    return row;
}

void
Cursor::Advance() {
    this->row_num += 1;
    if (this->row_num >= this->table->num_rows) {
        this->end_of_table = true;
    }
}

} // namespace casualdb
