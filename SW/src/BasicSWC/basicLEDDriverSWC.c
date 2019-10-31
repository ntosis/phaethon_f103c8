/*
 * basicLEDDriverSWC.c
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */

#include "stm32f1xx_hal.h"

#include "basicLEDDriverSWC.h"

#include "hardwareCfg.h"

#include "interfaces.h"

uint8_t basicGlobalLedDriver(uint32_t time) {

	static uint32_t previousTime=0;
	static int16_t LedFastBlinkCounter = (int16_t) LedFastBlinkTimeInms;
	static int16_t LedSlowBlinkCounter = (int16_t) LedSlowBlinkTimeInms;

	LedFastBlinkCounter -= (int16_t) (time - previousTime);
	LedSlowBlinkCounter -= (int16_t) (time - previousTime);

	if(redLedBlinking & (1<<MaskRedLedFastBlinking)){
		/*fast blink red led*/
		if(LedFastBlinkCounter <= 0) {

			HAL_GPIO_TogglePin(RedLed_GPIO_Port,RedLed_Pin);
		}

	}

	else if(redLedBlinking & (1<<MaskRedLedSlowBlinking)){
		 /*slow blink red led*/
		if(LedSlowBlinkCounter <= 0) {

			HAL_GPIO_TogglePin(RedLed_GPIO_Port,RedLed_Pin);
		}

	}

	else if(redLedBlinking==0) {

		/* no error, red led off*/
		HAL_GPIO_WritePin(RedLed_GPIO_Port,RedLed_Pin,GPIO_PIN_RESET);
	}

	if(MotorRotationRequest_sig){
			/*slow blink green led*/
			if(LedSlowBlinkCounter <= 0) {

				HAL_GPIO_TogglePin(GreenLed_GPIO_Port,GreenLed_Pin);
			}

		}

	else if(!MotorRotationRequest_sig) {
			 /*green led on when motor is off*/

			HAL_GPIO_WritePin(GreenLed_GPIO_Port,GreenLed_Pin,GPIO_PIN_SET);

		}

	if(AmbientLightRequest_sig){

			/*Ambient Led on*/

			HAL_GPIO_WritePin(PowerLed_GPIO_Port,PowerLed_Pin,GPIO_PIN_SET);
		}

	else if(!AmbientLightRequest_sig) {

			/*Ambient Led off*/

			HAL_GPIO_WritePin(PowerLed_GPIO_Port,PowerLed_Pin,GPIO_PIN_RESET);

		}

	previousTime=time;

	if(LedFastBlinkCounter <= 0) { LedFastBlinkCounter = (int16_t) LedFastBlinkTimeInms; }

	if(LedSlowBlinkCounter <= 0) { LedSlowBlinkCounter = (int16_t) LedSlowBlinkTimeInms;}

	return 0;
}
