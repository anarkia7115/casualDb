#include "gtest/gtest.h"
#include <sstream>
#include "main/parser.h"

using namespace std;

TEST(Parser, IStringStream) {
    istringstream ss("11 aaa bbb ccc ddd");
    int id;
    string url;
    string title;
    int another;
    ss >> id >> url >> title >> another;
    cout << id << url << title << another;

    EXPECT_EQ(id, 11);
    EXPECT_EQ(url, "aaa");
    EXPECT_EQ(title, "bbb");
    EXPECT_EQ(another, 0);
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
    EXPECT_EQ(row.id, 1);
    EXPECT_EQ(row.url, "cnn.com/exciting");
    EXPECT_EQ(row.title, "exciting");
}
