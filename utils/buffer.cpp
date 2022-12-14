#include <iostream>
#include <string.h>

#include "buffer.h"


Buffer::Buffer(int size)
{
    if(size < 0)
    {
        this->buff_size = 0;
        std::cerr << "WARNING buffer can't have a negative size, buffer size is set to 0!" << std::endl;
    }
    else
    {
        this->buff_size = size;
    }
    ++size; // the '\0' byte at the end
    this->buff = (char*) calloc(size, sizeof(char));
}

Buffer::~Buffer()
{
    free(this->buff);
    this->buff = nullptr;
}

std::string Buffer::read()
{
    return std::string(this->buff);
}

void Buffer::write(std::string& text)
{
    size_t sz = text.size();
    this->clear();

    if(sz > this->buff_size)
        sz = this->buff_size;

    strncpy(this->buff, text.c_str(), sz);
    this->buff[sz] = 0;
}


void Buffer::clear()
{
    for(size_t i = 0; i < this->buff_size; ++i)
        this->buff[i] = 0;
}


char* Buffer::getBuffer(){return this->buff;}
int Buffer::getSize(){return this->buff_size;}
