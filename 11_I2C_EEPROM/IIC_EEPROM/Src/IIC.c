/**
  ******************************************************************************
  * @file    IIC.c
  * @author  可可城
  * @version V1.0
  * @date    2016-01-31
  * @brief   IIC读取EEPROM
  ******************************************************************************
  * @attention
  ******************************************************************************
  */ 

#include "IIC.h"

#define I2C_PageSize           8
#define  EEP_Firstpage      0x00

extern I2C_HandleTypeDef hi2c1;

uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];
uint16_t EEPROM_ADDRESS = 0xA0;

/**
  * @brief   在EEPROM的一个写循环中可以写多个字节，但一次写入的字节数
  *          不能超过EEPROM页的大小，AT24C02每页有8个字节
  * @param   
  *		@arg pBuffer:缓冲区指针
  *		@arg WriteAddr:写地址
  *   @arg NumByteToWrite:写的字节数
  * @retval  无
  */
void I2C_EE_PageWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite)
{
	HAL_I2C_Mem_Write (&hi2c1, EEPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToWrite, HAL_MAX_DELAY);
}

/**
  * @brief   从EEPROM里面读取一块数据 
  * @param   
  *		@arg pBuffer:存放从EEPROM读取的数据的缓冲区指针
  *		@arg ReadAddr:接收数据的EEPROM的地址
  *   @arg NumByteToWrite:要从EEPROM读取的字节数
  * @retval  无
  */
void I2C_EE_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
	HAL_I2C_Mem_Read (&hi2c1, EEPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToRead, HAL_MAX_DELAY);
}

/**
  * @brief   将缓冲区中的数据写到I2C EEPROM中
  * @param   
  *		@arg pBuffer:缓冲区指针
  *		@arg WriteAddr:写地址
  *   @arg NumByteToWrite:写的字节数
  * @retval  无
  */
void I2C_EE_BufferWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

  Addr = WriteAddr % I2C_PageSize;
  count = I2C_PageSize - Addr;
  NumOfPage =  NumByteToWrite / I2C_PageSize;
  NumOfSingle = NumByteToWrite % I2C_PageSize;
 
  /* If WriteAddr is I2C_PageSize aligned  */
  if(Addr == 0) 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage == 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
    /* If NumByteToWrite > I2C_PageSize */
    else  
    {
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize); 
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
				HAL_Delay(8);
      }
      if(NumOfSingle!=0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
  /* If WriteAddr is not I2C_PageSize aligned  */
  else 
  {
    /* If NumByteToWrite < I2C_PageSize */
    if(NumOfPage== 0) 
    {
      I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
    /* If NumByteToWrite > I2C_PageSize */
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / I2C_PageSize;
      NumOfSingle = NumByteToWrite % I2C_PageSize;	
      if(count != 0)
      {  
        I2C_EE_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr += count;
        pBuffer += count;
				HAL_Delay(8);
      }
      while(NumOfPage--)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
        WriteAddr +=  I2C_PageSize;
        pBuffer += I2C_PageSize;
				HAL_Delay(8);
      }
      if(NumOfSingle != 0)
      {
        I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle); 
      }
    }
  }
}

/**
  * @brief  I2C(AT24C02)读写测试
  * @param  无
  * @retval 无
  */
void I2C_Test(void)
{
	uint16_t i;
	printf("写入的数据\n\r");
	for ( i=0; i<=255; i++ ) //填充缓冲
  {   
    I2c_Buf_Write[i] = i;
    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)
		{
			printf("\n\r");
		}
	}
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);   //将I2c_Buf_Write中顺序递增的数据写入EERPOM中
  printf("\n\r写成功\n\r");
  printf("\n\r读出的数据\n\r");
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256);      //将EEPROM读出数据顺序保持到I2c_Buf_Read中
	for (i=0; i<256; i++)                                     //将I2c_Buf_Read中的数据通过串口打印
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			printf("错误:I2C EEPROM写入与读出的数据不一致\n\r");
			return;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)
		{
			printf("\n\r");
		}
	}
  printf("I2C(AT24C02)读写测试成功\n\r");
}

/*********************************************END OF FILE**********************/
