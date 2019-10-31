/*
 * errorHandler.c
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */
#include "stm32f1xx_hal.h"

#include "basicErrorHandlerSWC.h"

#include "basicLEDDriverSWC.h"

#include "interfaces.h"

#include "basicADCSWC.h"

#include "core_cm3.h"

uint8_t basicGlobalErrorState=0;
uint8_t redLedBlinking=0;

void basicCheckGlobalErrors(void){

	uint32_t now = HAL_GetTick();
	static uint32_t previousTime=0;

	if(basicGlobalErrorState & (1<<MaskGlobalErrorADCStatusIPROPx)) {


		NVIC_SystemReset();

		return;

	}

	else if(!(basicGlobalErrorState & (1<<MaskGlobalErrorADCStatusIPROPx))) {



	}

	if (basicGlobalErrorState & (1<<MaskGlobalErrorADCStatusUserMotorSpd)) {

		/*TODO error user motor speed, set speed to 80% of 327
		 */
		basicSetADCRawValueUserMotorSpd((uint16_t)228);
	}

	if((HBridgeFailureCode_sig==1)) {

		/* HBridge error is reported from the Hardware. (nFault pin)*/
		redLedBlinking |= (1 << MaskRedLedFastBlinking);

		/* Update the previous time */
			previousTime=now;
	}

	else if((HBridgeFailureCode_sig==0)&&((now - previousTime)>DebounceLEDErrorTimeInMS)){

		/* Clear HBridge error, is reported from the Hardware. (nFault pin)*/
		redLedBlinking &= ~(1 << MaskRedLedFastBlinking);
	}

	if(ApplicationInternalError_sig==1) {

		/* Application Software error is reported*/
		redLedBlinking |= (1 << MaskRedLedSlowBlinking);

		/* Update the previous time */
			previousTime=now;
	}
	else if((ApplicationInternalError_sig==0)&&((now - previousTime)>DebounceLEDErrorTimeInMS)) {

		/* Clear  Application Software error*/
		redLedBlinking &= ~(1 << MaskRedLedSlowBlinking);
	}


}
