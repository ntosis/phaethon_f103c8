/*
 * basicADCSWC.c
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */
#include "stm32f1xx_hal.h"

#include "basicADCSWC.h"

#include "hardwareCfg.h"

#include "basicErrorHandlerSWC.h"

#include "interfaces.h"


struct ADCErrorStruct {

	uint8_t ErrorADCStatusIPROPx;

	uint8_t ErrorADCStatusUserMotorSpd;

	uint32_t ErrorADCLastEntryIPROPx;

	uint32_t ErrorADCLastEntryUserMotorSpd;

} ADCErrorStruct_Tag;

struct ADCMeasurment {

	uint16_t ADCRawIPROP1Value;

	uint16_t ADCRawIPROP2Value;

	uint16_t ADCRawUserSetMtrSpd;

} ADCMeasurment_Tag;

struct ADCErrorStruct ADCErrorStruct_;

struct ADCMeasurment ADCMeasurment_;

void basicReadADCRawValues()
{
	basicReadADCRawIPROP();

	basicReadADCRawUserMtrSpeed();

	MotorCurrentADCRawValue_sig = ADCMeasurment_.ADCRawIPROP1Value + ADCMeasurment_.ADCRawIPROP2Value;

}

void basicReadADCRawIPROP(void){

 uint32_t tickstart = 0U;

 /* Get tick count */
 tickstart = HAL_GetTick();

 ADC_ChannelConfTypeDef adcChannelx;

 adcChannelx.Channel = IPROP1CHNL;

 adcChannelx.Rank = 1;

 adcChannelx.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;


if (HAL_ADC_ConfigChannel(&hadc1, &adcChannelx) != HAL_OK)
   	{

	ADCErrorStruct_.ErrorADCStatusIPROPx++;

	ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();
	return;
   	}

HAL_ADC_Start(&hadc1);

   while(1) {

     if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
     {

    	 ADCMeasurment_.ADCRawIPROP1Value = HAL_ADC_GetValue(&hadc1);


	    break;

	 }

     if((HAL_GetTick() - tickstart ) > ADC_TIMEOUT )

     {

    	 ADCErrorStruct_.ErrorADCStatusIPROPx++;

    	 ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();

    	 return;

     }

   }

HAL_ADC_Stop(&hadc1);



 adcChannelx.Channel = IPROP2CHNL;
 adcChannelx.Rank = 1;
 adcChannelx.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

if (HAL_ADC_ConfigChannel(&hadc1, &adcChannelx) != HAL_OK)
	{
		ADCErrorStruct_.ErrorADCStatusIPROPx++;

		ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();

		return;
	}

HAL_ADC_Start(&hadc1);

while(1){

    	if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
    	{

    		ADCMeasurment_.ADCRawIPROP2Value = HAL_ADC_GetValue(&hadc1);


			break;

	 	 }

    	if((HAL_GetTick() - tickstart ) > ADC_TIMEOUT )

    	{

   	 ADCErrorStruct_.ErrorADCStatusIPROPx++;

   	 ADCErrorStruct_.ErrorADCLastEntryIPROPx = HAL_GetTick();

   	 return;

    	}


	}

	HAL_ADC_Stop(&hadc1);

}

uint8_t basicGetErrorADCStatusIPROPx(void) {

	return ADCErrorStruct_.ErrorADCStatusIPROPx;

}

uint32_t basicGetErrorADCLastEntryIPROPx(void) {

	return ADCErrorStruct_.ErrorADCLastEntryIPROPx;

}

void basicReadADCRawUserMtrSpeed(void) {

	 uint32_t tickstart = 0U;

	 /* Get tick count */
	 tickstart = HAL_GetTick();

	 ADC_ChannelConfTypeDef adcChannelx;

	 adcChannelx.Channel = POTUSRMTRSPEED;

	 adcChannelx.Rank = 1;

	 adcChannelx.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;


	if (HAL_ADC_ConfigChannel(&hadc1, &adcChannelx) != HAL_OK)
	   	{

		ADCErrorStruct_.ErrorADCStatusUserMotorSpd++;

		ADCErrorStruct_.ErrorADCLastEntryUserMotorSpd = HAL_GetTick();
		return;
	   	}

	HAL_ADC_Start(&hadc1);

	   while(1) {

	     if(__HAL_ADC_GET_FLAG(&hadc1, ADC_FLAG_EOC))
	     {
	    	 /* the speed potentiometer is in volatage divider setup, maximum voltage is 3.3 /2. That means also max adc value
	    	  *ca. 4096 / 2 = 2300*/
	    	 ADCMeasurment_.ADCRawUserSetMtrSpd = map(HAL_ADC_GetValue(&hadc1),0,2000,0,320);


		    break;

		 }

	     if((HAL_GetTick() - tickstart ) > ADC_TIMEOUT )

	     {

	    	 ADCErrorStruct_.ErrorADCStatusUserMotorSpd++;

	    	 ADCErrorStruct_.ErrorADCLastEntryUserMotorSpd = HAL_GetTick();

	    	 return;

	     }

	   }

	HAL_ADC_Stop(&hadc1);
}

uint8_t basicGetErrorADCStatusUserMotorSpd(void) {


	return ADCErrorStruct_.ErrorADCStatusUserMotorSpd;

}


void basicADCErrorHandler(void){

	if((HAL_GetTick()-ADCErrorStruct_.ErrorADCLastEntryIPROPx) > INTERNAL_ADCErrorEraseTime ) {

		ADCErrorStruct_.ErrorADCStatusIPROPx = 0;

	}

	else if((HAL_GetTick()-ADCErrorStruct_.ErrorADCLastEntryUserMotorSpd) > INTERNAL_ADCErrorEraseTime ) {

		ADCErrorStruct_.ErrorADCStatusUserMotorSpd = 0;

	}

	else if( ADCErrorStruct_.ErrorADCStatusIPROPx > 3 ) {

		/*
		 * TODO enter global error variable
		 */
		basicGlobalErrorState |= (1 << (MaskGlobalErrorADCStatusIPROPx));
	}

	else if(ADCErrorStruct_.ErrorADCStatusUserMotorSpd > 3) {

	   /*
		* TODO enter global error variable
		*/
		basicGlobalErrorState |= (1 << (MaskGlobalErrorADCStatusUserMotorSpd));
	}
}

uint16_t basicGetADCRawValueUserMotorSpd(void) {


	return ADCMeasurment_.ADCRawUserSetMtrSpd;

}

void basicSetADCRawValueUserMotorSpd(uint16_t val) {


	ADCMeasurment_.ADCRawUserSetMtrSpd=val;

}

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
