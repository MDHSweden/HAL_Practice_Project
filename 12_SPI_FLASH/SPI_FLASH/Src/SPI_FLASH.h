 /**
  ******************************************************************************
  * @file    SPI_FLASH.h
  * @author  ¿É¿É³Ç
  * @version V1.0
  * @date    2016-02-01
  * @brief   SPI¶ÁÐ´FLASH
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f1xx_hal.h"

void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t SPI_FLASH_ReadID(void);
uint32_t SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);

#endif /* __SPI_FLASH_H */

