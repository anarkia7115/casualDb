#include "gtest/gtest.h"
#include <string>

TEST(TestSizeOfString, test_size_of_string) {
    std::string s1 = "a";
    std::string s2 = "aaa";
    // 256
    std::string s3 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    std::cout 
        << "s1:" << sizeof(s1) << "\t" << s1.size() << "\t" << s1.capacity() <<  std::endl
        << "s2:" << sizeof(s2) << "\t" << s2.size() << "\t" << s2.capacity() <<  std::endl
        << "s3:" << sizeof(s3) << "\t" << s3.size() << "\t" << s3.capacity() <<  std::endl
        << "string:" << sizeof(std::string) <<  std::endl
        << "string capacity:" << std::string().capacity() <<  std::endl;
}