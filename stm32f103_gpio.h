/*
 * stm32f103_gpio.h
 *
 *  Created on: Apr 10, 2026
 *      Author: Zelowi
 */

#ifndef INC_STM32F103_GPIO_H_
#define INC_STM32F103_GPIO_H_

#include "stm32f103xx.h"

#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_FT 4
#define GPIO_MODE_IT_RT 5
#define GPIO_MODE_IT_RFT 6


// Speed
#define GPIO_SPEED_10MHZ    1
#define GPIO_SPEED_2MHZ     2
#define GPIO_SPEED_50MHZ    3

// CNF (direct!)
#define GPIO_CNF_ANALOG         0
#define GPIO_CNF_FLOATING       1
#define GPIO_CNF_INPUT_PUPD     2

#define GPIO_CNF_GP_PP          0
#define GPIO_CNF_GP_OD          1
#define GPIO_CNF_AF_PP          2
#define GPIO_CNF_AF_OD          3


#define GPIO_PIN_NUMBER_0 0
#define GPIO_PIN_NUMBER_1 1
#define GPIO_PIN_NUMBER_2 2
#define GPIO_PIN_NUMBER_3 3
#define GPIO_PIN_NUMBER_4 4
#define GPIO_PIN_NUMBER_5 5
#define GPIO_PIN_NUMBER_6 6
#define GPIO_PIN_NUMBER_7 7
#define GPIO_PIN_NUMBER_8 8
#define GPIO_PIN_NUMBER_9 9
#define GPIO_PIN_NUMBER_10 10
#define GPIO_PIN_NUMBER_11 11
#define GPIO_PIN_NUMBER_12 12
#define GPIO_PIN_NUMBER_13 13
#define GPIO_PIN_NUMBER_14 14
#define GPIO_PIN_NUMBER_15 15


typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;   // INPUT / OUTPUT / AF
    uint8_t GPIO_PinSpeed;  // only for output
    uint8_t GPIO_PinCNF;    // use this to configure output type and who controll the pin
} GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t* pGPIOx;
	GPIO_PinConfig_t GPIO_PinGonfig;
}GPIO_Handle_t;




void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

void GPIO_PCLKCoontrol(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi);



uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t Value);
void IRQConfig(uint8_t IRQNumber,uint8_t EnOrDi);
void IRQHandling(uint8_t PinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);



#endif /* INC_STM32F103_GPIO_H_ */
