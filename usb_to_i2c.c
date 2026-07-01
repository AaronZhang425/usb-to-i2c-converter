#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define SDA_PIN_1 2
#define SCL_PIN_1 3
#define LED_PIN 25
#define I2C_ADDR 6

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

    i2c_set_slave_mode(i2c1, 1, I2C_ADDR);
    
}

int main() {
    init();

    return 0;

}