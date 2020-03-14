#ifndef REPL_H_
#define REPL_H_
#include <string>

namespace casualdb
{
typedef enum {
    kMetaCommandSuccess, 
    kMetaCommandUnrecognizedCommand
} MetaCommandResult;

void PrintPrompt();
int DoMetaCommand(std::string input);
} // namespace casualdb

#endif // REPL_H_