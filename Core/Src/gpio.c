//
// Created by zain_ on 11/8/2026.
//

#include "gpio.h"

#define ENABLE 1

void GPIO_PeriClockControl(GPIO_TypeDef *pGPIOx, uint8_t EnorDi) {
    if (EnorDi == ENABLE) {
        if (pGPIOx == GPIOA) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
        } else if (pGPIOx == GPIOB) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
        } else if (pGPIOx == GPIOC) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        } else if (pGPIOx == GPIOD) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
        } else if (pGPIOx == GPIOE) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
        } else if (pGPIOx == GPIOF) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
        } else if (pGPIOx == GPIOG) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
        } else if (pGPIOx == GPIOH) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
        } else if (pGPIOx == GPIOI) {
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
        }
    } else {
        // reset
    }
}


void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    uint32_t temp = 0;

    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
        pGPIOHandle->pGPIOx->MODER |= temp; //setting
    } else {
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) {
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        } else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT) {
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        } else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT) {
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        RCC->APB2ENR |= (1 << 14);
        SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

        EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    }

    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
        uint8_t temp1, temp2;

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); //clearing
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
    }
}


void GPIO_DeInit(GPIO_TypeDef *pGPIOx) {
    if (pGPIOx == GPIOA) {
        GPIOA_REG_RESET();
    } else if (pGPIOx == GPIOB) {
        GPIOB_REG_RESET();
    } else if (pGPIOx == GPIOC) {
        GPIOC_REG_RESET();
    } else if (pGPIOx == GPIOD) {
        GPIOD_REG_RESET();
    } else if (pGPIOx == GPIOE) {
        GPIOE_REG_RESET();
    } else if (pGPIOx == GPIOF) {
        GPIOF_REG_RESET();
    } else if (pGPIOx == GPIOG) {
        GPIOG_REG_RESET();
    } else if (pGPIOx == GPIOH) {
        GPIOH_REG_RESET();
    } else if (pGPIOx == GPIOI) {
        GPIOI_REG_RESET();
    }
}

uint8_t GPIO_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber) {
    uint8_t value;

    value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001);

    return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_TypeDef *pGPIOx) {
    uint16_t value;

    value = (uint16_t) pGPIOx->IDR;

    return value;
}


void GPIO_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value == GPIO_PIN_SET) {
        pGPIOx->ODR |= (1 << PinNumber);
    } else {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}


void GPIO_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint16_t Value) {
    pGPIOx->ODR = Value;
}


void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber);
}


void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi) {
    if (EnorDi == ENABLE) {
        if (IRQNumber <= 31) {
            // *NVIC_ISER0 |= (1 << IRQNumber);
            NVIC->ISER[0] |= (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) //32 to 63
        {
            NVIC->ISER[1] |= (1 << (IRQNumber % 32));
            // *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            NVIC->ISER[2] |= (1 << (IRQNumber % 64));
            // *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    } else {
        if (IRQNumber <= 31) {
            NVIC->ISER[0] |= (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            NVIC->ISER[1] |= (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            NVIC->ISER[2] |= (1 << (IRQNumber % 64));
        }
    }
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority) {
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *((volatile uint32_t*)NVIC_BASE + iprx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber) {
    if (EXTI->PR & (1 << PinNumber)) {
        EXTI->PR |= (1 << PinNumber);
    }
}
