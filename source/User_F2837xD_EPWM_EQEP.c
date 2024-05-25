//###########################################################################
//
// FILE:   User_F2837xD_EPWM.c
// AUTHOR:  Zirui Liu
// TITLE:  F2837xD EPWM Initialization & Support Functions.
//
//###########################################################################

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "Parameter_settings.h"
#include "User_F2837xD_EPWM_EQEP.h"

#include "F2837xD_EPwmMACRO.h"
#include "F2837xD_EQepMACRO.h"

// **********************************************************
// ********************* Functions **************************
// **********************************************************
_iq ramper(_iq in, _iq out, _iq rampDelta);

//*********************** USER Variables *************************************
// Global variables used in this system
//****************************************************************************
Uint16 DA_A;
Uint16 DA_B;
Uint16 DA_C;

Uint16 volt_Ds = 0;
Uint16 volt_Qs = 0;
// ****************************************************************************
// Variables for current measurement
// ****************************************************************************
int16 Offset_counter=0;

_iq K1 = _IQ(0.998),          // Offset filter coefficient K1: 0.05/(T+0.05);
    K2 = _IQ(0.001999);       // Offset filter coefficient K2: T/(T+0.05);

_iq IA_Offset=0,
    IB_Offset=0,
    IC_Offset=0,
    Total_Voltage_Offset=0;

// ****************************************************************************
// Flag variables
// ****************************************************************************
// lsw =0 定位
//     =1 电流闭环
//     =2 双闭环
//     =3 开环
Uint16 lsw = 0,
       TripFlagDMC = 0,              //PWM trip status
       clearTripFlagDMC = 0,
       Block_PWM = 0,                //PWM protection
       RunMotor = 0;

Uint16 VVF_flag = 0;

Uint16 SpeedLoopPrescaler = 10,      // Speed loop pre scalar
       SpeedLoopCount = 1;           // Speed loop counter

// ****************************************************************************
// Variables for Field Oriented Control
// ****************************************************************************
float32 T = 0.001/ISR_FREQUENCY;    // Samping period (sec), see parameter.h
_iq IdRef     = _IQ(0.0),           // Id reference (pu)
    IqRef     = _IQ(0.0),           // Iq reference (pu)
    SpeedRef  = _IQ(0.0);           // For Closed Loop tests

// Instance a few transform objects
CLARKE clarke1 = CLARKE_DEFAULTS;
PARK   park1   = PARK_DEFAULTS;
IPARK  ipark1  = IPARK_DEFAULTS;

// Instance PI(D) regulators to regulate the d and q  axis currents, speed and position
PID_CONTROLLER  pid_spd = {PID_TERM_DEFAULTS, PID_PARAM_DEFAULTS, PID_DATA_DEFAULTS};
PI_CONTROLLER   pi_id   = PI_CONTROLLER_DEFAULTS;
PI_CONTROLLER   pi_iq   = PI_CONTROLLER_DEFAULTS;
// Instance a PWM driver instance
PWMGEN pwm1 = PWMGEN_DEFAULTS;

// Instance a Space Vector PWM modulator. This modulator generates a, b and c
// phases based on the d and q stationery reference frame inputs
SVGEN svgen1 = SVGEN_DEFAULTS;

// Instance a ramp controller to smoothly ramp the frequency
RMPCNTL rc1 = RMPCNTL_DEFAULTS;

//  Instance a ramp generator to simulate an Anglele
RAMPGEN rg1 = RAMPGEN_DEFAULTS;

//  Instance a phase voltage calculation
PHASEVOLTAGE volt1 = PHASEVOLTAGE_DEFAULTS;

// Instance a speed calculator based on Encoder position
SPEED_MEAS_QEP speed1 = SPEED_MEAS_QEP_DEFAULTS;


// Instance a speed calculator based on sliding-mode position observer
SPEED_ESTIMATION speed3 = SPEED_ESTIMATION_DEFAULTS;


// Instance a QEP interface driver
QEP qep1 = QEP_DEFAULTS;

// Instance a position estimator
SMOPOS smo1 = SMOPOS_DEFAULTS;
// Instance a sliding-mode position observer constant Module
SMOPOS_CONST smo1_const = SMOPOS_CONST_DEFAULTS;

