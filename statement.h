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

typedef map<StatementType, string> StatementTypeKeywords;