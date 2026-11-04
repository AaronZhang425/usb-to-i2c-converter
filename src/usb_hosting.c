#include <stdlib.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_hosting.h"
#include "tusb_config.h"
#include "event.h"
#include "deque.h"

// tusb_desc_device_t *device_descriptors[CFG_TUH_DEVICE_MAX];
uint8_t device_addresses[CFG_TUH_DEVICE_MAX];
uint8_t usb_devices_connected = 0;

// struct event_queue *event_queue;
struct deque *event_deque;

// TODO: handle new USB devices during runtime

void usb_hosting_init() {
    tusb_rhport_init_t host_init = {
        .role = TUSB_ROLE_HOST,
        .speed = TUSB_SPEED_AUTO
    };
    
    tusb_init(BOARD_TUH_RHPORT, &host_init);

    event_deque = new_deque();

}

static void keyboard_handler(
    uint8_t dev_addr,
    uint8_t instance,
    const hid_keyboard_report_t* report,
    uint16_t len
) {

}

static void mouse_handler(
    uint8_t dev_addr,
    uint8_t instance,
    const hid_mouse_report_t* report,
    uint16_t len    
) {
    struct event *mouse_event = new_event_cpy(USB_MOUSE_EVENT, report, len);

    add_to_tail_no_cpy_deque(event_deque, &mouse_event);

}

// GENERAL USB CALLBAKCS

void tuh_mount_cb(uint8_t dev_addr) {
    // If the device address is 0 for some reason, it is probably not set up
    // correctly by TinyUSB
    if (!dev_addr) {
        return;

    }

    // Map device addresses to an index in the array of USB devices
    // Subtract 1 so that index 0 is also used
    device_addresses[dev_addr - 1] = dev_addr;

    struct event *new_usb_device = new_event_cpy(
        NEW_USB_ADDR,
        &dev_addr,
        1 // The device address is 1 byte long
    );

    // Add the event to the head of the deque to be processed immediately
    add_to_head_no_cpy_deque(event_deque, &new_usb_device);

    // Increment the number of devices connected
    usb_devices_connected++;

}

void tuh_unmount_cb(uint8_t dev_addr) {    
    device_addresses[dev_addr - 1] = 0;

    // Allocate some memory for the event
    struct event *release_addr_event = new_event_cpy(
        USB_ADDR_RELEASE_EVENT,
        &dev_addr,
        1 // Device addresses are a single byte    
    );

    // If a device disconnects, handling the event is not as urgent as when 
    // a device connects. Place the event at the end of the deque
    add_to_tail_no_cpy_deque(event_deque, &release_addr_event);

    usb_devices_connected--;

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

