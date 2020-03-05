#include <iostream>
// #include "my_exception.cc"
#include "repl.h"
#include "statement.h"

int main(int argc, char* argv[]) {
    std::string input;
    Table table = Table();
    while(true) {
        PrintPrompt();
        std::getline(std::cin, input);

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
        statement.Execute();
        std::cout << "Executed!" << std::endl;
    }
}

int DoMetaCommand(std::string input) {
    if (input.compare(".exit") == 0) {
        std::cout << "Bye!" << std::endl;
        exit(EXIT_SUCCESS);
    } else {
        return kMetaCommandUnrecognizedCommand;
    }
}

void PrintPrompt() {
    std::cout << "hello, zen > "; 
}