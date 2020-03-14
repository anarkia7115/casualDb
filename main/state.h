#ifndef STATE_H_
#define STATE_H_

namespace casualdb
{

typedef enum {
    kStatementInsert, 
    kStatementSelect
} StatementType;

typedef enum {
    kPrepareSuccess, 
    kPrepareIdNegative, 
    kPrepareStringTooLong, 
    kPrepareSyntaxError, 
    kPrepareUnrecognizedStatement
} PrepareResult;

typedef enum {
    kExecuteSuccess, 
    kExecuteTableFull, 
    kExecuteFail
} ExecuteResult; 
    
} // namespace casualdb

#endif // STATE_H_