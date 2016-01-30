/**
  ******************************************************************************
  * @file    ADC.c
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-29
  * @brief   ADC1
  ******************************************************************************
  * @attention
  * ADC1��ѯģʽ
  ******************************************************************************
  */ 
 
#include "ADC.h" 

extern ADC_HandleTypeDef hadc1;

uint32_t ADC_Value[4];

/**
  * @brief   ADC1�ĸ�ͨ��������ȡһ��
  * @param   ��
  * @retval  ��
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
