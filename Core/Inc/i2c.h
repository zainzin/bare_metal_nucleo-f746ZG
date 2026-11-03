//
// Created by zain_ on 11/2/2026.
//

#ifndef HIGH_LEVEL_NOW_I2C_H
#define HIGH_LEVEL_NOW_I2C_H

#endif //HIGH_LEVEL_NOW_I2C_H

#include "stm32f746xx.h"
#include "stm32f7xx.h"

#define SLAVE_OWN_ADDRESS 0x5A
#define I2C_TIMING 0x00303D5B
#define I2C_DIRECTION_WRITE = 0x00000000U

void i2c2_init_slave(void);
void i2c1_init_master(void);