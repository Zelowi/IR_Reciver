/*
 * stm32f103xx.h
 *
 *  Created on: Apr 7, 2026
 *      Author: Zelowi
 */

#ifndef INC_STM32F103XX_H_
#define INC_STM32F103XX_H_

#include <stdint.h>



#define AHB_BASEADDR 0x40018000U
#define APB1_BASEADDR 0x40000000U
#define APB2_BASEADDR 0x40010000U

#define GPIOA_BASEADDR (APB2_BASEADDR + 0x0800)
#define GPIOB_BASEADDR (APB2_BASEADDR + 0x0C00)
#define GPIOC_BASEADDR (APB2_BASEADDR + 0x1000)

#define RCC_BASEADDR 0x40021000U

#define SPI2_BASEADDR (APB1_BASEADDR + 0x3800)


#define AFIO_BASEADDR        0x40010000U


#define EXTI_BASEADDR        0x40010400U


//Structure for GPIO registers
typedef struct
{
    volatile uint32_t CRL;   // 0x00 → config for pins 0–7
    volatile uint32_t CRH;   // 0x04 → config for pins 8–15
    volatile uint32_t IDR;   // 0x08 → input data
    volatile uint32_t ODR;   // 0x0C → output data
    volatile uint32_t BSRR;  // 0x10 → bit set/reset
    volatile uint32_t BRR;   // 0x14 → bit reset
    volatile uint32_t LCKR;  // 0x18 → lock register
} GPIO_RegDef_t;



#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)



//Structure for RCC register
typedef struct
{
    volatile uint32_t CR;        // 0x00 Clock control
    volatile uint32_t CFGR;      // 0x04 Clock config
    volatile uint32_t CIR;       // 0x08 Clock interrupt
    volatile uint32_t APB2RSTR;  // 0x0C APB2 reset
    volatile uint32_t APB1RSTR;  // 0x10 APB1 reset
    volatile uint32_t AHBENR;    // 0x14 AHB enable
    volatile uint32_t APB2ENR;   // 0x18 APB2 enable
    volatile uint32_t APB1ENR;   // 0x1C APB1 enable
    volatile uint32_t BDCR;      // 0x20 Backup domain
    volatile uint32_t CSR;       // 0x24 Control/status
} RCC_RegDef_t;


#define TIM2_BASEADDR    0x40000000U

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RESERVED1;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t RESERVED2;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
} TIM_RegDef_t;

#define TIM2    ((TIM_RegDef_t*)TIM2_BASEADDR)

#define TIM2_Enable() RCC->APB1ENR |= (1 << 0)



typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t MAPR2;

}AFIO_RegDef_t;


typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_RegDef_t;


#define AFIO    ((AFIO_RegDef_t*)AFIO_BASEADDR)
#define AFIO_PCLK_EN()   (RCC->APB2ENR |= (1 << 0))

#define EXTI    ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)

//Enable clock for GPIOx Port
#define GPIOA_PCLCK_EN() ( RCC-> APB2ENR |= (1 << 2))
#define GPIOB_PCLCK_EN() ( RCC-> APB2ENR |= (1 << 3))
#define GPIOC_PCLCK_EN() ( RCC-> APB2ENR |= (1 << 4))

//Disable clock for GPIOx Port
#define GPIOA_PCLCK_DI() ( RCC-> APB2ENR &= ~(1 << 2))
#define GPIOB_PCLCK_DI() ( RCC-> APB2ENR &= ~(1 << 3))
#define GPIOC_PCLCK_DI() ( RCC-> APB2ENR &= ~(1 << 4))

// need to do SPI2 RegDef,SPI2bitPosition,Enable disable SPI2clock,


// SPI register structure
typedef struct
{
		volatile uint32_t CR1;
	    volatile uint32_t CR2;
	    volatile uint32_t SR;
	    volatile uint32_t DR;
	    volatile uint32_t CRCPR;
	    volatile uint32_t RXCRCR;
	    volatile uint32_t TXCRCR;
	    volatile uint32_t I2SCFGR;
	    volatile uint32_t I2SPR;
} SPI_RegDef_t;


#define SPI2 ((SPI_RegDef_t*)SPI2_BASEADDR)

//SPI2 clock enable
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1 << 14))

//SPI2 clock disable
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1 << 14))

//CR1 bit structure
#define SPI_CR1_CPHA 0
#define SPI_CR1_CPOL 1
#define SPI_CR1_MSTR 2
#define SPI_CR1_BR   3
#define SPI_CR1_SPE  6
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SSI  8
#define SPI_CR1_SSM  9
#define SPI_CR1_RXONLY 10
#define SPI_CR1_DFF  11
#define SPI_CR1_BIDIMODE 15

//SPI_SR bit structure
#define SPI_SR_RXNE    0
#define SPI_SR_TXE     1
#define SPI_SR_CHSIDE  2
#define SPI_SR_UDR     3
#define SPI_SR_CRCERR  4
#define SPI_SR_MODF    5
#define SPI_SR_OVR     6
#define SPI_SR_BSY     7

//nvic iser to enable interrupt
#define NVIC_ISER0   (*(volatile uint32_t*)0xE000E100)
#define NVIC_ISER1   (*(volatile uint32_t*)0xE000E104)


//nvic icer to clear/disable interupt
#define NVIC_ICER0   (*(volatile uint32_t*)0xE000E180)
#define NVIC_ICER1   (*(volatile uint32_t*)0xE000E184)


//IRQ numbers
#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40




#define SPI_RXNE_FLAG (1 << SPI_SR_RXNE)
#define SPI_TXE_FLAG (1 << SPI_SR_TXE)
#define SPI_BUSY_FLAG (1 << SPI_SR_BSY)

#define ENABLE 1
#define DISABLE 0
#define SET 1
#define RESET 0



#endif /* INC_STM32F103XX_H_ */
