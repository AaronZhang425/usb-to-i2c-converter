#include <pico/stdlib.h>
#include <tusb.h>
#include "usb_hosting.h"

void usb_hosting_init() {
    tusb_rhport_init_t host_init = {
        .role = TUSB_ROLE_HOST,
        .speed = TUSB_SPEED_AUTO
    };
    
    tusb_init(BOARD_TUH_RHPORT, &host_init);

}

void tuh_hid_mount_cb(
    uint8_t dev_addr,
    uint8_t instance,
    uint8_t const* desc_report,
    uint16_t desc_len
) {

}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {

}

void tuh_hid_report_received_cb(
    uint8_t dev_addr,
    uint8_t instance,
    uint8_t const *report,
    uint16_t len
) {

}