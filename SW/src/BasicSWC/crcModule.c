/*
 * crcModule.c
 *
 *  Created on: Oct 25, 2019
 *      Author: unix
 */
#include "stm32f1xx_hal.h"
#include "eeprom_calib.h"
#include "crcModule.h"
#include <string.h>
/* CRC handler declaration */
CRC_HandleTypeDef   CrcHandle;

void initCRC(void) {

	CrcHandle.Instance = CRC;

	if (HAL_CRC_Init(&CrcHandle) != HAL_OK)
	  {
	    /* Initialization Error */
	    Error_Handler();
	  }
}

/**
  * @brief CRC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
  /* CRC Peripheral clock enable */
  __HAL_RCC_CRC_CLK_ENABLE();
}

uint32_t calculateCRCfromStruct(struct caldata_tag *data) {

 uint32_t buffer[U32BUFFERSIZE] = {0};


 CrcHandle.Instance = CRC;

 /*  calculate the crc value of the data and patch it in the struct*/
 memcpy(buffer,data,sizeof(struct caldata_tag));

 /*  END OF crc calculation */

 return HAL_CRC_Calculate(&CrcHandle,buffer,U32BUFFERSIZE);
}
