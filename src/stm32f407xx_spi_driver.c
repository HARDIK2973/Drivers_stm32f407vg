/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: May 14, 2023
 *      Author: 91701
 */
#include "stm32f407xx_spi_driver.h"
#include "stm32f407xx.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);


void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_EN();
			}else if (pSPIx == SPI2)
			{
				SPI2_PCLK_EN();
			}else if (pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}

		}
		else
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_DI();
			}else if (pSPIx == SPI2)
			{
				SPI2_PCLK_DI();
			}else if (pSPIx == SPI3)
			{
				SPI3_PCLK_DI();
			}


		}

}

void SPI_PeriPheralControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);

	}
}

//SSI COnfig
void SPI_SSIConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
		{
			pSPIx->CR1 |= (1 << SPI_CR1_SSI);
		}else
		{
			pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);

		}
}


/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// Peripheral clock enable
	SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);

	// Configure SPI_CR1 register
	uint32_t tempreg = 0;

	//1. CONFIGRE THE mode
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	//2. configre the bus confi
	if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//clear the bidi mode
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//set the bidi mode
		tempreg |= (1 << SPI_CR1_BIDIMODE);
	}else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//clear the bidi mode
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);

		//set the RX only bit

		tempreg |= (1 << SPI_CR1_RXONLY);
	}

	//3. configure the spi serial clock speed
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//4.Configure the DFF
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_DFF << SPI_CR1_DFF;

	//5.Configure the CPOL
	tempreg |= pSPIHandle->SPI_PinConfig.SPI_CPOL << SPI_CR1_CPOL;

	//6.Configure CPHA
	tempreg |=pSPIHandle->SPI_PinConfig.SPI_CPHA << SPI_CR1_CPHA;

	pSPIHandle->pSPIx->CR1 = tempreg;
}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
		if(pSPIx == SPI1)
		{
			 SPI1_REG_RESET();
		}else if(pSPIx == SPI2)
		{
			SPI2_REG_RESET();
		}else if(pSPIx == SPI3)
		{
			SPI3_REG_RESET();
		}
}

/*
 * Data send and receive
 */

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len)
{

	 while(Len != 0)
	 {
		 //wait until TXE is SET
		 while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == SPI_FLAG_RESET);


		 //2.CHeck the DFF bit in cr1

		 if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		 {
			 //16 bit DFF
			 ///1.load the data into DR
			 pSPIx->DR = *((uint16_t*)pTxBuffer);
			 Len--;
			 Len--;
			 (uint16_t*)pTxBuffer++;

		 }else
		 {
			 //8 bit DFF
			 //load data into DR
			 pSPIx->DR = *pTxBuffer;
			 Len--;
			 pTxBuffer++;

		 }
	 }
}


void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len)
{
	while(Len != 0)
		 {
			 //wait until TXE is SET
			 while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == SPI_FLAG_RESET);


			 //2.CHeck the DFF bit in cr1

			 if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
			 {
				 //16 bit DFF
				 ///1.load the data from DR to Rxbuffer
				  *((uint16_t*)pRxBuffer) = pSPIx->DR ;
				 Len--;
				 Len--;
				 (uint16_t*)pRxBuffer++;

			 }else
			 {
				 //8 bit DFF
				 //1.load the data from DR to Rxbuffer
				 *(pRxBuffer) = pSPIx->DR ;
				 Len--;
				 pRxBuffer++;

			 }
		 }

}

//SSOE Config
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
{
	pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
}else
{
	pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);

}

}

//send and receiver using Interrupt
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer,uint32_t Len)
{
	uint8_t state = pSPIHandle->TxState;

	if(state!= SPI_BUSY_IN_TX)
	{
	//1. Save TxBuffer address and Length information in global variable
	pSPIHandle->pTxBuffer = pTxBuffer;
	pSPIHandle->TxLen = Len;



	//2.Make SPI state busy in transmission so that
	//no other code take over  same SPI peripheral uint transmission is over
	pSPIHandle->TxState = SPI_BUSY_IN_TX;


	//3.Enable the TXEIE control bit to get interrupt when TXE flag is set in SR
	pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_TXEIE);


	//4.Data Transmmision will be handled by ISR

	}
	return state;
}


uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer,uint32_t Len)
{
	uint8_t state = pSPIHandle->RxState;

		if(state!= SPI_BUSY_IN_RX)
		{
		//1. Save TxBuffer address and Length information in global variable
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;


		//2.Make SPI state busy in transmission so that
		//no other code take over  same SPI peripheral uint transmission is over
		pSPIHandle->RxState = SPI_BUSY_IN_RX;


		//3.Enable the TXEIE control bit to get interrupt when TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_RXNEIE);


		//4.Data Transmision will be handled by ISR

		}
		return state;

}


/*
* IRQ config and handle
*  */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == ENABLE) {
		if (IRQNumber <= 31) {
			//program ISER0 register
			*NVIC_ISER0 |= (1 << IRQNumber);

		} else if (IRQNumber > 31 && IRQNumber < 64) //32 to 63
				{
			//program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		} else if (IRQNumber >= 64 && IRQNumber < 96) {
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= (1 << (IRQNumber % 64));
		}
	} else {
		if (IRQNumber <= 31) {
			//program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		} else if (IRQNumber > 31 && IRQNumber < 64) {
			//program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		} else if (IRQNumber >= 6 && IRQNumber < 96) {
			//program ICER2 register
			*NVIC_ICER3 |= (1 << (IRQNumber % 64));
		}
	}

}


void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{

	//1. first lets find out the ipr register
		uint8_t iprx = IRQNumber / 4;
		uint8_t iprx_section  = IRQNumber %4 ;

		uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

		*(  NVIC_PR_BASEADDR + iprx ) |=  ( IRQPriority << shift_amount );
}


void SPI_IRQHandling(SPI_Handle_t *pHandle)
{

	uint8_t temp1,temp2;
	//first check for TXE
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_TXE);
	temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		//handle TXE
		spi_txe_interrupt_handle(pHandle);
	}


		//first check for RXE
		temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
		temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);

		if(temp1 && temp2)
		{
			//handle RXNE
			spi_rxe_interrupt_handle(pHandle);
		}

		//check for OVR flag;
		temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);
		temp2 = pHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);

		if(temp1 && temp2)
				{
					//handle RXNE
					spi_ovr_err_interrupt_handle(pHandle);
				}
}

//some helper function
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	      //2.CHeck the DFF bit in cr1

			 if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
			 {
				 //16 bit DFF
				 ///1.load the data into DR
				 pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
				 pSPIHandle->TxLen--;
				 pSPIHandle->TxLen--;
				 (uint16_t*)pSPIHandle->pTxBuffer++;

			 }else
			 {
				 //8 bit DFF
				 //load data into DR
				 pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
				 pSPIHandle->TxLen--;
				 pSPIHandle->pTxBuffer++;

			 }

		if(!pSPIHandle->TxLen)
		{
			//TxLen is zzero , so close the transmmision and inform the application that TX is over
			//this prevents interrupts from setting up of TXE flag
			SPI_CloseTransmmison(pSPIHandle);

			SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);

		}

}

static void spi_rxe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	 //2.CHeck the DFF bit in cr1

				 if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
				 {
					 //16 bit DFF
					 ///1.load the data into DR
					 *((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
					 pSPIHandle->RxLen--;
					 pSPIHandle->RxLen--;
					 (uint16_t*)pSPIHandle->pRxBuffer--;

				 }else
				 {
					 //8 bit DFF
					 //load data into DR
					  *pSPIHandle->pTxBuffer= (uint8_t)pSPIHandle->pSPIx->DR ;
					 pSPIHandle->RxLen--;
					 pSPIHandle->pRxBuffer--;

				 }

			if(!pSPIHandle->RxLen)
			{
				//TxLen is zzero , so close the transmmision and inform the application that TX is over
				//this prevents interrupts from setting up of TXE flag
				SPI_CloseReception(pSPIHandle);

				SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);

			}


}

static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	//1. clr ovrr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{

	temp = pSPIHandle->pSPIx->DR;
	temp = pSPIHandle->pSPIx->SR;
	}
	(void)temp;
	//2. Inform the application
	SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);

}

void SPI_CloseTransmmison(SPI_Handle_t *pSPIHandle)
{
	    		pSPIHandle->pSPIx->CR2 &= ~(1 <<  SPI_CR2_TXEIE);
				pSPIHandle->pTxBuffer = NULL;
				pSPIHandle->TxLen = 0;
				pSPIHandle->TxState = SPI_READY;

}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 <<  SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;

}

void SPI_ClearovrFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv)
{

}