// Variables for Position Sensor Suite
_iq  IdRef_lock = _IQ(0.2),
     IdRef_run  = _IQ(0.0),
     IqRef_lock = _IQ(0.0),
     IqRef_run  = _IQ(0.0),
     VdTesting  = _IQ(0.0),
     VqTesting  = _IQ(0.1),
     I_Kp_Test  = _IQ(2.5),
     I_Ki_Test  = _IQ(0.05),
     S_Kp_Test  = _IQ(0.4),
     S_Ki_Test  = _IQ(0.004);

_iq  Us,     EQep_cont;


void reset_pull_up(void)
{

    EALLOW;

    GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO38 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO38 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO39 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO40 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO40 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO41 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO41 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO44 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO45 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO45 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO46 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO46 = 0;

    GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO47 = 1;
    GpioCtrlRegs.GPBQSEL1.bit.GPIO47 = 0;

    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO48 = 0;

    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO49 = 0;

    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO50 = 1;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 0;

    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 0;     //RESET
    GpioCtrlRegs.GPBDIR.bit.GPIO51 = 1;
    GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 0;

    EDIS;

    //RESET
    GpioDataRegs.GPBSET.bit.GPIO38=1;
    GpioDataRegs.GPBSET.bit.GPIO39=1;
    GpioDataRegs.GPBSET.bit.GPIO40=1;
    GpioDataRegs.GPBSET.bit.GPIO41=1;
    GpioDataRegs.GPBSET.bit.GPIO44=1;
    GpioDataRegs.GPBSET.bit.GPIO45=1;
    GpioDataRegs.GPBSET.bit.GPIO46=1;
    GpioDataRegs.GPBSET.bit.GPIO47=1;
    GpioDataRegs.GPBSET.bit.GPIO48=1;
    GpioDataRegs.GPBSET.bit.GPIO49=1;
    GpioDataRegs.GPBSET.bit.GPIO50=1;
    GpioDataRegs.GPBSET.bit.GPIO51=1;

}

void ConfigureEPwm(void)
{

    InitEPwmGpio();
    // ------------------------------------------------------------------------------
    //  User function:pull-high of the driver reset signal
    // ------------------------------------------------------------------------------
    reset_pull_up();

    pwm1.PeriodMax = INV_PWM_TBPRD;
    pwm1.HalfPerMax= INV_PWM_HALF_TBPRD;
    pwm1.Deadband  = DB*SYSTEM_FREQUENCY;          // 200 counts -> 1.0 usec for TBCLK = SYSCLK/1

    PWM_INIT_MACRO(1,2,3,pwm1)
    PWM_INIT_MACRO(4,5,6,pwm1)

// -----------------------------------------------------------------------------------
// Setting up link from EPWM to ADC
// -----------------------------------------------------------------------------------
    EPwm1Regs.ETSEL.bit.SOCASEL = ET_CTR_PRD; // Select SOC from counter at ctr = 0
    EPwm1Regs.ETPS.bit.SOCAPRD  = ET_1ST;     // Generate pulse on 1st even
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;          // Enable SOC on A group
// -----------------------------------------------------------------------------------
//  EPWM1作为中断触发源
// -----------------------------------------------------------------------------------
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

    EDIS;
}


void  ConfigureEQep(void)
{
    //init QEP parameters   [enhanced quadrature encoder pulse]
    qep1.LineEncoder = 2500;    //slots in the QEP encoder
    qep1.MechScaler  = _IQ30(0.25/qep1.LineEncoder);
    qep1.PolePairs   = 4;
    qep1.CalibratedAngle = 0;
    QEP_INIT_MACRO(1,qep1)
    EQep1Regs.QEPCTL.bit.IEI = 0;        // disable POSCNT=POSINIT @ Index
}

