/*
 * F2837xD_EPwmMACRO.h
 *
 *  使用该头文件设置pwm模块时，PeriodMax即TBPRD为pwm周期的一半。CMPA/TBPRD即为占空比。
 *
 */

#ifndef F2837xD_EPwmMACRO_H__
#define F2837xD_EPwmMACRO_H__

#include "F2837xD_drvlib.h"
#include "F2837xD_xbmsk.h"
#include "IQmathLib.h"
/*----------------------------------------------------------------------------
Initialization constant for the F28377 Time-Base Control Registers for PWM Generation.
Sets up the timer to run free upon emulation suspend, count up-down mode
prescaler 1.
----------------------------------------------------------------------------*/
#define PWM_INIT_STATE ( FREE_RUN_FLAG +        /*自由运行*/ \
                         PRDLD_IMMEDIATE  +       /*禁止影子寄存器*/\
                         TIMER_CNT_UPDN +         /*计数模式 上-下*/\
                         HSPCLKDIV_PRESCALE_X_1 + /*高速外设时基不分频*/\
                         CLKDIV_PRESCALE_X_1  +   /*时基时钟不分频*/\
                         PHSDIR_CNT_UP    +       /*同步信号到来时向上计数*/\
                         CNTLD_DISABLE/*禁止装载相位寄存器*/ )

/*----------------------------------------------------------------------------
Initialization constant for the F28377 Compare Control Register.
----------------------------------------------------------------------------*/
#define CMPCTL_INIT_STATE ( LOADAMODE_ZRO + /*CMPA影子装载模式，CTR=0*/\
                            LOADBMODE_ZRO + /*CMPB影子装载模式，CTR=0*/\
                            SHDWAMODE_SHADOW + /*缓冲装载*/\
                            SHDWBMODE_SHADOW )

/*----------------------------------------------------------------------------
Initialization constant for the F28377 Action Qualifier Output A Register.
----------------------------------------------------------------------------*/
#define AQCTLA_INIT_STATE ( CAD_SET/*向下计数时基计数器=CMPA输出高*/ + CAU_CLEAR/*向上计数时基计数器=CMPA清零，使 ePWMxA 输出低*/ )
/*只用到了CMPA*/
/*----------------------------------------------------------------------------
Initialization constant for the F28377 Dead-Band Generator registers for PWM Generation.
Sets up the dead band for PWM and sets up dead band values.
----------------------------------------------------------------------------*/
#define DBCTL_INIT_STATE  (BP_ENABLE + POLSEL_ACTIVE_HI_CMP )

#define DBCNT_INIT_STATE   200   // 200 counts = 1) usec (delay)  (for TBCLK = SYSCLK/1)

/*----------------------------------------------------------------------------
Initialization constant for the F28377 PWM Chopper Control register for PWM Generation.
----------------------------------------------------------------------------*/
#define  PCCTL_INIT_STATE  CHPEN_DISABLE

/*----------------------------------------------------------------------------
Initialization constant for the F28377 Trip Zone Select Register
----------------------------------------------------------------------------*/
#define  TZSEL_INIT_STATE  DISABLE_TZSEL

/*----------------------------------------------------------------------------
Initialization constant for the F28377 Trip Zone Control Register
----------------------------------------------------------------------------*/
#define  TZCTL_INIT_STATE ( TZA_FORCE_LO + TZB_FORCE_LO + \
                            DCAEVT1_HI_Z + DCAEVT2_HI_Z + \
                            DCBEVT1_HI_Z + DCBEVT2_HI_Z )

/*-----------------------------------------------------------------------------
	Define the structure of the PWM Driver Object
-----------------------------------------------------------------------------*/
typedef struct {
        Uint16 PeriodMax;   // Parameter: PWM Half-Period in CPU clock cycles (Q0)
        Uint16 HalfPerMax;	// Parameter: Half of PeriodMax (Q0)
        Uint16 Deadband;    // Parameter: PWM deadband in CPU clock cycles (Q0)
        _iq MfuncC1;        // Input: EPWM1 A&B Duty cycle ratio (Q24)
        _iq MfuncC2;        // Input: EPWM2 A&B Duty cycle ratio (Q24)
        _iq MfuncC3;        // Input: EPWM3 A&B Duty cycle ratio (Q24)
        } PWMGEN ;


/*------------------------------------------------------------------------------
	Default Initializers for the F2833X PWMGEN Object
------------------------------------------------------------------------------*/
#define F28377_FC_PWM_GEN    { 1000,  \
							   1000,  \
                              	200,  \
                              0x4000, \
                              0x4000, \
                              0x4000, \
                             }


#define PWMGEN_DEFAULTS 	F28377_FC_PWM_GEN

/*------------------------------------------------------------------------------
	PWM Init & PWM Update Macro Definitions
------------------------------------------------------------------------------*/



