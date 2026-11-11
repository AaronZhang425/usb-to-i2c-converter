// Represents different commands the host can send to the I2C slave
// All commands should be representable by a single byte

#ifndef I2C_DEV_COMMANDS_H
#define I2C_DEV_COMMANDS_H

// HCMD is for Host Command for lack of better prefix

#define HCMD_NEW_I2C_HOST 0
#define HCMD_GET_USB_DEV_DESC 1
#define HCMD_GET_USB_CONFIG_DESC 2
#define HCMD_GET_MAX_USB_DEV 3
#define HCMD_POLL_EVENTS 4

#endif