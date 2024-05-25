//###########################################################################
//
// FILE:   User_F2837xD_ADC.c
// AUTHOR:  Zirui Liu
// TITLE:  F2837xD ADC Initialization & Support Functions.
//
//###########################################################################

#include <F2837xD_device.h>     // F2837xS Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xS Examples Include File
#include "User_F2837xD_ADC.h"


void Configure_ADC(void)
{
    Configure_ADC_a();
    Configure_ADC_b();
    Configure_ADC_c();
    Configure_ADC_d();
}


void Configure_ADC_a(void)
{
    EALLOW;

    //write configurations
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //Set pulse positions to late
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //power up the ADC
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);
    EDIS;
}


void Configure_ADC_b(void)
{
    EALLOW;

    //write configurations
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //Set pulse positions to late
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //power up the ADC
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);
    EDIS;
}




void Configure_ADC_c(void)
{
    EALLOW;

    //write configurations
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //Set pulse positions to late
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //power up the ADC
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);
    EDIS;
}

void Configure_ADC_d(void)
{
    EALLOW;

    //write configurations
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //Set pulse positions to late
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //power up the ADC
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //delay for 1ms to allow ADC time to power up
    DELAY_US(1000);
    EDIS;
}

void InitADC(void)
{
    InitADC_A();
    InitADC_B();
    //InitADC_C();
    InitADC_D();   //ATEMP SENSOR
}

void InitADC_A(void)
{
    Uint16 acqps;
    //determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcbRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

//Select the channels to convert and end of conversion flag
    EALLOW;
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;      //pin A4    total voltage
    //AdcaRegs.ADCSOC5CTL.bit.CHSEL = 5;      //pin A5    total current

    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles

    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA

// Configure PPB to eliminate subtraction related calculation
    AdcaRegs.ADCPPB1CONFIG.bit.TWOSCOMPEN = 1;
    AdcaRegs.ADCPPB1CONFIG.bit.CONFIG = 4;    // PPB1 is associated with SOC4
    AdcaRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;    // Write zero to this for now till offset ISR is run


    AdcaRegs.ADCPPB2CONFIG.bit.TWOSCOMPEN = 1;
    AdcaRegs.ADCPPB2CONFIG.bit.CONFIG = 5;    // PPB2 is associated with SOC5
    AdcaRegs.ADCPPB2OFFCAL.bit.OFFCAL = 0;    // Write zero to this for now till offset ISR is run

    EDIS;
}

void InitADC_B(void)
{
    Uint16 acqps;
    //determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcbRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    //Select the channels to convert and end of conversion flag
    EALLOW;
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;      //pin B0    U2 current
    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 14;     //pin 14    W2 current
    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 15;     //pin 15    V2 current
//    AdcbRegs.ADCSOC3CTL.bit.CHSEL = 3;      //pin B3    W1 current
//    AdcbRegs.ADCSOC4CTL.bit.CHSEL = 4;      //pin B4    V1 current
//    AdcbRegs.ADCSOC5CTL.bit.CHSEL = 5;      //pin B5    U1 current

    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
//    AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
//    AdcbRegs.ADCSOC4CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
//    AdcbRegs.ADCSOC5CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles

    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
//    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
//    AdcbRegs.ADCSOC4CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
//    AdcbRegs.ADCSOC5CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA

    // Configure PPB to eliminate subtraction related calculation
    AdcbRegs.ADCPPB1CONFIG.bit.TWOSCOMPEN = 1;
    AdcbRegs.ADCPPB1CONFIG.bit.CONFIG = 0;    // PPB is associated with SOC0
    AdcbRegs.ADCPPB1OFFCAL.bit.OFFCAL = 0;    // Write zero to this for now till offset ISR is run
    AdcbRegs.ADCPPB2CONFIG.bit.TWOSCOMPEN = 1;
    AdcbRegs.ADCPPB2CONFIG.bit.CONFIG = 2;    // PPB is associated with SOC2
    AdcbRegs.ADCPPB2OFFCAL.bit.OFFCAL = 0;    // Write zero to this for now till offset ISR is run
    AdcbRegs.ADCPPB3CONFIG.bit.TWOSCOMPEN = 1;
    AdcbRegs.ADCPPB3CONFIG.bit.CONFIG = 1;    // PPB is associated with SOC1
    AdcbRegs.ADCPPB3OFFCAL.bit.OFFCAL = 0;    // Write zero to this for now till offset ISR is run
    EDIS;
}

void InitADC_C(void)
{
    Uint16 acqps;
    //determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdccRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    //Select the channels to convert and end of conversion flag
    EALLOW;
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 0;      //D1    ATEMP 1
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 1;      //D2    ATEMP 2
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 2;      //D3    ATEMP 3
    AdccRegs.ADCSOC3CTL.bit.CHSEL = 3;      //D4    ATEMP 4

    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC3CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles

    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA

    EDIS;
}



void InitADC_D(void)
{
    Uint16 acqps;
    //determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcbRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    //Select the channels to convert and end of conversion flag
    EALLOW;
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0;      //D1    ATEMP 1
    AdcdRegs.ADCSOC1CTL.bit.CHSEL = 1;      //D2    ATEMP 2
    AdcdRegs.ADCSOC2CTL.bit.CHSEL = 2;      //D3    ATEMP 3
    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 3;      //D4    ATEMP 4

    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC2CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps;  //sample window is 100 SYSCLK cycles

    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = 0x05;    //trigger on ePWM1 SOCA

    EDIS;
}


void EnableTZ(void)
{
    EALLOW;
    GpioCtrlRegs.GPDMUX1.bit.GPIO102 = 0;    // Enable Total_Current_TZ
    GpioCtrlRegs.GPDDIR.bit.GPIO102 = 0;
    GpioCtrlRegs.GPDQSEL1.bit.GPIO102 = 0;

    GpioCtrlRegs.GPDMUX1.bit.GPIO101 = 0;    // Enable UVW1_Current_TZ
    GpioCtrlRegs.GPDDIR.bit.GPIO101 = 0;
    GpioCtrlRegs.GPDQSEL1.bit.GPIO101 = 0;

    GpioCtrlRegs.GPDMUX1.bit.GPIO100 = 0;    // Enable UVW2_Current_TZ
    GpioCtrlRegs.GPDDIR.bit.GPIO100 = 0;
    GpioCtrlRegs.GPDQSEL1.bit.GPIO100 = 0;
    EDIS;
}

