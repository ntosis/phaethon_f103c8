/*
 * basicErrorHandlerSWC.h
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */

#ifndef INCLUDE_BASICSWC_BASICERRORHANDLERSWC_H_
#define INCLUDE_BASICSWC_BASICERRORHANDLERSWC_H_


#define MaskGlobalErrorADCStatusIPROPx ((uint8_t)0x01U) //0b001
#define MaskGlobalErrorADCStatusUserMotorSpd ((uint8_t)0x02U) //0b010
#define MaskHBridgeFailureCode ((uint8_t)0x04U) //0b100
#define DebounceLEDErrorTimeInMS ((uint16_t)10000U)

extern uint8_t basicGlobalErrorState;


void basicCheckGlobalErrors(void);

#endif /* INCLUDE_BASICSWC_BASICERRORHANDLERSWC_H_ */
