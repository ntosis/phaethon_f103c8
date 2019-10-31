/*
 * File: MainApplicationSystem.h
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

#ifndef RTW_HEADER_MainApplicationSystem_h_
#define RTW_HEADER_MainApplicationSystem_h_
#ifndef MainApplicationSystem_COMMON_INCLUDES_
# define MainApplicationSystem_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* MainApplicationSystem_COMMON_INCLUDES_ */

#include "MainApplicationSystem_types.h"

/* Includes for objects with custom storage classes. */
#include "tunableParams.h"
#include "interfaces.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<S4>/Subsystem' */
typedef struct {
  uint8_T UnitDelay_DSTATE;            /* '<S8>/Unit Delay' */
  boolean_T Subsystem_MODE;            /* '<S4>/Subsystem' */
} DW_Subsystem_MainApplicationS_T;

/* Block signals (default storage) */
typedef struct {
  boolean_T Compare;                   /* '<S11>/Compare' */
  boolean_T Compare_i;                 /* '<S10>/Compare' */
} B_MainApplicationSystem_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint32_T UnitDelay1_DSTATE;          /* '<S2>/Unit Delay1' */
  uint32_T UnitDelay_DSTATE;           /* '<S2>/Unit Delay' */
  boolean_T DelayInput1_DSTATE;        /* '<S3>/Delay Input1' */
  boolean_T DelayInput1_DSTATE_n;      /* '<S12>/Delay Input1' */
  DW_Subsystem_MainApplicationS_T Subsystem1;/* '<S4>/Subsystem1' */
  DW_Subsystem_MainApplicationS_T Subsystem;/* '<S4>/Subsystem' */
} DW_MainApplicationSystem_T;

/* Real-time Model Data Structure */
struct tag_RTM_MainApplicationSystem_T {
  const char_T *errorStatus;
};

/* Block signals (default storage) */
extern B_MainApplicationSystem_T MainApplicationSystem_B;

/* Block states (default storage) */
extern DW_MainApplicationSystem_T MainApplicationSystem_DW;

/* Model entry point functions */
extern void MainApplicationSystem_initialize(void);
extern void MainApplicationSystem_step(void);
extern void MainApplicationSystem_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MainApplicationSyste_T *const MainApplicationSystem_M;
extern real32_T rtb_Gain;
/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S7>/Display' : Unused code path elimination
 * Block '<S7>/Display1' : Unused code path elimination
 * Block '<S7>/Display2' : Unused code path elimination
 * Block '<S7>/Display3' : Unused code path elimination
 * Block '<S7>/Display4' : Unused code path elimination
 * Block '<S7>/Display5' : Unused code path elimination
 * Block '<S5>/Switch' : Eliminated due to constant selection input
 * Block '<S5>/Extern motor direction' : Unused code path elimination
 * Block '<S5>/calibration ' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('AppSoftware/MainApplicationSystem')    - opens subsystem AppSoftware/MainApplicationSystem
 * hilite_system('AppSoftware/MainApplicationSystem/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'AppSoftware'
 * '<S1>'   : 'AppSoftware/MainApplicationSystem'
 * '<S2>'   : 'AppSoftware/MainApplicationSystem/Ambient light system'
 * '<S3>'   : 'AppSoftware/MainApplicationSystem/Detect Increase'
 * '<S4>'   : 'AppSoftware/MainApplicationSystem/Failure system'
 * '<S5>'   : 'AppSoftware/MainApplicationSystem/Motor direction system'
 * '<S6>'   : 'AppSoftware/MainApplicationSystem/Ambient light system/Compare To Zero'
 * '<S7>'   : 'AppSoftware/MainApplicationSystem/Failure system/Convert ADC to Amperes'
 * '<S8>'   : 'AppSoftware/MainApplicationSystem/Failure system/Subsystem'
 * '<S9>'   : 'AppSoftware/MainApplicationSystem/Failure system/Subsystem1'
 * '<S10>'  : 'AppSoftware/MainApplicationSystem/Failure system/Subsystem/Compare To Constant'
 * '<S11>'  : 'AppSoftware/MainApplicationSystem/Failure system/Subsystem1/Compare To Constant'
 * '<S12>'  : 'AppSoftware/MainApplicationSystem/Motor direction system/Detect Decrease'
 */
#endif                                 /* RTW_HEADER_MainApplicationSystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
