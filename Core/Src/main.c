/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <stdio.h>
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define UART_RX_BUFFER_SIZE 64
volatile char uart_rx_buffer[UART_RX_BUFFER_SIZE];
volatile uint32_t uart_rx_index = 0;
/* USER CODE END 0 */
const uint8_t i2c_msg[] = "HELLO";
uint8_t *p_tx_buffer = (uint8_t*)i2c_msg;
uint8_t tx_size = sizeof(i2c_msg);
volatile uint8_t tx_index = 0;

uint8_t rx_buffer[sizeof(i2c_msg)];
uint8_t rx_size = sizeof(i2c_msg);
volatile uint8_t rx_index = 0;

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  // PC13_EXTI_Init();
  // TIMER1_1Hz_Interrupt_Init();
  // USART3_Init();
  USART3_Interrupt_Init();
  // LED_Init();
  i2c2_init_slave();
  i2c1_init_master();
  handle_i2c_master();
  while (1)
  {
    /* USER CODE END WHILE */
    // GPIOB->ODR ^= 1U<<7;
    // if (GPIOC->IDR & (1<<13)) {
    //   printf("Pressed");
    // }

    // if (strcmp(rx_buffer,"0") == 0) {
    //   GPIOB->ODR |= 1U<<7;
    // } else if (strcmp(rx_buffer,"1") != 0) {
    //   GPIOB->ODR &= ~1U<<7;
    // }

    // USART3_SendChar('Z');
    // for (int i = 0; i < 10000000; i++);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

// void USART3_IRQHandler(void) {
//   if (USART3->ISR & USART_ISR_TXE) {
//     USART3->TDR = 'I';
//   }
// }

// void EXTI15_10_IRQHandler() {
//   if (EXTI->PR & EXTI_PR_PR13) {
//     EXTI->PR |= EXTI_PR_PR13;
//     GPIOB->ODR ^= 1U<<7;
//     USART3_SendChar('Z');
//     USART3_SendString("Stop Interrupting me");
//   }
// }

void I2C2_EV_IRQHandler(void) {
  if (I2C2->ISR & (1<<3)) {
    if (i2c2_get_address_matchcode() == SLAVE_OWN_ADDRESS) {
      I2C2->ICR |= (1<<3);
      I2C2->CR1 |= 1<<2;
    }
  } else if (I2C2->ISR & (1<<2)) {
    rx_buffer[rx_index++] = I2C2->RXDR & 0xFF;
  } else if (I2C2->ISR & (1<<5)) {
    I2C2->ICR |= (1<<5);
    USART3_SendString("Complete");
  } else {
    USART3_SendString("Error");
  }
}

uint32_t i2c2_get_address_matchcode(void) {
  return (uint32_t)(READ_BIT(I2C2->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}

static void handle_i2c_master(void) {
  I2C1->CR2 |= SLAVE_OWN_ADDRESS;
  I2C1->CR2 &= ~(1<<11);
  I2C1->CR2 |= (tx_size<<16);
  I2C1->CR2 |= (1<<25);
  I2C1->CR2 |= (1<<13);

  while (!(I2C1->ISR & (1<<5))) {
    if (I2C1->ISR & (1<<1)) {
      I2C1->TXDR = *p_tx_buffer++;
    }
  }
  I2C1->ICR |= (1<<5);
}

void USART3_IRQHandler(void) {
  // Check if the interrupt flag for received data is set
  if (USART3->ISR & USART_ISR_RXNE) {
    char received_byte = (char)(USART3->RDR & 0xFF);

    if (uart_rx_index < UART_RX_BUFFER_SIZE - 1) {
      uart_rx_buffer[rx_index++] = received_byte;
      uart_rx_buffer[rx_index] = '\0'; // Dynamic null-termination
    }
  }
}

// void TIM1_UP_TIM10_IRQHandler(void) {
//   if (TIM1->SR & TIM_SR_UIF) {
//     TIM1->SR &= ~(TIM_SR_UIF);
//     GPIOB->ODR ^= 1U<<7;
//   }
// }

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
