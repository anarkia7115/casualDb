#include "row.h"

#include <cstring>
#include <cstdio>

#include <iostream>
namespace casualdb
{

void 
Row::Serialize(Row* destination) {
    destination->id = this->id;
    std::strcpy(destination->url, this->url);
    std::strcpy(destination->title, this->title);
}

void 
Row::Deserialize(Row* source) {
    this->id = source->id;
    std::strcpy(this->url, source->url);
    std::strcpy(this->title, source->title);
}

void
Row::Print() {
    printf("(%d, %s, %s)\n", id, url, title);
}

} // namespace casualdb