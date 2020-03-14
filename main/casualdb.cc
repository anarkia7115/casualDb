#include <iostream>
#include <string>

#include "main/statement.h"

namespace casualdb {

typedef enum {
    kMetaCommandExit,
    kMetaCommandSuccess, 
    kMetaCommandUnrecognizedCommand
} MetaCommandResult;

int DoMetaCommand(std::string input) {
    if (input.compare(".exit") == 0) {
        std::cout << "Bye!" << std::endl;
        return kMetaCommandExit;
    } else {
        return kMetaCommandUnrecognizedCommand;
    }
}

void PrintPrompt() {
    std::cout << "db > "; 
}

void Repl(std::string db_file) {
    Table table = Table(db_file);

    std::string input;
    while(true) {
        PrintPrompt();
        if(!std::getline(std::cin, input)) {
            return;
        }

        // meta command
        if (input[0] == '.') {
            switch(DoMetaCommand(input)) {
                case (kMetaCommandExit):
                    return;
                case (kMetaCommandSuccess):
                    continue;
                case(kMetaCommandUnrecognizedCommand):
                    std::cout << "Unrecognized command '" << input 
                        << "'." << std::endl;
                    continue;
            }
        }

        // parse statement
        Statement statement = Statement(input, &table);
        switch(statement.Prepare()) {
            case (kPrepareSuccess):
                break;
            case (kPrepareIdNegative):
                std::cout << "ID must be positive." << std::endl;
                continue;
            case (kPrepareStringTooLong):
                std::cout << "String is too long." << std::endl;
                continue;
            case (kPrepareUnrecognizedStatement):
                std::cout << "Unrecognized keyword at start of '" << input
                    << "'." << std::endl;
                continue;
            case (kPrepareSyntaxError):
                std::cout << "Syntax Error '" << input
                    << "'." << std::endl;
                continue;
        }

        // execute statement
        switch(statement.Execute()) {
            case (kExecuteSuccess):
                std::cout << "Executed!" << std::endl;
                break;
            case (kExecuteTableFull):
                std::cout << "Error: Table full." << std::endl;
                break;
            case (kExecuteFail):
                std::cout << "Failed!" << std::endl;
                break;
        }
    }
}
} // namespace casualdb

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        casualdb::Repl(argv[1]);
    } else {
        casualdb::Repl(".casualdb");
    }
    return 0;
}