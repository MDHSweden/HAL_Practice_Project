/**
  ******************************************************************************
  * @file    IIC.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-31
  * @brief   IIC
  ******************************************************************************
  * @attention
  * 提供模拟IIC接口
  ******************************************************************************
  */

#include "IIC.h"

#define I2C_SCL_1()  HAL_GPIO_WritePin (SCL_GPIO_Port, SCL_Pin, GPIO_PIN_SET)
#define I2C_SCL_0()  HAL_GPIO_WritePin (SCL_GPIO_Port, SCL_Pin, GPIO_PIN_RESET)
#define I2C_SDA_1()  HAL_GPIO_WritePin (SDA_GPIO_Port, SDA_Pin, GPIO_PIN_SET)
#define I2C_SDA_0()  HAL_GPIO_WritePin (SDA_GPIO_Port, SDA_Pin, GPIO_PIN_RESET)
#define I2C_SDA_READ()  HAL_GPIO_ReadPin (SDA_GPIO_Port, SDA_Pin)

/**
  * @brief   IIC延时
  * @param   无
  * @retval  无
  */
static void i2c_Delay(void)
{
	uint8_t i;
	for(i=0;i<10;i++);
}

/**
  * @brief   IIC开始信号
  * @param   无
  * @retval  无
  */
void i2c_Start(void)
{
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/**
  * @brief   IIC停止信号
  * @param   无
  * @retval  无
  */
void i2c_Stop(void)
{
	I2C_SDA_0();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_1();
}

/**
  * @brief   发送一字节数据
  * @param   一字节数据
  * @retval  无
  */
void i2c_SendByte(uint8_t data)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{		
		if(data & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();	
		I2C_SCL_0();
		if(i == 7)
		{
			 I2C_SDA_1();
		}
		data <<= 1;
		i2c_Delay();
	}
}

/**
  * @brief   读取一字节数据
  * @param   无
  * @retval  一字节数据
  */
uint8_t i2c_ReadByte(void)
{
	uint8_t i;
	uint8_t data;
	data = 0;
	for(i=0;i<8;i++)
	{
		data <<= 1;
		I2C_SCL_1();
		i2c_Delay();
		if(I2C_SDA_READ())
		{
			data++;
		}
		I2C_SCL_0();
		i2c_Delay();
	}
	return data;
}

/**
  * @brief   等待从设备响应
  * @param   无
  * @retval  1成功，0失败
  */
uint8_t i2c_WaitAck(void)
{
	uint8_t status;
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	if (I2C_SDA_READ())
	{
		status = 1;
	}
	else
	{
		status = 0;
	}
	I2C_SCL_0();
	i2c_Delay();
	return status;
}

/**
  * @brief   产生要求响应信号
  * @param   无
  * @retval  无
  */
void i2c_Ack(void)
{
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	I2C_SDA_1();
}

/**
  * @brief   要求从设备不再响应
  * @param   无
  * @retval  无
  */
void i2c_NAck(void)
{
	I2C_SDA_1();
	i2c_Delay();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();	
}

/**
  * @brief  IIC发送
  * @param  设备地址，数据指针，字节数
  * @retval 无
  */
void I2C_Transmit (uint8_t DevAddress, uint8_t * pData, uint16_t Size)
{
	i2c_Start();
	i2c_SendByte(DevAddress);
	i2c_WaitAck();
	while(Size--)
	{
		i2c_SendByte(*pData++);
		i2c_WaitAck();
	}
	i2c_Stop();
}

/**
  * @brief  IIC接收
  * @param  设备地址，数据指针，字节数
  * @retval 无
  */
void I2C_Receive (uint8_t DevAddress, uint8_t * pData, uint16_t Size)
{
	i2c_Start();
	i2c_SendByte(DevAddress);
	i2c_WaitAck();
	i2c_Start();
	i2c_SendByte(DevAddress + 1);
	i2c_WaitAck();
	while(Size--)
	{
		*pData++ = i2c_ReadByte();
		if(Size != 0)
		{
			i2c_Ack();
		}
		else
		{
			i2c_NAck();
		}
	}
	i2c_Stop();
}

/**
  * @brief  IIC写内存
  * @param  设备地址，内存地址，数据指针，字节数
  * @retval 无
  */
void I2C_Mem_Write (uint8_t DevAddress, uint8_t MemAddress, uint8_t * pData, uint16_t Size)
{
	i2c_Start();
	i2c_SendByte(DevAddress);
	i2c_WaitAck();
	i2c_SendByte(MemAddress);
	i2c_WaitAck();
	while(Size--)
	{
		i2c_SendByte(*pData++);
		i2c_WaitAck();
	}
	i2c_Stop();
}

/**
  * @brief  IIC读内存
  * @param  设备地址，内存地址，数据指针，字节数
  * @retval 无
  */
void I2C_Mem_Read (uint8_t DevAddress, uint8_t MemAddress, uint8_t * pData, uint16_t Size)
{
	i2c_Start();
	i2c_SendByte(DevAddress);
	i2c_WaitAck();
	i2c_SendByte(MemAddress);
	i2c_WaitAck();
	i2c_Start();
	i2c_SendByte(DevAddress + 1);
	i2c_WaitAck();
	while(Size--)
	{
		*pData++ = i2c_ReadByte();
		if(Size != 0)
		{
			i2c_Ack();
		}
		else
		{
			i2c_NAck();
		}
	}
	i2c_Stop();
}

/************************************END OF FILE*******************************/
