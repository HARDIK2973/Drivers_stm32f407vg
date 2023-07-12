/*
 * gpiofunctions.c
 *
 *  Created on: Jun 21, 2023
 *      Author: 91701
 */
#include "gpiofunctions.h"



void GPIOWrite(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber,uint8_t high_low,uint8_t PUPD)
{

	GPIO_Handle_t GPIOPeripheral;
	GPIOPeripheral.pGPIOx = pGPIOx;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;

	switch (PUPD)
	{
	case 0:
		GPIOPeripheral.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
		break;
	case 1:
		GPIOPeripheral.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
		break;
	case 2:
		GPIOPeripheral.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;
		break;
	}


	GPIO_Init(&GPIOPeripheral);

	if(high_low == HIGH)
	{
	GPIO_WriteToOutputPin(pGPIOx, GPIO_PinNumber,GPIO_PIN_SET );
	}
	else
	{
		GPIO_WriteToOutputPin(pGPIOx, GPIO_PinNumber,GPIO_PIN_RESET );
	}

}

void GPIOTogglePin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber)
{

	GPIO_Handle_t GPIOPeripheral;
	GPIOPeripheral.pGPIOx = pGPIOx;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Init(&GPIOPeripheral);

	GPIO_ToggleOutputPin(pGPIOx, GPIO_PinNumber);

}

uint8_t GPIORead(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber)
{

	GPIO_Handle_t GPIOPeripheral;
	GPIOPeripheral.pGPIOx = pGPIOx;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNumber;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOPeripheral.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Init(&GPIOPeripheral);

	uint8_t value;

	value = GPIO_ReadFromInputPin(pGPIOx, GPIO_PinNumber);

	return value;

}



