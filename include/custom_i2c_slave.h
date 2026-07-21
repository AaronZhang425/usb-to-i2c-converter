#ifndef CUSTOM_I2C_SLAVE_H
#define CUSTOM_I2C_SLAVE_H

typedef struct {
    uint8_t buffer[256];
    uint8_t buffer_idx;
    uint8_t device_addr;
} i2c_slave_stats;

extern i2c_slave_stats i2c_slave_data;

void i2c_slave_auto_init(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
);

#endif