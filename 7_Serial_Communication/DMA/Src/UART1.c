/**
  ******************************************************************************
  * @file    UART1.c
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-28
  * @brief   UART1
  ******************************************************************************
  * @attention
  * UART1 DMAģʽ
  ******************************************************************************
  */ 
  
#include "UART1.h" 

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;

uint8_t RxCompFlag = 0; //0Ϊû������ϣ�1Ϊ�������
uint8_t RxLength = 0;
uint8_t TxLength = 0;
uint8_t RxBuff[100];
uint8_t TxBuff[100];

/**
  * @brief   UART1���ͺ���
  * @param   ��
  * @retval  ��
  */
void UART1_Send_Date (void)
{
	uint8_t i;
	if(RxCompFlag == 1)                                  //�������
	{
		TxLength = RxLength;                               //�������ǽ��������ݱ��Ҫ�������ݣ�Ȼ����
		for(i=0;i<TxLength;i++)
		{
			TxBuff[i] = RxBuff[i];
		}
		HAL_UART_Transmit_DMA (&huart1, RxBuff, TxLength);
		RxCompFlag = 0;                                    //���ý�����ɱ�־
		HAL_UART_Receive_DMA (&huart1, RxBuff, 100);       //�������������
	}
}


/*********************************************END OF FILE**********************/
