//
// Created by zain_ on 10/30/2026.
//

#ifndef HIGH_LEVEL_NOW_UART_H
#define HIGH_LEVEL_NOW_UART_H

#endif //HIGH_LEVEL_NOW_UART_H

#include "stm32f746xx.h"

void USART3_Init(void);
void USART3_Interrupt_Init(void);
void USART3_SendChar(char c);
void USART3_SendString(const char *str);
char USART3_ReceiveChar(void);
void USART3_ReceiveString(char *buffer, uint32_t max_len);