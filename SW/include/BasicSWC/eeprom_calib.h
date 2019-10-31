/*
 * eeprom_calib.h
 *
 *  Created on: Jul 5, 2016
 *      Author: unix
 */

#ifndef EEPROM_CALIB_H_
#define EEPROM_CALIB_H_

#define _start 0x800C000 /*TODO delete it if not used */

/* Virtual address defined by the user: 0xFFFF value is prohibited */
#define VIRTUALL_ADDRESS_OF_STRUCT ((uint16_t)0x8888U)
//#define U32BUFFERSIZE (uint16_t) (sizeof(struct caldata_tag) / sizeof(uint32_t))
// Find the quotient of sizeof caldata_tag / sizeof(uint32_t), rounded up
#define U32BUFFERSIZE ((sizeof(struct caldata_tag) + sizeof(uint32_t) - 1)/sizeof(uint32_t))
// Create structure

struct caldata_tag {
	    float K_P_Htng;
	    uint16_t K_I_Htng;
	    uint16_t K_D_Htng;
	    uint16_t K_P_Coolg;
	    uint16_t K_I_Coolg;
	    uint16_t K_D_Coolg;
	    const uint16_t virtualAddress;
	    uint8_t  oneLevelSystem_C;
	    uint8_t smartCnt_C;
	    uint8_t debugInfosFlag_C;
	    uint8_t statusOfThisBlock;
	    uint8_t test;
} caldata;

struct CAL_PARAM_tag {

	uint32_t data_crc;

	struct caldata_tag data;

} CAL_PARAM;



void initCAL(void);
void writeStructToEEprom(void);

extern void  *pInitCAL;
extern uint8_t *a_ptr;
extern struct CAL_PARAM_tag CALinRAM;

/*
#define K_P_Htng (p->K_P_Htng)
#define K_I_Htng (p->K_I_Htng)
#define K_D_Htng (p->K_D_Htng)
#define K_P_Coolg (p->K_P_Coolg)
#define K_I_Coolg (p->K_I_Coolg)
#define K_D_Coolg (p->K_D_Coolg)
#define oneLevelSystem_C (p->oneLevelSystem_C)
#define smartCnt_C (p->smartCnt_C)
#define debugInfosFlag_C p->debugInfosFlag_C)
*/
#endif /* EEPROM_CALIB_H_ */