interrupt void OffsetISR(void)
{

    Offset_counter++;
    if (Offset_counter>=5000)
    {
        IA_Offset= K1*IA_Offset + K2*(IFB_IA2)*ADC_PU_SCALE_FACTOR;    //Phase A offset
        IB_Offset= K1*IB_Offset + K2*(IFB_IB2)*ADC_PU_SCALE_FACTOR;    //Phase B offset
        IC_Offset= K1*IC_Offset + K2*(IFB_IC2)*ADC_PU_SCALE_FACTOR;    //Phase C offset

//                Total_Voltage_Offset= K1*Total_Voltage_Offset + K2*(IFB_Total_Voltage)*ADC_PU_SCALE_FACTOR;   //Total Voltage offset
    }

    EALLOW;
    AdcbRegs.ADCPPB1OFFREF = (IA_Offset*4096.0);                  // Setting IA Offset
    AdcbRegs.ADCPPB2OFFREF = (IB_Offset*4096.0);                  // Setting IB Offset
    AdcbRegs.ADCPPB3OFFREF = (IC_Offset*4096.0);                  // Setting IC Offset
    EDIS;

    if (Offset_counter > 10000)
     {
         EALLOW;
         PieVectTable.EPWM1_INT= &MainISR;
         EDIS;
     }

    EPwm1Regs.ETCLR.bit.INT=1;                                    //Clear Tigger
    PieCtrlRegs.PIEACK.all=PIEACK_GROUP3;
}

