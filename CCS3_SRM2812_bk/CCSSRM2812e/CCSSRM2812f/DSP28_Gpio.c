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

	EALLOW;
	GpioMuxRegs.GPFMUX.bit.MFSRA_GPIOF11=0;// IO, input the state
	GpioMuxRegs.GPFMUX.bit.MDXA_GPIOF12=0;
	GpioMuxRegs.GPFMUX.bit.MDRA_GPIOF13=0 ;



	GpioMuxRegs.GPFDIR.bit.GPIOF11=0;//设置F11对应的DSP引脚为input
	GpioMuxRegs.GPFDIR.bit.GPIOF12=0;//Test
	GpioMuxRegs.GPFDIR.bit.GPIOF13=0;//Test,to be deleted


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
