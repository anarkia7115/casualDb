typedef enum {
    kMetaCommandSuccess, 
    kMetaCommandUnrecognizedCommand
} MetaCommandResult;

void PrintPrompt();
int DoMetaCommand(string input);