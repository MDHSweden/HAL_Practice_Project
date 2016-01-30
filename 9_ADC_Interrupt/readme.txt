使用ADC1 的通道0,1,2,3四个通道，引脚为PA0，PA1，PA2，PA3。
轮流读取，依次通过串口发送。
在回调函数中配置ADC通道会导致ADC不可用，也有可能是我弄得不对。
在回调函数中再次开启ADC可行，但配置通道就不可行，因此只能制作标志位，在主函数中查询开启新中断。
常用操作：
HAL_StatusTypeDef HAL_ADC_ConfigChannel (ADC_HandleTypeDef * hadc, ADC_ChannelConfTypeDef * sConfig)
HAL_StatusTypeDef HAL_ADC_Start_IT (ADC_HandleTypeDef * hadc)
HAL_StatusTypeDef HAL_ADC_Stop_IT (ADC_HandleTypeDef * hadc)
uint32_t HAL_ADC_GetValue (ADC_HandleTypeDef * hadc)
void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef * hadc)
