#include <stdint.h>

#include "event.h"

struct event *new_event_from_raw(
    uint8_t evnet_type,
    uint32_t raw_data,
    size_t event_data_type
) {
    return NULL;

}

struct event *new_event_from_ptr(
    uint8_t event_type,
    void *data_ptr,
    size_t event_data_type
) {
    return NULL;

}

void destroy_event(struct event *event) {


}