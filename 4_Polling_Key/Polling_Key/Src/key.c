/**
  ******************************************************************************
  * @file    key.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-27
  * @brief   按键
  ******************************************************************************
  * @attention
  * 引脚PA0，按下为高电平
  ******************************************************************************
  */ 
  
#include "key.h" 

/**
  * @brief   检测按键是否按下
  * @param   无
  * @retval  按键状态
  */
uint8_t Key_Scan(void)
{
	if(HAL_GPIO_ReadPin (Key_GPIO_Port, Key_Pin) == GPIO_PIN_SET)         //如果按键按下
	{	   
		HAL_Delay(40);                                                      //延时20ms用于消抖
		if(HAL_GPIO_ReadPin (Key_GPIO_Port, Key_Pin) == GPIO_PIN_SET)       //如果按键真的按下
		{
			while(HAL_GPIO_ReadPin (Key_GPIO_Port, Key_Pin) == GPIO_PIN_SET); //等待按键释放
			return 	KEY_ON;	                                                  //返回按下
		}
		else
		{
			return KEY_OFF;                                                   //该错误一般不会出现，可以增加容错率
		}
	}
	else
	{
		return KEY_OFF;                                                     //按键没有按下则返回没有按下
	}
}

/*********************************************END OF FILE**********************/
