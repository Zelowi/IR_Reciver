/*
 * Led.h
 *
 *  Created on: May 23, 2026
 *      Author: Zelowi
 */

#ifndef INC_LED_H_
#define INC_LED_H_

void LED_Init(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number);
void LED_ON(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number);
void LED_OFF(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number);
void LED_Toggle(GPIO_RegDef_t *pGPIOx, uint8_t Pin_Number);

#endif /* INC_LED_H_ */
