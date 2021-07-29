#include <stdlib.h>
#include "list.h"
#include "dbg.h"

List*   list_create()
{
    return calloc(1, sizeof(List));
}

int     list_length(List* list)
{
    int len = 0;

    ListNode* node = NULL;
    for (node = list->first; node != NULL; node = node->next) {
        len ++;
    }

    return len;
}

void    list_destroy(List* list)
{
    LIST_FOREACH(list, first, next, cur){
        if(cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void    list_clear(List* list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void    list_clear_destroy(List *list)
{
    list_clear(list);
    list_destroy(list);
}

void    list_push(List* list, void* value)
{
    ListNode* node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void*   list_pop(List* list)
{
    ListNode* node = list->last;
    return node != NULL? list_remove(list, node) : NULL; 
}

void    list_unshift(List* list, void* value)
{
    ListNode* node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void*   list_shift(List* list)
{
    ListNode* node = list->first;
    return node != NULL? list_remove(list, node) : NULL;
}

void*   list_remove(List* list, ListNode* node)
{
    void* result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can not be NULL");

    if (node == list->first && node == list->last ) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, got first is NULL");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalide list, got last is NULL");
        list->last->next = NULL;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    list->count --;
    result = node->value;
    free(node);

error:
    return result;
}

int     list_bubble_sort(List* list, LIST_CMP_FUNC cmp_func)
{
    check(list != NULL, "List can not be null");
    check(cmp_func != NULL ,"compare function can not be null");

    ListNode* current_node =  list->first;
    ListNode* next_node = NULL;
    void* v = NULL;

    while (current_node != NULL) {
        for (next_node = current_node->next; next_node != NULL; next_node = next_node->next) {
            if (cmp_func(current_node->value, next_node->value) > 0) {
                // current_node->next = next_node->next;
                // if (current_node->next != NULL) {
                //     current_node->next->prev = current_node;
                // } else {
                //     list->last = current_node;
                // }
                // next_node->next = current_node;

                // next_node->prev = current_node->prev;
                // if (next_node->prev != NULL) {
                //     next_node->prev->next = next_node;
                // } else {
                //     list->first = next_node;
                // }
                // current_node->prev = next_node;
                v = current_node->value;
                current_node->value = next_node->value;
                next_node->value = v;
            }
        }
        current_node = current_node->next;
    }

    return 0;

error:
    return 1;
}

List*   list_merge_sort(List* list, LIST_CMP_FUNC cmp_func)
{
    check(list != NULL, "List can not be null");
    check(cmp_func != NULL ,"compare function can not be null");

    return NULL;

error:
    return NULL;
}
