#ifndef QUEUE_H
#define QUEUE_H

#define NEW_USB_DESCRIPTOR 0
#define USB_RELEASE 1
#define USB_MOUSE_EVENT 2

#define MAX_QUEUE_SIZE 100

struct event {
    size_t event_data_size;
    void* event_data;
    uint8_t event_type;
};

struct serialized_data {
    uint8_t* data;
    size_t length;
};

struct event_queue_node {
    struct event *data;
    struct event_queue_node *next_node;
};

struct event_queue {
    struct event_queue_node *head;
    struct event_queue_node *tail;  
    size_t size;
};

struct event_queue *new_queue();
void destroy_queue(struct event_queue *queue);
void destroy_queue_node_full(struct event_queue_node *queue);
int queue_add_by_event(struct event_queue *queue, struct event event);
struct event_queue_node *queue_poll(struct event_queue *queue);

#endif