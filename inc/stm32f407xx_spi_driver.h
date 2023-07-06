/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: May 14, 2023
 *      Author: 91701
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"


/*
 * This is a Configuration structure for a SPI pin
 */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;			/*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t SPI_SclkSpeed;			/*!< possible values from @GPIO_PIN_SPEED >*/
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

/*
 * This is a Handle structure for a SPI pin
 */

typedef struct
{
	SPI_RegDef_t *pSPIx;       		/*!< This holds the base address of the GPIO port to which the pin belongs >*/
	SPI_Config_t SPI_PinConfig;   /*!< This holds GPIO pin configuration settings >*/
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxState;
	uint8_t RxState;
}SPI_Handle_t;



//@SPI_Devicemode
#define SPI_DEVICE_MODE_MASTER							1
#define SPI_DEVICE_MODE_SLAVE							0

//@SPI_Devicemode
#define SPI_BUS_CONFIG_FD								1
#define SPI_BUS_CONFIG_HD								2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY					3

//@SPI_SCLK
#define SPI_SCLK_SPEED_DIV2								0
#define SPI_SCLK_SPEED_DIV4								1
#define SPI_SCLK_SPEED_DIV8								2
#define SPI_SCLK_SPEED_DIV16							3
#define SPI_SCLK_SPEED_DIV32							4
#define SPI_SCLK_SPEED_DIV64							5
#define SPI_SCLK_SPEED_DIV128							6
#define SPI_SCLK_SPEED_DIV256							7

//@SPI_DFF
#define SPI_DFF_8BITS									0
#define SPI_DFF_16BITS									1

//CPOL
#define SPI_CPOL_HIGH									1
#define SPI_CPOL_LOW									0

//CPHA
#define SPI_CPHA_LOW									0
#define SPI_CPHA_HIGH									1

//SSM
#define SPI_SSM_EN										0
#define SPI_SSM_DI										1


//SPI related status registers

#define SPI_TXE_FLAG 			(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG 			(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG 			(1 << SPI_SR_BSY)


#define SPI_READY				0
#define SPI_BUSY_IN_RX			1
#define SPI_BUSY_IN_TX			2

//Possible SPI Application Event
#define SPI_EVENT_TX_CMPLT		1
#define SPI_EVENT_RX_CMPLT		2
#define SPI_EVENT_OVR_ERR		3
#define SPI_EVENT_CRC_ERR		4






/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/

/*
 * Peripheral Clock setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data send and receive
 */

void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer,uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer,uint32_t Len);


/*
* IRQ config and handle
*  */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

//other
void SPI_PeriPheralControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
void SPI_ClearovrFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmmison(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv);



#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
