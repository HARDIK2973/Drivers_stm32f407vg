/*
 * 002_LED_User_Button.c
 *
 *  Created on: May 14, 2023
 *      Author: 91701
 */




#include <stdint.h>
#include "stm32f407xx.h"

#define Btn_Pressed HIGH
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
	GPIOled.pGPIOx = GPIOD;
	GPIOled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIOled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);

	GPIO_Init(&GPIOled);

		GPIOBtn.pGPIOx = GPIOA;
		GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
		GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
		GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
		GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOA, ENABLE);

		GPIO_Init(&GPIOBtn);



//    /* Loop forever */
	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)== Btn_Pressed)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		}


	}
	return 0;
}


