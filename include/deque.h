#ifndef DEQUE_H
#define DEQUE_H

struct deque_node {
    struct deque_node *prev;
    struct deque_node *next;
    void *data;
};

struct deque {
    struct deque_node *head;
    struct deque_node *tail;
    uint16_t size;
};

struct deque *new_deque(void);
void destroy_deque(struct deque *list);
void destroy_deque_node_full(struct deque_node *list);
int add_to_head_deque(struct deque *list, void *data, size_t data_size);
struct deque_node *poll_head_deque(struct deque *list);
int add_to_tail_deque(struct deque *list, void *data, size_t data_size);
struct deque_node *poll_tail_deque(struct deque *list);

#endif