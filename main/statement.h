#ifndef STATEMENT_H_
#define STATEMENT_H_

#include <map>
#include <string>

#include "row.h"
#include "table.h"

class Statement {
  private:
    StatementType type_;
    std::string query_;
    Row row_;
    Table* table_;

  public:
    Statement(std::string q, Table* t): query_(q), table_(t) {}
    PrepareResult Prepare();
    ExecuteResult Execute();
};

#endif // STATEMENT_H_