#include <stdio.h>

typedef struct person {
    char* name;
    int age;
    int height;
} Person;

int main(int argc, char* argv[])
{
    Person p1 = {
        .name = "John",
        .age = 18,
        .height = 178
    };

    printf("Name: %s, Age: %d, Height: %d\n", p1.name, p1.age, p1.height);

    return 0;
}
