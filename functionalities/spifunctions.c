/*
 * spifunctions.c
 *
 *  Created on: Jul 4, 2023
 *      Author: 91701
 */
#include "stm32f407xx.h"


void SPI1Begin(void)
{
	GPIO_Handle_t SPI1pins;
	SPI1pins.pGPIOx = GPIOA;
	SPI1pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI1pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI1pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI1pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI1pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPI1pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPI1pins);

	//MOSI
	SPI1pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPI1pins);

	//MISO
	SPI1pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPI1pins);

	//NSS
	SPI1pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPI1pins);


	//SPI Init
	SPI_Handle_t SPI1Handle;
	SPI1Handle.pSPIx = SPI1;
	SPI1Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1Handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI1Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI1Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DI;
	SPI1Handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;

	SPI_Init(&SPI1Handle);

	//this makes NSS signal internally high and avoid MODF error
	SPI_SSIConfig(SPI1,ENABLE);

}

void SPI2Begin(void)
{
	GPIO_Handle_t SPI2pins;
	SPI2pins.pGPIOx = GPIOB;
	SPI2pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI2pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPI2pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI2pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI2pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPI2pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPI2pins);

	//MOSI
	SPI2pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI2pins);

	//MISO
	SPI2pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPI2pins);

	//NSS
	SPI2pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPI2pins);


	//SPI Init
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI1;
	SPI2Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DI;
	SPI2Handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;

	SPI_Init(&SPI2Handle);

	//this makes NSS signal internally high and avoid MODF error
	SPI_SSIConfig(SPI2,ENABLE);


	//enable SPI2 Peripheral
	SPI_PeriPheralControl(SPI2,ENABLE);

}

void SPI3Begin(void)
{
	GPIO_Handle_t SPI3pins;
	SPI3pins.pGPIOx = GPIOA;
	SPI3pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI3pins.GPIO_PinConfig.GPIO_PinAltFunMode = 6;
	SPI3pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI3pins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPI3pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//NSS
	SPI3pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPI3pins);

	//SCLK
	SPI3pins.pGPIOx = GPIOB;
	SPI3pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&SPI3pins);

	//MOSI
	SPI3pins.pGPIOx = GPIOB;
	SPI3pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPI3pins);

	//MISO
	SPI3pins.pGPIOx = GPIOB;
	SPI3pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPI3pins);




	//SPI Init
	SPI_Handle_t SPI3Handle;
	SPI3Handle.pSPIx = SPI3;
	SPI3Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI3Handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI3Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI3Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI3Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI3Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DI;
	SPI3Handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;

	SPI_Init(&SPI3Handle);

	//this makes NSS signal internally high and avoid MODF error
	SPI_SSIConfig(SPI3,ENABLE);


	//enable SPI2 Peripheral
	SPI_PeriPheralControl(SPI3,ENABLE);
}

void SPI1Send(uint8_t *data,uint32_t Len)
{
	//enable SPI1 Peripheral
	SPI_PeriPheralControl(SPI1,ENABLE);

	SPI_SendData(SPI1,data,Len);

	//lets conform SPI is not Busy
	while(SPI_GetFlagStatus(SPI1,SPI_BUSY_FLAG));

	//Disable SPI2 Peripheral
	SPI_PeriPheralControl(SPI1,DISABLE);
}

void SPI2Send(uint8_t *data,uint32_t Len)
{
	//enable SPI2 Peripheral
	SPI_PeriPheralControl(SPI2,ENABLE);

	SPI_SendData(SPI2,data,Len);

	//lets conform SPI is not Busy
	while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));

	//Disable SPI2 Peripheral
	SPI_PeriPheralControl(SPI2,DISABLE);
}

void SPI3Send(uint8_t *data,uint32_t Len)
{
	//enable SPI3 Peripheral
	SPI_PeriPheralControl(SPI3,ENABLE);

	SPI_SendData(SPI3,data,Len);

	//lets conform SPI is not Busy
	while(SPI_GetFlagStatus(SPI3,SPI_BUSY_FLAG));

	//Disable SPI2 Peripheral
	SPI_PeriPheralControl(SPI3,DISABLE);
}


