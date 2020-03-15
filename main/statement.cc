#include "main/statement.h"

#include <iostream>

#include "main/utils.h"
#include "main/parser.h"
#include "main/state.h"
#include "main/cursor.h"

namespace casualdb
{

PrepareResult 
Statement::Prepare() {
    if (StartsWith(query_, "insert")) {
        type_ = kStatementInsert;
        return ParseInsert(query_, this->row_);
    }

    if (StartsWith(query_, "select")) {
        type_ = kStatementSelect;
        return kPrepareSuccess;
    }

    return kPrepareUnrecognizedStatement;
}

ExecuteResult
Statement::Execute() {
    switch (type_)
    {
    Cursor* cursor;
    case kStatementInsert:
        cursor = new Cursor(table_, kTableEnd);
        return cursor->Insert(this->row_);
    case kStatementSelect:
        cursor = new Cursor(table_, kTableStart);
        while(!(cursor->end_of_table)) {
            cursor->Select().Print();
            cursor->Advance();
        }
        return kExecuteSuccess;
    default:
        std::cout << "Unexpected statement type" << std::endl;
        return kExecuteFail;
    }
}
    
} // namespace casualdb