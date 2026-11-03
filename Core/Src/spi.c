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

    // fPCLK/256
    SPI1->CR1 |= 1<<3;
    SPI1->CR1 |= 1<<4;
    SPI1->CR1 |= 1<<5;

    SPI1->CR1 |= 1<<14;
    SPI1->CR1 |= 1<<15;

    SPI1->CR1 |= 1<<0;
    SPI1->CR1 |= 1<<1;

    // set data width to 8-bit
    SPI1->CR2 |= 1<<8;
    SPI1->CR2 |= 1<<9;
    SPI1->CR2 |= 1<<10;
    SPI1->CR2 &= ~(1<<11);

    SPI1->CR1 |= 1<<9;

    SPI1->CR2 |= 1<<2;
    SPI1->CR2 |= 1<<12;

    SPI1->CR2 |= 1<<7;
    SPI1->CR1 |= 1<<2;
}

void init_spi3_slave(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER &= ~(1<<6);
    GPIOB->MODER |= 1<<7;

    // 12 13 14 15 1001
    GPIOB->AFR[0] &= ~(1<<12);
    GPIOB->AFR[0] |= 1<<13;
    GPIOB->AFR[0] |= 1<<14;
    GPIOB->AFR[0] &= ~(1<<15);

    GPIOB->OSPEEDR |= 1<<6;
    GPIOB->OSPEEDR |= 1<<7;

    GPIOB->PUPDR &= ~(1<<6);
    GPIOB->PUPDR |= 1<<7;

    GPIOB->MODER &= ~(1<<8);
    GPIOB->MODER |= 1<<9;

    // 16 17 18 19 1001
    GPIOB->AFR[0] &= ~(1<<16);
    GPIOB->AFR[0] |= 1<<17;
    GPIOB->AFR[0] |= 1<<18;
    GPIOB->AFR[0] &= ~(1<<19);

    GPIOB->OSPEEDR |= 1<<8;
    GPIOB->OSPEEDR |= 1<<9;

    GPIOB->PUPDR &= ~(1<<8);
    GPIOB->PUPDR |= 1<<9;

    NVIC_EnableIRQ(SPI3_IRQn);

    RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;

    // fPCLK/256
    SPI3->CR1 |= 1<<3;
    SPI3->CR1 |= 1<<4;
    SPI3->CR1 |= 1<<5;

    SPI3->CR1 |= 1<<0;
    SPI3->CR1 |= 1<<1;

    // set data width to 8-bit
    SPI3->CR2 |= 1<<8;
    SPI3->CR2 |= 1<<9;
    SPI3->CR2 |= 1<<10;
    SPI3->CR2 &= ~(1<<11);

    SPI3->CR1 |= 1<<9;
    SPI3->CR2 |= 1<<2;
    SPI3->CR1 |= 1<<15;
    SPI3->CR1 &= ~(1<<14);
    SPI3->CR2 |= 1<<12;
    SPI3->CR2 |= 1<<6;
}

void spi1_activate(void) {
    SPI1->CR1 |= 1<<6;
}

void spi3_activate(void) {
    SPI3->CR1 |= 1<<6;
}