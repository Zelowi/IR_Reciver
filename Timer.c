/*
 * Timer.c
 *
 *  Created on: May 23, 2026
 *      Author: Zelowi
 */

#include "timer.h"
#include "stm32f103xx.h"

void Timer2_Init_1MHz(void)
{
    // 1. Enable TIM2 clock
	TIM2_Enable();

    // 2. Stop timer before configuration
    TIM2->CR1 &= ~(1 << 0);

    // 3. Set prescaler
    // 72 MHz / (7 + 1) = 1 MHz
    TIM2->PSC = 7;//1 MHz means that timer count 1000000 times per second

    // 4. Set auto-reload to maximum
    // TIM2 is 32-bit on STM32F103
    TIM2->ARR = 0xFFFFFFFF;

    // 5. Reset counter
    TIM2->CNT = 0;

    // 6. Generate update event to load prescaler immediately
    TIM2->EGR |= (1 << 0);

    // 7. Start timer
    TIM2->CR1 |= (1 << 0);
}

uint32_t Timer2_GetMicros(void)
{
    return TIM2->CNT;
}

void Timer2_Reset(void)
{
    TIM2->CNT = 0;
}
