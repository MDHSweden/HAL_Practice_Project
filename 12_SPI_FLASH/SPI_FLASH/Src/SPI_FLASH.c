 /**
  ******************************************************************************
  * @file    SPI_FLASH.c
  * @author  可可城
  * @version V1.0
  * @date    2016-02-01
  * @brief   SPI读写FLASH
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
 
#include "SPI_FLASH.h"

#define SPI_FLASH_PageSize      256
#define SPI_FLASH_PerWritePageSize      256
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		    0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	    0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F 
#define WIP_Flag                  0x01
#define Dummy_Byte                0xFF

#define CS_LOW() HAL_GPIO_WritePin (CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define CS_HIGH() HAL_GPIO_WritePin (CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)

extern SPI_HandleTypeDef hspi1;

/**
  * @brief  FLASH使能写
  * @param  无
  * @retval 无
  */
void SPI_FLASH_WriteEnable(void)
{
	CS_LOW();
	uint8_t pData[1] = {W25X_WriteEnable};
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	CS_HIGH();
}

/**
  * @brief  FLASH等待写完毕
  * @param  无
  * @retval 无
  */
void SPI_FLASH_WaitForWriteEnd(void)
{
  uint8_t FLASH_Status = 0;
	uint8_t pData[1] = {W25X_ReadStatusReg};
	CS_LOW();
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
  do
  {
    HAL_SPI_Receive (&hspi1, &FLASH_Status, 1, HAL_MAX_DELAY);	 
  }
  while ((FLASH_Status & WIP_Flag) == SET);
	CS_HIGH();
}

/**
  * @brief  清空FLASH块
  * @param  块地址
  * @retval 无
  */
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
	uint8_t pData[4] = {W25X_SectorErase,(SectorAddr & 0xFF0000) >> 16,(SectorAddr & 0xFF00) >> 8,SectorAddr & 0xFF};
	SPI_FLASH_WriteEnable();
	CS_LOW();
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	CS_HIGH();
	SPI_FLASH_WaitForWriteEnd();
}

/**
  * @brief  清空所有FLASH块
  * @param  无
  * @retval 无
  */
void SPI_FLASH_BulkErase(void)
{
	uint8_t pData[1] = {W25X_ChipErase};
  SPI_FLASH_WriteEnable();
	CS_LOW();
  HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	CS_HIGH();
  SPI_FLASH_WaitForWriteEnd();
}

/**
  * @brief  FLASH写
  * @param  数据地址，FLASH地址，字节数
  * @retval 无
  */
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint8_t pData[4] = {W25X_PageProgram,(WriteAddr & 0xFF0000) >> 16,(WriteAddr & 0xFF00) >> 8,WriteAddr & 0xFF};
  SPI_FLASH_WriteEnable();
	CS_LOW();
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
  if (NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
  }
	HAL_SPI_Transmit (&hspi1, pBuffer, NumByteToWrite, HAL_MAX_DELAY);
	CS_HIGH();
  SPI_FLASH_WaitForWriteEnd();
}

/**
  * @brief  FLASH分块写
  * @param  数据地址，FLASH地址，字节数
  * @retval 无
  */
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
  if (Addr == 0)
  {
    if (NumOfPage == 0)
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else
  {
    if (NumOfPage == 0)
    {
      if (NumOfSingle > count)
      {
        temp = NumOfSingle - count;
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/**
  * @brief  FLASH读
  * @param  数据存放地址，FLASH地址，字节数
  * @retval 无
  */
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	uint8_t pData[4] = {W25X_ReadData,(ReadAddr & 0xFF0000) >> 16,(ReadAddr& 0xFF00) >> 8,ReadAddr & 0xFF};
	CS_LOW();
  HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	HAL_SPI_Receive (&hspi1, pBuffer, NumByteToRead, HAL_MAX_DELAY);
	CS_HIGH();
}

/**
  * @brief  FLASH读ID
  * @param  无
  * @retval ID
  */
uint32_t SPI_FLASH_ReadID(void)
{
  uint8_t Temp[3];
	uint8_t pData[1] = {W25X_JedecDeviceID};
	CS_LOW();
  HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	HAL_SPI_Receive (&hspi1, Temp, 3, HAL_MAX_DELAY);
	CS_HIGH();
  return (Temp[0] << 16) | (Temp[1] << 8) | Temp[2];
}

/**
  * @brief  FLASH读设备ID
  * @param  无
  * @retval ID
  */
uint32_t SPI_FLASH_ReadDeviceID(void)
{
  uint8_t Temp = 0;
	uint8_t pData[4] = {W25X_DeviceID,Dummy_Byte,Dummy_Byte,Dummy_Byte};
	CS_LOW();
  HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	HAL_SPI_Receive (&hspi1, &Temp, 1, HAL_MAX_DELAY);
	CS_HIGH();
  return Temp;
}

/**
  * @brief  FLASH开始读序列
  * @param  读地址
  * @retval 无
  */
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
	uint8_t pData[4] = {W25X_ReadData,(ReadAddr & 0xFF0000) >> 16,(ReadAddr& 0xFF00) >> 8,ReadAddr & 0xFF};
	CS_LOW();
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	CS_HIGH();
}

/**
  * @brief  FLASH掉电模式
  * @param  无
  * @retval 无
  */
void SPI_Flash_PowerDown(void)   
{
	uint8_t pData[1] = {W25X_PowerDown};
	CS_LOW();
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	CS_HIGH();
}   

/**
  * @brief  FLASH唤醒
  * @param  无
  * @retval 无
  */
void SPI_Flash_WAKEUP(void)   
{
	uint8_t pData[1] = {W25X_ReleasePowerDown};
	CS_LOW();
	HAL_SPI_Transmit (&hspi1, pData, sizeof(pData), HAL_MAX_DELAY);
	CS_HIGH();
}   
   
/*********************************************END OF FILE**********************/