interrupt void MainISR(void)
{
    if(RunMotor == 0)
    {
        if(motor_type == THREE_PHASE)
        {
            EPwm4Regs.CMPA.bit.CMPA = 0;
            EPwm5Regs.CMPA.bit.CMPA = 0;
            EPwm6Regs.CMPA.bit.CMPA = 0;
        }
        else
        {
            EPwm1Regs.CMPA.bit.CMPA = 0;
            EPwm2Regs.CMPA.bit.CMPA = 0;
            EPwm3Regs.CMPA.bit.CMPA = 0;
            EPwm4Regs.CMPA.bit.CMPA = 0;
            EPwm5Regs.CMPA.bit.CMPA = 0;
            EPwm6Regs.CMPA.bit.CMPA = 0;
        }
    }
    // ------------------------------------------------------------------------------
    //  Connect inputs of the RMP module and call the ramp control macro
    // ------------------------------------------------------------------------------
    rc1.TargetValue = SpeedRef;
    RC_MACRO(rc1)

    // ------------------------------------------------------------------------------
    //  Connect inputs of the RAMP GEN module and call the ramp generator macro
    // ------------------------------------------------------------------------------
    rg1.Freq = rc1.SetpointValue;
    RG_MACRO(rg1)
    // ------------------------------------------------------------------------------
    //  Measure phase currents, subtract the offset and normalize from (-0.5,+0.5) to (-1,+1).
    //  Connect inputs of the CLARKE module and call the clarke transformation macro
    // ------------------------------------------------------------------------------
    clarke1.As = (float)IFB_IA2_PPB*ADC_PU_SCALE_FACTOR * 34/RATED_CURRENT;
    clarke1.Bs = (float)IFB_IB2_PPB*ADC_PU_SCALE_FACTOR * 34/RATED_CURRENT;
    clarke1.Cs = (float)IFB_IC2_PPB*ADC_PU_SCALE_FACTOR * 34/RATED_CURRENT;
    CLARKE1_MACRO(clarke1)

    if((clarke1.As>=_IQ(3.0))||(clarke1.Bs>=_IQ(3.0))) {Block_PWM = 1;}
    OneShot_Protection();
    // ------------------------------------------------------------------------------
    //   Position encoder suite module
    // ------------------------------------------------------------------------------
    PosEncoderSuite();


    // ------------------------------------------------------------------------------
    //  Connect inputs of the PARK module and call the park trans. macro
    // ------------------------------------------------------------------------------
    park1.Alpha = clarke1.Alpha;
    park1.Beta  = clarke1.Beta;

    if(SpeedLoopCount == SpeedLoopPrescaler)
    {
        SPEED_FR_MACRO(speed1);
        pid_spd.term.Ref = rc1.SetpointValue;
        pid_spd.term.Fbk = speed1.Speed;
        PID_MACRO(pid_spd);
        SpeedLoopCount = 1;
    }
    else
        SpeedLoopCount++;

    // lsw =0 定位
    //     =1 电流闭环
    //     =2 双闭环
    //     =3 开环
    if(lsw == 0 || lsw == 1)
    {
        pid_spd.data.d1 = 0; pid_spd.data.d2 = 0; pid_spd.data.i1 = 0;
        pid_spd.data.ud = 0; pid_spd.data.ui = 0; pid_spd.data.up = 0;
    }

    // ------------------------------------------------------------------------------
    //    Connect inputs of the PI module and call the PID IQ controller macro
    // ------------------------------------------------------------------------------
    if(lsw == 0)//校准模式
    {
        park1.Angle = 0;

        pi_iq.Ref = IqRef_lock;
        pi_iq.ui = 0;

        pi_iq.Ref = IdRef_lock;
    }
    else if(lsw == 1)
    {
        park1.Angle = rg1.Out;

        pi_iq.Ref = IqRef_run;
        pi_id.Ref = ramper(IdRef_run,pi_id.Ref,_IQ(0.00001));
    }
    else if(lsw == 2)
    {
        park1.Angle = speed1.ElecTheta;

        pi_iq.Ref = pid_spd.term.Out;
        pi_id.Ref = IdRef_run;
    }


    park1.Sine   = __sinpuf32(park1.Angle);
    park1.Cosine = __cospuf32(park1.Angle);
    PARK_MACRO(park1);

    pi_iq.Fbk = park1.Qs;
    PI_MACRO(pi_iq)

    pi_id.Fbk = park1.Ds;
    PI_MACRO(pi_id)

    Us=_IQmag(pi_id.Out,pi_iq.Out);

    ipark1.Ds = pi_id.Out;
    ipark1.Qs = pi_iq.Out;

    if(lsw == 3)
    {
        if(VVF_flag == 1)
            VqTesting = SpeedRef*10/4.0;

        ipark1.Ds = VdTesting;
        ipark1.Qs = VqTesting;

        park1.Angle = rg1.Out;
    }

    ipark1.Sine  = park1.Sine;
    ipark1.Cosine= park1.Cosine;
    IPARK_MACRO(ipark1);

    // ------------------------------------------------------------------------------
    //  Connect inputs of the SVGEN_DQ module and call the space-vector gen. macro
    // ------------------------------------------------------------------------------
    //sv_generator
    svgen1.Ualpha = ipark1.Alpha;
    svgen1.Ubeta  = ipark1.Beta;
    SVGENDQ_MACRO(svgen1);

    // ------------------------------------------------------------------------------
    // 直流母线电压&相电压计算
    // ------------------------------------------------------------------------------
    volt1.DcBusVolt = (float)IFB_Total_Voltage_PPB* Total_Voltage_FACTOR*2;

    volt1.MfuncV1 = svgen1.Ta;
    volt1.MfuncV2 = svgen1.Tb;
    volt1.MfuncV3 = svgen1.Tc;
    PHASEVOLT_MACRO(volt1)



    smo1.Ialpha = clarke1.Alpha;
    smo1.Ibeta  = clarke1.Beta;
    smo1.Valpha = volt1.Valpha;
    smo1.Vbeta  = volt1.Vbeta;
    SMO_MACRO(smo1)

    speed3.EstimatedTheta = smo1.Theta;
    SE_MACRO(speed3)

    volt_Ds = volt1.Valpha * park1.Cosine + volt1.Vbeta * park1.Sine;
    volt_Qs = -volt1.Valpha * park1.Sine + volt1.Vbeta * park1.Cosine;
    // ------------------------------------------------------------------------------
    //  Computed Duty and Write to CMPA register
    // ------------------------------------------------------------------------------
    EPwm4Regs.CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*svgen1.Ta)+INV_PWM_HALF_TBPRD;
    EPwm5Regs.CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*svgen1.Tb)+INV_PWM_HALF_TBPRD;
    EPwm6Regs.CMPA.bit.CMPA = (INV_PWM_HALF_TBPRD*svgen1.Tc)+INV_PWM_HALF_TBPRD;

    //------------------------------------------------------------------------------------
    DA_C=EQep1Regs.QPOSCNT;
    DA_C=EQep1Regs.QPOSCNT;
    DA_A=_IQ24toF(pi_iq.Ref)*4096;
    EQep_cont=0.4*(EQep1Regs.QPOSCNT);
    DA_B=_IQ24toF(EQep_cont);
    DA_C=_IQ24toF(speed1.ElecTheta)*4000;
    DA_A=_IQ24toF(pi_iq.Ref)*4096;
    DA_B=_IQ24toF(pi_iq.Fbk)*4096;
    DacaRegs.DACVALS.all = DA_A;
    DacbRegs.DACVALS.all = DA_B;
    DaccRegs.DACVALS.all = DA_C;
    // Clear INT flag for this timer
    EPwm1Regs.ETCLR.bit.INT = 1;

    // Acknowledge this interrupt to receive more interrupts from group 3
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;

}


