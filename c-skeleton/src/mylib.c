#include <stdio.h>
#include <assert.h>

void println(char* msg)
{
    assert(msg != NULL);

    printf("%s\n", msg);    
}
