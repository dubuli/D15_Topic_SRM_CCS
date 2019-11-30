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
     ///����SPI�����蹦��
     GpioMuxRegs.GPFMUX.bit.SPISIMOA_GPIOF0 = 1;
     GpioMuxRegs.GPFMUX.bit.SPISOMIA_GPIOF1 = 1;
     GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2  = 1;
     GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3  = 1;//0ΪIO�ڣ�1Ϊ�����
     
  	 ///����PD5Ϊ���������DAC���������
  	 GpioMuxRegs.GPAMUX.all&=0x7fff;
  	 GpioMuxRegs.GPADIR.all |= 0x8000;
  	 
  	 
	 //////////////////////////////////////////
	 ///CAP6QI2_GPIOB10:1; // TDIRB_GPIOB11:1;   
	 // TCLKINB_GPIOB12:1; // C4TRIP_GPIOB13:1;  // 
  	 GpioMuxRegs.GPBMUX.bit.CAP6QI2_GPIOB10 = 0;
  	 GpioMuxRegs.GPBMUX.bit.TDIRB_GPIOB11 = 0;
  	 GpioMuxRegs.GPBMUX.bit.TCLKINB_GPIOB12  = 0;
  	 GpioMuxRegs.GPBMUX.bit.C4TRIP_GPIOB13 = 0;        
		GpioMuxRegs.GPBMUX.bit.CAP4Q1_GPIOB8=0;   // 8 
		GpioMuxRegs.GPBMUX.bit.CAP5Q2_GPIOB9=0;   // 9 
		GpioMuxRegs.GPBMUX.bit.C5TRIP_GPIOB14=0;  // 14  //IO MODE 0ΪIO�ڣ�1Ϊ�����
		GpioMuxRegs.GPBMUX.bit.C6TRIP_GPIOB15=0;  // 15   
         


  	 GpioMuxRegs.GPBDIR.bit.GPIOB10 = 0;
  	 GpioMuxRegs.GPBDIR.bit.GPIOB11 = 0;
  	 GpioMuxRegs.GPBDIR.bit.GPIOB12 = 0;
  	 GpioMuxRegs.GPBDIR.bit.GPIOB13 = 0;
   		 GpioMuxRegs.GPBDIR.bit.GPIOB8 = 1;  //0Ϊ���룬1Ϊ���
  		 GpioMuxRegs.GPBDIR.bit.GPIOB9 = 1;
  		 GpioMuxRegs.GPBDIR.bit.GPIOB14 = 0;
  		 GpioMuxRegs.GPBDIR.bit.GPIOB15 = 1; 	   	 
  	 
     EDIS;
}	
	
//===========================================================================
// No more.
//===========================================================================
