//
// Created by zain_ on 10/28/2026.
//
#include "timer.h"

void TIMER1_1Hz_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC   = 1600 - 1;
    TIM1->ARR = 10000 - 1;
    TIM1->CR1 |= TIM_CR1_CEN;
}

void TIMER1_1Hz_Interrupt_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->PSC   = 1600 - 1;
    TIM1->ARR = 10000 - 1;

    TIM1->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

    TIM1->CR1 |= TIM_CR1_CEN;
    TIM1->EGR |= TIM_EGR_UG;
}