#ifndef STATE_H_
#define STATE_H_

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

#endif // STATE_H_