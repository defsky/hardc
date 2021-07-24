#include <stdio.h>
#include <ctype.h>

#include "dbg.h"

int print_a_message(const char* msg)
{
    check(msg != NULL,"param msg can not be null");

    printf("A STRING: %s\n", msg);

    return 0;

error:
    return 1;
}

int uppercase(const char* msg)
{
    check(msg != NULL,"param msg can not be null");

    int i = 0;

    for(i=0; msg[i] != '\0'; i++) {
        printf("%c", toupper(msg[i]));
    }

    printf("\n");

    return 0;

error:
    return 1;
}

int lowercase(const char* msg)
{
    check(msg != NULL,"param msg can not be null");

    int i = 0;

    for (i=0; msg[i]!='\0'; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;

error:
    return 1;
}

int fail_on_purpose(const char* msg)
{
    check(msg != NULL,"param msg can not be null");

    return 0;

error:
    return 1;
}
