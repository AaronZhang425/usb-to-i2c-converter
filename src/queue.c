#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

struct queue *new_queue() {
    struct queue *new_queue = calloc(1, sizeof(struct queue));
    return new_queue;

}

void destroy_queue(struct queue *queue) {
    struct queue_node *working_node = queue->head;
    
    if (!working_node) {
        free(queue);
        return;

    }
    
    struct queue_node *next_node = working_node->next_node;

    free(queue);

    while (next_node) {
        free(working_node->data);
        free(working_node);

        working_node = next_node;
        next_node = next_node->next_node;

    }

    free(working_node->data);
    free(working_node);

}

void destroy_queue_node_full(struct queue_node *queue) {
    free(queue->data);
    free(queue);

}

int queue_add(struct queue *queue, void *data, size_t size) {
    if (MAX_QUEUE_SIZE >= queue->size) {
        return;

    }

    struct queue_node *new_node = calloc(1, sizeof(struct queue_node));
    
    if (!new_node) {
        return -1;

    }

    void *data_copy = calloc(1, size);

    if (!data_copy) {
        free(new_node);
        return -1;

    }

    memcpy(data_copy, data, size);

    new_node->data = data_copy;

    queue->size++;

    // If queue is empty
    if (!(queue->tail)) {
        queue->tail = new_node;
        queue->head = new_node;
        return 0;

    }

    queue->tail->next_node = new_node;
    queue->tail = new_node;

    return 0;
}

struct queue_node *queue_poll(struct queue *queue) {
    if (!queue->size) {
        return NULL;

    }

    struct queue_node *old_head = queue->head;
    queue->head = old_head->next_node;
    
    if (!(queue->head)) {
        queue->tail = NULL;

    }

    // Detach old head
    old_head->next_node = NULL;

    queue->size--;

    return old_head;

}