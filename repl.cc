#include <iostream>
#include <string>
#include "my_exception.cc"
#include "repl.h"
#include "statement.cc"

using namespace std;

int main(int argc, char* argv[]) {
    string input;
    while(true) {
        PrintPrompt();
        // cin >> input;
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
        switch(statement.prepare()) {
            case (kPrepareSuccess):
                break;
            case (kPrepareUnrecognizedStatement):
                cout << "Unrecognized keyword at start of '" << input
                    << "'." << endl;
                continue;
        }

        statement.execute();
        cout << "Executed!" << endl;
    }
}

int DoMetaCommand(string input) {
    if (input.compare(".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return kMetaCommandUnrecognizedCommand;
    }
}

void PrintPrompt() {
    cout << "be cool > "; 
}