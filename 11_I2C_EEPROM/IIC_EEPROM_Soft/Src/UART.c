/**
  ******************************************************************************
  * @file    UART.c
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-29
  * @brief   UART
  ******************************************************************************
  * @attention
  * ���¸�дprintf
  ******************************************************************************
  */ 
  
#include "UART.h" 

extern UART_HandleTypeDef huart1;

int fputc(int ch, FILE *f)                          //�ض���printf
{ 	
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 10);
	return ch;
}

int fgetc(FILE *f)                                  //scanfû����֤�����ܱ�֤��������ǶԵ�
{
	uint8_t ch;
	HAL_UART_Receive(&huart1, &ch, 1, 10);
	return (int)ch;
}

/*********************************************END OF FILE**********************/
