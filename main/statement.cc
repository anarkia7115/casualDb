#include <iostream>
#include "statement.h"
#include "utils.h"
#include "parser.h"

using namespace std;

PrepareResult 
Statement::Prepare() {
    if (StartsWith(query_, "insert")) {
        type_ = kStatementInsert;
        ParseInsert(query_, row_to_insert);
        return kPrepareSuccess;
    }
    if (StartsWith(query_, "select")) {
        type_ = kStatementSelect;
        return kPrepareSuccess;
    }

    return kPrepareUnrecognizedStatement;
}

void 
Statement::Execute() {
    switch (type_)
    {
    case kStatementInsert:
        cout << "This is where we will do an insert." << endl;
        break;
    case kStatementSelect:
        cout << "This is where we will do an insert." << endl;
        break;
    default:
        cout << "Unexpected statement type" << endl;
        break;
    }
}