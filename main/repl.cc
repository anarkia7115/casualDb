#include <iostream>
// #include "my_exception.cc"
#include "repl.h"
#include "statement.h"

int main(int argc, char* argv[]) {
    string input;
    while(true) {
        PrintPrompt();
        getline(cin, input);

        if (input[0] == '.') {
            switch(DoMetaCommand(input)) {
                case (kMetaCommandSuccess):
                    continue;
                case(kMetaCommandUnrecognizedCommand):
                    cout << "Unrecognized command '" << input 
                        << "'." << endl;
                    continue;
            }
        }

        Statement statement = Statement(input);
        switch(statement.Prepare()) {
            case (kPrepareSuccess):
                break;
            case (kPrepareUnrecognizedStatement):
                cout << "Unrecognized keyword at start of '" << input
                    << "'." << endl;
                continue;
        }

        statement.Execute();
        cout << "Executed!" << endl;
    }
}

int DoMetaCommand(string input) {
    if (input.compare(".exit") == 0) {
        cout << "Bye!" << endl;
        exit(EXIT_SUCCESS);
    } else {
        return kMetaCommandUnrecognizedCommand;
    }
}

void PrintPrompt() {
    cout << "hello, zen > "; 
}