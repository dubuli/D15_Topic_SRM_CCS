//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_Gpio.c
//
// TITLE:	DSP28 General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//###########################################################################

#include "DSP28_Device.h"

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known state.
//
void InitGpio(void)
{

// Set GPIO A port pins,AL(Bits 7:0)(input)-AH(Bits 15:8) (output) 8bits
// Input Qualifier =0, none
//     EALLOW;
//     GpioMuxRegs.GPAMUX.all=0x0000;     
//     GpioMuxRegs.GPADIR.all=0xFF00;    	// upper byte as output/low byte as input
  //   GpioMuxRegs.GPAQUAL.all=0x0000;	// Input qualifier disabled

// Set GPIO B port pins, configured as EVB signals
// Input Qualifier =0, none
// Set bits to 1 to configure peripherals signals on the pins
//    GpioMuxRegs.GPBMUX.all=0xFFFF;   
//     GpioMuxRegs.GPBQUAL.all=0x0000;	// Input qualifier disabled
//     EDIS;

	EALLOW;
	GpioMuxRegs.GPAMUX.bit.CAP1Q1_GPIOA8=0;// IO
	GpioMuxRegs.GPAMUX.bit.CAP2Q2_GPIOA9=0;
	GpioMuxRegs.GPAMUX.bit.CAP3QI1_GPIOA10=0 ;
	GpioMuxRegs.GPAMUX.bit.TCLKINA_GPIOA12=0;

	GpioMuxRegs.GPADIR.bit.GPIOA10=1;//Test 设置D1对应的DSP引脚为输出
	GpioMuxRegs.GPADIR.bit.GPIOA9=1;//Test
	GpioMuxRegs.GPADIR.bit.GPIOA8=1;//Test,to be deleted
	GpioMuxRegs.GPADIR.bit.GPIOA12=1;//as LED output

	GpioDataRegs.GPADAT.bit.GPIOA10=0;//D1对应输出电平
	GpioDataRegs.GPADAT.bit.GPIOA9=1;//D1对应输出电平
	GpioDataRegs.GPADAT.bit.GPIOA8=0;
	GpioDataRegs.GPADAT.bit.GPIOA12=0;

	GpioMuxRegs.GPBMUX.bit.PWM7_GPIOB0 = 1;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM8_GPIOB1 = 1;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM9_GPIOB2 = 1;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM10_GPIOB3 = 1;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM11_GPIOB4 = 1;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM12_GPIOB5 = 1;// PWM
	GpioMuxRegs.GPBMUX.bit.CAP4Q1_GPIOB8=1;
	GpioMuxRegs.GPBMUX.bit.CAP5Q2_GPIOB9=1;
	GpioMuxRegs.GPBMUX.bit.CAP6QI2_GPIOB10=1;

/*-------------------**
** 	//test the T3CMP ,**
attention!
**-------------------*/
	GpioMuxRegs.GPBMUX.bit.T3PWM_GPIOB6=1;
	GpioMuxRegs.GPBMUX.bit.T4PWM_GPIOB7=1;



	EDIS;
}	
	
//===========================================================================
// No more.
//===========================================================================
