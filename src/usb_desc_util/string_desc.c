#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_desc_util/string_desc.h"

void handle_str_header(tuh_xfer_t *xfer) {


    free(xfer->buffer);

}


int get_str_desc_async(
    uint8_t dev_addr,
    uint8_t string_index,
    uint16_t lang_id,
    uint8_t *buffer
) {
    // String header is 2 bytes long
    uint8_t *string_desc_header = calloc(1, STRING_HEADER_SIZE);

    if (!string_desc_header) {
        return -1;

    }

    return tuh_descriptor_get_string(
        dev_addr,
        string_index,
        lang_id,
        string_desc_header,
        STRING_HEADER_SIZE,
        handle_str_header,
        (uintptr_t) buffer
    );

}

int get_str_desc_sync(uint8_t dev_addr) {
    return 0;

}