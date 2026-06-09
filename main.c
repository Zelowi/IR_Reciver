/*
 * clap.c
 *
 *  Created on: May 17, 2026
 *      Author: Zelowi
 */


#include "stm32f103_gpio.h"
#include "stm32f103xx.h"
#include "IR_Reciver.h"
#include "Timer.h"
#include <stdint.h>
#include "Led.h"

/*void LED_ON(){
	GPIO_PCLKCoontrol(GPIOC,ENABLE);
	GPIOC->CRH &= ~((0xf << (GPIO_PIN_NUMBER_13 - 8) * 4));// clear
	GPIOC->CRH |= (0x2 << ((GPIO_PIN_NUMBER_13 - 8) * 4));
	GPIOC->ODR &= ~(1 << GPIO_PIN_NUMBER_13);

}
void LED_OFF(){
	GPIO_PCLKCoontrol(GPIOC,ENABLE);
	GPIOC->CRH &= ~((0xf << (GPIO_PIN_NUMBER_13 - 8) * 4));// clear
	GPIOC->CRH |= (0x2 << ((GPIO_PIN_NUMBER_13 - 8) * 4));
	GPIOC->ODR |= (1 << GPIO_PIN_NUMBER_13);

}*/

void GPIOInitClap(){

	GPIO_Handle_t GPIOHandle;
	GPIOHandle.pGPIOx = GPIOA;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinCNF = GPIO_CNF_FLOATING;
	GPIOHandle.GPIO_PinGonfig.GPIO_PinNumber = GPIO_PIN_NUMBER_0;
	GPIO_Init(&GPIOHandle);

}



int main(){

	uint32_t last_toggle = 0;
	uint8_t blink_mode = 0;
	uint32_t code = 0;

    GPIO_Handle_t IRPin;
    IRPin.pGPIOx = GPIOA;
    IRPin.GPIO_PinGonfig.GPIO_PinNumber = GPIO_PIN_NUMBER_0;
    IRPin.GPIO_PinGonfig.GPIO_PinMode = GPIO_MODE_IN;
    IRPin.GPIO_PinGonfig.GPIO_PinCNF = GPIO_CNF_FLOATING;
    IRPin.GPIO_PinGonfig.GPIO_PinSpeed = GPIO_SPEED_10MHZ;

    Timer2_Init_1MHz();


    IR_Init(&IRPin,IRQ_NO_EXTI0 );
    LED_Init(GPIOA, GPIO_PIN_NUMBER_2);

    while(1)
    {
    	if(frame_ready)
    	{
    	    code = IR_DecodeTimings();

    	    ir_index = 0;
    	    frame_ready = 0;
    	}

    	    if(code == IR_BUTTON_1)
    	        	{
    	        	    blink_mode = 0;
    	        	    LED_ON(GPIOA, GPIO_PIN_NUMBER_2);
    	        	    //code = 0;
    	        	}

    	        	if(code == IR_BUTTON_2)
    	        	{
    	        	    blink_mode = 0;
    	        	    LED_OFF(GPIOA, GPIO_PIN_NUMBER_2);
    	        	   // code = 0;
    	        	}

    	        	if(code == IR_BUTTON_3)
    	        	{
    	        	    blink_mode = 1;
    	        	    code = 0;
    	        	}

    	        	if(blink_mode)
    	        	    	{
    	        	    	    if(Timer2_GetMicros() - last_toggle > 50000)
    	        	    	    {
    	        	    	        LED_Toggle(GPIOA, GPIO_PIN_NUMBER_2);
    	        	    	        last_toggle = Timer2_GetMicros();
    	        	    	    }
    	        	    	}


    }








}
