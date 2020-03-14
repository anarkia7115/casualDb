#include "main/utils.h"

#include <string>
#include <ctime>

namespace casualdb
{

bool StartsWith(std::string one_string, std::string another_string) {
    // one_string.substr(0, another_string.length)
    return one_string.compare(0, another_string.size(), another_string) == 0;
}

std::string NowTime() {
    std::time_t now = std::time(0);
    return std::ctime(&now);
}
    
} // namespace casualdb
