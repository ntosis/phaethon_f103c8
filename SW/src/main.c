
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "hardwareCfg.h"
#include "basicLEDDriverSWC.h"
#include "basicADCSWC.h"
#include "basicErrorHandlerSWC.h"
#include "basicPWMMotorDriver.h"
#include "MainApplicationSystem.h"
#include "eeprom_em.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId Task50mskHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void Task50ms(void const * argument);
void Task100ms(void const * argument);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  initCRC();

  /* USER CODE BEGIN 2 */
  format();
  EE_Init(); /* init the eeprom emulation modul */
  initCAL(); /* init the calibrations parameter */

  basicStartTIM4();
  MainApplicationSystem_initialize();
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(Task50ms_, Task50ms, osPriorityRealtime, 0, 512);
  Task50mskHandle = osThreadCreate(osThread(Task50ms_), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  osThreadDef(defaultTask, Task100ms, osPriorityRealtime, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
/*  __HAL_RCC_DBGMCU_CLK_ENABLE();
  __HAL_DBGMCU_FREEZE_IWDG();*/
  MX_IWDG_Init();
  __HAL_IWDG_START(&hiwdg);
  /* USER CODE END RTOS_QUEUES */
 

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */




/* USER CODE BEGIN 4 */
void Task50ms(void const * argument)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(argument);

	portTickType xLastWakeTime;
	    const portTickType xDelay = 50 / portTICK_RATE_MS;
	    // Initialise the xLastWakeTime variable with the current time.
	         xLastWakeTime = xTaskGetTickCount ();
			while(1) {
				/*  Update the time interface for the application module*/
				HAL_getMstime_sig = HAL_GetTick();

				basicReadInputs();

				basicGlobalLedDriver(HAL_GetTick());


				// Wait for the next cycle.
				vTaskDelayUntil( &xLastWakeTime, xDelay );
			}

}
/* USER CODE END 4 */

/* StartDefaultTask function */
void Task100ms(void const * argument)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(argument);
  /* USER CODE BEGIN 5 */
	portTickType xLastWakeTime;
	    const portTickType xDelay = 100 / portTICK_RATE_MS;
	    // Initialise the xLastWakeTime variable with the current time.
	         xLastWakeTime = xTaskGetTickCount ();
			while(1) {

				static unsigned char internalTaskCounter = 0;

				basicReadADCRawValues();

				basicADCErrorHandler();

				basicCheckGlobalErrors();

				MainApplicationSystem_step();

				basicMotorTask();

				if(internalTaskCounter>0) {
					/* refresh IWDG*/
					HAL_IWDG_Refresh(&hiwdg);

					internalTaskCounter = 0;
				}

				internalTaskCounter++;
				// Wait for the next cycle.
				vTaskDelayUntil( &xLastWakeTime, xDelay );
			}
  /* USER CODE END 5 */ 
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* Prevent unused argument(s) compilation warning */
	UNUSED(line); UNUSED(file);
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
