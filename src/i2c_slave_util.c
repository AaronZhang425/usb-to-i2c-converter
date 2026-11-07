/*
 * Original found here:
 * https://github.com/raspberrypi/pico-examples/blob/master/i2c/slave_mem_i2c/slave_mem_i2c.c
 * The modified code is in the i2c_slave_handler function
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
#include "deque.h"
#include "usb_event.h"
#include "usb_descriptor_getters.h"

// Represents the command from the host
uint8_t host_command;

// Represents the argument of the host command
uint8_t hcmd_arg;

static uint8_t i2c_buffer[DEFAULT_BUFFER_SIZE];

static int new_host_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {
    // The number of bytes written will match the number of addresses written
    uint8_t bytes_written = 0;

    for (
        uint8_t index = 0;
        (
            index < CFG_TUH_DEVICE_MAX 
            && bytes_written < num_usb_connected
            && bytes_written < max_bytes_written
        );
        index++
    ) {
        if (device_addresses[index]) {
            buffer[bytes_written] = device_addresses[index];
            bytes_written++;

        }

    }

    return bytes_written;

}

static int get_usb_dev_desc_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {

}

static int get_usb_config_desc_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {

}

static int get_usb_interface_desc_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {

}

static int get_usb_endpoint_desc_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {

}

static int get_max_usb_dev_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {

}

static int poll_usb_event_handler(
    uint8_t *buffer,
    const uint8_t max_bytes_written
) {

}

static void read_from_slave_handler(i2c_inst_t *i2c) {
    i2c_buffer[0] = host_command;
    uint16_t used_buffer_size = 1;

    switch (host_command) {
        case HCMD_NEW_I2C_HOST:
            used_buffer_size += new_host_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );
            
            // buffer[0] = NEW_USB_ADDR;
            // used_buffer_size = 1;
        
            // for (uint8_t index = 0; index < usb_devices_connected; index++) {
            //     buffer[1 + index ] = device_addresses[index];
            //     used_buffer_size++;

            // }

            break;

        case HCMD_GET_USB_DEV_DESC:
            used_buffer_size += get_usb_dev_desc_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );

            // buffer[0] = MAX_USB_DEVICES_EVENT;
            // buffer[1] = CFG_TUH_DEVICE_MAX;
            // used_buffer_size = 2;

            // tusb_desc_device_t *dev_desc;
            // get_dev_desc_sync(hcmd_arg, &dev_desc);


            break;

        case HCMD_GET_USB_CONFIG_DESC:
            used_buffer_size += get_usb_config_desc_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );

            break;

        case HCMD_GET_USB_INTERFACE_DESC:
            used_buffer_size += get_usb_interface_desc_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );

            break;

        case HCMD_GET_USB_ENDPOINT_DESC:
            used_buffer_size += get_usb_endpoint_desc_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );

            break;

        case HCMD_GET_MAX_USB_DEV:
            used_buffer_size += get_max_usb_dev_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );

            break;

        case HCMD_POLL_EVENTS:
            used_buffer_size += poll_usb_event_handler(
                &i2c_buffer[used_buffer_size],
                DEFAULT_BUFFER_SIZE - used_buffer_size
            );

            // struct usb_event *event = (struct usb_event *) poll_head_deque(event_deque);

            // buffer[0] = event->event_type;

            // memcpy(
            //     &buffer[1],
            //     event->event_data,
            //     event->event_data_size
            // );

            // used_buffer_size = 1 + event->event_data_size;

            break;


        default:
            return;
        
    }

    i2c_write_raw_blocking(i2c, i2c_buffer, used_buffer_size);

}

static void write_to_slave_handler(i2c_inst_t *i2c) {
    host_command = i2c_read_byte_raw(i2c);
    hcmd_arg = i2c_read_byte_raw(i2c);

}


static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
        case I2C_SLAVE_RECEIVE:
            read_from_slave_handler(i2c);
            break;
        
        case I2C_SLAVE_REQUEST:
            write_to_slave_handler(i2c);
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