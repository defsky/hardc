#include <stdio.h>
#include "mylib.h"

int main(int argc, char* argv[])
{
    int i = 0;

    char* names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    char** cur_name = names;

    long unsigned int names_size = sizeof(names);
    long unsigned int char_pointer_size = sizeof(char*);
    unsigned int names_count = names_size / char_pointer_size;

    printf("size of names: %ld\n", sizeof(names));
    printf("size of char*: %ld\n", sizeof(char*));

    for(i=0; i<names_count; i++){
        printf("%p -> %p(%p) = names[%d] :  %s\n", 
                cur_name + i, *(cur_name + i), names[i], i, *(cur_name + i));
    }

    return 0;
}
