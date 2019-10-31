#include <string.h>
#include "stm32f1xx_hal.h"
#include "eeprom_calib.h"
#include "eeprom_em.h"
#include "crcModule.h"
// Create variable in Flash with initial values
const struct CAL_PARAM_tag InitCAL = {{0x00},{0.15,0x02,0x03,0x04,0x05,0x06,VIRTUALL_ADDRESS_OF_STRUCT,0x07,0x08,0x09,0x10,0x11}} ;
// Create pointer for the calibration parameters
void  *pInitCAL = &InitCAL;

struct CAL_PARAM_tag CALinRAM;

void initCAL(void) {


    uint16_t retVal = EE_ReadBlockInEEm(&CALinRAM,sizeof(CAL_PARAM),VIRTUALL_ADDRESS_OF_STRUCT);

    if(retVal==0) {

    	/*Address found*/
    	FcdEEpromEmFailStatus &= ~FcdEEprmStructNotFoundError;
    	/* calculate the CRC */

    	uint32_t crcValue = calculateCRCfromStruct(&CALinRAM.data);

    	 if(CALinRAM.data_crc == crcValue) {

    		 /* reset eeprom emulation error codes*/
    		 FcdEEpromEmFailStatus = 0;

    	    }

    	 else {

    		 //CRC is wrong, load the default struct
    		 FcdEEpromEmFailStatus |= FcdEEprmCRCError;
    		 memcpy(&CALinRAM, &InitCAL, sizeof(struct CAL_PARAM_tag));

    	    }
    }
    else if(retVal==1){
    	/* Address no found load the default struct */

    	FcdEEpromEmFailStatus |= FcdEEprmStructNotFoundError;

    	memcpy(&CALinRAM, &InitCAL, sizeof(struct CAL_PARAM_tag));

    	/* Write in EEprom the default value */

    	uint8_t rV = EE_WriteBlock(pInitCAL,sizeof(struct CAL_PARAM_tag));

    	if(rV==HAL_OK) {

    		FcdEEpromEmFailStatus = 0;
    	}
    	else if(rV==PAGE_FULL) {

    		FcdEEpromEmFailStatus |= FcdEEprmPageFullError;

    	}
    	else if(rV==NO_VALID_PAGE) {

    		FcdEEpromEmFailStatus |= FcdEEprmNoValidPageError;
    	}
    	else {

    		FcdEEpromEmFailStatus |= FcdFlashError;
    	}

    }
    else if(retVal==NO_VALID_PAGE) {

    	/* load the default struct */
    	FcdEEpromEmFailStatus |= FcdEEprmNoValidPageError;

    	memcpy(&CALinRAM, &InitCAL, sizeof(struct CAL_PARAM_tag));

    }


}

void writeStructToEEprom(void) {
	/* Write in EEprom the data from the software */

	    	uint8_t rV = EE_WriteBlock(&CALinRAM,sizeof(struct CAL_PARAM_tag));

	    	if(rV==HAL_OK) {

	    		FcdEEpromEmFailStatus = 0;
	    	}
	    	else if(rV==PAGE_FULL) {

	    		FcdEEpromEmFailStatus |= FcdEEprmPageFullError;

	    	}
	    	else if(rV==NO_VALID_PAGE) {

	    		FcdEEpromEmFailStatus |= FcdEEprmNoValidPageError;
	    	}
	    	else {

	    		FcdEEpromEmFailStatus |= FcdFlashError;
	    	}
}


