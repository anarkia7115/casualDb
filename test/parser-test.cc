#include "gtest/gtest.h"
#include <sstream>
#include "main/parser.h"

TEST(Parser, IStringStream) {
    std::istringstream ss("11 aaa bbb ccc ddd");
    int id;
    std::string url;
    std::string title;
    int another;
    ss >> id >> url >> title >> another;
    std::cout << id << url << title << another << std::endl;

    EXPECT_EQ(id, 11);
    EXPECT_EQ(url, "aaa");
    EXPECT_EQ(title, "bbb");
    EXPECT_EQ(another, 0);

    std::istringstream ss2("22 bbb2");
    ss2 >> id >> url >> title >> another;
    std::cout << id << url << title << another << std::endl;
    EXPECT_EQ(id, 22);
    EXPECT_EQ(url, "bbb2");
    EXPECT_EQ(title, "");
}

TEST(Parser, ParseInsert) {
    Row row;
    PrepareResult toFail = ParseInsert(
        "inserts hello", 
        row
    );
    EXPECT_EQ(toFail, kPrepareUnrecognizedStatement);

    PrepareResult successInsert = ParseInsert(
        "insert 1 cnn.com/exciting exciting", 
        row
    );
    EXPECT_EQ(successInsert, kPrepareSuccess);
    EXPECT_EQ(row.id, (uint32_t) 1);
    EXPECT_EQ(strcmp(row.url, "cnn.com/exciting"), 0);
    EXPECT_EQ(strcmp(row.title, "exciting"), 0);
}
