/*
 * basicLEDDriverSWC.h
 *
 *  Created on: May 31, 2019
 *      Author: unix
 */

#ifndef INCLUDE_BASICSWC_BASICLEDDRIVERSWC_H_
#define INCLUDE_BASICSWC_BASICLEDDRIVERSWC_H_

#define MaskRedLedFastBlinking ((uint8_t)(0x01U))
#define MaskRedLedSlowBlinking ((uint8_t)(0x02U))

#define LedFastBlinkTimeInms ((uint16_t)(150U))
#define LedSlowBlinkTimeInms ((uint16_t)(500U))


extern uint8_t redLedBlinking;
uint8_t basicGlobalLedDriver(uint32_t time);


#endif /* INCLUDE_BASICSWC_BASICLEDDRIVERSWC_H_ */
