#include <assert.h>
#include "minunit.h"
#include "list.h"

static List* list = NULL;
char* test1 = "test1 data";
char* test2 = "test2 data";
char* test3 = "test3 data";

char* test_create()
{
    list = list_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char* test_destroy()
{
    list_clear_destroy(list);

    return NULL;
}

char* test_push_pop()
{
    list_push(list, test1);
    mu_assert(LIST_LAST(list) == test1, "Wrong last value.");

    list_push(list, test2);
    mu_assert(LIST_LAST(list) == test2, "Wrong last value.");
    
    list_push(list, test3);
    mu_assert(LIST_LAST(list) == test3, "Wront last value.");
    mu_assert(LIST_COUNT(list) == 3, "Wrong count on push.");

    char* val = list_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = list_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = list_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(LIST_COUNT(list) == 0, "Wrong count after pop");

    return NULL;
}

char* test_unshift()
{
    list_unshift(list, test1);
    mu_assert(LIST_FIRST(list) == test1, "Wrong first value.");

    list_unshift(list, test2);
    mu_assert(LIST_FIRST(list) == test2, "Wrong first value");

    list_unshift(list, test3);
    mu_assert(LIST_LAST(list) == test1, "Wrong last value");
    mu_assert(LIST_COUNT(list) == 3, "Wrong count on unshift");

    return NULL;
}

char* test_shift()
{
    mu_assert(LIST_COUNT(list) != 0, "Wrong count before shift");

    char* val = list_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = list_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(LIST_COUNT(list) == 0, "Wrong count after shift.");

    return NULL;
}

char* test_remove()
{
    char* val = list_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(LIST_COUNT(list) == 2, "Wrong count after remove");
    mu_assert(LIST_FIRST(list) == test3, "Wrong first after remove");
    mu_assert(LIST_LAST(list) == test1, "Wrong last after remove");

    return NULL;
}

char* all_tests(){
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
