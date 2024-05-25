/*
 * Parameter_settings.h
 *
 *  Created on: 2019年4月10日
 *      Author: Downstream
 */

#ifndef PARAMETER_SETTINGS_H_
#define PARAMETER_SETTINGS_H_

#include "F28x_Project.h"
#include "IQmathLib.h"

/*------------------------------------------------------------------------------
                                    Ti DMClib
------------------------------------------------------------------------------*/
#include "park.h"           //include header for the PARK object
#include "ipark.h"          //include header for the IPARK object
#include "pi.h"             //include header for the PID object
#include "clarke.h"         //include header for the CLARKE object
#include "svgen.h"          //include header for the space vector PWM with Quadrature Control(include IClarke Trans.) object
#include "rampgen.h"        //include header for the generates ramp output of adjustable gain project
#include "rmp_cntl.h"       //include header for the ramp control object
#include "volt_calc.h"      //include header for the phase voltage object
#include "speed_est.h"      //include header for the SPEED_ESTIMATION object     ??
#include "speed_fr.h"       //include header for the SPEED_MEAS_QEP object       ??
#include "smopos.h"
#include "smopos_const.h"

#include "math.h"
#include "pid_grando.h"
#include "pid_reg3.h"

/*------------------------------------------------------------------------------
                            parameter setting
------------------------------------------------------------------------------*/
#define PI 3.1415926        //pi
#define Vd 100                 //DC bus voltage


/*------------------------------------------------------------------------------
                    ISR[interrupt service routine] frequency (KHz)
------------------------------------------------------------------------------*/
#define SYSTEM_FREQUENCY    200
#define ISR_FREQUENCY       20                                 //pwm_interrupt_frequency
#define INV_PWM_TICKS       (SYSTEM_FREQUENCY/ISR_FREQUENCY)*1000
#define INV_PWM_TBPRD       INV_PWM_TICKS/2                    //up-down count mode
#define INV_PWM_HALF_TBPRD  INV_PWM_TBPRD/2
#define DB                  1                                  //Dead Band(us)

/*------------------------------------------------------------------------------
                     set the motor parameters to the one available
------------------------------------------------------------------------------*/
#define SIX_PHASE   1
#define THREE_PHASE 0

#define motor_type THREE_PHASE

#define RS        0.801      //stator resistance
#define RR        0      //rator resistance
#define LS        0.0036      //stator inductance
#define LR        0      //rator inductance
#define LM        0.02      //Magnetizing inductance
#define P         8      //poles

#define RATED_VOLTAGE   Vd/sqrt(3)
#define RATED_CURRENT   18             //sampling current is three times the rated current
#define RATED_TORQUE
#define RATED_FLUX
#define RATED_FREQ      100

#define Jm1     0.006
//#define ws1     8*2*PI
//#define faif    0.0056
//#define WC      300*2*PI
//#define KT_mw   0.0369228
//#define KT_rw   2.7775


/*------------------------------------------------------------------------------
                             program parameter settings
------------------------------------------------------------------------------*/
#define ADC_PU_SCALE_FACTOR        0.000244140625     //1/2^12
#define ADC_PU_PPB_SCALE_FACTOR    0.000488281250     //1/2^11

#define IFB_IA2  AdcbResultRegs.ADCRESULT0
#define IFB_IB2  AdcbResultRegs.ADCRESULT2
#define IFB_IC2  AdcbResultRegs.ADCRESULT1
#define IFB_Total_Voltage  AdcaResultRegs.ADCRESULT4


// Processing Block Result. The result of the offset
// reference Subtraction post conversion processing
// is stored in this register. [writed in an interrupt]
#define IFB_IA2_PPB  ((signed int)AdcbResultRegs.ADCPPB1RESULT.all)
#define IFB_IB2_PPB  ((signed int)AdcbResultRegs.ADCPPB2RESULT.all)
#define IFB_IC2_PPB  ((signed int)AdcbResultRegs.ADCPPB3RESULT.all)

#define IFB_Total_Voltage_PPB  ((signed int)AdcaResultRegs.ADCRESULT4)
#define IFB_Total_Current_PPB  ((signed int)AdcbResultRegs.ADCPPB2RESULT.all)

#define LEM_TO_ADC              20.053333   //[(50(量程)/2000(传感器系数)*(470/4测量电阻)+3]/2/3*2048(后电流叠加板减半)
#define Total_Voltage_FACTOR    0.1472204
#endif




/* PARAMETER_SETTINGS_H_ */
