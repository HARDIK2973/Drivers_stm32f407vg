/*
 * gpiofunctions.h
 *
 *  Created on: Jun 21, 2023
 *      Author: 91701
 */


#ifndef GPIOFUNCTIONS_H_
#define GPIOFUNCTIONS_H_

#include "stm32f407xx.h"

#define HIGH	GPIO_PIN_SET
#define LOW		GPIO_PIN_RESET

#define NO_PULLUP	GPIO_NO_PUPD
#define PULLUP		GPIO_PIN_PU
#define PULLDOWN	GPIO_PIN_PD

void GPIOWrite(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber,uint8_t high_low,uint8_t PUPD);

void GPIOTogglePin(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber);

uint8_t GPIORead(GPIO_RegDef_t *pGPIOx,uint8_t GPIO_PinNumber);


#endif /* GPIOFUNCTIONS_H_ */
