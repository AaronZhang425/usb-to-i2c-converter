#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/i2c_slave.h"

#define SDA_PIN_1 2
#define SCL_PIN_1 3
#define LED_PIN 25
#define I2C_ADDR 0x17

struct {
    uint8_t mem[256],
    uint8_t mem_addr;
} data;

void i2c_slave_handler(i2c_inst_t* i2c, i2c_slave_event_t event) {
    switch (event) {
        case I2C_SLAVE_REQUEST:
            break;

        case I2C_SLAVE_RECEIVE:
            break;

        case I2C_SLAVE_FINISH:
            break;
    }

}

void init() {
    gpio_init(LED_PIN);
    // Set direction to output
    gpio_set_dir(LED_PIN, 1);
    // Send signal light to turn on
    gpio_put(LED_PIN, 1);
    
    i2c_init(i2c1, 100000);

    // USE EXTERNAL RESISTORS FOR I2C
    gpio_set_function(SDA_PIN_1, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN_1, GPIO_FUNC_I2C);

    // Set pi pico to slave
    i2c_slave_init(i2c1, I2C_ADDR, &i2c_slave_handler);
    
}

int main() {
    init();

    return 0;

}