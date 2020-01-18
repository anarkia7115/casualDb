#ifndef STATEMENT_H_
#define STATEMENT_H_
#include <map>
#include <string>
using namespace std;

typedef enum {
    kStatementInsert, 
    kStatementSelect
} StatementType;

typedef enum {
    kPrepareSuccess, 
    kPrepareUnrecognizedStatement
} PrepareResult;

typedef struct {
    uint32_t id;
    string url;
    string title;
} Row;

class Statement {
    private:
    StatementType type_;
    string query_;
    Row row_to_insert;

    public:
    Statement(string q): query_(q) {}

    PrepareResult Prepare();

    void Execute();
};

#endif // STATEMENT_H_