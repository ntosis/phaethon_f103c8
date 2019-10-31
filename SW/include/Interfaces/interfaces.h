/*
 * interfaces.h
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */

#ifndef INCLUDE_INTERFACES_INTERFACES_H_
#define INCLUDE_INTERFACES_INTERFACES_H_
#include <stdint.h>

extern unsigned char AmbientLightRequest_sig;
extern unsigned char ApplicationInternalError_sig;
extern uint32_t HAL_getMstime_sig;
extern unsigned char HBridgeFailureCode_sig;
extern uint16_t MotorCurrentADCRawValue_sig;
extern unsigned char MotorDirection_sig;
extern unsigned char MotorRotationRequest_sig;
extern uint16_t MotorSpdUserRequest_sig;
extern unsigned char StartStopUserRequest_sig;

#endif
