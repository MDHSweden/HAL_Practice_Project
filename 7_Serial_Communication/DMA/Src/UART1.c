/**
  ******************************************************************************
  * @file    UART1.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-28
  * @brief   UART1
  ******************************************************************************
  * @attention
  * UART1 DMA模式
  ******************************************************************************
  */ 
  
#include "UART1.h" 

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

uint8_t RxCompFlag = 0; //0为没接收完毕，1为接收完毕
uint8_t RxLength = 0;
uint8_t TxLength = 0;
uint8_t RxBuff[100];
uint8_t TxBuff[100];

/**
  * @brief   UART1发送函数
  * @param   无
  * @retval  无
  */
void UART1_Send_Date (void)
{
	uint8_t i;
	if(RxCompFlag == 1)                                  //接收完毕
	{
		TxLength = RxLength;                               //这六行是将读的数据变成要发的数据，然后发送
		for(i=0;i<TxLength;i++)
		{
			TxBuff[i] = RxBuff[i];
		}
		HAL_UART_Transmit_DMA (&huart1, RxBuff, TxLength);
		RxCompFlag = 0;                                    //重置接收完成标志
		HAL_UART_Receive_DMA (&huart1, RxBuff, 100);       //发送完后开启接收
	}
}


/*********************************************END OF FILE**********************/
