/*
 * 004_LED_Btn_ext.c
 *
 *  Created on: May 17, 2023
 *      Author: 91701
 */




#include <stdint.h>
#include "stm32f407xx.h"

#define Btn_Pressed LOW
#define LOW 		0
#define HIGH		1

//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif

void delay(void)
{
	for(uint32_t i=0; i<500000/2;i++);
}

int main(void)
{
	GPIO_Handle_t GPIOled,GPIOBtn;
	GPIOled.pGPIOx = GPIOA;
	GPIOled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIOled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);

	GPIO_Init(&GPIOled);

		GPIOBtn.pGPIOx = GPIOB;
		GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
		GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
		GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOB, ENABLE);

		GPIO_Init(&GPIOBtn);



//    /* Loop forever */
	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12)== Btn_Pressed)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8);
		}


	}
	return 0;
}


