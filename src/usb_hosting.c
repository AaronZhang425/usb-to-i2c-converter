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

void keyboard_handler(
    uint8_t dev_addr,
    uint8_t instance,
    const hid_keyboard_report_t* report,
    uint16_t len
) {

}

void mouse_handler(
    uint8_t dev_addr,
    uint8_t instance,
    const hid_mouse_report_t* report,
    uint16_t len    
) {

}

// HUMAN INTERFACE DEVICES (HID) CALLBACKS

void tuh_hid_mount_cb(
    uint8_t dev_addr,
    uint8_t instance,
    const uint8_t* desc_report,
    uint16_t desc_len
) {
    
    if (!tuh_hid_receive_report(dev_addr, instance)) {
        printf("Cannot recieve report");
    }
}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {

}

void tuh_hid_report_received_cb(
    uint8_t dev_addr,
    uint8_t instance,
    const uint8_t* report,
    uint16_t len
) {

    switch (tuh_hid_interface_protocol(dev_addr, instance)) {
        case HID_ITF_PROTOCOL_KEYBOARD:
            keyboard_handler(
                dev_addr,
                instance,
                (hid_keyboard_report_t const*) report,
                len
            );

            break;
        
        case HID_ITF_PROTOCOL_MOUSE:
            mouse_handler(
                dev_addr,
                instance,
                (hid_mouse_report_t const*) report,
                len
            );

            break;

        case HID_ITF_PROTOCOL_NONE:
            break;

        default:
            break;

    }


    if (!tuh_hid_receive_report(dev_addr, instance)) {
        printf("Cannot recieve report");
    }
}

// COMMUNICATIONS DEVICE CLASS (CDC) CALLBACKS

void tuh_cdc_mount_cb(uint8_t idx) {

}

void tuh_cdc_unmount_cb(uint8_t idx) {

}

void tuh_cdc_rx_cb(uint8_t idx) {

}

void tuh_cdc_tx_complete_cb(uint8_t idx) {

}