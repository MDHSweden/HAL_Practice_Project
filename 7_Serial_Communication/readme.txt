使用USART1，分别使用轮询，中断和DMA模式进行串口通讯，异步全双工。
使用引脚PA9，PA10，注意cubemx默认的USART1的引脚不是这两个！
三种方式实现接收未知长度的帧数据，并用相同方式发送该帧数据。
中断方式使用超时认为接收完毕。
DMA方式使用空闲中断认为接收完毕。
附网址：http://www.stmcu.org/module/forum/thread-602761-1-1.html

常用操作：
HAL_StatusTypeDef HAL_UART_Transmit (UART_HandleTypeDef * huart, uint8_t * pData, uint16_t Size, uint32_t Timeout)
HAL_StatusTypeDef HAL_UART_Receive (UART_HandleTypeDef * huart, uint8_t * pData, uint16_t Size, uint32_t Timeout)
HAL_StatusTypeDef HAL_UART_Transmit_IT (UART_HandleTypeDef * huart, uint8_t * pData, uint16_t Size)
HAL_StatusTypeDef HAL_UART_Receive_IT (UART_HandleTypeDef * huart, uint8_t * pData, uint16_t Size)
HAL_StatusTypeDef HAL_UART_Transmit_DMA (UART_HandleTypeDef * huart, uint8_t * pData, uint16_t Size)
HAL_StatusTypeDef HAL_UART_Receive_DMA (UART_HandleTypeDef * huart, uint8_t * pData, uint16_t Size)
HAL_StatusTypeDef HAL_UART_DMAPause (UART_HandleTypeDef * huart)
HAL_StatusTypeDef HAL_UART_DMAResume (UART_HandleTypeDef * huart)
HAL_StatusTypeDef HAL_UART_DMAStop (UART_HandleTypeDef * huart)

void HAL_UART_TxCpltCallback (UART_HandleTypeDef * huart)
void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart)


