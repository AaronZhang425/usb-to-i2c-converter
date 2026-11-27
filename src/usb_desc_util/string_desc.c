#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_desc_util/string_desc.h"

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


void default_handle_full_string_desc_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Cannot get the full string descriptor");
    }

}

// void handle_str_desc_header_cb(tuh_xfer_t *xfer) {
//     uint8_t dev_addr = xfer->daddr;

//     uint8_t string_index = xfer->buffer[-3];
//     uint16_t lang_id = (uint16_t) *(xfer->buffer - 2);

//     *((uint8_t **) (xfer->user_data)) = calloc(1, xfer->buffer[0]);

//     tuh_descriptor_get_string(
//         dev_addr,
//         string_index,
//         lang_id,
//         xfer->user_data,
//         xfer->buffer[0],
//         default_handle_full_string_desc_cb,
//         0
//     );

//     free(xfer->buffer - 1);

// }


// int get_str_desc_async(
//     uint8_t dev_addr,
//     uint8_t string_index,
//     uint16_t lang_id,
//     uint8_t **buffer
// ) {
//     // String header is 2 bytes long
//     uint8_t *string_desc_header_meta_data_tuple = calloc(
//         1,
//         STRING_HEADER_SIZE + sizeof(string_index) + sizeof(lang_id)
//     );

//     if (!string_desc_header_meta_data_tuple) {
//         return -1;

//     }

//     string_desc_header_meta_data_tuple[0] = string_index;
//     string_desc_header_meta_data_tuple[1] = lang_id;

//     if (
//         !tuh_descriptor_get_string(
//             dev_addr,
//             string_index,
//             lang_id,
//             (
//                 string_desc_header_meta_data_tuple
//                 + sizeof(string_index)
//                 + sizeof(lang_id)
//             ),
//             STRING_HEADER_SIZE,
//             handle_str_desc_header_cb,
//             (uintptr_t) buffer
//         )
//     ) {
//         return -1;

//     }

//     return 0;

// }

int get_str_desc_sync(uint8_t dev_addr) {
    return 0;

}