#define NEW_USB_ADDR 0
#define USB_ADDR_RELEASE_EVENT 1
#define MAX_USB_DEVICES_EVENT 2
#define USB_MOUSE_EVENT 3

struct usb_event {
    size_t event_data_size;
    void* event_data;
    uint8_t event_type;
};

struct usb_event *new_event_cpy(
    const uint8_t event_data_type,
    const void *data_ptr,
    const size_t event_data_size
);

void destroy_usb_event(struct usb_event *event);