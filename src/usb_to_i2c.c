#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>

#include "custom_i2c_slave.h"

#define SDA_PIN_1 2
#define SCL_PIN_1 3
#define LED_PIN 25
#define I2C_ADDR 0x17
#define I2C_BUS i2c1
#define BAUDRATE 100000

void init() {
    gpio_init(LED_PIN);
    // Set direction to output
    gpio_set_dir(LED_PIN, 1);
    // Send signal light to turn on
    gpio_put(LED_PIN, 1);
    
}

int main() {
    init();
    custom_i2c_slave_init(I2C_BUS, I2C_ADDR, BAUDRATE, SDA_PIN_1, SCL_PIN_1);

    return 0;

}