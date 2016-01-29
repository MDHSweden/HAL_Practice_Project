灯为PB0，低电平亮，按键PA0，按下为高电平。
另外该按键消抖时间较长，需要40ms。
常用操作：
GPIO_PinState HAL_GPIO_ReadPin (GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
void HAL_GPIO_WritePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
void HAL_GPIO_TogglePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin) //反转电平
HAL_StatusTypeDef HAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)    //锁引脚，复位才释放
void HAL_Delay (__IO uint32_t Delay)

另附：
Typedef enum
{
HAL_OK = 0x00,
HAL_ERROR = 0x01,
HAL_BUSY = 0x02,
HAL_TIMEOUT = 0x03
} HAL_StatusTypeDef;