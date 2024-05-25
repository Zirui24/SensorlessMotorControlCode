//###########################################################################
//
// FILE:   User_F2837xD_DAC.c
// AUTHOR:  Zirui Liu
// TITLE:  F2837xD DAC Initialization & Support Functions.
//
//###########################################################################

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "User_F2837xD_DAC.h"

//template DAC output voltage [testing]
int DAC_A = 2;
int DAC_B = 4;
int DAC_C = 6;

//initialize DAC pointer
volatile struct DAC_REGS* DAC_PTR[4] = {0x0,&DacaRegs,&DacbRegs,&DaccRegs};


void Configure_DAC(void)
{
    ConfigureDAC_single(DACA);
    ConfigureDAC_single(DACB);
    ConfigureDAC_single(DACC);
}

void ConfigureDAC_single(Uint16 dac_num)
{
    EALLOW;
    DAC_PTR[dac_num] -> DACCTL.bit.DACREFSEL = REFERENCE;
    DAC_PTR[dac_num] -> DACOUTEN.bit.DACOUTEN = 1;
    DAC_PTR[dac_num] -> DACVALS.all = 0;
    DELAY_US(10);
    EDIS;
}

void DAC_Output(Uint16 dac_num,Uint16 DAC_value)
{
    DAC_PTR[dac_num]->DACVALS.all = DAC_value;
}


//===========================================================================
// End of file.
//===========================================================================
