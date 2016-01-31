/**
  ******************************************************************************
  * @file    UART.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-29
  * @brief   UART
  ******************************************************************************
  * @attention
  * 重新改写printf
  ******************************************************************************
  */ 
  
#include "UART.h" 

extern UART_HandleTypeDef huart1;

int fputc(int ch, FILE *f)                          //重定向printf
{ 	
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 10);
	return ch;
}

int fgetc(FILE *f)                                  //scanf没有验证，不能保证这个函数是对的
{
	uint8_t ch;
	HAL_UART_Receive(&huart1, &ch, 1, 10);
	return (int)ch;
}

/*********************************************END OF FILE**********************/
