/*
 * basicPWMMotorDriver.c
 *
 *  Created on: Jun 5, 2019
 *      Author: unix
 */

#include "basicPWMMotorDriver.h"

#include "stm32f1xx_hal.h"

#include "hardwareCfg.h"

#include "interfaces.h"

#include "basicErrorHandlerSWC.h"

#include "basicADCSWC.h"

static uint8_t isDriverinSleepMode = 1;

void basicMotorTask(void) {

	/* Application Software requests motor rotation and error is not set*/
		if(MotorRotationRequest_sig &&(!(basicGlobalErrorState & MaskGlobalErrorADCStatusIPROPx))) {

			basicStartMotor();

		}

		else {

			basicStopMotor();
		}

}

void basicStartMotor(void){

	if(isDriverinSleepMode) {
	/* nSleep To exit a low-power sleep mode, set this pin logic high.*/
	HAL_GPIO_WritePin(NSLeepMotorDriver_GPIO_Port,NSLeepMotorDriver_Pin,GPIO_PIN_SET);

	/* Bridge enable input. A logic low on this pin enables the H-bridge Hi-Z. Internal pullup to DVDD */
	HAL_GPIO_WritePin(DisableMotorDriver_GPIO_Port,DisableMotorDriver_Pin,GPIO_PIN_RESET);

	/*reset sleep mode*/
	isDriverinSleepMode=0;

	}

	/* EN/IN1 PH/IN2 OUT1 OUT2
	 * 0      1      L    H
	 * 1      0		 H    L
	 * 1      1      H    H
	 * 0	  0      L    L
	 */
	 /**TIM4 GPIO Configuration
	    PB8     ------> TIM4_CH3 --> IN2
	    PB9     ------> TIM4_CH4 --> IN1
	    */

	/*left direction */
	if(MotorDirection_sig) {

		uint16_t speed = basicGetADCRawValueUserMotorSpd();

		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,(uint16_t)0);

		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,(uint16_t)speed);

	}
	/*right direction */
	else {
		uint16_t speed = basicGetADCRawValueUserMotorSpd();

		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,(uint16_t)speed);

		__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,(uint16_t)0);
	}


}
void basicStopMotor(void) {

	/* nSleep To enter a low-power sleep mode, set this pin logic low.*/
	HAL_GPIO_WritePin(NSLeepMotorDriver_GPIO_Port,NSLeepMotorDriver_Pin,GPIO_PIN_RESET);

	/* Bridge enable input. A logic high on this pin disables the H-bridge Hi-Z. Internal pullup to DVDD */
	HAL_GPIO_WritePin(DisableMotorDriver_GPIO_Port,DisableMotorDriver_Pin,GPIO_PIN_SET);

	isDriverinSleepMode = 1;
}
