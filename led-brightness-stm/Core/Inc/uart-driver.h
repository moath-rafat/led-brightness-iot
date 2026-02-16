#ifndef INC_UART_DRIVER_H_
#define INC_UART_DRIVER_H_

void uart_init();

#include "main.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart;

#endif
