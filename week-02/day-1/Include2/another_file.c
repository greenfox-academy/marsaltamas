// TODO: Include needed header files
#include <stdint.h>
#include <string.h>
#include "another_file.h"

void StringManipulator(char* str)
{
    uint32_t str_len = strlen(str);

    for(uint32_t i = 0; i < str_len; i++) {
        str[i] -= 1;
    }
}

void StringResetter(char* str)
{
    uint32_t str_len = strlen(str);

    for(uint32_t i = 0; i < str_len; i++) {
        str[i] -= -1;
    }
}

void IntegerManipulator(int* num){
    *num = num - an_example_number;
}
