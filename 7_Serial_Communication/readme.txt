ʹ��USART1���ֱ�ʹ����ѯ���жϺ�DMAģʽ���д���ͨѶ���첽ȫ˫����
ʹ������PA9��PA10��ע��cubemxĬ�ϵ�USART1�����Ų�����������
���ַ�ʽʵ�ֽ���δ֪���ȵ�֡���ݣ�������ͬ��ʽ���͸�֡���ݡ�
�жϷ�ʽʹ�ó�ʱ��Ϊ������ϡ�
DMA��ʽʹ�ÿ����ж���Ϊ������ϡ�
����ַ��http://www.stmcu.org/module/forum/thread-602761-1-1.html

���ò�����
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


