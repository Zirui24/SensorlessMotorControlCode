//###########################################################################
//
// FILE:   User_F2837xD_SCI.c
// AUTHOR:  Zirui Liu
// TITLE:  F2837xD SCI Initialization & Support Functions.
//
//###########################################################################


#include "F2837xD_device.h"     // F2837xS Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xS Examples Include File
#include "User_F2837xD_SCI.h"
#include "Parameter_settings.h"

void Configure_Sci_A(void)
{
    InitSciaGPIO();
    scia_init_fifo();
}


void InitSciaGPIO(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAGMUX2.bit.GPIO29 = 0;
    EDIS;
}

void scia_init_fifo(void)
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;

    SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;

    //²¨ÌØÂÊ115200
    SciaRegs.SCIHBAUD.all = 0x0000;
    SciaRegs.SCILBAUD.all = 0x0036;

    SciaRegs.SCICTL1.all =0x0023;  // Relinquish SCI from Reset
}

void scia_ximt(unsigned char send)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}//0h (R/W) = Transmit FIFO is empty
    SciaRegs.SCITXBUF.all = send;
}

void shanwai_sci(short *data)
{
    unsigned char data_ximt[20];

    unsigned char count = 0;

    data_ximt[0] = 0x03;
    data_ximt[1] = 0xfc;

    data_ximt[2] = (data[0]>>8)&0x00ff;
    data_ximt[3] = data[0]&0x00ff;

    data_ximt[4] = (data[1]>>8)&0x00ff;
    data_ximt[5] = data[1]&0x00ff;

    data_ximt[6] = (data[2]>>8)&0x00ff;
    data_ximt[7] = data[2]&0x00ff;

    data_ximt[8] = (data[3]>>8)&0x00ff;
    data_ximt[9] = data[3]&0x00ff;

    data_ximt[10] = (data[4]>>8)&0x00ff;
    data_ximt[11] = data[4]&0x00ff;

    data_ximt[12] = (data[5]>>8)&0x00ff;
    data_ximt[13] = data[5]&0x00ff;

    data_ximt[14] = 0xfc;
    data_ximt[15] = 0x03;


    for (count = 0;count<16;count++)
    scia_ximt(data_ximt[count]);
}

