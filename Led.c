/*
 * Led.c
 *
 *  Created on: May 23, 2026
 *      Author: Zelowi
 */
#include "stdint.h"
#include "stm32f103_gpio.h"
#include "stm32f103xx.h"


void delay()
{
    for(volatile int i = 0; i < 500000; i++);
}

void LED_Init(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number){
	GPIO_Handle_t GPIOHandle;
	GPIOHandle.pGPIOx = pGPIOx;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinCNF = GPIO_CNF_GP_PP;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinNumber = Pin_Number;
	GPIO_Init(&GPIOHandle);
}
void LED_ON(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number){
	GPIO_WriteToOutputPin(pGPIOx,Pin_Number,1);
}
void LED_OFF(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number){
	GPIO_WriteToOutputPin(pGPIOx,Pin_Number,0);
}
void LED_Toggle(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number){
	pGPIOx->ODR ^= (1 << Pin_Number);
}
