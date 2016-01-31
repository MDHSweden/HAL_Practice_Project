/**
  ******************************************************************************
  * @file    IIC.c
  * @author  �ɿɳ�
  * @version V1.0
  * @date    2016-01-31
  * @brief   IIC��ȡEEPROM
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
  * @brief   ��EEPROM��һ��дѭ���п���д����ֽڣ���һ��д����ֽ���
  *          ���ܳ���EEPROMҳ�Ĵ�С��AT24C02ÿҳ��8���ֽ�
  * @param   
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ
  *   @arg NumByteToWrite:д���ֽ���
  * @retval  ��
  */
void I2C_EE_PageWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite)
{
	HAL_I2C_Mem_Write (&hi2c1, EEPROM_ADDRESS, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToWrite, HAL_MAX_DELAY);
}

/**
  * @brief   ��EEPROM�����ȡһ������ 
  * @param   
  *		@arg pBuffer:��Ŵ�EEPROM��ȡ�����ݵĻ�����ָ��
  *		@arg ReadAddr:�������ݵ�EEPROM�ĵ�ַ
  *   @arg NumByteToWrite:Ҫ��EEPROM��ȡ���ֽ���
  * @retval  ��
  */
void I2C_EE_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead)
{
	HAL_I2C_Mem_Read (&hi2c1, EEPROM_ADDRESS, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, NumByteToRead, HAL_MAX_DELAY);
}

/**
  * @brief   ���������е�����д��I2C EEPROM��
  * @param   
  *		@arg pBuffer:������ָ��
  *		@arg WriteAddr:д��ַ
  *   @arg NumByteToWrite:д���ֽ���
  * @retval  ��
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
  * @brief  I2C(AT24C02)��д����
  * @param  ��
  * @retval ��
  */
void I2C_Test(void)
{
	uint16_t i;
	printf("д�������\n\r");
	for ( i=0; i<=255; i++ ) //��仺��
  {   
    I2c_Buf_Write[i] = i;
    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)
		{
			printf("\n\r");
		}
	}
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);   //��I2c_Buf_Write��˳�����������д��EERPOM��
  printf("\n\rд�ɹ�\n\r");
  printf("\n\r����������\n\r");
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256);      //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read��
	for (i=0; i<256; i++)                                     //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			printf("0x%02X ", I2c_Buf_Read[i]);
			printf("����:I2C EEPROMд������������ݲ�һ��\n\r");
			return;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)
		{
			printf("\n\r");
		}
	}
  printf("I2C(AT24C02)��д���Գɹ�\n\r");
}

/*********************************************END OF FILE**********************/
