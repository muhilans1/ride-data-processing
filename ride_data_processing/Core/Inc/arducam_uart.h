#ifndef __ARDUCAM_UART_H
#define __ARDUCAM_UART_H

#include "main.h"

extern UART_HandleTypeDef huart1;

#define SerialBegin(baudRate)     /* Not needed, UART initialized by HAL */
#define SerialWrite(ch)           HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY)
#define SerialWriteBuff(buf, len) HAL_UART_Transmit(&huart1, (uint8_t*)buf, len, HAL_MAX_DELAY)
#define SerialPrintf(str)         HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY)
#define SerialAvailable()         (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) == SET)
#define SerialRead()              ({uint8_t ch; HAL_UART_Receive(&huart1, &ch, 1, HAL_MAX_DELAY); ch;})
#define delayUs(us)               HAL_Delay((us)/1000)

#endif
