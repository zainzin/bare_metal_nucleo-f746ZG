//
// Created by zain_ on 10/30/2026.
//

#include "uart.h"

void USART3_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOD->MODER |= (2U << GPIO_MODER_MODER8_Pos) | (2U << GPIO_MODER_MODER9_Pos);

    GPIOD->AFR[1] &= ~((0xFU << GPIO_AFRH_AFRH0_Pos) | (0xFU << GPIO_AFRH_AFRH1_Pos));
    GPIOD->AFR[1] |=  (7U << GPIO_AFRH_AFRH0_Pos) |  (7U << GPIO_AFRH_AFRH1_Pos);

    // Optional: Set pins to High Speed
    GPIOD->OSPEEDR |= ((3 << (8 * 2)) | (3 << (9 * 2)));

    USART3->BRR = 139;

    USART3->CR1 = 0;

    USART3->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);
}

void USART3_Interrupt_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

    GPIOD->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOD->MODER |= (2U << GPIO_MODER_MODER8_Pos) | (2U << GPIO_MODER_MODER9_Pos);

    GPIOD->AFR[1] &= ~((0xFU << GPIO_AFRH_AFRH0_Pos) | (0xFU << GPIO_AFRH_AFRH1_Pos));
    GPIOD->AFR[1] |=  (7U << GPIO_AFRH_AFRH0_Pos) |  (7U << GPIO_AFRH_AFRH1_Pos);


    // Optional: Set pins to High Speed
    GPIOD->OSPEEDR |= ((3 << (8 * 2)) | (3 << (9 * 2)));

    USART3->BRR = 139;

    USART3->CR1 = 0;

    // Enable RXNE Interrupt
    USART3->CR1 |= USART_CR1_RXNEIE;
    // Enable TXNE Interrupt
    // USART3->CR1 |= (USART_CR1_TXEIE);

    USART3->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

    // 5. Enable USART3 Interrupt in the NVIC
    NVIC_SetPriority(USART3_IRQn, 0);
    NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_SendChar(char c) {
    // Wait until Transmit Data Register Empty (TXE) is set
    while (!(USART3->ISR & USART_ISR_TXE));
    USART3->TDR = c;
}

void USART3_SendString(const char *str) {
    while (*str) {
        USART3_SendChar(*str++);
    }
}

char USART3_ReceiveChar(void) {
    // 1. Wait until the Read Data Register Not Empty flag (RXNE) is set
    while (!(USART3->ISR & USART_ISR_RXNE));

    // 2. Return the data from the Receive Data Register (RDR)
    // Reading RDR automatically clears the RXNE flag
    return (char)(USART3->RDR & 0xFF);
}

void USART3_ReceiveString(char *buffer, uint32_t max_len) {
    uint32_t i = 0;
    while (i < (max_len - 1)) {
        char c = USART3_ReceiveChar();

        // Terminate on Carriage Return or Newline
        if (c == '\r' || c == '\n') {
            break;
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0'; // Null-terminate string
}