#ifndef USB_HOSTING_H
#define USB_HOSTING_H

void usb_hosting_init();
void tuh_hid_report_received_cb(
    uint8_t dev_addr,
    uint8_t instance,
    uint8_t const *report,
    uint16_t len
);

#endif