#ifndef USB_DESCIRPTOR_GETTERS_H
#define USB_DESCRIPTOR_GETTERS_H

#define USB_DEV_DESC_LENGTH 18
#define USB_CONFIG_DESC_LENGTH 9
#define USB_INTERFACE_DESC_LENGTH 9
#define UBS_ENDPOINT_DESC_LENGTH 7

#define USB_DEV_DESC_TYPE 0x01
#define USB_CONFIG_DESC_TYPE 0x02
#define USB_STRING_DESC_TYPE 0x03
#define USB_INTERFACE_DESC_TYPE 0x04
#define USB_ENDPOINT_DESC_TYPE 0x05

// #define CONFIG_BUFFER_SIZE

/******************************************

DEVICE DESCRIPTOR FUNCTIONS

******************************************/

void destroy_dev_desc(tusb_desc_device_t *descriptor);
int get_dev_desc_async(
    uint8_t dev_addr,
    tusb_desc_device_t **dev_desc,
    void (*callback)(tuh_xfer_t *xfer)
);
int get_dev_desc_sync(uint8_t dev_addr, tusb_desc_device_t **dev_desc);

/******************************************

CONFIGURATION DESCRIPTOR FUNCTIONS

******************************************/


#endif