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

  	 
  	GpioMuxRegs.GPDMUX.bit.T3CTRIP_PDPB_GPIOD5 = 0;//���������ƹܽţ�D5��
  	GpioMuxRegs.GPAMUX.bit.CAP1Q1_GPIOA8 = 0;
  	GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0 = 0;


  	 GpioMuxRegs.GPDDIR.bit.GPIOD5 = 1; //D5������Ϊ���
  	GpioMuxRegs.GPADIR.bit.GPIOA8 = 0;
  	GpioMuxRegs.GPADIR.bit.GPIOA0 = 1;
  	 
     EDIS;

}	
	
//===========================================================================
// No more.
//===========================================================================
