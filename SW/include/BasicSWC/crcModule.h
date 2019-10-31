/*
 * crcModeule.h
 *
 *  Created on: Oct 25, 2019
 *      Author: unix
 */

#ifndef INCLUDE_BASICSWC_CRCMODEULE_H_
#define INCLUDE_BASICSWC_CRCMODEULE_H_

/* CRC handler declaration */
CRC_HandleTypeDef   CrcHandle;

void initCRC(void);
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc);

uint32_t calculateCRCfromStruct(struct caldata_tag *data);

#endif /* INCLUDE_BASICSWC_CRCMODEULE_H_ */
