/*
 * hardwareCfg.h
 *
 *  Created on: May 26, 2019
 *      Author: unix
 */

#ifndef INCLUDE_HARDWARECFG_HARDWARECFG_H_
#define INCLUDE_HARDWARECFG_HARDWARECFG_H_

#include "stm32f1xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define IPROPI1_Pin GPIO_PIN_1
#define IPROPI1_GPIO_Port GPIOA
#define IPROPI2_Pin GPIO_PIN_2
#define IPROPI2_GPIO_Port GPIOA
#define SetSpeedInput_Pin GPIO_PIN_0
#define SetSpeedInput_GPIO_Port GPIOB
#define nFaultInput_Pin GPIO_PIN_1
#define nFaultInput_GPIO_Port GPIOB
#define NSLeepMotorDriver_Pin GPIO_PIN_11
#define NSLeepMotorDriver_GPIO_Port GPIOB
#define RedLed_Pin GPIO_PIN_12
#define RedLed_GPIO_Port GPIOB
#define GreenLed_Pin GPIO_PIN_13
#define GreenLed_GPIO_Port GPIOB
#define PowerLed_Pin GPIO_PIN_14
#define PowerLed_GPIO_Port GPIOB
#define DisableMotorDriver_Pin GPIO_PIN_15
#define DisableMotorDriver_GPIO_Port GPIOB
#define InputUserRequestButton_Pin GPIO_PIN_3
#define InputUserRequestButton_GPIO_Port GPIOA

/*
 Extern Variables
 */
extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim4;

extern IWDG_HandleTypeDef hiwdg;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_TIM4_Init(void);
void MX_ADC1_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void basicStartTIM4(void);
void basicReadInputs(void);
void MX_IWDG_Init(void);

#endif /* INCLUDE_HARDWARECFG_HARDWARECFG_H_ */
