利用系统时间和延时API控制LED灯，引脚PB0，低电平点亮。
具体为开机5s后亮灯，延时5s后灭灯。
常用操作：
uint32_t HAL_GetTick (void )  //得到系统运行时间，单位ms
void HAL_Delay (__IO uint32_t Delay) //单位ms

GPIO_PinState HAL_GPIO_ReadPin (GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
void HAL_GPIO_WritePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
void HAL_GPIO_TogglePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin) //反转电平
HAL_StatusTypeDef HAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)    //锁引脚，复位才释放