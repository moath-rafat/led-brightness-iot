#ifndef INC_ADC_DRIVER_H_
#define INC_ADC_DRIVER_H_

void adc_init();

#include <stdint.h>

extern volatile uint16_t knob_val;
extern volatile uint8_t knob_ready;

#define RESOLUTION 12

#include "main.h"
#include "stm32f4xx_hal.h"

#endif
