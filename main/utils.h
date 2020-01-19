#ifndef UTILS_H_
#define UTILS_H_
#include <string>

bool StartsWith(string one_string, string another_string) {
    // one_string.substr(0, another_string.length)
    return one_string.compare(0, another_string.size(), another_string) == 0;
}

#endif // UTILS_H_