使用ADC1 的通道0,1,2,3四个通道，引脚为PA0，PA1，PA2，PA3。
轮流读取，依次通过串口发送
常用操作：
HAL_StatusTypeDef HAL_ADC_ConfigChannel (ADC_HandleTypeDef * hadc, ADC_ChannelConfTypeDef * sConfig)
HAL_StatusTypeDef HAL_ADC_Start (ADC_HandleTypeDef * hadc)
HAL_StatusTypeDef HAL_ADC_Stop (ADC_HandleTypeDef * hadc)
HAL_StatusTypeDef HAL_ADC_PollForConversion (ADC_HandleTypeDef * hadc, uint32_t Timeout)
uint32_t HAL_ADC_GetValue (ADC_HandleTypeDef * hadc)