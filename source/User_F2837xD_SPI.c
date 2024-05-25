//###########################################################################
//
// FILE:   User_F2837xD_SPI.c
// AUTHOR:  Zirui Liu
// TITLE:  F2837xD SPI Initialization & Support Functions.
//
//###########################################################################

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "User_F2837xD_SPI.h"

void InitSpia_SpiFIFO(void)
{
    // Initialize SPI registers and SPI FIFO registers
//SPI-A
    /* Initialize SPI periphery */
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;             /* Reset SPI and hold */
    SpiaRegs.SPICCR.all = 0x0007;                   /* Loopback off  8-bit character, Clock Polarity 0 */
    SpiaRegs.SPICTL.all = 0x0006;                   /* master, xmit enable */
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = 0x01;        /* SYSCLK = 80Mhz = LSPCLK, baud rate = LSPCLK/(SPIBRR+1) = 8 MHz */
    SpiaRegs.SPISTS.all = 0x0000;                   /* reset all status information */
    SpiaRegs.SPIPRI.bit.FREE = 1;                   /* priority control settings - free run */
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;             /* Release from SPI reset */
    /* reset both fifos */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 0;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0; /*and keep them in reset during configuration */
    /* configure fifos  */
    SpiaRegs.SPIFFTX.all = 0xC004; /* Enable FIFO's, do not use interrupts */
    SpiaRegs.SPIFFRX.all = 0x0004; /* Set RX FIFO, do not use interrupts  */
    SpiaRegs.SPIFFCT.all = 0x0000; /* no delay between FIFO and TXBUF */
    /* releasing fifos from reset */
    SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1; /* OK */
}

void InitSpib_SpiFIFO(void)
{
//SPI-B
    SpibRegs.SPICCR.all =0x000F;                 // Reset on, rising edge, 16-bit char bits
    SpibRegs.SPICTL.all =0x0006;                 // Enable master mode, normal phase,
                                                 // enable talk, and SPI int disabled.
    SpibRegs.SPIBRR.bit.SPI_BIT_RATE = 0x01;
    SpibRegs.SPICCR.all =0x008F;                 // Relinquish SPI from Reset
    SpibRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
    SpibRegs.SPIFFTX.all=0xE040;
    SpibRegs.SPIFFRX.all=0x2044;
    SpibRegs.SPIFFCT.all=0x0;
}

void InitSpic_SpiFIFO(void)
{
//SPI-C
    SpicRegs.SPICCR.all =0x000F;//CLOCK POLARITY=0       // Reset on, rising edge, 16-bit char bits
    SpicRegs.SPICTL.all =0x0006;//CLOCK PHASE=0                                         // enable talk, and SPI int disabled.
    SpicRegs.SPIBRR.bit.SPI_BIT_RATE = 0x01;//7.5MHZ/0x00e;--3M //SPI Baud Rate=LSPCLK/(SPIBRR+1)
    SpicRegs.SPICCR.all =0x008F;                 // Relinquish SPI from Reset
    SpicRegs.SPIPRI.bit.FREE = 1;                // Set so breakpoints don't disturb xmission
    SpicRegs.SPIFFTX.all=0xE021;      // Enable FIFO's, set TX FIFO level to 1
    SpicRegs.SPIFFRX.all=0x0;//0x0021;      // Set RX FIFO level to 8
    SpicRegs.SPIFFCT.all=0x0;
}

void InitSpiGpio(void)
{
    InitSpiaGpio();
    InitSpibGpio();
    InitSpicGpio();
}

void InitSpiaGpio(void)
{
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;   // Enable pull-up on GPIO58 (SPISIMOA)
   GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0;   // Enable pull-up on GPIO55 (SPISOMIA)
   GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0;   // Enable pull-up on GPIO56 (SPICLKA)
   GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0;   // Enable pull-up on GPIO57 (SPISTEA)


/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; // Asynch input GPIO58 (SPISIMOA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO55 (SPISOMIA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO56 (SPICLKA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO57 (SPISTEA)

/* Configure SPI-A pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.
    GpioCtrlRegs.GPBGMUX2.bit.GPIO58 = 3; // Configure GPIO58 as SPISIMOA
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 =  3; // Configure GPIO58 as SPISIMOA
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
    GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

    EDIS;
}


void InitSpibGpio(void)
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;   // Enable pull-up on GPIO25 (SPISOMIC)
   GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pull-up on GPIO24 (SPISIMOC)
   GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;   // Enable pull-up on GPIO26 (SPICLKC)
   GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;   // Enable pull-up on GPIO27 (SPISTEC)

   GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3; // Asynch input GPIO25 (SPISOMIC)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; // Asynch input GPIO24 (SPISIMOC)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3; // Asynch input GPIO26 (SPICLKC)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3; // Asynch input GPIO27 (SPISTEC)

/* Configure SPI-B pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be SPI functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 2; // Configure GPIO16 as SPISOMIC
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 2; // Configure GPIO16 as SPISIMOC
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 2; // Configure GPIO18 as SPICLKC
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 2; // Configure GPIO18 as SPISTEC

    GpioCtrlRegs.GPAGMUX2.bit.GPIO25 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = 1; // Configure GPIO18 as SPISTEC

    EDIS;
}


void InitSpicGpio(void)
{

   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPDPUD.bit.GPIO122 = 0;   // Enable pull-up on GPIO16 (SPISOMIC)
   GpioCtrlRegs.GPDPUD.bit.GPIO123 = 0;   // Enable pull-up on GPIO16 (SPISIMOC)
   GpioCtrlRegs.GPDPUD.bit.GPIO124 = 0;   // Enable pull-up on GPIO18 (SPICLKC)
   GpioCtrlRegs.GPDPUD.bit.GPIO125 = 0;   // Enable pull-up on GPIO18 (SPISTEC)

   GpioCtrlRegs.GPDQSEL2.bit.GPIO122 = 3; // Asynch input GPIO16 (SPISOMIC)
   GpioCtrlRegs.GPDQSEL2.bit.GPIO123 = 3; // Asynch input GPIO16 (SPISIMOC)
   GpioCtrlRegs.GPDQSEL2.bit.GPIO124 = 3; // Asynch input GPIO18 (SPICLKC)
   GpioCtrlRegs.GPDQSEL2.bit.GPIO125 = 3; // Asynch input GPIO18 (SPISTEC)

   GpioCtrlRegs.GPDMUX2.bit.GPIO122 = 2; // Configure GPIO16 as SPISOMIC
   GpioCtrlRegs.GPDMUX2.bit.GPIO123 = 2; // Configure GPIO16 as SPISIMOC
   GpioCtrlRegs.GPDMUX2.bit.GPIO124 = 2; // Configure GPIO18 as SPICLKC
   GpioCtrlRegs.GPDMUX2.bit.GPIO125 = 2; // Configure GPIO18 as SPISTEC

   GpioCtrlRegs.GPDGMUX2.bit.GPIO122 =1; // Configure GPIO16 as SPISOMIC
   GpioCtrlRegs.GPDGMUX2.bit.GPIO123 =1; // Configure GPIO16 as SPISIMOC
   GpioCtrlRegs.GPDGMUX2.bit.GPIO124 = 1; // Configure GPIO18 as SPICLKC
   GpioCtrlRegs.GPDGMUX2.bit.GPIO125 = 1; // Configure GPIO18 as SPISTEC

    EDIS;
}

void hal_assert(void)
{
    __asm("        ESTOP0"); /* stops emulation at this point */

    while (1); /* just in case */
}
//===========================================================================
// End of file.
//===========================================================================
