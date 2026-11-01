#include <stdint.h>
#include <string.h>

#include "event.h"

struct event *new_event_from_raw(
    uint8_t event_data_type,
    uint64_t raw_data,
    size_t event_data_size
) {
    struct event *new_event = calloc(1, sizeof(struct event));

    if (!new_event) {
        return NULL;

    }

    void *event_data = calloc(1, event_data_size);

    if (!event_data) {
        free(new_event);
        return NULL;

    }

    memcpy(event_data, &raw_data, event_data_size);

    new_event->event_data = event_data;
    new_event->event_type = event_data_type;
    new_event->event_data_size = event_data_size;

    return new_event;

}

struct event *new_event_from_ptr(
    uint8_t event_data_type,
    void *data_ptr,
    size_t event_data_size
) {
    struct event *new_event = calloc(1, sizeof(struct event));

    if (!new_event) {
        return NULL;

    }

    void *data_copy = calloc(1, event_data_size);

    if (!data_copy) {
        free(new_event);
        return NULL;

    }

    memcpy(data_copy, data_ptr, event_data_size);

    new_event->event_data = data_copy;
    new_event->event_data_size = event_data_size;
    new_event->event_type = event_data_type;

    return new_event;

}

void destroy_event(struct event *event) {
    free(event->event_data);
    free(event);

}