#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "deque.h"

struct deque *new_deque(void) {
    return calloc(1, sizeof(struct deque));

}

void destroy_deque(struct deque *list) {
    if (!list) {
        return;

    }

    if (!list->head) {
        free(list);
        return;

    }

    struct deque_node *current = list->head;
    struct deque_node *prev = NULL;

    while (current) {
        prev = current;
        current = current->next;

        free(prev);
        free(prev->data);

    }

    free(list);

}

// void destroy_deque_node_full(struct deque_node *node) {
//     if (!node) {
//         return;

//     }

//     free(node->data);
//     free(node);

// }

// void destory_just_deque_node(struct deque_node *node) {
//     if (!node) {
//         return;

//     }

//     free(node);

// }

int add_to_head_deque(struct deque *list, void *data, size_t data_size) {
    if (!list) {
        return -1;

    }

    struct deque_node *new_node = calloc(1, sizeof(struct deque_node));

    if (!new_node) {
        return -1;

    }

    void *data_copy = calloc(1, data_size);

    if (!data_copy) {
        free(new_node);
        return -1;

    }

    memcpy(data_copy, data, data_size);

    new_node->data = data_copy;

    new_node->prev = NULL;
    new_node->next = list->head;

    if (list->head) {
        list->head->prev = new_node;

    } else {
        list->tail = new_node;

    }
    
    list->head = new_node;

    list->size++;

    return 0;

}

void *poll_head_deque(struct deque *list) {
    if (!list) {
        return NULL;

    }
    
    // Guard for if deqeue is empty
    if (!list->head) {
        return NULL;

    }

    struct deque_node *old_head = list->head;
    list->head = old_head->next;
    
    // If deqeue is now empty    
    if (!list->head) {
        list->tail = NULL;
        
    }
    
    void *data = old_head->data;

    free(old_head);

    list->size--;

    return data;

}

int add_to_tail_deque(struct deque *list, void *data, size_t data_size) {
    if (!list) {
        return -1;

    }

    struct deque_node *new_node = calloc(1, sizeof(struct deque_node));

    if (!new_node) {
        return -1;

    }

    void *data_copy = calloc(1, data_size);

    if (!data_copy) {
        free(new_node);
        return -1;

    }

    memcpy(data_copy, data, data_size);

    new_node->data = data_copy;
    
    new_node->next = NULL;
    new_node->prev = list->tail;

    if (list->tail) {
        list->tail->next = new_node;

    } else {
        list->head = new_node;

    }

    list->tail = new_node;

    list->size++;

    return 0;

}

void *poll_tail_deque(struct deque *list) {
    if (!list) {
        return NULL;

    }
    
    if (!list->tail) {
        return NULL;

    }

    struct deque_node *old_tail = list->tail;
    
    list->tail = old_tail->prev;

    if (!list->tail) {
        list->head = NULL;

    }

    void *data = old_tail->data;

    free(old_tail);

    // Update the size of the list
    list->size--;

    return data;

}