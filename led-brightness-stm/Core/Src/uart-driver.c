#include "uart-driver.h"
#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart;
volatile uint8_t recieved_data = 0;
extern uint8_t brightness_per;

void uart_init() {
	__HAL_RCC_UART4_CLK_ENABLE();

	huart.Init.BaudRate = 115200;
	huart.Instance = UART4;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.Parity = UART_PARITY_NONE;

	HAL_UART_Init(&huart);

//	NVIC_EnableIRQ(UART4_IRQn);
//	HAL_UART_Receive_IT(&huart, &recieved_data, 1);
}

//void UART4_IRQHandler(void) {
//    HAL_UART_IRQHandler(&huart);
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	if(huart->Instance == UART4) {
//		brightness_per = recieved_data;
//		HAL_UART_Receive_IT(&huart, &recieved_data, 1);
//	}
//}
//
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
//{
//    if (huart->Instance == UART4)
//    {
//        uint32_t err = huart->ErrorCode;
//
//        if(err & HAL_UART_ERROR_ORE) {
//            __HAL_UART_CLEAR_OREFLAG(huart);
//        }
//
//        if(err & HAL_UART_ERROR_FE) {
//            __HAL_UART_CLEAR_FEFLAG(huart);
//        }
//
//        if(err & HAL_UART_ERROR_NE) {
//            __HAL_UART_CLEAR_NEFLAG(huart);
//        }
//
//        if(err & HAL_UART_ERROR_PE) {
//            __HAL_UART_CLEAR_PEFLAG(huart);
//        }
//
//        HAL_UART_Receive_IT(&huart, &recieved_data, 1);
//    }
//}






