#ifndef PARSER_H_
#define PARSER_H_
#include "statement.h"
#include <sstream>
PrepareResult ParseInsert(string query, Row &row_to_insert) {
    /*
    id int
    url string
    title string

    > insert 1 cnn.com/one_news.html i_m_a_news
    */

    istringstream query_stream(query);
    query_stream >> row_to_insert.id >> row_to_insert.url 
        >> row_to_insert.title;

}
#endif // PARSER_H_