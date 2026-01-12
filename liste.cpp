#include <iostream>
#include <cstdlib>
using namespace std;
#define NAME_MAX_LEN 255
#define STR(v) #v
#define PRINT_OPTION(v) cout << "  '" << v << "' = " << STR(v) << endl

typedef struct sl_list_node
{
    struct sl_list_node *next;
    int value;
} sl_list_node_t;

typedef struct sl_list
{
    sl_list_node_t *head;
    sl_list_node_t *tail;
    unsigned int len;
} sl_list_t;

sl_list_node_t *list_node_new(int value)
{
    sl_list_node_t *node = (sl_list_node_t *)malloc(sizeof(sl_list_node_t));
    if (!node)
        return NULL;

    node->value = value;
    node->next = NULL;
    return node;
}

sl_list_t *list_new(void)
{
    sl_list_t *list = (sl_list_t *)malloc(sizeof(sl_list_t));
    if (!list)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

sl_list_node_t *list_rpush(sl_list_t *self, sl_list_node_t *node)
{
    if (!self || !node)
        return NULL;

    node->next = self->head;

    self->head = node;

    if (self->tail == NULL)
    {
        self->tail = node;
    }

    self->len++;
    return node;
}

sl_list_node_t *list_lpush(sl_list_t *self, sl_list_node_t *node)
{
    if (!self || !node)
        return NULL;

    node->next = NULL;

    if (self->len == 0)
    {
        self->head = node;
        self->tail = node;
    }
    else
    {
        self->tail->next = node;
        self->tail = node;
    }

    self->len++;
    return node;
}

sl_list_node_t *list_find(sl_list_t *self, int value)
{
    if (!self)
        return NULL;

    sl_list_node_t *curr = self->head;
    while (curr != NULL)
    {
        if (curr->value == value)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

sl_list_node_t *list_at(sl_list_t *self, int index)
{
    if (!self || index < 0 || index >= self->len)
        return NULL;

    sl_list_node_t *curr = self->head;
    int count = 0;
    while (curr != NULL)
    {
        if (count == index)
        {
            return curr;
        }
        count++;
        curr = curr->next;
    }
    return NULL;
}

sl_list_node_t *list_rpop(sl_list_t *self)
{
    if (!self || self->len == 0)
        return NULL;

    sl_list_node_t *old_head = self->head;

    self->head = self->head->next;

    if (self->head == NULL)
    {
        self->tail = NULL;
    }

    self->len--;

    old_head->next = NULL;
    return old_head;
}

sl_list_node_t *list_lpop(sl_list_t *self)
{
    if (!self || self->len == 0)
        return NULL;

    sl_list_node_t *node_to_remove = self->tail;

    if (self->head == self->tail)
    {
        self->head = NULL;
        self->tail = NULL;
    }
    else
    {
        sl_list_node_t *curr = self->head;
        while (curr->next != self->tail)
        {
            curr = curr->next;
        }
        curr->next = NULL;
        self->tail = curr;
    }

    self->len--;
    return node_to_remove;
}

void list_remove(sl_list_t *self, sl_list_node_t *node)
{
    if (!self || !node || self->len == 0)
        return;

    if (node == self->head)
    {
        sl_list_node_t *popped = list_rpop(self);
        free(popped);
        return;
    }

    sl_list_node_t *prev = self->head;
    while (prev != NULL && prev->next != node)
    {
        prev = prev->next;
    }

    if (prev != NULL)
    {
        if (node == self->tail)
        {
            list_lpop(self);
            free(node);
        }
        else
        {
            prev->next = node->next;
            self->len--;
            free(node);
        }
    }
}

void list_destroy(sl_list_t *self)
{
    if (!self)
        return;

    while (self->len > 0)
    {
        sl_list_node_t *node = list_rpop(self);
        free(node);
    }
    free(self);
}

void print_list(sl_list_t *self)
{
    if (!self)
        return;
    sl_list_node_t *curr = self->head;
    printf("Lista (len %d): ", self->len);
    while (curr != NULL)
    {
        printf("[%d] -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main()
{
    sl_list_t *my_list = list_new();

    list_rpush(my_list, list_node_new(10));
    list_rpush(my_list, list_node_new(20));
    list_lpush(my_list, list_node_new(30));

    print_list(my_list);

    sl_list_node_t *n = list_rpop(my_list);
    printf("Am scos head: %d\n", n->value);
    free(n);
    print_list(my_list);

    n = list_lpop(my_list);
    printf("Am scos tail: %d\n", n->value);
    free(n);
    print_list(my_list);

    list_destroy(my_list);
    return 0;
}
