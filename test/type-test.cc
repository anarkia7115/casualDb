#include <typeinfo>
#include <iostream>
#include <string>
#include "gtest/gtest.h"

TEST(Type_test, test_ostream_type) {
    std::string a = "Hello";
    std::cerr << "type: " << typeid(a).name() << std::endl;
}