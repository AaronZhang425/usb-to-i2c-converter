#ifndef DEQUE_H
#define DEQUE_H

#define DEQUE_SIZE_LIMIT 128

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

int add_to_head_cpy_deque(
    struct deque *list,
    void *data_to_cpy,
    size_t data_size
);

int add_to_head_no_cpy_deque(struct deque *list, void *data);

void *poll_head_deque(struct deque *list);

int add_to_tail_cpy_deque(
    struct deque *list,
    void *data_to_cpy,
    size_t data_size
);

int add_to_tail_no_cpy_deque(struct deque *list, void *data);

void *poll_tail_deque(struct deque *list);

#endif