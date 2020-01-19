#ifndef REPL_H_
#define REPL_H_
#include <string>
typedef enum {
    kMetaCommandSuccess, 
    kMetaCommandUnrecognizedCommand
} MetaCommandResult;

void PrintPrompt();
int DoMetaCommand(std::string input);

#endif // REPL_H_