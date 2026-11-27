#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_desc_util/config_desc.h"

/**
 * 
 * WARING: THE WHEN THE ADDRESS OF A POINTER IN THE STACK IS PASSED TO THE 
 * ASNYC FUNCTIONS, IT MAY NOT EXIST WHEN IT IS WRITTEN TO
 * 
 * TODO: DOUBLE CHECK FIXES (MAYBE PATCHED)
 * 
 * 
 */



void destroy_config_desc(tusb_desc_configuration_t *config_desc) {
    free(config_desc);

}

// Only used if user does not provide a callback function of their own
static void default_config_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get configuration descriptor");

    }
    

}

/**
 * @param[in] dev_addr The address of the device to get the configuration 
 * descriptor header from
 * @param[in] get_config_index The index of the configuration to get when sending
 * the GET_CONFIGURATION request. This index can be different from the actual
 * index of the configuration
 * @param[in] callback The callback function to handle the reply from the 
 * USB device. Must free xfer->user_data at the end
 */
int get_config_desc_header_async(
    uint8_t dev_addr,
    uint8_t get_config_index,
    void (*callback)(tuh_xfer_t *xfer)
) {
    
    if (!callback) {
        return -1;

    }

    tusb_desc_configuration_t *config_desc_header_buffer = calloc(
        1,
        sizeof(tusb_desc_configuration_t)
    );
    
    if (!config_desc_header_buffer) {
        return -1;        

    }

    // Pass the ptr to allocated data in heap to the user_data variable
    // for easy freeing to avoid complex ptr arithmetic
    if (
        !tuh_descriptor_get_configuration(
            dev_addr,
            get_config_index,
            config_desc_header_buffer,
            sizeof(tusb_desc_configuration_t),
            callback,
            (uintptr_t) config_desc_header_buffer
        )
    ) {
        free(config_desc_header_buffer);
        return -1;

    }

    return 0;

}

static void get_full_config_desc_block_from_header_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Could not get configuration descriptor");

    }
    
    // The value in the byte before is the get config value, assigned in
    // get_full_config_desc_block_async(...)
    uint8_t get_config_index = xfer->buffer[-(sizeof(void *(tuh_xfer_t)) + 1)]; 
    void (*callback)(tuh_xfer_t) = xfer->buffer[-sizeof(void *(tuh_xfer_t))]; 

    uint8_t *full_config_buffer = (
        calloc(1, ((tusb_desc_configuration_t *) xfer->buffer)->wTotalLength)
    ); 

    if (
        !tuh_descriptor_get_configuration(
            xfer->daddr,
            get_config_index,
            full_config_buffer,
            ((tusb_desc_configuration_t *) xfer->buffer)->wTotalLength,
            callback,
            (uintptr_t) full_config_buffer
        )
    ) {
        printf("Could not get full config descriptor");

    }  

    free(xfer->user_data);

}

int get_full_config_desc_block_async(
    uint8_t dev_addr,
    uint8_t get_config_index,
    void (*callback)(tuh_xfer_t xfer)
) {

    // Contains the descriptor header and the index of the GET_CONFIGURATION
    // index (different from the SET_CONFIGURATION index)
    uint8_t *config_desc_buf_and_meta_data = calloc(
        1,
        (
            sizeof(tusb_desc_configuration_t)
            + sizeof(callback)
            + sizeof(get_config_index)
        )
    );

    if (!config_desc_buf_and_meta_data) {
        return -1;
        
    }

    config_desc_buf_and_meta_data[0] = get_config_index;
    config_desc_buf_and_meta_data[1] = callback;

    // The buffer for the actual descriptor header is not at index 0
    if (
        !tuh_descriptor_get_configuration(
            dev_addr,
            get_config_index,
            (
                config_desc_buf_and_meta_data
                + sizeof(get_config_index)
                + sizeof(callback)
            ),
            sizeof(tusb_desc_configuration_t),
            get_full_config_desc_block_from_header_cb,
            (uintptr_t) config_desc_buf_and_meta_data
        )
    ) {
        free(config_desc_buf_and_meta_data);
        return -1;

    }

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