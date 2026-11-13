#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_descriptor_util.h"

struct config_request_description {

};

/******************************************

DEVICE DESCRIPTOR FUNCTIONS

******************************************/

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
        USB_DEV_DESC_LENGTH,
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

/******************************************

CONFIGURATION DESCRIPTOR FUNCTIONS

******************************************/

void destroy_config_desc(tusb_desc_configuration_t *config_desc) {
    free(config_desc);

}

static void default_config_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get configuration descriptor");

    }
    

}

int get_config_desc_header_async(
    uint8_t dev_addr,
    tusb_desc_configuration_t **config_desc_header_buffer,
    uint8_t config_index,
    void (*callback)(tuh_xfer_t *xfer)
) {

    if (!config_desc_header_buffer) {
        return -1;

    }

    if (!callback) {
        callback = default_dev_desc_cb;

    }

    *config_desc_header_buffer = malloc(sizeof(tusb_desc_configuration_t));
    
    if (!(*config_desc_header_buffer)) {
        return -1;        

    }

    bool status = tuh_descriptor_get_configuration(
        dev_addr,
        config_index,
        *config_desc_header_buffer,
        sizeof(tusb_desc_configuration_t),
        callback,
        0
    );

    if (!status) {
        free(*config_desc_header_buffer);
        return -1;

    }    

    return 0;

}

static void get_full_config_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get configuration descriptor");

    }
    
    

}

int get_full_config_desc_hierarchy_block_async(
    uint8_t dev_addr,
    uint8_t **config_buffer,
    uint16_t buffer_size,
    uint8_t config_index,
    void (*callback)(tuh_xfer_t xfer)
) {
   
    tusb_desc_configuration_t *config_desc_header = calloc(
        1,
        sizeof(tusb_desc_configuration_t)
    );

    if (!config_desc_header) {
        return -1;

    }

    bool status = tuh_descriptor_get_configuration(
        dev_addr,
        config_index,
        config_desc_header,
        sizeof(tusb_desc_configuration_t),
        get_full_config_desc_cb,
        config_buffer
    );

    return 0;

}

int get_config_desc_header_sync(
    uint8_t dev_addr,
    tusb_desc_configuration_t **config_desc_buffer,
    uint8_t index
) {

    if (!config_desc_buffer) {
        return -1;

    }
    
    *config_desc_buffer = calloc(1, sizeof(tusb_desc_configuration_t));
    
    if (!(*config_desc_buffer)) {
        return -1;

    }

    if (
        tuh_descriptor_get_configuration_sync(
            dev_addr,
            index,
            *config_desc_buffer,
            sizeof(tusb_desc_configuration_t)
        ) != XFER_RESULT_SUCCESS
    ) {
        return -1;

    }

    return 0;

}

int get_config_desc_hierarchy_block_sync() {
    return 0;

}