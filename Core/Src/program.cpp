/*
 * program.cpp
 *
 *  Created on: Dec 9, 2020
 *      Author: vincent
 */

#include "program.h"
#include "gpio.h"
#include "main.h"
#include "i2s.h"
#include <stdint.h>

void entrypoint()
{
	uint16_t buffer[256];

	for(int i = 0; i < 256; i++)
	{
		buffer[i] = (i % 10 >= 5) ? 250 : 50;
	}

	while(true)
	{
		//auto state = HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin);
		//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, state);

		HAL_I2S_Transmit(&hi2s1, buffer, sizeof(buffer) / sizeof(buffer[0]), 10);
		//HAL_Delay(100);
	}
}
