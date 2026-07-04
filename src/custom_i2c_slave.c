#include <pico/stdlib.h>
#include <pico/i2c_slave.h>

#include "custom_i2c_slave.h"

slave_memory data;

void i2c_slave_handler(i2c_inst_t* i2c, i2c_slave_event_t event) {
    switch (event) {
        case I2C_SLAVE_RECEIVE:
            data.mem[data.mem_addr] = i2c_read_byte_raw(i2c);
            break;
        
        case I2C_SLAVE_REQUEST:
            i2c_write_byte_raw(i2c, data.mem[data.mem_addr]);
            break;

        case I2C_SLAVE_FINISH:
            break;
    }

}

void custom_i2c_slave_init(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
) {

    i2c_init(i2c, baudrate);

    // USE EXTERNAL RESISTORS FOR I2C
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

    // Set pi pico to slave
    i2c_slave_init(i2c, address, &i2c_slave_handler);
}

void stop_led() {
    gpio_put(25, 0);
}