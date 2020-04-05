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

#include "DSP281x_Device.h"

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
	GpioMuxRegs.GPFDIR.bit.GPIOF13=0;//


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


	GpioMuxRegs.GPFMUX.bit.MFSXA_GPIOF10=0;	//PA-oc-up,MFXA,26pin
	GpioMuxRegs.GPBMUX.bit.TCLKINB_GPIOB12=0;	//PA-oc-dn,TCLKINB,72pin
	GpioMuxRegs.GPFMUX.bit.MCLKRA_GPIOF9=0;	//PB-oc-up,MCLKRA,25pin
	GpioMuxRegs.GPAMUX.bit.PWM3_GPIOA2=0;	//PB-oc-dn,PWM3,94pin
	GpioMuxRegs.GPAMUX.bit.PWM4_GPIOA3=0;	//PC-oc-up,PWM4,95
	GpioMuxRegs.GPAMUX.bit.PWM2_GPIOA1=0;	//PC-oc-DN,pwm2,93

	GpioMuxRegs.GPFDIR.bit.GPIOF10=0;
	GpioMuxRegs.GPBDIR.bit.GPIOB12=0;
	GpioMuxRegs.GPFDIR.bit.GPIOF9=0;
	GpioMuxRegs.GPADIR.bit.GPIOA2=0;
	GpioMuxRegs.GPADIR.bit.GPIOA3=0;
	GpioMuxRegs.GPADIR.bit.GPIOA1=0;

	GpioMuxRegs.GPAMUX.bit.PWM6_GPIOA5=0;	//Swith, start or stop the motor
	GpioMuxRegs.GPADIR.bit.GPIOA5=0;


	EDIS;
}	
	
//===========================================================================
// No more.
//===========================================================================
