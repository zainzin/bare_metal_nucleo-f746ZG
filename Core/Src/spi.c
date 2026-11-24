//
// Created by zain_ on 11/3/2026.
//

#include "spi.h"

#include <stddef.h>


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

static void handleTxInterrupt(SPI_Handle_t * handle);
static void handleRxInterrupt(SPI_Handle_t * handle);
static void handleOVRErrorInterrupt(SPI_Handle_t * handle);

void SPI_PeriClockControl(SPI_TypeDef *pSPIx, uint8_t enOrDis) {
    if (enOrDis == ENABLE) {
        if (pSPIx == SPI1) {
            RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        } else if (pSPIx == SPI2) {
            RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
        } else if (pSPIx == SPI3) {
            RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
        } else if (pSPIx == SPI4) {
            RCC->APB2ENR |= RCC_APB2ENR_SPI4EN;
        }
    } else {
        if (pSPIx == SPI1) {
            RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN;
        } else if (pSPIx == SPI2) {
            RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN;
        } else if (pSPIx == SPI3) {
            RCC->APB1ENR &= ~RCC_APB1ENR_SPI3EN;
        } else if (pSPIx == SPI4) {
            RCC->APB2ENR &= ~RCC_APB2ENR_SPI4EN;
        }
    }
}

void SPI_Init(SPI_Handle_t *pSPIx) {
    SPI_PeriClockControl(pSPIx->SPIx, ENABLE);

    uint32_t cr1_reg_config = 0;
    cr1_reg_config |= pSPIx->Config.SPI_DeviceMode << 2;

    if (pSPIx->Config.SPI_BusConfig == SPI_BUS_CONFIG_FD) {
        cr1_reg_config &= ~(1<<15);
    } else if (pSPIx->Config.SPI_BusConfig == SPI_BUS_CONFIG_HD) {
        cr1_reg_config |= 1<<15;
    } else if (pSPIx->Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY) {
        cr1_reg_config &= ~(1<<15);
        cr1_reg_config |= 1<<10;
    }

    cr1_reg_config |= pSPIx->Config.SPI_SclkSpeed << 3;
    cr1_reg_config |= pSPIx->Config.SPI_DFF << 11;
    cr1_reg_config |= pSPIx->Config.SPI_CPOL << 1;
    cr1_reg_config |= pSPIx->Config.SPI_CPHA << 0;
    cr1_reg_config |= pSPIx->Config.SPI_SSM << 9;

    pSPIx->SPIx->CR1 = cr1_reg_config;
}
void SPI_DeInit(SPI_TypeDef *pSPIx){}

void SPI_SendData(SPI_TypeDef *pSPIx, uint8_t *txData, uint32_t length) {
    while (length > 0) {
        while (!(pSPIx->SR & (1<<1)));
        if ((pSPIx->CR1 & 1<<11)) {
            // 16bit
            pSPIx->DR = *((uint16_t*)txData);
            length -= 2;
            (uint16_t*)txData++;
        } else {
            pSPIx->DR = *txData;
            length--;
            txData++;
        }
    }

}
void SPI_ReceiveData(SPI_TypeDef *pSPIx, uint8_t *rxData, uint32_t length) {
    while (length > 0) {
        while (!(pSPIx->SR & (1<<1)));
        if ((pSPIx->CR1 & 1<<11)) {
            // 16bit
            *((uint16_t*)rxData) = pSPIx->DR;
            length -= 2;
            (uint16_t*)rxData++;
        } else {
            *rxData = pSPIx->DR;
            length--;
            rxData++;
        }
    }
}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIx, uint8_t *txData, uint32_t length) {
    uint8_t state = pSPIx->TxState;

    if (state != SPI_BUSY_STATE_TX) {
        pSPIx->pTxBuffer = txData;
        pSPIx->TxLength = length;
        pSPIx->TxState = SPI_BUSY_STATE_TX;
        pSPIx->SPIx->CR2 |= 1<<7;
    }

    return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIx, uint8_t *rxData, uint32_t length) {
    uint8_t state = pSPIx->RxState;

    if (state != SPI_BUSY_STATE_RX) {
        pSPIx->pRxBuffer = rxData;
        pSPIx->RxLength = length;
        pSPIx->RxState = SPI_BUSY_STATE_RX;
        pSPIx->SPIx->CR2 |= 1<<6;
    }

    return state;
}

