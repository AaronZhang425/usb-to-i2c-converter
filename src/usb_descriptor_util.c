#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_descriptor_util.h"

// Used to pack data needed by callback function when getting the full
// configuration descriptor block (configuration, interface, endpoint, etc.)
struct buf_config_tuple {
    uint8_t *buff_ptr;
    uint8_t get_config_index;
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

// Only used if player does not provide a callback function of their own
static void default_config_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get configuration descriptor");

    }
    

}

int get_config_desc_header_async(
    uint8_t dev_addr,
    tusb_desc_configuration_t **config_desc_header_buffer,
    uint8_t get_config_index,
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
        get_config_index,
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

static void get_full_config_desc_block_cb_handle_block(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get full configuration descriptor block");

    }

}

static void get_full_config_desc_block_from_header_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get configuration descriptor");

    }
    
    // The value in the byte before is the get config value, assigned in
    // get_full_config_desc_block_async(...)
    uint8_t get_config_index = xfer->buffer[-1]; 
    
    tusb_desc_configuration_t *config_desc_header = (
        (tusb_desc_configuration_t *) xfer->buffer
    );
    
    uint8_t **full_config_buffer = (uint8_t **) (xfer->user_data);
    *full_config_buffer = calloc(1, config_desc_header->wTotalLength);

    // Do something
    bool status = tuh_descriptor_get_configuration(
        xfer->daddr,
        get_config_index,
        *full_config_buffer,
        sizeof(tusb_desc_configuration_t),
        get_full_config_desc_block_from_header_cb,
        0
    );    

    // The buffer defined in get_full_config_desc_block_async(...) points to
    // get_config_index, not the actual descriptor buffer
    free((xfer->buffer) - 1);
    

}

int get_full_config_desc_block_async(
    uint8_t dev_addr,
    uint8_t **config_buffer,
    uint8_t get_config_index,
    void (*callback)(tuh_xfer_t xfer)
) {

    // Contains the descriptor header and the index of the GET_CONFIGURATION
    // index (different from the SET_CONFIGURATION index)
    uint8_t *config_desc_header_buf_index_tuple = calloc(
        1,
        sizeof(tusb_desc_configuration_t) + 1
    );

    if (!config_desc_header_buf_index_tuple) {
        return -1;
        
    }

    config_desc_header_buf_index_tuple[0] = get_config_index;

    bool status = tuh_descriptor_get_configuration(
        dev_addr,
        get_config_index,
        config_desc_header_buf_index_tuple + 1,
        sizeof(tusb_desc_configuration_t),
        get_full_config_desc_block_from_header_cb,
        (uintptr_t) config_buffer
    );

    return 0;

}

int get_config_desc_header_sync(
    uint8_t dev_addr,
    tusb_desc_configuration_t **config_desc_buffer,
    uint8_t get_config_index
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
            get_config_index,
            *config_desc_buffer,
            sizeof(tusb_desc_configuration_t)
        ) != XFER_RESULT_SUCCESS
    ) {
        return -1;

    }

    return 0;

}

/**
 * Given an address to a pointer, change the pointer to reference an allocation 
 * of the full configuration descriptor block from the requested device address
 * and configuration index
 * 
 * @param[in] dev_addr The address of the device to request the configuration 
 * descriptor block from
 * @param[out] config_block_buffer
 * @param[in] get_config_index
 * @return Return -1 if fail and 0 for success
 * 
 */
int get_config_desc_block_sync(
    uint8_t dev_addr,
    uint8_t **config_block_buffer,
    uint8_t get_config_index
) {
    // If the provided pointer is not valid, stop
    if (!config_block_buffer) {
        return -1;

    }

    tusb_desc_configuration_t config_header;

    // Get the configuration header. If it does not work, stop. The 
    // configuration descriptor header is just the configuration descriptor,
    // the first 9 bytes of the entire configuration descriptor block
    if (
        tuh_descriptor_get_configuration_sync(
            dev_addr,
            get_config_index,
            &config_header,
            sizeof(tusb_desc_configuration_t)
        ) != XFER_RESULT_SUCCESS
    ) {
        return -1;

    }

    // Allocate the size of the entire configuration descriptor block after
    // determining the total size. Set the pointer the user wants to change
    // to the allocation, not the pointer to pointer
    *config_block_buffer = calloc(1, config_header.wTotalLength);

    // If the allocation fails, stop
    if (!(*config_block_buffer)) {
        return -1;

    }

    // Get the entire configuration descriptor block. If it is unsuccessful,
    // return -1
    if (
        tuh_descriptor_get_configuration_sync(
            dev_addr,
            get_config_index,
            *config_block_buffer,
            config_header.wTotalLength
        ) != XFER_RESULT_SUCCESS
    ) {
        return -1;

    }

    return 0;

}

/******************************************

STRING DESCRIPTOR FUNCTIONS

******************************************/

int get_str_desc_async(uint8_t dev_addr) {
    return 0;

}

int get_str_desc_async(uint8_t dev_addr) {
    return 0;

}