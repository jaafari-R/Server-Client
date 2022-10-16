#ifndef __BUFFER__
#define __BUFFER__
#include <string>

/*  Holds a dynamically allocated char string,
    provides reading, writing operations on the string
*/
class Buffer
{
public:
    /*  Initializes the buffer according to the provided size
    /*  If the size is less than 0, buffer_size is set to 0, 
    /*   and a Warning is printed.
    */
    Buffer(int size);
    /*  Frees/Cleans the buffer
    */
    ~Buffer();

    /* TODO 
    */
    void read();

    /* clears the buffer and writes new text to it
    */
    void write(std::string text);
    
    /* Sets all values in the buffer to 0
    */
    void clear();
    
    char* getBuffer();
    int getSize();

private:
    char* buff;
    int buff_size;
};

#endif//__BUFFER__