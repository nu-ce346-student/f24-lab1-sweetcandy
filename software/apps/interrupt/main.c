// Interrupt app
//
// Trigger GPIO and Software interrupts

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"

// Initialize software interrupts
void software_interrupt_init(void) {
  NRF_EGU1->INTENSET = 0x1;
  NVIC_EnableIRQ(SWI1_EGU1_IRQn);
}

// Trigger a software interrupt
void software_interrupt_trigger(void) {
  NRF_EGU1->TASKS_TRIGGER[0] = 1;
}

void SWI1_EGU1_IRQHandler(void) {
  // Clear interrupt event
  NRF_EGU1->EVENTS_TRIGGERED[0] = 0;

  // Implement me
  printf("Entered the software interrupt\n");
  nrf_delay_ms(2000);
  printf("Exiting the software interrupt\n");
}

void GPIOTE_IRQHandler(void) {
  // Clear interrupt event
  NRF_GPIOTE->EVENTS_IN[0] = 0;

  // Implement me
  printf("Entered the GPIOTE interrupt\n");
  nrf_delay_ms(2000);
  printf("Exiting the GPIOTE interrupt\n");
}

void printBinary(uint32_t n) {
    printf("0x");
    // Iterate over all bits in the 32-bit integer
    for (int i = 31; i >= 0; i--) {
        // Print the corresponding bit (shift and mask)
        printf("%d", (int) (n >> i) & 1);
    }
    printf("\n");
}

int main(void) {
  printf("Board started!\n");

  // First task. Trigger a GPIOTE interrupt
  // You can access the GPIOTE register map as NRF_GPIOTE->
  //    where the register name in all caps goes after the arrow.
  //    For example, NRF_GPIOTE->CONFIG[0]
  // Add code here
  
  // setup config
  uint32_t config = 0;
  // MODE = Event = 1 = 0b01
  config |= 0b01;
  // PSEL = 14 = 0b01110
  config |= (14 << 8);
  // PORT
  config |= (0 << 13);
  // POLARITY = HiToLo = 2
  config |= (2 << 16);
  // OUTINIT
  config |= (0 << 20);
  printBinary(config);

  // write the config into memory
  NRF_GPIOTE->CONFIG[0] = config;

  // enable interrupt on channel 0
  int32_t intenset = 0;
  intenset |= 1;
  NRF_GPIOTE->INTENSET = intenset;

  // enable interrupt in NVIC
  NVIC_EnableIRQ(GPIOTE_IRQn);
  NVIC_SetPriority(GPIOTE_IRQn, 0);


  // Second task. Trigger a software interrupt
  // Use the software_interupt_* functions defined above
  // Add code here
  software_interrupt_init();
  NVIC_SetPriority(SWI1_EGU1_IRQn, 1);
  software_interrupt_trigger();

  // loop forever
  while (1) {
    printf("Looping\n");
    nrf_delay_ms(1000);
  }
}

