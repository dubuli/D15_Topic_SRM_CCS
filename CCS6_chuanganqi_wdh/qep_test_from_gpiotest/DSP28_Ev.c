//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_Ev.c
//
// TITLE:	DSP28 Event Manager Initialization & Support Functions.
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
// InitEv: 
//---------------------------------------------------------------------------
// This function initializes to a known state.
//
void InitEv(void)
{

	EvaRegs.T2CON.all=0x1872;
	EvaRegs.T2PR=0xffff;
	EvaRegs.T2CNT=0;
	EvaRegs.EVAIFRB.bit.T2PINT=1;//period interupt
	EvaRegs.EVAIMRB.bit.T2PINT=1;
//*****	  qep34    	**********
	EvaRegs.CAPCON.bit.CAPRES=0;
	EvaRegs.CAPCON.bit.CAPQEPN=3;//使能qep
	EvaRegs.CAPCON.bit.CAP3EN=0;//CAP6//主程序打开
	EvaRegs.CAPCON.bit.CAP3TSEL=1;//3-T1;	CAP6==T3
	EvaRegs.CAPCON.bit.CAP12TSEL=0;//12-T2;	qep45==T 4
	EvaRegs.CAPCON.bit.CAP3TOADC=0;//不动ADC
	EvaRegs.CAPCON.bit.CAP1EDGE=3;//QEP4 检测两个边沿
	EvaRegs.CAPCON.bit.CAP2EDGE=3;//QEP5 检测连个边沿
	EvaRegs.CAPCON.bit.CAP3EDGE=1;//上升沿
	EvaRegs.CAPFIFO.all=0x0000;
	EvaRegs.CAP3FIFO=0;
	EvaRegs.CAP3FBOT=0;
	EvaRegs.EVAIMRC.bit.CAP3INT=1;//CAP6中断使能
	EvaRegs.EVAIFRC.bit.CAP3INT=1;//CAP6中断标志复位	*/

}	
	
//===========================================================================
// No more.
//===========================================================================
