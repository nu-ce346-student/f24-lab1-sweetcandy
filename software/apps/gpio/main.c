// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");

  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here
  // DIR config
  *(uint32_t*) (0x50000514) = (1 << 20);
  // OUT config
  *(uint32_t*) (0x50000504) = (1 << 20);

  // Turn on all LEDs on the back of the Microbit
  // Add code here
  // ROW 1
  gpio_config(21, GPIO_OUTPUT);
  gpio_set(21);
  // ROW 2
  gpio_config(22, GPIO_OUTPUT);
  gpio_set(22);
  // ROW 3
  gpio_config(15, GPIO_OUTPUT);
  gpio_set(15);
  // ROW 4
  gpio_config(24, GPIO_OUTPUT);
  gpio_set(24);
  // ROW 5
  gpio_config(19, GPIO_OUTPUT);
  gpio_set(19);

  // COLUMN 1
  gpio_config(28, GPIO_OUTPUT);
  gpio_clear(28);
  // COLUMN 2
  gpio_config(11, GPIO_OUTPUT);
  gpio_clear(11);
  // COLUMN 3
  gpio_config(31, GPIO_OUTPUT);
  gpio_clear(31);
  // COLUMN 4
  gpio_config(37, GPIO_OUTPUT);
  gpio_clear(37);
  // COLUMN 5
  gpio_config(30, GPIO_OUTPUT);
  gpio_clear(30);
  
  // setup button gpios as inputs
  gpio_config(14, GPIO_INPUT);
  gpio_config(23, GPIO_INPUT);
  // setup led gpio
  gpio_config(20, GPIO_OUTPUT);

  // loop forever
  printf("Looping\n");
  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    bool read_button_a = gpio_read(14);
    bool read_button_b = gpio_read(23);

    if (!read_button_a) {
      gpio_set(20);
    }
    if (!read_button_b) {
      gpio_clear(20);
    }
    nrf_delay_ms(100);
  }
}

