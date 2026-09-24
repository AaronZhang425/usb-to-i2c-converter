#ifndef CUSTOM_I2C_SLAVE_H
#define CUSTOM_I2C_SLAVE_H

#define DEFAULT_BUFFER_SIZE 2048

void auto_init_i2c_slave(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
);

#endif