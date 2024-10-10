#include "gpio.h"

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t _unused0[(0x504)/4];
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR;
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t _unused1[(0x700-0x524)/4 - 1];
  uint32_t PIN_CNF[32];
} gpio_reg_t;
volatile gpio_reg_t* GPIO_REG_T_P0 = (gpio_reg_t*) (0x50000000);
volatile gpio_reg_t* GPIO_REG_T_P1 = (gpio_reg_t*) (0x50000300);

void printBinary(uint32_t n) {
    printf("0x");
    // Iterate over all bits in the 32-bit integer
    for (int i = 31; i >= 0; i--) {
        // Print the corresponding bit (shift and mask)
        printf("%d", (int) (n >> i) & 1);
    }
    printf("\n");
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  uint8_t adjusted_gpio_num = gpio_num;
  volatile gpio_reg_t* GPIO_REG;
  if (gpio_num >= 32) {
    GPIO_REG = GPIO_REG_T_P1;
    adjusted_gpio_num = gpio_num - 32;
  } else {
    GPIO_REG = GPIO_REG_T_P0;
  }
  GPIO_REG->PIN_CNF[adjusted_gpio_num] = (dir << 0) | (dir << 1);
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured
  uint8_t adjusted_gpio_num = gpio_num;
  volatile gpio_reg_t* GPIO_REG;
  if (gpio_num >= 32) {
    GPIO_REG = GPIO_REG_T_P1;
    adjusted_gpio_num = gpio_num - 32;
  } else {
    GPIO_REG = GPIO_REG_T_P0;
  }
  uint32_t old_value = GPIO_REG->OUT;
  old_value |= (1 << adjusted_gpio_num);
  GPIO_REG->OUT = old_value;
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  uint8_t adjusted_gpio_num = gpio_num;
  volatile gpio_reg_t* GPIO_REG;
  if (gpio_num >= 32) {
    GPIO_REG = GPIO_REG_T_P1;
    adjusted_gpio_num = gpio_num - 32;
  } else {
    GPIO_REG = GPIO_REG_T_P0;
  }
  uint32_t old_value = GPIO_REG->OUT;
  old_value &= ~(1 << adjusted_gpio_num);
  GPIO_REG->OUT = old_value;
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured
  uint8_t adjusted_gpio_num = gpio_num;
  volatile gpio_reg_t* GPIO_REG;
  if (gpio_num >= 32) {
    GPIO_REG = GPIO_REG_T_P1;
    adjusted_gpio_num = gpio_num - 32;
  } else {
    GPIO_REG = GPIO_REG_T_P0;
  }
  uint32_t value = GPIO_REG->IN;
  if (value & (1 << adjusted_gpio_num)) {
    return true;
  } else {
    return false;
  }
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here
  printBinary(GPIO_REG_T_P0->OUT);
}

