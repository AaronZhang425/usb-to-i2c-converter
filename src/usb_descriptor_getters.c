#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_descriptor_getters.h"

// Frees a device descriptor
void destroy_device_descriptor(tusb_desc_device_t *descriptor) {
    free(descriptor);

}

static void get_device_descriptor_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get device descriptor");

    }

}

int get_device_descriptor(uint8_t device_addr, tusb_desc_device_t **device_descriptor) {
    if (!device_descriptor) {
        return -1;

    }
    
    *device_descriptor = malloc(sizeof(tusb_desc_device_t));
    
    if (!(*device_descriptor)) {
        return -1;        

    }

    bool status = tuh_descriptor_get_device(
        device_addr,
        device_descriptor,
        USB_DEV_DESC_LENGTH,
        get_device_descriptor_cb,
        0
    );

    if (!status) {
        free(*device_descriptor);
        return -1;

    }

    return 0;

}