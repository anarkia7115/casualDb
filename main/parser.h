#ifndef PARSER_H_
#define PARSER_H_
#include <sstream>
#include <cstring>
PrepareResult ParseInsert(std::string query, Row &row_to_insert) {
    /*
    id int
    url string
    title string

    > insert 1 cnn.com/one_news.html i_m_a_news
    */

    std::istringstream query_stream(query);
    std::string query_keyword;
    std::string str_id;
    std::string url;
    std::string title;
    query_stream >> query_keyword 
        >> str_id
        >> url 
        >> title;
    int id = std::stoi(str_id);
    if (id < 0) {
        return kPrepareIdNegative;
    }
    if (url.size() > kColumnUrlSize) {
        return kPrepareStringTooLong;
    }
    if (title.size() > kColumnTitleSize) {
        return kPrepareStringTooLong;
    }

    row_to_insert.id = id;
    std::strcpy(row_to_insert.url, url.c_str());
    std::strcpy(row_to_insert.title, title.c_str());

    return kPrepareSuccess;
}

#endif // PARSER_H_