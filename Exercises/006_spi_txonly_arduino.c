#include "stm32f407xx.h"
#include <string.h>

/*-->PB15 as SPI2_MOSI
 *-->PB14 as SPI2_MISO
 *-->PB13 as SPI2_SCLK
 *-->PB12 as SPI2_NSS
 *-->ALT Function mode 5
 */
void delay(void) {
	for (uint32_t i = 0; i < 500000 / 2; i++);
}

void GPIO_ButtonInit(void);

void SPI2_GpioInits(void) {
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
	SPIpins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIpins);
}

void SPI2_Inits(void) {
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DI; //Hardware
	SPI2Handle.SPI_PinConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;

	SPI_Init(&SPI2Handle);
}

int main() {
	char user_data[] = "Hello World";

	GPIO_ButtonInit();

	SPI2_GpioInits();

	SPI2_Inits();

	SPI_SSOEConfig(SPI2, ENABLE);

	while (1) {
		while (!GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));

		delay();

		//enable SPI2 Peripheral
		SPI_PeriPheralControl(SPI2, ENABLE);

		//first send length information
		//	uint8_t datalen = strlen(user_data);
		//	SPI_SendData(SPI2, &datalen, 1);

		SPI_SendData(SPI2, (uint8_t*) user_data, strlen(user_data));

		//lets conform SPI is not Busy
		while (SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG))
			;

		//Disable SPI2 Peripheral
		SPI_PeriPheralControl(SPI2, DISABLE);
	}

	return 0;
}

void GPIO_ButtonInit(void) {
	GPIO_Handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOA, ENABLE);

	GPIO_Init(&GPIOBtn);
}

/*
 * 004_spi_txonly_arduino.c
 *
 *  Created on: May 23, 2023
 *
 *      Author: 91701
 */

