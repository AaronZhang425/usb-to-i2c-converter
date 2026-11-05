#ifndef USB_HOSTING_H
#define USB_HOSTING_H

extern uint8_t device_addresses[];
extern uint8_t usb_devices_connected; 

extern struct deque *event_deque;

void usb_hosting_init();

#endif