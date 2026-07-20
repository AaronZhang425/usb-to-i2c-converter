#ifndef TUSB_CONFIG_H
#define TUSB_CONFIG_H

#define CFG_TUH_ENABLED 1
#define CFG_TUSB_RHPORT0_MODE OPT_MODE_HOST
#define BOARD_TUH_RHPORT 0
#define CFG_TUH_HUB 1
#define CFG_TUH_DEVICE_MAX 3 // There are 3 ports on the hub being used

#define CFG_TUH_HID_EP_BUFSIZE 64
#define CFG_TUH_CDC_EP_BUFSIZE 64

#define CFG_TUH_HID (3 * CFG_TUH_DEVICE_MAX)
#define CFG_TUH_CDC (3 * CFG_TUH_DEVICE_MAX)

#endif