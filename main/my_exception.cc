#include <exception>
class MetaCommandException: public std::exception {
    public:
    const char* what() const throw() {
        return "Unrecognized command ";
    }

};