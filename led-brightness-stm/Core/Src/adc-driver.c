#include "adc-driver.h"
#include "uart-driver.h"
#include "stm32f4xx_hal.h"

ADC_HandleTypeDef hadc = {0};
volatile uint16_t adc_val = 0;
volatile uint8_t conv_count = 0;
volatile uint16_t knob_val = 0;
volatile uint8_t knob_ready = 0;
uint16_t adc_vals[5];

void adc_init() {
	__HAL_RCC_ADC1_CLK_ENABLE();

	hadc.Instance = ADC1;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.ScanConvMode = DISABLE;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	HAL_ADC_Init(&hadc);

	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	NVIC_EnableIRQ(ADC_IRQn);

	HAL_ADC_Start_IT(&hadc);
}

void ADC_IRQHandler(void) {
	HAL_ADC_IRQHandler(&hadc);
	HAL_ADC_Start_IT(&hadc);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	adc_val = HAL_ADC_GetValue(hadc);
	adc_vals[conv_count] = adc_val;
	conv_count = conv_count + 1;
	if(conv_count == 5) {
		uint16_t sum = 0;
		for(int i = 0; i < conv_count; i++) {
			sum += adc_vals[i];
		}
		knob_val = sum/5;
		conv_count = 0;
		knob_ready = 1;
	}

}



