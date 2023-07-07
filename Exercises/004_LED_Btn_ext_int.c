/*
 * 005_LED_Btn_ext_int.c
 *
 *  Created on: May 17, 2023
 *      Author: 91701
 */



#include <stdint.h>
#include<string.h>
#include "stm32f407xx.h"


//#define Btn_Pressed LOW
//#define LOW 		0
//#define HIGH		1

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

	memset(&GPIOled,0,sizeof(GPIOled));
	memset(&GPIOBtn,0,sizeof(GPIOBtn));


	GPIOled.pGPIOx = GPIOD;
	GPIOled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIOled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIOled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOled.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD, ENABLE);

	GPIO_Init(&GPIOled);

	GPIOBtn.pGPIOx = GPIOD;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


		GPIO_PeriClockControl(GPIOD, ENABLE);

		GPIO_Init(&GPIOBtn);



//IRQ Configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5,NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI9_5, ENABLE);


	while(1);

}


void EXTI9_5_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}


