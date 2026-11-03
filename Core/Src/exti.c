//
// Created by zain_ on 10/28/2026.
//

#include "exti.h"

void LED_Init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    GPIOB->MODER |= GPIO_MODER_MODER7_0;
}

void PC13_EXTI_Init() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOC->MODER &= ~(1 << 26);
    GPIOC->MODER &= ~(1 << 27);
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13_PC; // 1U << 4, 1U << 5, 1U << 6, 1U << 7
    // SYSCFG->EXTICR[3] &= ~(1U << 4);
    // SYSCFG->EXTICR[3] &= ~(1U << 5);
    // SYSCFG->EXTICR[3] &= ~(1U << 6);
    // SYSCFG->EXTICR[3] &= ~(1U << 7);
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
    EXTI->IMR |= EXTI_IMR_MR13;
    EXTI->FTSR |= EXTI_FTSR_TR13;
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}
