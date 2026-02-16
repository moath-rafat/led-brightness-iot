#include "main.h"
#include "stm32f4xx_hal.h"
#include "uart-driver.h"
#include "adc-driver.h"
#include "pwm-driver.h"

void SystemClock_Config(void);
void gpio_init();

uint8_t brightness_per = 0;
uint32_t last_transmit = 0;

int main(void) {
    HAL_Init();
    SystemClock_Config();

    gpio_init();
    uart_init();
    adc_init();
    pwm_init();

    while (1) {
    	if(knob_ready) {
    		knob_ready = 0;
    		TIM2->CCR2 = (knob_val * TIM2->ARR) / (4096);
    		if(HAL_GetTick() - last_transmit >= 100) {
    			uint8_t per = (knob_val*100) / 4096;
				HAL_UART_Transmit(&huart, per, 1, 10);
				last_transmit = HAL_GetTick();
    		}
    	}
    }
}

void gpio_init() {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef gpio_init = {0};

	// PB3 for LED PWM output using TIM2_CH2(AF1)
	gpio_init.Mode = GPIO_MODE_AF_PP;
	gpio_init.Alternate = GPIO_AF1_TIM2;
	gpio_init.Pin = GPIO_PIN_3;

	HAL_GPIO_Init(GPIOB, &gpio_init);

	// PA0 for ADC1_IN0
	gpio_init.Mode = GPIO_MODE_ANALOG;
	gpio_init.Pin = GPIO_PIN_0;

	HAL_GPIO_Init(GPIOA, &gpio_init);

	// PC10 and PC11 for UART4 TX and RX(AF8)
	gpio_init.Mode = GPIO_MODE_AF_PP;
	gpio_init.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	gpio_init.Pull = GPIO_PULLUP;
	gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_init.Alternate = GPIO_AF8_UART4;

	HAL_GPIO_Init(GPIOC, &gpio_init);
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}



void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}

}
