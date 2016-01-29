/**
  ******************************************************************************
  * @file    key.c
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-27
  * @brief   ����
  ******************************************************************************
  * @attention
  * ����PA0������Ϊ�ߵ�ƽ
  ******************************************************************************
  */ 
  
#include "key.h" 

/**
  * @brief   ��ⰴ���Ƿ���
  * @param   ��
  * @retval  ����״̬
  */
uint8_t Key_Scan(void)
{
	if(HAL_GPIO_ReadPin (Key_GPIO_Port, Key_Pin) == GPIO_PIN_SET)         //�����������
	{	   
		HAL_Delay(40);                                                      //��ʱ20ms��������
		if(HAL_GPIO_ReadPin (Key_GPIO_Port, Key_Pin) == GPIO_PIN_SET)       //���������İ���
		{
			while(HAL_GPIO_ReadPin (Key_GPIO_Port, Key_Pin) == GPIO_PIN_SET); //�ȴ������ͷ�
			return 	KEY_ON;	                                                  //���ذ���
		}
		else
		{
			return KEY_OFF;                                                   //�ô���һ�㲻����֣����������ݴ���
		}
	}
	else
	{
		return KEY_OFF;                                                     //����û�а����򷵻�û�а���
	}
}

/*********************************************END OF FILE**********************/
