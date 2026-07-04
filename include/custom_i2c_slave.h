#ifndef CUSTOM_I2C_SLAVE_H
#define CUSTOM_I2C_SLAVE_H

typedef struct {
    uint8_t mem[256];
    uint8_t mem_addr;
} slave_memory;

extern slave_memory data;

void custom_i2c_slave_init(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
);

#endif