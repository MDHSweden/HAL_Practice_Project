/**
  ******************************************************************************
  * @file    IIC.h
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-31
  * @brief   IIC
  ******************************************************************************
  * @attention
  * �ṩģ��IIC�ӿ�
  ******************************************************************************
  */ 
	
#ifndef __IIC_H
#define __IIC_H

#include "stm32f1xx_hal.h"

void I2C_Transmit (uint8_t DevAddress, uint8_t * pData, uint16_t Size);
void I2C_Receive (uint8_t DevAddress, uint8_t * pData, uint16_t Size);
void I2C_Mem_Write (uint8_t DevAddress, uint8_t MemAddress, uint8_t * pData, uint16_t Size);
void I2C_Mem_Read (uint8_t DevAddress, uint8_t MemAddress, uint8_t * pData, uint16_t Size);

#endif
