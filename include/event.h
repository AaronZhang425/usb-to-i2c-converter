#define NEW_USB_ADDR 0
#define USB_ADDR_RELEASE_EVENT 1
#define MAX_USB_DEVICES_EVENT 2
#define USB_MOUSE_EVENT 3

struct event {
    size_t event_data_size;
    void* event_data;
    uint8_t event_type;
};
