/**
  ******************************************************************************
  * @file    UART1.c
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-28
  * @brief   UART1
  ******************************************************************************
  * @attention
  * UART1�ж�ģʽ
  ******************************************************************************
  */ 
  
#include "UART1.h" 

extern UART_HandleTypeDef huart1;

uint8_t RxTemp;
uint8_t RxCount;
uint8_t TxCount;
uint32_t RxLastTime = 0; //���һ�ν��յ����ݵ�ʱ��
uint32_t TxLastTime = 0; //���һ�η��͵Ľ��յ����ݵ�ʱ�䣬ע���ǽ��յ����ݵ�ʱ�䣬�������һ�η��͵�ʱ��
uint8_t RxBuff[100];
uint8_t TxBuff[100];

/**
  * @brief   UART1�ص�����
  * @param   ��������
  * @retval  ��
  */
void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart)
{
	if(huart == &huart1)
	{
		if(HAL_GetTick() - RxLastTime >= 100)       //�������100ms��Ϊ����һ֡����
		{
			RxCount = 0;
			RxBuff[0] = RxTemp;
		}
		else                                        //��������ջ����������
		{
			RxCount++;
			RxBuff[RxCount] = RxTemp;
		}
		RxLastTime = HAL_GetTick();                 //��¼�˱��ν������ݵ�ʱ��
		HAL_UART_Receive_IT (&huart1, &RxTemp, 1);  //�ؿ��жϽ���
	}
}

/**
  * @brief   UART1���ͺ���
  * @param   ��
  * @retval  ��
  */
void UART1_Send_Date (void)
{
	uint8_t i;
	if(HAL_GetTick() - RxLastTime >= 100)         //����100ms��Ϊ������ϣ���ʼ���ͽ��յ�������
	{
		if(TxLastTime != RxLastTime)                //Ϊ�����ظ�������ͬ���ݣ�ֻ�д���������ʱ��Ҳ���ǽ���ʱ���и���ʱ���ŷ���
		{
			TxCount = RxCount;
			for(i=0;i<=TxCount;i++)
			{
				TxBuff[i] = RxBuff[i];
			}
			TxLastTime = RxLastTime;                  //�����жϿ����󣬽�����ʱ�����ϴν���ʱ��ͬ������ζ�ŷ��������½���ʱ�������
			HAL_UART_Transmit_IT (&huart1, RxBuff, TxCount+1);
		}
	}
}


/*********************************************END OF FILE**********************/
