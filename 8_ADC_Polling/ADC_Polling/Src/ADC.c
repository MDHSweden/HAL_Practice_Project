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

/**
  * @brief   ADC1四个通道轮流读取一次
  * @param   无
  * @retval  无
  */
void ADC_GetValue (void)
{
	ADC_ChannelConfTypeDef sConfig;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
	
	sConfig.Channel = ADC_CHANNEL_0;
	HAL_ADC_ConfigChannel (&hadc1, &sConfig);
	HAL_ADC_Start (&hadc1);
	if(HAL_ADC_PollForConversion (&hadc1, HAL_MAX_DELAY) == HAL_OK)
	{
		ADC_Value[0] = HAL_ADC_GetValue (&hadc1);
	}
	HAL_ADC_Stop (&hadc1);

	sConfig.Channel = ADC_CHANNEL_1;
	HAL_ADC_ConfigChannel (&hadc1, &sConfig);
	HAL_ADC_Start (&hadc1);
	if(HAL_ADC_PollForConversion (&hadc1, HAL_MAX_DELAY) == HAL_OK)
	{
		ADC_Value[1] = HAL_ADC_GetValue (&hadc1);
	}
	HAL_ADC_Stop (&hadc1);
	
	sConfig.Channel = ADC_CHANNEL_2;
	HAL_ADC_ConfigChannel (&hadc1, &sConfig);
	HAL_ADC_Start (&hadc1);
	if(HAL_ADC_PollForConversion (&hadc1, HAL_MAX_DELAY) == HAL_OK)
	{
		ADC_Value[2] = HAL_ADC_GetValue (&hadc1);
	}
	HAL_ADC_Stop (&hadc1);
	
	sConfig.Channel = ADC_CHANNEL_3;
	HAL_ADC_ConfigChannel (&hadc1, &sConfig);
	HAL_ADC_Start (&hadc1);
	if(HAL_ADC_PollForConversion (&hadc1, HAL_MAX_DELAY) == HAL_OK)
	{
		ADC_Value[3] = HAL_ADC_GetValue (&hadc1);
	}
	HAL_ADC_Stop (&hadc1);
}

/*********************************************END OF FILE**********************/