#define PWM_INIT_MACRO(ch1,ch2,ch3,v)										\
	     /* Setup Sync*/													\
         (*ePWM[ch1]).TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/		\
		 (*ePWM[ch2]).TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/		\
		 (*ePWM[ch3]).TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/		\
		 																	\
         /* Allow each timer to be sync'ed*/								\
         (*ePWM[ch1]).TBCTL.bit.PHSEN = 1;									\
         (*ePWM[ch2]).TBCTL.bit.PHSEN = 1;									\
         (*ePWM[ch3]).TBCTL.bit.PHSEN = 1;									\
         																	\
         /* Init Timer-Base Period Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).TBPRD = v.PeriodMax;									\
         (*ePWM[ch2]).TBPRD = v.PeriodMax;									\
         (*ePWM[ch3]).TBPRD = v.PeriodMax;									\
																			\
         /* Init Timer-Base Phase Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).TBPHS.bit.TBPHS = 0;									\
         (*ePWM[ch2]).TBPHS.bit.TBPHS = 0;									\
         (*ePWM[ch3]).TBPHS.bit.TBPHS = 0;									\
																			\
         /* Init Timer-Base Control Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).TBCTL.all = PWM_INIT_STATE;							\
		 (*ePWM[ch2]).TBCTL.all = PWM_INIT_STATE;							\
		 (*ePWM[ch3]).TBCTL.all = PWM_INIT_STATE;							\
																			\
         /* Init Compare Control Register for EPWM1-EPWM3*/					\
         (*ePWM[ch1]).CMPCTL.all = CMPCTL_INIT_STATE;						\
         (*ePWM[ch2]).CMPCTL.all = CMPCTL_INIT_STATE;						\
         (*ePWM[ch3]).CMPCTL.all = CMPCTL_INIT_STATE;						\
																			\
         /* Init Action Qualifier Output A Register for EPWM1-EPWM3*/		\
         (*ePWM[ch1]).AQCTLA.all = AQCTLA_INIT_STATE;						\
         (*ePWM[ch2]).AQCTLA.all = AQCTLA_INIT_STATE;						\
         (*ePWM[ch3]).AQCTLA.all = AQCTLA_INIT_STATE;						\
																			\
         /* Init Dead-Band Generator Control Register for EPWM1-EPWM3*/		\
         (*ePWM[ch1]).DBCTL.all = DBCTL_INIT_STATE;							\
         (*ePWM[ch2]).DBCTL.all = DBCTL_INIT_STATE;							\
         (*ePWM[ch3]).DBCTL.all = DBCTL_INIT_STATE;							\
         	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	\
																			\
         /* Init Dead-Band Generator for EPWM1-EPWM3*/						\
         (*ePWM[ch1]).DBFED.bit.DBFED = v.Deadband;									\
         (*ePWM[ch1]).DBRED.bit.DBRED = v.Deadband;									\
         (*ePWM[ch2]).DBFED.bit.DBFED = v.Deadband;									\
         (*ePWM[ch2]).DBRED.bit.DBRED = v.Deadband;									\
         (*ePWM[ch3]).DBFED.bit.DBFED = v.Deadband;									\
         (*ePWM[ch3]).DBRED.bit.DBRED = v.Deadband;									\
																			\
         /* Init PWM Chopper Control Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).PCCTL.all = PCCTL_INIT_STATE;							\
         (*ePWM[ch2]).PCCTL.all = PCCTL_INIT_STATE;							\
         (*ePWM[ch3]).PCCTL.all = PCCTL_INIT_STATE;							\
          																	\
         EALLOW;                       /* Enable EALLOW */					\
																			\
         /* Init Trip Zone Select Register*/								\
         (*ePWM[ch1]).TZSEL.all = TZSEL_INIT_STATE;							\
         (*ePWM[ch2]).TZSEL.all = TZSEL_INIT_STATE;							\
         (*ePWM[ch3]).TZSEL.all = TZSEL_INIT_STATE;							\
																			\
         /* Init Trip Zone Control Register*/								\
         (*ePWM[ch1]).TZCTL.all = TZCTL_INIT_STATE;							\
         (*ePWM[ch2]).TZCTL.all = TZCTL_INIT_STATE;							\
         (*ePWM[ch3]).TZCTL.all = TZCTL_INIT_STATE;							\
																			\
         EDIS;                         /* Disable EALLOW*/



#define PWM_MACRO(ch1,ch2,ch3,v)													\
																					\
/*  Mfuncx range is (-1,1)														*/	\
/*  The code below changes PeriodMax*Mfuncx range ....  						*/	\
/*  from (-PeriodMax,PeriodMax) to (0,PeriodMax) where HalfPerMax=PeriodMax/2	*/	\
																					\
	(*ePWM[ch1]).CMPA.bit.CMPA = _IQmpy(v.HalfPerMax,v.MfuncC1)+ v.HalfPerMax;		\
	(*ePWM[ch2]).CMPA.bit.CMPA = _IQmpy(v.HalfPerMax,v.MfuncC2)+ v.HalfPerMax;		\
	(*ePWM[ch3]).CMPA.bit.CMPA = _IQmpy(v.HalfPerMax,v.MfuncC3)+ v.HalfPerMax;		\




#endif /* F28377PWM_H_ */
