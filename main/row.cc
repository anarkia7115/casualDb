#include <iostream>
#include <cstring>
#include "row.h"

void 
Row::Serialize(void* destination) {
    memcpy(destination + kIdOffset, &(this->id), kIdSize);
    memcpy(destination + kUrlOffset, &(this->url), kUrlSize);
    memcpy(destination + kTitleOffset, &(this->title), kTitleSize);
}

void 
Row::Deserialize(void* source) {
    memcpy( &(this->id), source + kIdOffset, kIdSize);
    memcpy( &(this->url), source + kUrlOffset, kUrlSize);
    memcpy( &(this->title), source + kTitleOffset, kTitleSize);
}

void
Row::Print() {
    std::cout << id << url << title << std::endl;
}