#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "usb_event.h"

struct usb_event *new_event_cpy(
    const uint8_t event_data_type,
    const void *data_ptr,
    const size_t event_data_size
) {
    struct usb_event *new_event = calloc(1, sizeof(struct usb_event));

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

void destroy_usb_event(struct usb_event *event) {
    free(event->event_data);
    free(event);

}