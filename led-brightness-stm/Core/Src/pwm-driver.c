#include "pwm-driver.h"
#include "stm32f4xx_hal.h"
#include "adc-driver.h"

void pwm_init() {
	__HAL_RCC_TIM2_CLK_ENABLE();

	TIM2->ARR = 1023;
	TIM2->PSC = 7;

	TIM2->CCER |= TIM_CCER_CC2E;
	TIM2->CR1 |= TIM_CR1_ARPE;
	TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
	TIM2->CCMR1 |= (0b110 << 12);

	TIM2->CR1 |= TIM_CR1_CEN;
}
