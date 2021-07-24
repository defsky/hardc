#include <stdio.h>

#include "dbg.h"

typedef struct person {
    int age;
    char first_name[100];
    char last_name[100];
    float income;
} Person;

char* rtrim(char* str)
{
    check_debug(str != NULL,"str can not be NULL");

    int i = 0;

    while (str[i] > 0)
        i++;

    i = i - 1; // index of last char in str

    while ( i>=0 ) {
        switch (str[i]) {
        case '\n':
        case '\t':
        case '\r':
        case ' ':
            str[i] = '\0';
            i--;
            break;
        default:
            i = -1;
        }
    }

    return str;

error:
    return NULL; 
}

int main(int argc, char* argv[])
{
    Person you = {
        .age = 0
    };

    int i = 0;
    char* in = NULL;

    printf("What is your First name? ");
    in = rtrim(fgets(you.first_name, 100 - 1, stdin));
    check(in != NULL, "Failed to read first name.");

    printf("What is you Last name? ");
    in = rtrim(fgets(you.last_name, 100 - 1, stdin));
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("\n=========Summary Info==========\n\tFull Name: %s %s\n\tAge: %d\n",
            you.first_name, you.last_name, you.age);

error:
    return -1;
}
