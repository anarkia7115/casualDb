#include <exception>
using namespace std;
class MetaCommandException: public exception {
    public:
    const char* what() const throw() {
        return "Unrecognized command ";
    }

};