/*
 * IR_Reciver.c
 *
 *  Created on: May 23, 2026
 *      Author: Zelowi
 */
#include "IR_Reciver.h"
#include "Timer.h"
#include <stdint.h>

volatile uint32_t ir_edge_count = 0;


volatile uint32_t previous_time = 0;

volatile uint32_t ir_timings[100];

volatile uint8_t ir_index = 0;


volatile uint8_t frame_done = 0;

volatile uint8_t frame_ready = 0;







void IR_IRQConfig(uint8_t IRQNumber,uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        if(IRQNumber < 32)
        {
            NVIC_ISER0 |= (1 << IRQNumber);
        }

        else if(IRQNumber < 64)
        {
            NVIC_ISER1 |=
                (1 << (IRQNumber % 32));
        }
    }

    else
    {
        if(IRQNumber < 32)
        {
            NVIC_ICER0 |=
                (1 << IRQNumber);
        }

        else if(IRQNumber < 64)
        {
            NVIC_ICER1 |=
                (1 << (IRQNumber % 32));
        }
    }
}

void IR_Init(GPIO_Handle_t *pGPIOHandle,uint8_t IRQ_Number){
	GPIO_Init(pGPIOHandle);
	RCC->APB2ENR |= (1 << 0);// enable afio clock


	uint8_t pin = pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber;
	uint8_t exticr_index = pin / 4;// we have exitcr[4] so here we decide which we need for our pin
	uint8_t exticr_pos   = (pin % 4) * 4;//here we decide which 4 bits we need to write
	uint8_t gpio_code = 0;

	if(pGPIOHandle->pGPIOx == GPIOA)
	{
	    gpio_code = 0;
	}
	else if(pGPIOHandle->pGPIOx == GPIOB)
	{
	    gpio_code = 1;
	}
	else if(pGPIOHandle->pGPIOx == GPIOC)
	{
	    gpio_code = 2;
	}


	/* Clear EXTIx port selection */
	AFIO->EXTICR[exticr_index] &= ~(0xF << exticr_pos);

	/* Set EXTIx port selection */
	AFIO->EXTICR[exticr_index] |= (gpio_code << exticr_pos);

	EXTI->IMR |= (1 << pin);// allow to request interrupt for chosen pin
	EXTI->FTSR |= (1 << pin);// triger interrupt when change from 1 to 0
	EXTI->RTSR |= (1 << pin);// triger interrupt when change from 0 to 1
	IR_IRQConfig(IRQ_Number ,ENABLE);



}

void IR_ProcessEdge()
{

	if(frame_ready){
	        return;
	}

    uint32_t now =
        Timer2_GetMicros();

    uint32_t duration =
        now - previous_time;

    previous_time = now;

    if(ir_index < 67)
    {
        ir_timings[ir_index++] = duration;
    }

    if(ir_index >= 67)
    {
        frame_ready = 1;
    	uint32_t wait_start = Timer2_GetMicros();
    	    while(Timer2_GetMicros() - wait_start < 120000)
    	    {
    	    }
    }

}


void EXTI0_IRQHandler(void)
	{
	IR_ProcessEdge();

	EXTI->PR |= (1<<0);
	}

uint32_t IR_DecodeTimings(void)
{
    uint32_t code = 0;
    uint8_t i = 3;

    for(uint8_t bit = 0; bit < 32; bit++)
    {
        uint32_t high_time = ir_timings[i + 1];

        if(high_time > 1200)
        {
            code |= (1UL << bit);
        }

        i += 2;
    }

    return code;
}
