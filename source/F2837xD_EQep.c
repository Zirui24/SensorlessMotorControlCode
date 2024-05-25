//###########################################################################
//
// FILE:   F2837xS_EQep.c
//
// TITLE:  F2837xS eQEP Initialization & Support Functions.
//
//!    Watch Variables
//!  - qep_posspeed.SpeedRpm_fr - Speed meas. in rpm using QEP position counter
//!  - qep_posspeed.SpeedRpm_pr - Speed meas. in rpm using capture unit
//!  - qep_posspeed.theta_mech  - Motor mechanical angle (Q15)
//!  - qep_posspeed.theta_elec  - Motor electrical angle (Q15)
//###########################################################################
// $TI Release: F2837xS Support Library v190 $
// $Release Date: Mon Feb  1 16:59:09 CST 2016 $
// $Copyright: Copyright (C) 2014-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#include "F28x_Project.h"     // Device Headerfile and Examples Include File

void InitEQep1Gpio(void)
{
    EALLOW;

    GpioCtrlRegs.GPDPUD.bit.GPIO96 = 1;    // Disable pull-up on GPIO96 (EQEP1A)
    GpioCtrlRegs.GPDPUD.bit.GPIO97 = 1;    // Disable pull-up on GPIO97 (EQEP1B)
//    GpioCtrlRegs.GPDPUD.bit.GPIO98 = 1;    // Disable pull-up on GPIO98 (EQEP1S)
    GpioCtrlRegs.GPDPUD.bit.GPIO99 = 1;    // Disable pull-up on GPIO99 (EQEP1I)

    GpioCtrlRegs.GPDQSEL1.bit.GPIO96 = 0;   // Sync GPIO96 to SYSCLK  (EQEP1A)
    GpioCtrlRegs.GPDQSEL1.bit.GPIO97 = 0;   // Sync GPIO97 to SYSCLK  (EQEP1B)
//    GpioCtrlRegs.GPDQSEL1.bit.GPIO98 = 0;   // Sync GPIO98 to SYSCLK  (EQEP1S)
    GpioCtrlRegs.GPDQSEL1.bit.GPIO99 = 0;   // Sync GPIO99 to SYSCLK  (EQEP1I)

    GpioCtrlRegs.GPDGMUX1.bit.GPIO96 = 1;   // Configure GPIO96 as EQEP1A
    GpioCtrlRegs.GPDMUX1.bit.GPIO96 = 1;    // Configure GPIO96 as EQEP1A
    GpioCtrlRegs.GPDGMUX1.bit.GPIO97 = 1;   // Configure GPIO97 as EQEP1B
    GpioCtrlRegs.GPDMUX1.bit.GPIO97 = 1;    // Configure GPIO97 as EQEP1B
//    GpioCtrlRegs.GPDGMUX1.bit.GPIO98 = 1;   // Configure GPIO98 as EQEP1S
//    GpioCtrlRegs.GPDMUX1.bit.GPIO98 = 1;    // Configure GPIO98 as EQEP1S
    GpioCtrlRegs.GPDGMUX1.bit.GPIO99 = 1;   // Configure GPIO99 as EQEP1I
    GpioCtrlRegs.GPDMUX1.bit.GPIO99 = 1;    // Configure GPIO99 as EQEP1I

//    // Setup GPIO for QEP operation
//    GPIO_SetupPinOptions(96, GPIO_INPUT, GPIO_SYNC);
//    GPIO_SetupPinMux(96,0,1);
//
//    GPIO_SetupPinOptions(97, GPIO_INPUT, GPIO_SYNC);
//    GPIO_SetupPinMux(97,0,1);
//
////    GPIO_SetupPinOptions(22, GPIO_INPUT, GPIO_SYNC);
////    GPIO_SetupPinMux(22,0,1);
//
//    GPIO_SetupPinOptions(99, GPIO_INPUT, GPIO_SYNC);
//    GPIO_SetupPinMux(99,0,1);

}
//===========================================================================
// End of file.
//===========================================================================
