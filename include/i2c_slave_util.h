#ifndef CUSTOM_I2C_SLAVE_H
#define CUSTOM_I2C_SLAVE_H

typedef struct {
    uint8_t buffer[256];
    uint8_t buffer_idx;
    uint8_t device_addr;
} i2c_slave_buffer_stats;

extern i2c_slave_buffer_stats i2c_slave_data;

void auto_init_i2c_slave(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
);

#endif