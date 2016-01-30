使用ADC1 的通道0,1,2,3四个通道，引脚为PA0，PA1，PA2，PA3。
使用DMA的方式重复读取四个通道的数据。
对于单一ADC多通道连续读取，使用DMA非常简洁，而单ADC单通道使用轮询和中断也很简洁，但切换通道不是轮询和中断擅长的。
常用操作：
HAL_StatusTypeDef HAL_ADC_Start_DMA (ADC_HandleTypeDef * hadc, uint32_t * pData, uint32_t Length)
HAL_StatusTypeDef HAL_ADC_Stop_DMA (ADC_HandleTypeDef * hadc)
