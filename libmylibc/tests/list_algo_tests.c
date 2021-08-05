#include <assert.h>
#include <string.h>

#include "minunit.h"
#include "list.h"

#define NUM_VALUES 5

char* values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

List* create_words()
{
    int i = 0;
    List* words = list_create();

    for(i=0; i<NUM_VALUES; i++) {
        list_push(words, values[i]);
    }

    return words;
}

int is_sorted(List* words)
{
    LIST_FOREACH(words, first, next, cur) {
        if (cur->next && strcmp(cur->value, cur->next->value) > 0) {
            debug("%s %s", (char*)cur->value, (char*)cur->next->value);
            return 0;
        }
    }

    return 1;
}

void print_list(char* flag, List* l)
{
    debug("%s", flag);

    LIST_FOREACH(l,first,next,cur) {
        debug("%s", (char*)cur->value);
    }
}

int     count_list(List* list)
{
    int len = 0;

    ListNode* node = NULL;
    for (node = list->first; node != NULL; node = node->next) {
        len ++;
    }

    return len;
}

char* test_bubble_sort()
{
    List* words = create_words();

    int rc = list_bubble_sort(words, (LIST_CMP_FUNC)strcmp);
    mu_assert(rc == 0, "Bubble sort failed.");
    mu_assert(is_sorted(words), "Words are not sorted after bubble sort.");
    mu_assert(NUM_VALUES == count_list(words),"After sorted, words count should equal to before.");

    rc = list_bubble_sort(words, (LIST_CMP_FUNC)strcmp);
    mu_assert(rc == 0, "Bubble sort of already sorted failed.");
    mu_assert(is_sorted(words), "Words should be sort if already bubble sorted.");

    list_destroy(words);

    words = list_create();
    rc = list_bubble_sort(words, (LIST_CMP_FUNC)strcmp);
    mu_assert(rc == 0, "Bubble sort failed on empty list.");
    mu_assert(is_sorted(words), "Words should be sorted if empty.");

    list_destroy(words);

    return NULL;
}

char* test_merge_sort()
{
    List* words = create_words();

    List* res = list_merge_sort(words, (LIST_CMP_FUNC)strcmp);
    mu_assert(res != NULL, "merge sort failed.");
    mu_assert(is_sorted(res), "Words are not sorted after merge sort.");

    List* res2 = list_merge_sort(res, (LIST_CMP_FUNC)strcmp);
    mu_assert(res2 != NULL, "merge sort failed on sorted list");
    mu_assert(is_sorted(res2), "Should still be sorted after merge sort.");
    
    list_destroy(res2);
    list_destroy(res);
    list_destroy(words);

    return NULL;
}

char* all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);