void OneShot_Protection(void)
{
    EALLOW;
    if(Block_PWM != 0)
    {
        (*ePWM[4]).TZSEL.all = 0x000A;//强制PWM4为低电平
        (*ePWM[5]).TZSEL.all = 0x000A;//强制PWM5为低电平
        (*ePWM[6]).TZSEL.all = 0x000A;//强制PWM6为低电平

        (*ePWM[4]).TZEINT.all = 0x0004;//使能PWM4错误联防中断
        (*ePWM[5]).TZEINT.all = 0x0004;//使能PWM5错误联防中断
        (*ePWM[6]).TZEINT.all = 0x0004;//使能PWM6错误联防中断

        (*ePWM[4]).TZFRC.all = 0x0004;//强制OST置位
        (*ePWM[5]).TZFRC.all = 0x0004;//强制OST置位
        (*ePWM[6]).TZFRC.all = 0x0004;//强制OST置位

    }
    else
    {
        (*ePWM[4]).TZCLR.all = 0x0005;//清除错误标志位
        (*ePWM[5]).TZCLR.all = 0x0005;//清除错误标志位
        (*ePWM[6]).TZCLR.all = 0x0005;//清除错误标志位

        (*ePWM[4]).TZEINT.all = 0x0000;//禁止PWM1错误联防中断
        (*ePWM[5]).TZEINT.all = 0x0000;//禁止PWM1错误联防中断
        (*ePWM[6]).TZEINT.all = 0x0000;//禁止PWM1错误联防中断
    }
    EDIS;
}


void PosEncoderSuite(void)
{
    // ----------------------------------
    // lsw = 0 ---> Alignment Routine
    // ----------------------------------
    if (lsw == 0)
    {
    // during alignment, assign the current shaft position as initial position
        EQep1Regs.QPOSCNT = 0;
        EQep1Regs.QCLR.bit.IEL = 1;  // Reset position cnt for QEP
    } // end if (lsw=0)

    // ******************************************************************************
    //    Detect calibration angle and call the QEP module
    // ******************************************************************************
        // for once the QEP index pulse is found, go to lsw=2
    if(lsw==1)
    {
        if (EQep1Regs.QFLG.bit.IEL == 1)            // Check the index occurrence
        {
            qep1.CalibratedAngle=EQep1Regs.QPOSILAT;
//            EQep1Regs.QPOSINIT = EQep1Regs.QPOSILAT; //new
//            EQep1Regs.QEPCTL.bit.IEI = IEI_RISING;   // new
//            Keep the latched pos. at the first index
        }
    }

    if(lsw != 0)
    {
        QEP_MACRO(1,qep1);
    }
    // Reverse the sense of position if needed - comment / uncomment accordingly
    // Position Sense as is
    //posEncElecTheta[QEP_POS_ENCODER] = qep1.ElecTheta;
    //posEncMechTheta[QEP_POS_ENCODER] = qep1.MechTheta;

    // Position Sense Reversal
    speed1.ElecTheta = 1.0 - qep1.ElecTheta;

    return;
}

_iq ramper(_iq in, _iq out, _iq rampDelta)
{
    _iq err;

    err = in - out;
    if (err > rampDelta)
        return(out + rampDelta);
    else if (err < -rampDelta)
        return(out - rampDelta);
    else
        return(in);
}
