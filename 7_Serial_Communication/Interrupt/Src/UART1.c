/**
  ******************************************************************************
  * @file    UART1.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-28
  * @brief   UART1
  ******************************************************************************
  * @attention
  * UART1中断模式
  ******************************************************************************
  */ 
  
#include "UART1.h" 

extern UART_HandleTypeDef huart1;

uint8_t RxTemp;
uint8_t RxCount;
uint8_t TxCount;
uint32_t RxLastTime = 0; //最后一次接收到数据的时间
uint32_t TxLastTime = 0; //最后一次发送的接收的数据的时间，注意是接收的数据的时间，不是最后一次发送的时间
uint8_t RxBuff[100];
uint8_t TxBuff[100];

/**
  * @brief   UART1回调函数
  * @param   串口名字
  * @retval  无
  */
void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart)
{
	if(huart == &huart1)
	{
		if(HAL_GetTick() - RxLastTime >= 100)       //如果超过100ms认为另起一帧数据
		{
			RxCount = 0;
			RxBuff[0] = RxTemp;
		}
		else                                        //否则向接收缓存填充数据
		{
			RxCount++;
			RxBuff[RxCount] = RxTemp;
		}
		RxLastTime = HAL_GetTick();                 //记录了本次接收数据的时间
		HAL_UART_Receive_IT (&huart1, &RxTemp, 1);  //重开中断接收
	}
}

/**
  * @brief   UART1发送函数
  * @param   无
  * @retval  无
  */
void UART1_Send_Date (void)
{
	uint8_t i;
	if(HAL_GetTick() - RxLastTime >= 100)         //超过100ms认为接收完毕，开始发送接收到的数据
	{
		if(TxLastTime != RxLastTime)                //为避免重复发送相同数据，只有存在新数据时（也就是接收时间有更新时）才发送
		{
			TxCount = RxCount;
			for(i=0;i<=TxCount;i++)
			{
				TxBuff[i] = RxBuff[i];
			}
			TxLastTime = RxLastTime;                  //发送中断开启后，将发送时间与上次接收时间同步，意味着发送了最新接收时间的数据
			HAL_UART_Transmit_IT (&huart1, RxBuff, TxCount+1);
		}
	}
}


/*********************************************END OF FILE**********************/
