#include <stdlib.h>
#include "list.h"
#include "dbg.h"

List*   list_create()
{
    return calloc(1, sizeof(List));
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

static void _sort_merge_to(List* merged, List* left, List* right, LIST_CMP_FUNC cmp_func)
{
    ListNode* left_cur_node = left->first;
    ListNode* right_cur_node = right->first;

    while (left_cur_node != NULL || right_cur_node != NULL) {
        if (left_cur_node != NULL && right_cur_node != NULL) {
            if (cmp_func(left_cur_node->value, right_cur_node->value) > 0) {
                list_push(merged, right_cur_node->value);
                right_cur_node = right_cur_node->next;
            } else {
                list_push(merged, left_cur_node->value);
                left_cur_node = left_cur_node->next;
            }
        } else if (left_cur_node != NULL) {
            list_push(merged, left_cur_node->value);
            left_cur_node = left_cur_node->next;
        } else {
            list_push(merged, right_cur_node->value);
            right_cur_node = right_cur_node->next;
        }
    }
}

List*   list_merge_sort(List* list, LIST_CMP_FUNC cmp_func)
{
    check(list != NULL, "List can not be null");
    check(cmp_func != NULL ,"compare function can not be null");

    int group_len = 1;
    int list_len = LIST_COUNT(list);
    int i = 0;

    List* merged_list = NULL;
    List* tmp_list = NULL;
    List* left_list = NULL;
    List* right_list = NULL;
    void* v = NULL;

    tmp_list = list_create();

    LIST_FOREACH(list, first, next, cur) {
        list_push(tmp_list, cur->value);
    }

    while (group_len < list_len) {
        merged_list = list_create();

        while (LIST_COUNT(tmp_list) > 0) {
            left_list = list_create();
            right_list = list_create();

            for (i=0;i<group_len;i++) {
                v = list_shift(tmp_list);
                if (v == NULL)
                    break;

                list_push(left_list, v);
            }
            for (i=0;i<group_len;i++) {
                v = list_shift(tmp_list);
                if (v == NULL)
                    break;

                list_push(right_list, v);
            }

            _sort_merge_to(merged_list, left_list, right_list, cmp_func);

            list_destroy(left_list);
            list_destroy(right_list);
            left_list = right_list = NULL;

        }

        list_destroy(tmp_list);
        tmp_list = merged_list;

        group_len = group_len << 1;
    }
    return tmp_list;

error:
    return NULL;
}
