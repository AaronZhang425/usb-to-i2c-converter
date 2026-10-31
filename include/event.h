#define NEW_USB_ADDR 0
#define USB_ADDR_RELEASE_EVENT 1
#define MAX_USB_DEVICES_EVENT 2
#define USB_MOUSE_EVENT 3

struct event {
    size_t event_data_size;
    void* event_data;
    uint8_t event_type;
};


struct event *new_event_from_raw(
    uint8_t evnet_type,
    uint32_t raw_data,
    size_t event_data_type
);

struct event *new_event_from_ptr(
    uint8_t event_type,
    void *data_ptr,
    size_t event_data_type
);

void destroy_event(struct event *event);