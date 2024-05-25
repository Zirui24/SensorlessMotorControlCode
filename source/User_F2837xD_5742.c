//###########################################################################
//
// FILE:   F2837xD_Spi.c
// AUTHOR:	CL
// TITLE:  F2837xD SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xS Support Library v190 $
// $Release Date: Mon Feb  1 16:59:09 CST 2016 $
// $Copyright: Copyright (C) 2014-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2837xD_device.h"     // F2837xS Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xS Examples Include File
#include "User_F2837xD_5742.h"
#include "User_F2837xD_SPI.h"
#define  NOP	asm(" NOP")

void Init5742(void)
{
	InitSpibGpio();
	InitSpib_SpiFIFO();
	int i=0;
    GpioDataRegs.GPASET.bit.GPIO27 = 1;//cs=1
    for(i=0;i<100;i++){}
    GpioDataRegs.GPACLEAR.bit.GPIO27 = 1; //cs=0
	SpibRegs.SPITXBUF=0xff10;//
	while(SpibRegs.SPISTS.bit.INT_FLAG!=1){}

	GpioDataRegs.GPASET.bit.GPIO27 = 1;//cs=1为下一次做准备

	SpibRegs.SPICCR.bit.SPISWRESET=0;//通过reset 清楚SPI中断标志INT_FLAG
	NOP;
	NOP;
	SpibRegs.SPICCR.bit.SPISWRESET=1;// Relinquish SPI from Reset
}

void spiDAC_a(Uint16 a)
{
	 SpibRegs.SPITXBUF=a | 0x0000;//DAC_A 通道
     while(SpibRegs.SPISTS.bit.INT_FLAG!=1){} //!=1 ==0
     SpibRegs.SPICCR.bit.SPISWRESET=0;/// clear le SPISTS,BIT6
	 NOP;
	 NOP;
	 SpibRegs.SPICCR.bit.SPISWRESET=1;//

}
//////////////////////////////////////////////

void spiDAC_b(Uint16 a)
{
     SpibRegs.SPITXBUF=a | 0x1000;//DAC_B 通道
     while(SpibRegs.SPISTS.bit.INT_FLAG!=1){}
     SpibRegs.SPICCR.bit.SPISWRESET=0;/// clear le SPISTS,BIT6
	 NOP;
	 NOP;
	 SpibRegs.SPICCR.bit.SPISWRESET=1;//
}
///////////////////////////////////////////////
void spiDAC_c(Uint16 a)
{
     SpibRegs.SPITXBUF=a | 0x2000;//DAC_C 通道
     while(SpibRegs.SPISTS.bit.INT_FLAG!=1){}
     SpibRegs.SPICCR.bit.SPISWRESET=0;/// clear le SPISTS,BIT6
	 NOP;
	 NOP;
	 SpibRegs.SPICCR.bit.SPISWRESET=1;//
}

/////////////////////////////////////////////////
void spiDAC_d(Uint16 a)
{
     SpibRegs.SPITXBUF=a | 0x3000;//DAC_D 通道
     while(SpibRegs.SPISTS.bit.INT_FLAG!=1){}
     SpibRegs.SPICCR.bit.SPISWRESET=0;/// clear le SPISTS,BIT6
	 NOP;
	 NOP;
	 SpibRegs.SPICCR.bit.SPISWRESET=1;//
}
