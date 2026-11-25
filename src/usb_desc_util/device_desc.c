#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_desc_util/device_desc.h"

/**
 * 
 * WARING: THE WHEN THE ADDRESS OF A POINTER IN THE STACK IS PASSED TO THE 
 * ASNYC FUNCTIONS, IT MAY NOT EXIST WHEN IT IS WRITTEN TO
 * 
 * TODO: FIX UNREACHABLE MEMORY ISSUES
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */


// Frees a device descriptor
void destroy_dev_desc(tusb_desc_device_t *dev_desc) {
    free(dev_desc);

}

static void default_dev_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get device descriptor");

    }

}

int get_dev_desc_async(
    uint8_t dev_addr,
    tusb_desc_device_t **dev_desc_buffer,
    void (*callback)(tuh_xfer_t *xfer)
) {
    if (!dev_desc_buffer) {
        return -1;

    }

    if (!callback) {
        callback = default_dev_desc_cb;

    }

    *dev_desc_buffer = malloc(sizeof(tusb_desc_device_t));
    
    if (!(*dev_desc_buffer)) {
        return -1;        

    }

    bool status = tuh_descriptor_get_device(
        dev_addr,
        *dev_desc_buffer,
        sizeof(tusb_desc_device_t),
        callback,
        0
    );

    if (!status) {
        free(*dev_desc_buffer);
        return -1;

    }

    return 0;

}

int get_dev_desc_sync(uint8_t dev_addr, tusb_desc_device_t **dev_desc_buffer) {
    if (!dev_desc_buffer) {
        return -1;

    }
    
    *dev_desc_buffer = calloc(1, sizeof(tusb_desc_device_t));
    
    if (!(*dev_desc_buffer)) {
        return -1;

    }

    if (
        tuh_descriptor_get_device_sync(
            dev_addr,
            *dev_desc_buffer,
            sizeof(tusb_desc_device_t)
        ) != XFER_RESULT_SUCCESS
    ) {
        return -1;

    }
    
    return 0;

}