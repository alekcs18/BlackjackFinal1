#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//liste dublu inlantuite
typedef struct dl_list_node {
    int value;
    struct dl_list_node *next;
    struct dl_list_node *prev;
} dl_list_node_t;

typedef struct dl_list {
    dl_list_node_t *head;
    dl_list_node_t *tail;
    unsigned int len;
} dl_list_t;

dl_list_node_t *dl_list_node_new(int value) {
    dl_list_node_t *node = (dl_list_node_t *)malloc(sizeof(dl_list_node_t));
    if (!node) return NULL;

    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

dl_list_t *dl_list_new(){
    dl_list_t *list =(dl_list_t *)malloc(sizeof(dl_list_t));
    if (!list) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->len = 0;

    return list;

}

dl_list_node_t *dl_list_rpush(dl_list_t *self, dl_list_node_t *node) {
    if (!self || !node) return NULL;

    if (self->len == 0) {
        self->head = self->tail = node;
    } else {
        node->prev = self->tail;
        self->tail->next = node;
        self->tail = node;
    }

    self->len++;
    return node;
}

dl_list_node_t *dl_list_lpush(dl_list_t *self, dl_list_node_t *node) {
    if (!self || !node) return NULL;

    if (self->len == 0) {
        self->head = self->tail = node;
    } else {
        node->next = self->head;
        self->head->prev = node;
        self->head = node;
    }

    self->len++;
    return node;
}

dl_list_node_t *dl_list_lpop(dl_list_t *self) {
    if (!self || self->len == 0) return NULL;

    dl_list_node_t *node = self->head;

    if (self->len == 1) {
        self->head = self->tail = NULL;
    } else {
        self->head = node->next;
        self->head->prev = NULL;
    }

    node->next = node->prev = NULL;
    self->len--;
    return node;
}

dl_list_node_t *dl_list_rpop(dl_list_t *self) {
    if (!self || self->len == 0) return NULL;

    dl_list_node_t *node = self->tail;

    if (self->len == 1) {
        self->head = self->tail = NULL;
    } else {
        self->tail = node->prev;
        self->tail->next = NULL;
    }

    node->next = node->prev = NULL;
    self->len--;
    return node;
}

void dl_list_destroy(dl_list_t *self) {
    if (!self) return;

    dl_list_node_t *curr = self->head;
    while (curr) {
        dl_list_node_t *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(self);
}

//liste circulare
typedef struct cl_list_node {
    int value;
    struct cl_list_node *next;
    struct cl_list_node *prev;
} cl_list_node_t;

typedef struct cl_list {
    cl_list_node_t *head;
    unsigned int len;
} cl_list_t;

cl_list_node_t *cl_list_node_new(int value) {
    cl_list_node_t *node = (cl_list_node_t *)malloc(sizeof(cl_list_node_t));
    if (!node) return NULL;

    node->value = value;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

cl_list_t *cl_list_new(void) {
    cl_list_t *list = (cl_list_t *)malloc(sizeof(cl_list_t));
    if (!list) return NULL;

    list->head = NULL;
    list->len = 0;

    return list;
}

cl_list_node_t *cl_list_rpush(cl_list_t *self, cl_list_node_t *node) {
    if (!self || !node) return NULL;

    if (self->len == 0) {
        node->next = node;
        node->prev = node;
        self->head = node;
    } else {
        cl_list_node_t *tail = self->head->prev;

        node->prev = tail;
        node->next = self->head;
        tail->next = node;
        self->head->prev = node;
    }

    self->len++;
    return node;
}

cl_list_node_t *cl_list_lpush(cl_list_t *self, cl_list_node_t *node) {
    cl_list_rpush(self, node);
    self->head = node;
    return node;
}

cl_list_node_t *cl_list_lpop(cl_list_t *self) {
    if (!self || self->len == 0) return NULL;

    cl_list_node_t *node = self->head;

    if (self->len == 1) {
        self->head = NULL;
    } else {
        cl_list_node_t *tail = node->prev;
        self->head = node->next;
        self->head->prev = tail;
        tail->next = self->head;
    }

    node->next = node->prev = NULL;
    self->len--;
    return node;
}

void cl_list_destroy(cl_list_t *self) {
    if (!self || self->len == 0) {
        free(self);
        return;
    }

    cl_list_node_t *curr = self->head;
    for (unsigned int i = 0; i < self->len; i++) {
        cl_list_node_t *tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(self);
}

void dl_print_list(dl_list_t *self) {
    if (!self){
      return;  
    } 

    dl_list_node_t *current = self->head;
    while (current) {
        cout<<current->value;
        current = current->next;
    }
    cout<<endl;
}

void dl_list_remove(dl_list_t *self, dl_list_node_t *node) {
    if (!self || !node || self->len == 0)
        return;

    if (node == self->head) {
        dl_list_rpop(self);
        free(node);
        return;
    }

    dl_list_node_t *current = self->head;
    while (current->next && current->next != node)
        current = current->next;

    if (current->next == node) {
        current->next = node->next;
        if (node == self->tail)
            self->tail = current;
        self->len--;
        free(node);
    }
}
void cl_list_remove(cl_list_t *self, cl_list_node_t *node) {
    if (!self || !node || self->len == 0)
        return;

    if (node == self->head) {
        cl_list_lpop(self);
        free(node);
        return;
    }

    cl_list_node_t *current = self->head;
    while (current->next && current->next != node)
        current = current->next;

    if (current->next == node) {
        current->next = node->next;
        if (node == self->head)
            self->head = current;
        self->len--;
        free(node);
    }
}
void cl_print_list(cl_list_t *self) {
    if (!self){
      return;  
    } 

    cl_list_node_t *current = self->head;
    while (current) {
        cout<<current->value;
        current = current->next;
    }
    cout<<endl;
}
typedef struct sl_list_node {
    struct sl_list_node *next;
    int value;
} sl_list_node_t;


typedef struct sl_list {
    sl_list_node_t *head;
    sl_list_node_t *tail;
    unsigned int len;
} sl_list_t;



sl_list_node_t *list_node_new(int value) {
    sl_list_node_t *node = (sl_list_node_t *)malloc(sizeof(sl_list_node_t));
    if (!node){
      return NULL;  
    } 
    node->value = value;
    node->next = NULL;
    return node;
}

sl_list_t *list_new(void) {
    sl_list_t *list = (sl_list_t *)malloc(sizeof(sl_list_t));
    if (!list) {
        return NULL;
    }
    list->head = list->tail = NULL;
    list->len = 0;
    return list;
}


sl_list_node_t *list_rpush(sl_list_t *self, sl_list_node_t *node) {
    if (!self || !node) {
        return NULL;
    }
    if (self->len == 0) {
        self->head = self->tail = node;
    } else {
        self->tail->next = node;
        self->tail = node;
    }
    self->len++;
    return node;
}

sl_list_node_t *list_lpush(sl_list_t *self, sl_list_node_t *node) {
    if (!self || !node) return NULL;

    if (self->len == 0) {
        self->head = self->tail = node;
    } else {
        node->next = self->head;
        self->head = node;
    }
    self->len++;
    return node;
}



sl_list_node_t *list_find(sl_list_t *self, int value) {
    if (!self) return NULL;

    sl_list_node_t *curr = self->head;
    while (curr) {
        if (curr->value == value)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

sl_list_node_t *list_at(sl_list_t *self, int index) {
    if (!self || index < 0 || index >= (int)self->len)
        return NULL;

    sl_list_node_t *curr = self->head;
    for (int i = 0; i < index; i++)
        curr = curr->next;

    return curr;
}


sl_list_node_t *list_rpop(sl_list_t *self) {
    if (!self || self->len == 0)
        return NULL;

    sl_list_node_t *node = self->head;
    self->head = node->next;

    if (self->len == 1)
        self->tail = NULL;

    node->next = NULL;
    self->len--;
    return node;
}


sl_list_node_t *list_lpop(sl_list_t *self) {
    if (!self || self->len == 0)
        return NULL;

    sl_list_node_t *node = self->tail;

    if (self->len == 1) {
        self->head = self->tail = NULL;
    } else {
        sl_list_node_t *curr = self->head;
        while (curr->next != self->tail)
            curr = curr->next;

        curr->next = NULL;
        self->tail = curr;
    }

    self->len--;
    return node;
}



void list_remove(sl_list_t *self, sl_list_node_t *node) {
    if (!self || !node || self->len == 0)
        return;

    if (node == self->head) {
        list_rpop(self);
        free(node);
        return;
    }

    sl_list_node_t *current = self->head;
    while (current->next && current->next != node)
        current = current->next;

    if (current->next == node) {
        current->next = node->next;
        if (node == self->tail)
            self->tail = current;
        self->len--;
        free(node);
    }
}



void list_destroy(sl_list_t *self) {
    if (!self){
        return;
    } 

    sl_list_node_t *current = self->head;
    while (current) {
        sl_list_node_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(self);
}


void print_list(sl_list_t *self) {
    if (!self){
      return;  
    } 

    sl_list_node_t *current = self->head;
    while (current) {
        cout<<current->value;
        current = current->next;
    }
    cout<<endl;
}

int main(){
    sl_list_node_t *node = list_node_new(2); //create new node;
sl_list_t *list = list_new(); // create new empty list
sl_list_node_t * list_rpush(sl_list_t * self, sl_list_node_t * node); // push node to the right (before head), return node address or NULL
sl_list_node_t * list_lpush(sl_list_t * self, sl_list_node_t * node); // push node to the left (after tail), return node address or NULL
sl_list_node_t * list_find (sl_list_t * self, int value); // find node with value, return node address or NULL
sl_list_node_t * list_at   (sl_list_t * self, int index); // return node address at index,, return node address or NULL
sl_list_node_t * list_rpop (sl_list_t * self); // pop node to the right (head node), return node address or NULL
sl_list_node_t * list_lpop (sl_list_t * self); // pop node to the left (tail node), return node address or NULL
void list_remove(sl_list_t * self, sl_list_node_t * node); // remove node from list
void list_destroy(sl_list_t * self); // free all nodes from list
void print_list(sl_list_t * self); // print all nodes in list
dl_list_node_t * dl_list_node_new(int value); 
dl_list_t * dl_list_new(void);
dl_list_node_t * dl_list_rpush(dl_list_t * self, dl_list_node_t * node);
dl_list_node_t * dl_list_lpush(dl_list_t * self, dl_list_node_t * node); 
dl_list_node_t * dl_list_find (dl_list_t * self, int value); 
dl_list_node_t * dl_list_at   (dl_list_t * self, int index);
dl_list_node_t * dl_list_rpop (dl_list_t * self); 
dl_list_node_t * dl_list_lpop (dl_list_t * self); 
void dl_list_remove(dl_list_t * self, dl_list_node_t * node); 
void dl_list_destroy(dl_list_t * self);
void dl_print_list(dl_list_t * self); 

cl_list_node_t * cl_list_node_new(int value); 
cl_list_t * cl_list_new(void);
cl_list_node_t * cl_list_rpush(cl_list_t * self, cl_list_node_t * node);
cl_list_node_t * cl_list_lpush(cl_list_t * self, cl_list_node_t * node); 
cl_list_node_t * cl_list_find (cl_list_t * self, int value); 
cl_list_node_t * cl_list_at   (cl_list_t * self, int index);
cl_list_node_t * cl_list_rpop (cl_list_t * self); 
dl_list_node_t * dl_list_lpop (cl_list_t * self); 
void cl_list_remove(cl_list_t * self, cl_list_node_t * node); 
void cl_list_destroy(cl_list_t * self);
void cl_print_list(cl_list_t * self); 
}
