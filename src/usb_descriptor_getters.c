#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_descriptor_getters.h"

// Frees a device descriptor
void destroy_dev_desc(tusb_desc_device_t *dev_desc) {
    free(dev_desc);

}

static void get_dev_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get device descriptor");

    }

}

int get_dev_desc_async(uint8_t dev_addr, tusb_desc_device_t **dev_desc) {
    if (!dev_desc) {
        return -1;

    }
    
    *dev_desc = malloc(sizeof(tusb_desc_device_t));
    
    if (!(*dev_desc)) {
        return -1;        

    }

    bool status = tuh_descriptor_get_device(
        dev_addr,
        dev_desc,
        USB_DEV_DESC_LENGTH,
        get_dev_desc_cb,
        0
    );

    if (!status) {
        free(*dev_desc);
        return -1;

    }

    return 0;

}

int get_dev_desc_sync(uint8_t dev_addr, tusb_desc_device_t **dev_desc) {
    if (!dev_desc) {
        return -1;

    }
    
    *dev_desc = calloc(1, sizeof(tusb_desc_device_t));
    
    if (!(*dev_desc)) {
        return -1;

    }

    if (
        tuh_descriptor_get_device_sync(
            dev_addr,
            *dev_desc,
            sizeof(tusb_desc_device_t)
        ) != XFER_RESULT_SUCCESS
    ) {
        return -1;

    }
    
    return 0;

}