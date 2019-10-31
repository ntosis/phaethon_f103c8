/*
 * File: MainApplicationSystem.c
 *
 * Code generated for Simulink model 'MainApplicationSystem'.
 *
 * Model version                  : 1.56
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Tue Jun 18 10:27:10 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MainApplicationSystem.h"
#include "MainApplicationSystem_private.h"

/* Block signals (default storage) */
B_MainApplicationSystem_T MainApplicationSystem_B;

/* Block states (default storage) */
DW_MainApplicationSystem_T MainApplicationSystem_DW;

/* Real-time model */
RT_MODEL_MainApplicationSyste_T MainApplicationSystem_M_;
RT_MODEL_MainApplicationSyste_T *const MainApplicationSystem_M =
  &MainApplicationSystem_M_;
real32_T rtb_Gain;
/*
 * System reset for enable system:
 *    '<S4>/Subsystem'
 *    '<S4>/Subsystem1'
 */
void MainApplication_Subsystem_Reset(DW_Subsystem_MainApplicationS_T *localDW)
{
  /* InitializeConditions for UnitDelay: '<S8>/Unit Delay' */
  localDW->UnitDelay_DSTATE = 0U;
}

/*
 * Disable for enable system:
 *    '<S4>/Subsystem'
 *    '<S4>/Subsystem1'
 */
void MainApplicati_Subsystem_Disable(boolean_T *rty_Out1,
  DW_Subsystem_MainApplicationS_T *localDW)
{
  /* Outputs for Enabled SubSystem: '<S4>/Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  /* Disable for Outport: '<S8>/Out1' */
  *rty_Out1 = false;

  /* End of Outputs for SubSystem: '<S4>/Subsystem' */
  localDW->Subsystem_MODE = false;
}

/*
 * Output and update for enable system:
 *    '<S4>/Subsystem'
 *    '<S4>/Subsystem1'
 */
void MainApplicationSystem_Subsystem(boolean_T rtu_Enable, boolean_T *rty_Out1,
  DW_Subsystem_MainApplicationS_T *localDW)
{
  int32_T tmp;

  /* Outputs for Enabled SubSystem: '<S4>/Subsystem' incorporates:
   *  EnablePort: '<S8>/Enable'
   */
  if (rtu_Enable) {
    if (!localDW->Subsystem_MODE) {
      MainApplication_Subsystem_Reset(localDW);
      localDW->Subsystem_MODE = true;
    }

    /* Sum: '<S8>/Add' incorporates:
     *  Constant: '<S8>/Constant'
     *  UnitDelay: '<S8>/Unit Delay'
     */
    tmp = (int32_T)(1U + localDW->UnitDelay_DSTATE);
    if ((uint32_T)tmp > 255U) {
      tmp = 255;
    }

    /* RelationalOperator: '<S10>/Compare' incorporates:
     *  Constant: '<S10>/Constant'
     *  Sum: '<S8>/Add'
     */
    *rty_Out1 = ((uint8_T)tmp > DebounceStepsToSetminmaxCurrError_C);

    /* Update for UnitDelay: '<S8>/Unit Delay' incorporates:
     *  Sum: '<S8>/Add'
     */
    localDW->UnitDelay_DSTATE = (uint8_T)tmp;
  } else {
    if (localDW->Subsystem_MODE) {
      MainApplicati_Subsystem_Disable(rty_Out1, localDW);
    }
  }

  /* End of Outputs for SubSystem: '<S4>/Subsystem' */
}

