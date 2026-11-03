//
// Created by zain_ on 11/3/2026.
//

#include "spi.h"


void init_spi1_master(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // SCL
    GPIOA->MODER &= ~(1<<10);
    GPIOA->MODER |= 1<<11;

    // 20 21 22 23 0101
    GPIOA->AFR[0] |= 1<<20;
    GPIOA->AFR[0] &= ~(1<<21);
    GPIOA->AFR[0] |= 1<<22;
    GPIOA->AFR[0] &= ~(1<<23);

    GPIOA->OSPEEDR |= 1<<10;
    GPIOA->OSPEEDR |= 1<<11;

    GPIOA->PUPDR &= ~(1<<10);
    GPIOA->PUPDR |= 1<<11;

    // PA7 MOSI
    GPIOA->MODER &= ~(1<<14);
    GPIOA->MODER |= 1<<15;

    GPIOA->AFR[0] |= 1<<28;
    GPIOA->AFR[0] &= ~(1<<29);
    GPIOA->AFR[0] |= 1<<30;
    GPIOA->AFR[0] &= ~(1<<31);

    GPIOA->OSPEEDR |= 1<<14;
    GPIOA->OSPEEDR |= 1<<15;

    GPIOA->PUPDR &= ~(1<<14);
    GPIOA->PUPDR |= 1<<15;

    NVIC_EnableIRQ(SPI1_IRQn);


    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

}