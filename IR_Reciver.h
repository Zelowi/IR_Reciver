/*
 * IR_Reciver.h
 *
 *  Created on: May 23, 2026
 *      Author: Zelowi
 */

#ifndef INC_IR_RECIVER_H_
#define INC_IR_RECIVER_H_
#include <stdint.h>
#include "stm32f103_gpio.h"


#define IR_BUTTON_1  0xEE11FB04
#define IR_BUTTON_2  0xED12FB04
#define IR_BUTTON_3  0xEC13FB04




extern volatile uint8_t ir_index;

extern volatile uint8_t frame_ready;


extern volatile uint32_t ir_timings[100];

void IR_Init(GPIO_Handle_t *pGPIOHandle,uint8_t IRQ_Number);
void IR_ProcessEdge(void);
uint32_t IR_DecodeTimings(void);

uint8_t IR_CommandAvailable(void);
uint32_t IR_GetCommand(void);


 void IR_IRQConfig(uint8_t IRQNumber,uint8_t EnOrDi);
 //void IR_IRQHandling(IR_Handle_t *pHandle);
 void IR_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

#endif /* INC_IR_RECIVER_H_ */
