#ifndef CUSTOM_I2C_MASTER_H
#define CUSTOM_I2C_MASTER_H

void i2c_master_auto_init(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
);

#endif