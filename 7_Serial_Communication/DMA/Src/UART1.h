/**
  ******************************************************************************
  * @file    UART1.h
  * @author  可可城
  * @version V1.0
  * @date    2016-01-28
  * @brief   UART1
  ******************************************************************************
  * @attention
  * UART1中断模式
  ******************************************************************************
  */

#ifndef __UART1_H
#define	__UART1_H

#include "stm32f1xx_hal.h"

extern uint8_t RxCompFlag;
extern uint8_t RxLength;
extern uint8_t RxBuff[100];
void UART1_Send_Date (void);

#endif
