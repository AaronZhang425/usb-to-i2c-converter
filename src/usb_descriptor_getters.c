#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_descriptor_getters.h"

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
    tusb_desc_device_t **dev_desc,
    void (*callback)(tuh_xfer_t *xfer)
) {
    if (!dev_desc) {
        return -1;

    }

    if (!callback) {
        callback = default_dev_desc_cb;

    }

    *dev_desc = malloc(sizeof(tusb_desc_device_t));
    
    if (!(*dev_desc)) {
        return -1;        

    }

    bool status = tuh_descriptor_get_device(
        dev_addr,
        dev_desc,
        USB_DEV_DESC_LENGTH,
        callback,
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

int get_config_desc_async(
    uint8_t dev_addr,
    tusb_desc_configuration_t **config_desc,
    void (*callback)(tusb_desc_configuration_t *xfer)
) {
    return 0;

}

int get_config_desc_sync(
    uint8_t dev_addr,
    tusb_desc_configuration_t **config_desc
) {
    return 0;

}

/******************************************

INTERFACE DESCRIPTOR FUNCTIONS

******************************************/

void destroy_interface_desc(tusb_desc_interface_t *interface_desc) {
    free(interface_desc);

}

static void default_interface_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get interface descriptor");

    }

}

int get_interface_desc_async(
    uint8_t dev_addr,
    tusb_desc_interface_t **interface_desc,
    void (*callback)(tuh_xfer_t *xfer)
) {
    return 0;

}

int get_interface_desc_sync() {
    return 0;

}

/******************************************

ENDPOINT DESCRIPTOR FUNCTIONS

******************************************/

void destroy_endpoint_desc(tusb_desc_endpoint_t *endpoint_desc) {
    free(endpoint_desc);

}

static void default_endpoint_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get endpoint descriptor");

    }

}

int get_endpoint_desc_async(
    uint8_t dev_addr,
    tusb_desc_endpoint_t **endpoint_desc,
    void (*callback)(tuh_xfer_t *xfer)
) {
    return 0;

}

int get_endpoint_desc_sync(
    uint8_t dev_addr,
    tusb_desc_endpoint_t **endpoint_desc
) {
    return 0;

}