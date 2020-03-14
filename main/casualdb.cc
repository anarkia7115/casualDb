#include <iostream>
#include <string>

#include "main/statement.h"

namespace casualdb {

typedef enum {
    kMetaCommandSuccess, 
    kMetaCommandUnrecognizedCommand
} MetaCommandResult;

int DoMetaCommand(std::string input) {
    if (input.compare(".exit") == 0) {
        std::cout << "Bye!" << std::endl;
        exit(EXIT_SUCCESS);
    } else {
        return kMetaCommandUnrecognizedCommand;
    }
}

void PrintPrompt() {
    std::cout << "db > "; 
}

int main(int argc, char* argv[]) {
    std::string input;
    Table table;
    if (argc >= 2) {
        std::string filename (argv[1]); 
        table = Table(filename);
    } else {
        table = Table();
    }

    while(true) {
        PrintPrompt();
        if(!std::getline(std::cin, input)) {
            exit(EXIT_SUCCESS);
        }

        // meta command
        if (input[0] == '.') {
            switch(DoMetaCommand(input)) {
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