#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 100

struct queue_node{
    void *data;
    struct queue_node *next_node;
};

struct queue {
    struct queue_node *head;
    struct queue_node *tail;  
    uint16_t size;
};

struct queue *new_queue();
void destroy_queue(struct queue *queue);
void destroy_queue_node_full(struct queue_node *queue);
int queue_add(struct queue *queue, void *data, size_t size);
struct queue_node *queue_poll(struct queue *queue);

#endif