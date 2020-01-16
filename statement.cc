#include <iostream>
#include "statement.h"
#include "utils.cc"

using namespace std;
class Statement {
    private:
    StatementType type_;
    string query_;
    const StatementTypeKeywords keywords_ { 
        {kStatementSelect,"select"}, 
        {kStatementInsert,"insert"}};

    public:
    Statement(string query): query_(query) {}
    PrepareResult prepare() {
        for (auto &[statement_type, keyword] : keywords_) {
            if (StartsWith(query_, keyword)) {
                type_ = statement_type;
                return kPrepareSuccess;
            }
        }
        return kPrepareUnrecognizedStatement;
    }

    void execute() {
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
};
