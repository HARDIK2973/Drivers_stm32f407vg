/*
 * stm32f407xx_rcc_driver.h
 *
 *  Created on: Jun 2, 2023
 *      Author: 91701
 */

#ifndef INC_STM32F407XX_RCC_DRIVER_H_
#define INC_STM32F407XX_RCC_DRIVER_H_

#include "stm32f407xx.h"


//This return APB1 Clk Value
uint32_t RCC_GetPCLK1Value(void);

//This return APB2 Clk Value
uint32_t RCC_GetPCLK2Value(void);

uint32_t  RCC_GetPLLOutputClock(void);

#endif /* INC_STM32F407XX_RCC_DRIVER_H_ */
