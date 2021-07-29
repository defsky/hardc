#ifndef __mylibc_list_h__
#define __mylibc_list_h__

typedef struct list_node {
    struct list_node* next;
    struct list_node* prev;
    void* value;
} ListNode;

typedef struct list {
    int count;
    ListNode* first;
    ListNode* last;
} List;

List*   list_create();
int     list_length(List* list);
void    list_destroy(List* list);
void    list_clear(List* list);
void    list_clear_destroy(List *list);

void    list_push(List* list, void* value);
void*   list_pop(List* list);
void    list_unshift(List* list, void* value);
void*   list_shift(List* list);

void*   list_remove(List* list, ListNode* node);

#define LIST_COUNT(A) ((A)->count)
#define LIST_FIRST(A) ((A)->first != NULL? (A)->first->value : NULL)
#define LIST_LAST(A) ((A)->last != NULL? (A)->last->value : NULL)

#define LIST_FOREACH(L, S, M, V) ListNode* _node = NULL;\
    ListNode* V = NULL;\
    for (V = _node = L->S; _node != NULL; V = _node = _node->M)

typedef int (* LIST_CMP_FUNC)(void* a, void* b);

int     list_bubble_sort(List* list, LIST_CMP_FUNC cmp_func);
List*   list_merge_sort(List* list, LIST_CMP_FUNC cmp_func);

#endif
