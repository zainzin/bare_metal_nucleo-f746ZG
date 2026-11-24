//
// Created by zain_ on 11/3/2026.
//

#ifndef HIGH_LEVEL_NOW_SPI_H
#define HIGH_LEVEL_NOW_SPI_H

#endif //HIGH_LEVEL_NOW_SPI_H

#include "stm32f746xx.h"
#include "stm32f7xx.h"

#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE 0

#define SPI_BUS_CONFIG_FD 1
#define SPI_BUS_CONFIG_HD 2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3

#define SPI_BAUDRATE_DIV2 0
#define SPI_BAUDRATE_DIV4 1
#define SPI_BAUDRATE_DIV8 2
#define SPI_BAUDRATE_DIV16 3
#define SPI_BAUDRATE_DIV32 4
#define SPI_BAUDRATE_DIV64 5
#define SPI_BAUDRATE_DIV128 6
#define SPI_BAUDRATE_DIV256 7

#define SPI_DFF_8BITS 0
#define SPI_DFF_16BITS 1

#define SPI_CPOL_HIGH 1
#define SPI_CPOL_LOW 0

#define SPI_CPHA_HIGH 1
#define SPI_CPHA_LOW 0

#define SPI_SSM_EN 1
#define SPI_SSM_DIS 0

#define SPI_TXE_FLAG    ( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   ( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   ( 1 << SPI_SR_BSY)

#define SPI_READY_STATE 0
#define SPI_BUSY_STATE_RX 1
#define SPI_BUSY_STATE_TX 2

#define SPI_EVENT_TX_COMPLETE 1
#define SPI_EVENT_RX_COMPLETE 2
#define SPI_EVENT_OVR_ERR 3
#define SPI_EVENT_CRC_ERR 3

void init_spi1_master(void);
void init_spi3_slave(void);
void spi1_activate(void);
void spi3_activate(void);

// new way to improve on old one

typedef struct {
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
} SPI_Config_t;

typedef struct {
    SPI_TypeDef *SPIx;
    SPI_Config_t Config;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxLength;
    uint32_t RxLength;
    uint8_t TxState;
    uint8_t RxState;
}SPI_Handle_t;

void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t enOrDis);
void SPI_SSIConfig(SPI_TypeDef *pSPIx, uint8_t EnOrDis);
void SPI_Init(SPI_Handle_t *pSPIx);
void SPI_DeInit(SPI_TypeDef *pSPIx);
void SPI_SSOEConfig(SPI_TypeDef *pSPIx, uint8_t EnOrDis);
uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx , uint32_t FlagName);
void SPI_ClearOVRFlag(SPI_TypeDef *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *handle);
void SPI_CloseReception(SPI_Handle_t *handle);

void SPI_SendData(SPI_TypeDef *pSPIx, uint8_t *txData, uint32_t length);
void SPI_ReceiveData(SPI_TypeDef *pSPIx, uint8_t *rxData, uint32_t length);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIx, uint8_t *txData, uint32_t length);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIx, uint8_t *rxData, uint32_t length);

void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t EnOrDis);

void SPI_IRQInterrupt(SPI_TypeDef *pSPIx, uint8_t EnOrDis);
void SPI_IRQPriorityConfig(SPI_TypeDef *pSPIx, uint32_t IRQPriority);
void SPI_IRQHandle(SPI_Handle_t * handle);
void SPI_ApplicationEventCallback(SPI_Handle_t * handle, uint8_t Event);