/**
  ******************************************************************************
  * @file    ADC.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-29
  * @brief   ADC1
  ******************************************************************************
  * @attention
  * ADC1轮询模式
  ******************************************************************************
  */ 
 
#include "ADC.h" 

extern ADC_HandleTypeDef hadc1;

uint32_t ADC_Value[4];
uint8_t ADC_Count = 0;
uint8_t ADC_Flag = 0;

/**
  * @brief   ADC中断回调函数
  * @param   无
  * @retval  无
  */
void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc)
{
	if(hadc == &hadc1)
	{
		ADC_Value[ADC_Count] = HAL_ADC_GetValue (&hadc1);
		ADC_Flag = 1;
	}
}

/**
  * @brief   ADC中断开启
  * @param   无
  * @retval  无
  */
void ADC_Start(void)
{
	if(ADC_Flag == 1)
	{
		ADC_Flag = 0;
		ADC_Count++;
		if(ADC_Count == 4)
		{
			printf("%d,%d,%d,%d\r\n",ADC_Value[0],ADC_Value[1],ADC_Value[2],ADC_Value[3]);
			ADC_Count = 0;
		}
		ADC_ChannelConfTypeDef sConfig;
		sConfig.Rank = 1;
		sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
		sConfig.Channel = ADC_CHANNEL_0;
		switch(ADC_Count)
		{
			case 0 : sConfig.Channel = ADC_CHANNEL_0;break;
			case 1 : sConfig.Channel = ADC_CHANNEL_1;break;
			case 2 : sConfig.Channel = ADC_CHANNEL_2;break;
			case 3 : sConfig.Channel = ADC_CHANNEL_3;break;
		}
		HAL_ADC_ConfigChannel (&hadc1, &sConfig);
		HAL_ADC_Start_IT (&hadc1);
	}
}

/*********************************************END OF FILE**********************/
