#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 25

int main() {
    // stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, true);

    gpio_put(LED_PIN, 1);

    return 0;

}
