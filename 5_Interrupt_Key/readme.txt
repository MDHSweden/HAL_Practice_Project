��ΪPB0���͵�ƽ��������PA0������Ϊ�ߵ�ƽ���������½��ش�����
˵�����������ж���ʹ����HAL_Delay()������HAL��Ĭ�ϵδ�ʱ�����ȼ���ߣ�
����ڳ�ʼ����������ʱҪע�����ȼ�����������ȼ���
ͬʱʹ��cubemxʱע������NVIC�ſ�ʹ���жϡ�
���������������˰��������������������ʱ��ܳ�����Ҫ��ʱ40ms��
���ò�����
GPIO_PinState HAL_GPIO_ReadPin (GPIO_TypeDef * GPIOx,uint16_t GPIO_Pin)
void HAL_GPIO_WritePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
void HAL_GPIO_TogglePin (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin) //��ת��ƽ
HAL_StatusTypeDef HAL_GPIO_LockPin (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)    //�����ţ���λ���ͷ�
void HAL_Delay (__IO uint32_t Delay)

����
Typedef enum
{
HAL_OK = 0x00,
HAL_ERROR = 0x01,
HAL_BUSY = 0x02,
HAL_TIMEOUT = 0x03
} HAL_StatusTypeDef;