#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_desc_util/device_desc.h"

// Frees a device descriptor
void destroy_dev_desc(tusb_desc_device_t *dev_desc) {
    free(dev_desc);

}

/**
 * @param[in] dev_addr The device address to get the device descriptor from
 * @param[in] callback Must free xfer->user_data at the end
 */
int get_dev_desc_async(
    uint8_t dev_addr,
    void (*callback)(tuh_xfer_t *xfer)
) {

    if (!callback) {
        return -1;

    }

    tusb_desc_device_t *dev_desc_buffer = malloc(sizeof(tusb_desc_device_t));
    
    if (!dev_desc_buffer) {
        return -1;        

    }

    if (
        !tuh_descriptor_get_device(
            dev_addr,
            dev_desc_buffer,
            sizeof(tusb_desc_device_t),
            callback,
            (uintptr_t) dev_desc_buffer
        )
    ) {
        free(dev_desc_buffer);
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