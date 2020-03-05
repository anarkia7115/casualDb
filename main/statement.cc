#include <iostream>
#include "statement.h"
#include "utils.h"
#include "parser.h"

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
    case kStatementInsert:
        return this->table_->Insert(this->row_);
    case kStatementSelect:
        return this->table_->Select();
    default:
        std::cout << "Unexpected statement type" << std::endl;
        return kExecuteFail;
    }
}