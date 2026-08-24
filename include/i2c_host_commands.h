// Represents different commands the host can send to the I2C slave
// All commands should be representable by a single byte

#ifndef I2C_DEV_COMMANDS_H
#define I2C_DEV_COMMANDS_H

// Arbitraily chosen. Will find better solution later.
#define DEVICE_STATE_SIZE 64 

#define NEW_I2C_HOST_SIG 0
#define GET_MAX_USB_DEV_SIG 1
#define UPDATE_DEVICE_STATES_SIG 2
#define POLL_DEIVCES_SIG 3

#endif