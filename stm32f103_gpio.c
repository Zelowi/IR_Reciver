/*
 * stm32f103_gpio.c
 *
 *  Created on: Apr 10, 2026
 *      Author: Zelowi
 */
#include"stm32f103_gpio.h"



uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber){
	uint8_t Value;
	Value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return Value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value)
{
    if(value)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}


void GPIO_PCLKCoontrol(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi)
{
if(EnOrDi == ENABLE){
	if(pGPIOx == GPIOA){
		GPIOA_PCLCK_EN();
	}
	else if(pGPIOx == GPIOB){
		GPIOB_PCLCK_EN();
	}
	else if(pGPIOx == GPIOC){
			GPIOC_PCLCK_EN();
		}
}

else{
	if(pGPIOx == GPIOA){
			GPIOA_PCLCK_DI();
		}
		else if(pGPIOx == GPIOB){
			GPIOB_PCLCK_DI();
		}
		else if(pGPIOx == GPIOC){
					GPIOC_PCLCK_DI();
				}


}
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    // 1. Enable clock
    GPIO_PCLKCoontrol(pGPIOHandle->pGPIOx, ENABLE);

    uint32_t pin = pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber;
    uint32_t pos = (pin % 8) * 4;

    uint32_t config = 0;
    uint8_t mode = pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode;
    uint8_t cnf  = pGPIOHandle->GPIO_PinGonfig.GPIO_PinCNF;
    uint8_t speed = pGPIOHandle->GPIO_PinGonfig.GPIO_PinSpeed;

    uint8_t mode_bits = 0;

    // ================= MODE selection =================
    if(mode == GPIO_MODE_IN)
    {
        mode_bits = 0x0; // input mode
    }
    else // OUTPUT or ALTFN
    {
        mode_bits = speed; // 1,2,3
    }

    // ================= Build config =================
    config = (cnf << 2) | mode_bits;// it's stupid gpt soluting in crl/crh we have to bit for cnf and two bit for mode now we join
    //cnf and mode together to have 4 bits and to fill that in register

    // ================= Write to CRL / CRH =================
    if(pin < 8)
    {
        pGPIOHandle->pGPIOx->CRL &= ~(0xF << pos); // clear
        pGPIOHandle->pGPIOx->CRL |= (config << pos);
    }
    else
    {
        pGPIOHandle->pGPIOx->CRH &= ~(0xF << pos); // clear
        pGPIOHandle->pGPIOx->CRH |= (config << pos);
    }


}




