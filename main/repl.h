#ifndef REPL_H_
#define REPL_H_
#include <string>
using namespace std;
typedef enum {
    kMetaCommandSuccess, 
    kMetaCommandUnrecognizedCommand
} MetaCommandResult;

void PrintPrompt();
int DoMetaCommand(string input);

#endif // REPL_H_