#include <pico/stdlib.h>
#include <hardware/i2c.h>

#include "custom_i2c_master.h"

void i2c_master_auto_init(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
) {
    return;
}
