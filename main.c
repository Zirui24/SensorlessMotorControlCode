//###########################################################################
//
// FILE:   main.c
// AUTHOR:  Zirui Liu
// TITLE:  PMSM_demo
//
//###########################################################################
#include "F28x_Project.h"
#include "User_include.h"
#include "Parameter_settings.h"
#include "math.h"
#include "Kalman.h"

extern SPEED_MEAS_QEP speed1;

extern SPEED_ESTIMATION speed3;
extern RAMPGEN rg1;
extern PID_CONTROLLER  pid_spd;
extern PI_CONTROLLER   pi_id;
extern PI_CONTROLLER   pi_iq;
extern _iq SpeedRef;
extern float32 T;
extern PHASEVOLTAGE volt1;


extern SMOPOS smo1;
extern SMOPOS_CONST smo1_const;

extern _iq IdRef_lock,
           IdRef_run ,
           IqRef_lock,
           IqRef_run,
           VdTesting,
           VqTesting,
           I_Kp_Test,
           I_Ki_Test,
           S_Kp_Test,
           S_Ki_Test;

extern PARK park1;
extern CLARKE clarke1;

int main(void)
  {
    short data_sci[32];
	InitSysCtrl();
	InitGpio();

	DINT;

	InitPieCtrl();

    IER = 0x0000;       //Disable CPU interrupt flag
    IFR = 0x0000;       //Clear CPU interrupt flag

    InitPieVectTable();

    EALLOW;
    PieVectTable.EPWM1_INT = &OffsetISR;    //function for EPWM1 interrupt 1
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 0; //Change default EPWM frequency from 100MHZ to 200MHZ
    EDIS;


    // PWM≥ı ºªØ
    InitEPwmGpio();
    ConfigureEPwm();

    Configure_ADC();
    InitADC();
    InitEQep1Gpio();
    ConfigureEQep();
    //    HVDMC_Protection();
    //  IOSet();
    //  Init5742();
    Configure_DAC();
    // Initialize SCI module
    Configure_Sci_A();
    scia_ximt(0xaa);
    //  ConfigureScic();

    // ****************************************************************************
    // ****************************************************************************
    // Paramaeter Initialisation
    // ****************************************************************************
    // ****************************************************************************

        // Initialize the Speed module for speed calculation from QEP/RESOLVER
    speed1.K1 = _IQ21(1/(RATED_FREQ*T));
    speed1.K2 = _IQ(1/(1+T*2*PI*5));      // Low-pass cut-off frequency
    speed1.K3 = _IQ(1)-speed1.K2;
    speed1.BaseRpm = 120/P*RATED_FREQ;


    // Initialize the Speed module for QEP based speed calculation
    speed1.K1 = _IQ21(1/(RATED_FREQ*T));
    speed1.K2 = _IQ(1/(1+T*2*PI*5));  // Low-pass cut-off frequency
    speed1.K3 = _IQ(1)-speed1.K2;
    speed1.BaseRpm = 120/P*RATED_FREQ;

    // Initialize the SPEED_EST module SMOPOS based speed calculation
    speed3.K1 = _IQ21(1/(RATED_FREQ*T));
    speed3.K2 = _IQ(1/(1+T*2*PI*5));  // Low-pass cut-off frequency
    speed3.K3 = _IQ(1)-speed3.K2;
    speed3.BaseRpm = 120/P*RATED_FREQ;


    smo1_const.Rs = RS;
    smo1_const.Ls = LS;
    smo1_const.Ib = RATED_CURRENT;
    smo1_const.Vb = RATED_VOLTAGE;
    smo1_const.Ts = T;
    SMO_CONST_MACRO(smo1_const)

    // Initialize the SMOPOS module
    smo1.Fsmopos = _IQ(smo1_const.Fsmopos);
    smo1.Gsmopos = _IQ(smo1_const.Gsmopos);
    smo1.Kslide  = _IQ(0.05308703613);
    smo1.Kslf = _IQ(0.017073975);


    // Initialize the RAMPGEN module
    rg1.StepAngleMax = _IQ(RATED_FREQ*T);

        // Initialize the PID module for speed
    pid_spd.param.Kp   = _IQ(0.58);
    pid_spd.param.Ki   = _IQ(0.004);
    pid_spd.param.Kd   = _IQ(0.0);
    pid_spd.param.Kr   = _IQ(1.0);
    pid_spd.param.Umax = _IQ(0.95);
    pid_spd.param.Umin = _IQ(-0.95);

        // Init PI module for ID loop
    pi_id.Kp   = _IQ(2.5);//_IQ(3.0);
    pi_id.Ki   = _IQ(0.05);//0.00125;
    pi_id.Umax = _IQ(0.5);
    pi_id.Umin = _IQ(-0.5);

        // Init PI module for IQ loop
    pi_iq.Kp   = _IQ(2.5);//_IQ(4.0);
    pi_iq.Ki   = _IQ(0.05);//0.00125;
    pi_iq.Umax = _IQ(0.8);
    pi_iq.Umin = _IQ(-0.8);

        // Set mock REFERENCES for Speed and Iq loops
    SpeedRef = 0.08;    //0.05

        // ****************************************************************************

    //Enable global Interrupts and higher priority real-time debug events:
    IER |= M_INT3; //Enable group 3 interrupts
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //enable PIE interrupt
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;  //EPwm1INT

    //sync ePWM
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;


    for(;;)
    {
        // State machine entry & exit point
        //===========================================================
//        (*Alpha_State_Ptr)();   // jump to an Alpha state (A0,B0,...)
        pi_iq.Kp   = I_Kp_Test;//_IQ(4.0);
        pi_iq.Ki   = I_Ki_Test;//0.00125;

        pi_id.Kp   = I_Kp_Test;//_IQ(3.0);
        pi_id.Ki   = I_Ki_Test;//0.00125;

        pid_spd.param.Kp   = S_Kp_Test;
        pid_spd.param.Ki   = S_Ki_Test;
        //===========================================================

        data_sci[0] = speed3.EstimatedTheta*100;
        data_sci[1] = speed1.ElecTheta*100;

        data_sci[2] = smo1.Zbeta*100;
        data_sci[3] = smo1.Zalpha*100;

        data_sci[2] = smo1.IalphaError*100;
        data_sci[3] = smo1.IbetaError*100;

        shanwai_sci(data_sci);

    }
}