void SPI_SSIConfig(SPI_TypeDef *pSPIx, uint8_t EnOrDis) {
    if (EnOrDis == ENABLE) {
        pSPIx->CR1 |= 1<<8;
    } else {
        pSPIx->CR1 &= ~(1<<8);
    }
}
void SPI_PeripheralControl(SPI_TypeDef *pSPIx, uint8_t EnOrDis) {
    if (EnOrDis == ENABLE) {
        pSPIx->CR1 |= 1<<6;
    } else {
        pSPIx->CR1 &= ~(1<<6);
    }
}

void SPI_SSOEConfig(SPI_TypeDef *pSPIx, uint8_t EnOrDis) {
    if (EnOrDis == ENABLE) {
        pSPIx->CR2 |= SPI_CR2_SSOE;
    } else {
        pSPIx->CR2 &= ~(SPI_CR2_SSOE);
    }
}

uint8_t SPI_GetFlagStatus(SPI_TypeDef *pSPIx , uint32_t FlagName)
{
    if(pSPIx->SR & FlagName)
    {
        return 1;
    }
    return 0;
}

void SPI_ClearOVRFlag(SPI_TypeDef *pSPIx) {
    uint8_t dataRegState;
    dataRegState = pSPIx->DR;
    dataRegState = pSPIx->SR;
    (void)dataRegState;
}

void SPI_CloseTransmission(SPI_Handle_t *handle) {
    handle->SPIx->CR2 &= ~(1<<7);
    handle->pTxBuffer = NULL;
    handle->TxLength = 0;
    handle->TxState = SPI_READY_STATE;
}

void SPI_CloseReception(SPI_Handle_t *handle) {
    handle->SPIx->CR2 &= ~(1<<6);
    handle->pRxBuffer = NULL;
    handle->RxLength = 0;
    handle->RxState = SPI_READY_STATE;
}

void SPI_IRQInterrupt(SPI_TypeDef *pSPIx, uint8_t EnOrDis){}

void SPI_IRQPriorityConfig(SPI_TypeDef *pSPIx, uint32_t IRQPriority){}

void SPI_IRQHandle(SPI_Handle_t * handle) {
    uint8_t statusRegState, intCR;
    statusRegState = handle->SPIx->SR & (1 << 1);
    intCR = handle->SPIx->CR2 & (1 << 7);

    if (statusRegState && intCR) {
        handleTxInterrupt(handle);
    }

    statusRegState = handle->SPIx->SR & (1 << 0);
    intCR = handle->SPIx->CR2 & (1 << 6);

    if (statusRegState && intCR) {
        handleRxInterrupt(handle);
    }

    statusRegState = handle->SPIx->SR & (1 << 6);
    intCR = handle->SPIx->CR2 & (1 << 5);

    if (statusRegState && intCR) {
        handleOVRErrorInterrupt(handle);
    }
}

void handleTxInterrupt(SPI_Handle_t * handle) {
    if ((handle->SPIx->CR1 & 1<<11)) {
        // 16bit
        handle->SPIx->DR = *((uint16_t*)handle->pTxBuffer);
        handle->TxLength -= 2;
        (uint16_t*)handle->pTxBuffer++;
    } else {
        handle->SPIx->DR = *handle->pTxBuffer;
        handle->TxLength--;
        handle->pTxBuffer++;
    }

    if (!handle->TxLength) {
        SPI_CloseTransmission(handle);
        SPI_ApplicationEventCallback(handle, SPI_EVENT_TX_COMPLETE);
    }
}

void handleRxInterrupt(SPI_Handle_t * handle) {
    if ((handle->SPIx->CR1 & 1<<11)) {
        // 16bit
        *((uint16_t*)handle->pRxBuffer) = handle->SPIx->DR;
        handle->TxLength -= 2;
        (uint16_t*)handle->pRxBuffer++;
    } else {
        *handle->pRxBuffer = handle->SPIx->DR;
        handle->RxLength--;
        handle->pRxBuffer++;
    }

    if (!handle->RxLength) {
        SPI_CloseReception(handle);
        SPI_ApplicationEventCallback(handle, SPI_EVENT_RX_COMPLETE);
    }
}

void handleOVRErrorInterrupt(SPI_Handle_t * handle) {
    uint8_t dataRegState;
    if (handle->TxState & SPI_BUSY_STATE_TX) {
        dataRegState = handle->SPIx->DR;
        dataRegState = handle->SPIx->SR;
    }
    (void)dataRegState;
    SPI_ApplicationEventCallback(handle, SPI_EVENT_OVR_ERR);
}

__WEAK void SPI_ApplicationEventCallback(SPI_Handle_t * handle, uint8_t Event);