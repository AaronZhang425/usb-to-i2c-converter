#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "event_queue.h"

struct event_queue *new_queue(void) {
    struct event_queue *new_queue = calloc(1, sizeof(struct event_queue));
    return new_queue;

}

void destroy_queue(struct event_queue *queue) {
    struct event_queue_node *working_node = queue->head;
    
    if (!working_node) {
        free(queue);
        return;

    }
    
    struct event_queue_node *next_node = working_node->next_node;

    free(queue);

    while (next_node) {
        free(working_node->data->event_data);
        free(working_node->data);
        free(working_node);

        working_node = next_node;
        next_node = next_node->next_node;

    }

    free(working_node->data);
    free(working_node);

}

void destroy_queue_node_full(struct event_queue_node *queue) {
    free(queue->data->event_data);
    free(queue->data);
    free(queue);

}

int queue_add_by_event(struct event_queue *queue, struct event event) {
    if (MAX_QUEUE_SIZE >= queue->size) {
        return -1;

    }

    struct event_queue_node *new_node = calloc(1, sizeof(struct event_queue_node));
    
    if (!new_node) {
        return -1;

    }

    // Allocate the new event struct to contain it
    struct event *new_event = calloc(1, sizeof(struct event));
    
    if (!new_event) {
        free(new_node);
        return -1;

    }
    
    *new_event = event;

    // Allocate data to copy the event data
    void *event_payload_copy = calloc(1, event.event_data_size);

    if (!event_payload_copy) {
        free(new_node);
        free(new_event);
        return -1;

    }

    memcpy(event_payload_copy, event.event_data, event.event_data_size);

    new_node->data = new_event;

    // If queue is empty
    if (!queue->tail) {
        queue->tail = new_node;
        queue->head = new_node;
        return 0;
        
    }
    
    queue->tail->next_node = new_node;
    queue->tail = new_node;

    queue->size++;

    return 0;
}

struct event_queue_node *queue_poll(struct event_queue *queue) {
    if (!queue->size) {
        return NULL;

    }

    struct event_queue_node *old_head = queue->head;
    queue->head = old_head->next_node;
    
    if (!(queue->head)) {
        queue->tail = NULL;

    }

    // Detach old head
    old_head->next_node = NULL;

    queue->size--;

    return old_head;

}