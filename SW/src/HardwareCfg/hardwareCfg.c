/*
 * hardwareCfg.c
 *
 *  Created on: May 26, 2019
 *      Author: unix
 */
#include "hardwareCfg.h"

#include "interfaces.h"

ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim4;

IWDG_HandleTypeDef hiwdg;


void SystemClock_Config(void)
{


	  RCC_OscInitTypeDef RCC_OscInitStruct;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_PeriphCLKInitTypeDef PeriphClkInit;

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Initializes the CPU, AHB and APB busses clocks
	    */
	  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /**Enables the Clock Security System
	    */
	  HAL_RCC_EnableCSS();

	    /**Configure the Systick interrupt time
	    */
	  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	    /**Configure the Systick
	    */
	  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	  /* SysTick_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  /**Configure Regular Channel
      */
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

      /**Configure Regular Channel
      */
    sConfig.Channel = ADC_CHANNEL_2;
    sConfig.Rank = ADC_REGULAR_RANK_2;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

      /**Configure Regular Channel
      */
    sConfig.Channel = ADC_CHANNEL_8;
    sConfig.Rank = ADC_REGULAR_RANK_3;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }


}

/* TIM4 init function */
void MX_TIM4_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 20;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 327;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim4);

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();



  /*Configure GPIO pin : nFaultInput_Pin */
  GPIO_InitStruct.Pin = nFaultInput_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(nFaultInput_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NSLeepMotorDriver_Pin RedLed_Pin GreenLed_Pin PowerLed_Pin
                           DisableMotorDriver_Pin PB5 */
  GPIO_InitStruct.Pin = NSLeepMotorDriver_Pin|RedLed_Pin|GreenLed_Pin|PowerLed_Pin
                          |DisableMotorDriver_Pin|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOB, RedLed_Pin|GreenLed_Pin|PowerLed_Pin
                           |GPIO_PIN_5, GPIO_PIN_RESET);
  /* init States of motor driver */
	/* nSleep To enter a low-power sleep mode, set this pin logic low.*/
	HAL_GPIO_WritePin(NSLeepMotorDriver_GPIO_Port,NSLeepMotorDriver_Pin,GPIO_PIN_RESET);

	/* Bridge enable input. A logic high on this pin disables the H-bridge Hi-Z. Internal pullup to DVDD */
	HAL_GPIO_WritePin(DisableMotorDriver_GPIO_Port,DisableMotorDriver_Pin,GPIO_PIN_SET);

}

void basicStartTIM4(void) {

    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);

    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);

    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,(uint16_t)0);

    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,(uint16_t)0);
}

void basicReadInputs(void) {

	/* Read users button request, invert the input cause of pull up resistor */
	StartStopUserRequest_sig = !(HAL_GPIO_ReadPin(InputUserRequestButton_GPIO_Port, InputUserRequestButton_Pin));

	/* Read hardware drv8873 input failure status. invert the input. Hardware low logic means error */
	HBridgeFailureCode_sig = !(HAL_GPIO_ReadPin(nFaultInput_GPIO_Port, nFaultInput_Pin));
}
/* IWDG init function */
void MX_IWDG_Init(void)
{

  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_256;
  hiwdg.Init.Reload = 30;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
