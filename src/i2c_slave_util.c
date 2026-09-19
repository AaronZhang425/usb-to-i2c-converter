/*
 * Original found here:
 * https://github.com/raspberrypi/pico-examples/blob/master/i2c/slave_mem_i2c/slave_mem_i2c.c
 *
 * Copyright (c) 2021 Valentin Milea <valentin.milea@gmail.com>
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 * Copyright 2020 (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include <pico/stdlib.h>
#include <pico/i2c_slave.h>
#include <tusb.h>

#include "i2c_slave_util.h"
#include "i2c_host_commands.h"
#include "tusb_config.h"
#include "usb_hosting.h"


static void write_to_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t *event) {

}

static void read_from_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t *event) {
    uint8_t buffer[DEFAULT_BUFFER_SIZE];

    uint16_t used_buffer_size = 0;

    switch (i2c_read_byte_raw(i2c)) {
        case NEW_I2C_HOST_SIG:
            for (uint8_t index = 0; index < CFG_TUH_DEVICE_MAX; index++) {
                

            }    

            break;

        case GET_MAX_USB_DEV_SIG:
            break;

        case POLL_DEVICES_SIG:
            break;

        default:
            break;

    }



}

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
        case I2C_SLAVE_RECEIVE:
            read_from_slave_handler(i2c, &event);

            break;
        
        case I2C_SLAVE_REQUEST:
            write_to_slave_handler(i2c, &event);
            break;

        case I2C_SLAVE_FINISH:
            break;

        default:
            break;
    }

}

void auto_init_i2c_slave(
    i2c_inst_t* i2c,
    uint8_t address,
    uint baudrate,
    uint sda_pin,
    uint scl_pin
) {
    gpio_init(sda_pin);
    gpio_init(scl_pin);

    // USE EXTERNAL RESISTORS FOR I2C
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);

    i2c_init(i2c, baudrate);

    // Set pi pico to slave
    i2c_slave_init(i2c, address, &i2c_slave_handler);

}