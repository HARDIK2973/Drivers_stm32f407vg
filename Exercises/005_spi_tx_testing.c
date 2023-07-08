/*
 * 003_spi_tx_testing.c
 *
 *  Created on: May 14, 2023
 *      Author: 91701
 */
#include "stm32f407xx.h"
#include <string.h>


/*-->PB15 as SPI2_MOSI
 *-->PB14 as SPI2_MISO
 *-->PB13 as SPI2_SCLK
 *-->PB12 as SPI2_NSS
 *-->ALT Function mode 5
 */

void SPI2_GpioInits(void)
{
	GPIO_Handle_t SPIpins;
	SPIpins.pGPIOx = GPIOB;
	SPIpins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIpins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIpins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIpins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIpins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIpins);

	//MOSI
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIpins);

//	//MISO
//	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
//	GPIO_Init(&SPIpins);
//
//	//NSS
//	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
//	GPIO_Init(&SPIpins);
}

void SPI2_Inits(void)
{
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_EN;
	SPI2Handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;

	SPI_Init(&SPI2Handle);
}

int main()
{
	char data[] = "Hello World";

	SPI2_GpioInits();

	SPI2_Inits();

	//this makes NSS signal internally high and avoid MODF error
	SPI_SSIConfig(SPI2,ENABLE);


	//enable SPI2 Peripheral
	SPI_PeriPheralControl(SPI2,ENABLE);


	SPI_SendData(SPI2, (uint8_t*)data, strlen(data));

	//lets conform SPI is not Busy
	while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));

	//Disable SPI2 Peripheral
	SPI_PeriPheralControl(SPI2,DISABLE);

	while(1);

	return 0;
}
