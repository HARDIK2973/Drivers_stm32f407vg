/*
 * 010_gpiofunctionality_test.c
 *
 *  Created on: Jun 21, 2023
 *      Author: 91701
 */

#include "stm32f407xx.h"
#include "gpiofunctions.h"

#include "spifunctions.h"
#include <string.h>

#define Btn_Pressed 		 HIGH



void delay(void)
{
	for(uint32_t i=0; i<500000;i++);
}

int main()
{

	while(1)
	{
	if(GPIORead(GPIOA, GPIO_PIN_NO_0)== Btn_Pressed)
	{
		delay();
		GPIOTogglePin(GPIOD, GPIO_PIN_NO_12);
	}

	GPIOWrite(GPIOD, GPIO_PIN_NO_12, HIGH, NO_PULLUP);


	}
}



