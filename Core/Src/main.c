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

#include "gpio.h"

void delay(void) {
  for (uint32_t i = 0; i < 500000/2; i++);
}

void SPI2_GPIOinit(void) {
  GPIO_Handle_t spi_handle;
  spi_handle.pGPIOx = GPIOB;
  spi_handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
  spi_handle.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
  spi_handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  spi_handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  spi_handle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

  spi_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13; // SCLK
  GPIO_Init(&spi_handle);

  spi_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15; // MOSI
  GPIO_Init(&spi_handle);

  spi_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12; // NSS
  GPIO_Init(&spi_handle);

  spi_handle.pGPIOx = GPIOC;
  spi_handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
  spi_handle.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
  spi_handle.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
  spi_handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
  spi_handle.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
  spi_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2; // MISO
  GPIO_Init(&spi_handle);
}

void BTN_GPIOInit(void) {
  GPIO_Handle_t btn_handle;
  btn_handle.pGPIOx = GPIOC;
  btn_handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
  btn_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
  btn_handle.GPIO_PinConfig.GPIO_PinSpeed =  GPIO_SPEED_FAST;
  btn_handle.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

  GPIO_PeriClockControl(GPIOC, ENABLE);
  GPIO_Init(&btn_handle);
}

void SPI2_Init(void) {
  SPI_Handle_t spi_handle;
  spi_handle.SPIx = SPI2;
  spi_handle.Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
  spi_handle.Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
  spi_handle.Config.SPI_SclkSpeed = SPI_BAUDRATE_DIV8;
  spi_handle.Config.SPI_DFF = SPI_DFF_8BITS;
  spi_handle.Config.SPI_CPOL = SPI_CPOL_LOW;
  spi_handle.Config.SPI_CPHA = SPI_CPHA_LOW;
  spi_handle.Config.SPI_SSM = SPI_SSM_DIS;

  SPI_Init(&spi_handle);
}

/**
  * SPI send
*/
// int main(void)
// {
//   char data[] = "Hello SPI";
//
//   SPI2_GPIOinit();
//   SPI2_Init();
//   BTN_GPIOInit();
//   // SPI_SSIConfig(SPI2, ENABLE);
//   SPI_SSOEConfig(SPI2, ENABLE);
//
//   while (1)
//   {
//
//     while (! (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)));
//     delay();
//
//     SPI_PeripheralControl(SPI2, ENABLE);
//
//     uint8_t dataLength = strlen(data);
//     SPI_SendData(SPI2, &dataLength, 1);
//     SPI_SendData(SPI2, (uint8_t*)data, strlen(data));
//     while (SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));
//     SPI_PeripheralControl(SPI2, DISABLE);
//
//   }
// }

/**
  * I2C
*/
int main(void)
{
  while (1) {
  }
}

uint32_t i2c2_get_address_matchcode(void) {
  return (uint32_t)(READ_BIT(I2C2->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}

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
