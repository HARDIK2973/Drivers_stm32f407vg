/*
 * spifunctions.h
 *
 *  Created on: Jul 4, 2023
 *      Author: 91701
 */
#include "stm32f407xx.h"


#ifndef SPIFUNCTIONS_H_
#define SPIFUNCTIONS_H_


void SPI1Begin(void);
void SPI2Begin(void);
void SPI3Begin(void);

void SPI1Send(uint8_t *data,uint32_t Len);
void SPI2Send(uint8_t *data,uint32_t Len);
void SPI3Send(uint8_t *data,uint32_t Len);


#endif /* SPIFUNCTIONS_H_ */
