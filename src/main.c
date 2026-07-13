#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/i2c.h>

#include "custom_i2c_slave.h"
#include "custom_i2c_master.h"

#define LED_PIN 25

#define SDA_SLAVE_GPIO_PIN 2
#define SCL_SLAVE_GPIO_PIN 3
#define I2C_SLAVE_BUS i2c1
#define I2C_SLAVE_ADDR 0x17
#define BAUD_RATE 100000

#define SDA_MASTER_GPIO_PIN 4
#define SCL_MASTER_GPIO_PIN 5
#define I2C_MASTER_BUS i2c0

void init() {
    stdio_init_all();

    gpio_init(LED_PIN);
    // Set direction to output
    gpio_set_dir(LED_PIN, GPIO_OUT);
    // Send signal light to turn on
    gpio_put(LED_PIN, true);
    
}

int main() {
    init();

    uint8_t buffer[256];

    i2c_slave_auto_init(
        I2C_SLAVE_BUS,
        I2C_SLAVE_ADDR,
        BAUD_RATE,
        SDA_SLAVE_GPIO_PIN,
        SCL_SLAVE_GPIO_PIN
    );

    i2c_master_auto_init(
        I2C_MASTER_BUS,
        BAUD_RATE,
        SDA_MASTER_GPIO_PIN,
        SCL_MASTER_GPIO_PIN
    );

    i2c_read_blocking(
        I2C_MASTER_BUS,
        I2C_SLAVE_ADDR,
        &(buffer[0]),
        32,
        false
    );

    while (true) {
        printf("Hello there\n");
        sleep_ms(1000);

    }

    return 0;

}