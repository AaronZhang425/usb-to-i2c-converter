#include <stdlib.h>
#include <string.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "event_defs.h"
#include "usb_hosting.h"
#include "event_queue.h"
#include "tusb_config.h"

uint8_t device_addresses[CFG_TUH_DEVICE_MAX];
struct event_queue *event_queue;


void usb_hosting_init() {
    tusb_rhport_init_t host_init = {
        .role = TUSB_ROLE_HOST,
        .speed = TUSB_SPEED_AUTO
    };
    
    tusb_init(BOARD_TUH_RHPORT, &host_init);

    event_queue = new_queue();

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

// struct serialized_data *serialize_event(struct event *event) {
//     struct serialized_data *serialized = calloc(
//         1,
//         sizeof(struct serialized_data)
//     );

//     if (!serialized) {
//         printf("Error serializing event");
//         return NULL;

//     }

// }

// void destory_serizlized_event(struct serialized_data *serialized_event) {
//     free(serialized_event->data);
//     free(serialized_event);

// }

void new_device_descriptor_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Failed to get descriptors");
        return;
        
    }

    struct event event = {
        .event_data_size = sizeof(tuh_xfer_t),
        .event_data = xfer,
        .event_type = NEW_USB_DESCRIPTOR
    };

    queue_add_by_event(event_queue, event);

}

void remove_device_descriptor_cb(tuh_xfer_t *xfer) {
    if (xfer->result != XFER_RESULT_SUCCESS) {
        printf("Failled to get desciptors");
        return;

    }


}


// GENERAL USB CALLBAKCS

void tuh_mount_cb(uint8_t dev_addr) {
    tusb_desc_device_t device_descriptor;

    bool status = tuh_descriptor_get_device(
        dev_addr,
        &device_descriptor,
        USB_DESCRIPTOR_LENGTH,
        new_device_descriptor_cb,
        0
    );

    if (!status) {
        printf("Cannot get the device descriptor");

    }

    device_addresses[dev_addr - 1] = dev_addr;

}

void tuh_unmount_cb(uint8_t dev_addr) {
    device_addresses[dev_addr - 1] = 0;

    

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

