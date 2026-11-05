#ifndef USB_DESCIRPTOR_GETTERS_H
#define USB_DESCRIPTOR_GETTERS_H

#define USB_DEV_DESC_LENGTH 18
#define USB_CONFIG_DESC_LENGTH 9
#define USB_INTERFACE_DESC_LENGTH 9
#define UBS_ENDPOINT_DESC_LENGTH 7

void destroy_dev_desc(tusb_desc_device_t *descriptor);
int get_dev_desc_async(uint8_t dev_addr, tusb_desc_device_t **dev_desc);
int get_dev_desc_sync(uint8_t dev_addr, tusb_desc_device_t **dev_desc);

#endif