/* Model step function */
void MainApplicationSystem_step(void)
{
  boolean_T rtb_FixPtRelationalOperator_c;
  //real32_T rtb_Gain;
  boolean_T rtb_UnitDelay1_a;
  boolean_T rtb_FailureFlag_j;
  uint32_T rtb_Switch;
  uint32_T qY;

  /* RelationalOperator: '<S3>/FixPt Relational Operator' incorporates:
   *  Inport: '<Root>/StartStopUserRequest'
   *  UnitDelay: '<S3>/Delay Input1'
   *
   * Block description for '<S3>/Delay Input1':
   *
   *  Store in Global RAM
   */
  rtb_FixPtRelationalOperator_c = ((int32_T)StartStopUserRequest_sig > (int32_T)
    MainApplicationSystem_DW.DelayInput1_DSTATE);

  /* Gain: '<S7>/Gain' incorporates:
   *  Constant: '<S7>/Iprop Resistor Value'
   *  Constant: '<S7>/adc resolution (12bit) 3.3 volt reference'
   *  DataTypeConversion: '<S7>/Data Type Conversion'
   *  Inport: '<Root>/MotorCurrentADCRawValue'
   *  Product: '<S7>/Divide'
   *  Product: '<S7>/Divide1'
   */
  rtb_Gain = (real32_T)MotorCurrentADCRawValue_sig * ADCResolutionmVproBit_C /
    (real32_T)IpropResistorValue_C * (real32_T)IPROPFactor_C;

  /* Outputs for Enabled SubSystem: '<S4>/Subsystem1' */
  /* RelationalOperator: '<S4>/Relational Operator' incorporates:
   *  Constant: '<S4>/MaxMotorCurrent'
   */
  MainApplicationSystem_Subsystem(rtb_Gain >= MaxMotorCurrent_C,
    &MainApplicationSystem_B.Compare, &MainApplicationSystem_DW.Subsystem1);

  /* End of Outputs for SubSystem: '<S4>/Subsystem1' */

  /* Logic: '<S4>/AND1' incorporates:
   *  Inport: '<Root>/HBridgeFailureCode'
   *  Logic: '<S4>/or'
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  rtb_FailureFlag_j = ((MainApplicationSystem_B.Compare ||
                        HBridgeFailureCode_sig) && MotorRotationRequest_sig);

  /* Outputs for Enabled SubSystem: '<S4>/Subsystem' */
  /* Logic: '<S4>/AND' incorporates:
   *  Constant: '<S4>/MinMotorCurrent'
   *  RelationalOperator: '<S4>/Relational Operator1'
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  MainApplicationSystem_Subsystem((rtb_Gain <= MinMotorCurrent_C) &&
    MotorRotationRequest_sig, &MainApplicationSystem_B.Compare_i,
    &MainApplicationSystem_DW.Subsystem);

  /* End of Outputs for SubSystem: '<S4>/Subsystem' */

  /* Switch: '<S4>/Switch' incorporates:
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  rtb_UnitDelay1_a = (MotorRotationRequest_sig &&
                      MainApplicationSystem_B.Compare_i);

  /* Logic: '<S1>/xor ' incorporates:
   *  Logic: '<S1>/OR1'
   *  UnitDelay: '<S1>/Unit Delay'
   */
  MotorRotationRequest_sig = (boolean_T)((rtb_FixPtRelationalOperator_c ||
    rtb_FailureFlag_j || rtb_UnitDelay1_a) ^ MotorRotationRequest_sig);

  /* Logic: '<S5>/xor motor direction' incorporates:
   *  RelationalOperator: '<S12>/FixPt Relational Operator'
   *  UnitDelay: '<S12>/Delay Input1'
   *  UnitDelay: '<S5>/Unit Delay1'
   *
   * Block description for '<S12>/Delay Input1':
   *
   *  Store in Global RAM
   */
  MotorDirection_sig = (boolean_T)(((int32_T)MotorRotationRequest_sig < (int32_T)
    MainApplicationSystem_DW.DelayInput1_DSTATE_n) ^ MotorDirection_sig);

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/AmbientLightOnTime_C'
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  if (rtb_FixPtRelationalOperator_c) {
    rtb_Switch = AmbientLightOnTime_C;
  } else {
    rtb_Switch = MainApplicationSystem_DW.UnitDelay1_DSTATE;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Sum: '<S2>/Add1' incorporates:
   *  Inport: '<Root>/In3'
   *  UnitDelay: '<S2>/Unit Delay'
   */
  qY = (rtb_Switch - HAL_getMstime_sig) +
    MainApplicationSystem_DW.UnitDelay_DSTATE;
  if (qY > rtb_Switch) {
    qY = 0U;
  }

  /* RelationalOperator: '<S6>/Compare' incorporates:
   *  Constant: '<S6>/Constant'
   *  Sum: '<S2>/Add1'
   */
  AmbientLightRequest_sig = (qY > 0U);

  /* Logic: '<S1>/OR' */
  ApplicationInternalError_sig = (rtb_FailureFlag_j || rtb_UnitDelay1_a);

  /* Update for UnitDelay: '<S3>/Delay Input1' incorporates:
   *  Inport: '<Root>/StartStopUserRequest'
   *
   * Block description for '<S3>/Delay Input1':
   *
   *  Store in Global RAM
   */
  MainApplicationSystem_DW.DelayInput1_DSTATE = StartStopUserRequest_sig;

  /* Update for UnitDelay: '<S12>/Delay Input1'
   *
   * Block description for '<S12>/Delay Input1':
   *
   *  Store in Global RAM
   */
  MainApplicationSystem_DW.DelayInput1_DSTATE_n = MotorRotationRequest_sig;

  /* Update for UnitDelay: '<S2>/Unit Delay1' incorporates:
   *  Sum: '<S2>/Add1'
   */
  MainApplicationSystem_DW.UnitDelay1_DSTATE = qY;

  /* Update for UnitDelay: '<S2>/Unit Delay' incorporates:
   *  Inport: '<Root>/In3'
   */
  MainApplicationSystem_DW.UnitDelay_DSTATE = HAL_getMstime_sig;
}

/* Model initialize function */
void MainApplicationSystem_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void MainApplicationSystem_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
