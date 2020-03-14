#include "row.h"

#include <cstring>
#include <cstdio>

#include <iostream>

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
    printf("(%d, %s, %s)\n", id, url, title);
}
