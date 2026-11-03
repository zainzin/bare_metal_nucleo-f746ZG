//
// Created by zain_ on 11/2/2026.
//

#include "i2c.h"

static void I2C2_setOwnAddress1(uint32_t OwnAddress, uint32_t OwnAddressSize);

/*
* PB10 - I2C2_SCL AF4
 * PB11 - I2C2_SDA AF4
 *
 */
void i2c2_init_slave(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // PB10 - I2C2_SCL AF4
    GPIOB->MODER &= ~(1<<20);
    GPIOB->MODER |= 1<<21;

    // 11 10 9 8 0100: AF4
    GPIOB->AFR[1] &= ~(1<<8);
    GPIOB->AFR[1] &= ~(1<<9);
    GPIOB->AFR[1] |= 1<<10;
    GPIOB->AFR[1] &= ~(1<<11);

    GPIOB->OTYPER |= 1<<10;
    GPIOB->PUPDR |= 1<<20;
    GPIOB->PUPDR &= ~(1<<21);

    // PB11 - I2C2_SDA AF4
    GPIOB->MODER &= ~(1<<22);
    GPIOB->MODER |= 1<<23;

    // 15 14 13 12 0100: AF4
    GPIOB->AFR[1] &= ~(1<<12);
    GPIOB->AFR[1] &= ~(1<<13);
    GPIOB->AFR[1] |= 1<<14;
    GPIOB->AFR[1] &= ~(1<<15);

    GPIOB->OTYPER |= 1<<11;
    GPIOB->PUPDR |= 1<<22;
    GPIOB->PUPDR &= ~(1<<23);

    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    NVIC_EnableIRQ(I2C2_EV_IRQn);

    // I2C2->CR1 &= ~(1<<23);
    I2C2->CR1 &= ~(1<<0);
    I2C2_setOwnAddress1(SLAVE_OWN_ADDRESS, 0);

    I2C2->OAR1 |= 1<<15;

    I2C2->CR1 |= 1<<0;
    // Enable Address match interrupt
    I2C2->CR1 |= 1<<3;
    // Enable NACK interrupt
    I2C2->CR1 |= 1<<4;
    // Enable STOP interrupt
    I2C2->CR1 |= 1<<5;

}

void i2c1_init_master(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // PB6 - I2C2_SCL AF4
    GPIOB->MODER &= ~(1<<12);
    GPIOB->MODER |= 1<<13;

    // 24 25 26 27 0100: AF4
    GPIOB->AFR[0] &= ~(1<<24);
    GPIOB->AFR[0] &= ~(1<<25);
    GPIOB->AFR[0] |= 1<<26;
    GPIOB->AFR[0] &= ~(1<<27);

    GPIOB->OTYPER |= 1<<6;
    GPIOB->PUPDR |= 1<<12;
    GPIOB->PUPDR &= ~(1<<13);

    // PB9 - I2C2_SDA AF4
    GPIOB->MODER &= ~(1<<18);
    GPIOB->MODER |= 1<<19;

    // 28 29 30 31 0100: AF4
    GPIOB->AFR[1] &= ~(1<<4);
    GPIOB->AFR[1] &= ~(1<<5);
    GPIOB->AFR[1] |= 1<<6;
    GPIOB->AFR[1] &= ~(1<<7);

    GPIOB->OTYPER |= 1<<9;
    GPIOB->PUPDR |= 1<<18;
    GPIOB->PUPDR &= ~(1<<19);

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // I2C1->CR1 &= ~(1<<23);
    I2C1->CR1 &= ~(1<<0);
    I2C1->TIMINGR = I2C_TIMING;
    I2C1->CR1 |= 1<<0;


}
static void I2C2_setOwnAddress1(uint32_t OwnAddress, uint32_t OwnAddressSize) {
    MODIFY_REG(I2C2->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE, OwnAddress | OwnAddressSize);
}