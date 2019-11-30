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

#include "DSP281x_Device.h"
#include "constant.h"
#include "typedefs.h"
//---------------------------------------------------------------------------
// InitEv: 
//---------------------------------------------------------------------------
// This function initializes to a known state.
//
void InitEv(void)
{
	WORD iperiod1;
	WORD iperiod3;	
			
	iperiod1 = (SYSCLK_FREQ / CPU_INT_FREQ) - 1;//5kHz

/*------**
** Test attentio**
**------*/	
/* 	EvaRegs.GPTCONA.all = 0x0859;	 */

	EvaRegs.T1PR = iperiod1;
	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	EvaRegs.T1CON.all = 0x1000;//TPS=0,enable=0,to be enabled;

	EvaRegs.GPTCONA.bit.T1TOADC = 2;//period to ADC


/*------**
** Test attentio**
test the EVA pwm
**------*/	
/* //	EvaRegs.GPTCONA.all = 0x0859; */
/* 	EvaRegs.T1CON.bit.TECMPR=1;       */
/* 	EvaRegs.T1CMPR=3000;              */

////EVB ------------------------------------------------
	iperiod3 = (SYSCLK_FREQ / PWM_FREQ) - 1;
	EvbRegs.T3PR = iperiod3;
	EvbRegs.T3CNT = 0;

	EvbRegs.T3CON.bit.TMODE = 2;//TPS=0,enable=0;
	EvbRegs.T3CON.bit.TPS=0;
	EvbRegs.T3CON.bit.TENABLE=0;//unenable the t3 count
	EvbRegs.T3CON.bit.TCLKS10=0;//divide 0
	EvbRegs.T3CON.bit.TECMPR=1;//enable the compare of PWM6-12


/*----------------------**
** 	attention,
T3PIN
t3cmpr    **
**----------------------*/	
	EvbRegs.GPTCONB.bit.TCMPOE=0;//test if 0,the CMPR will work or not
									//the test reasult is, when set 0, the T3 and T4 will not work
									//but the 6 PWM of CMPR will still work
	EvbRegs.GPTCONB.bit.T3PIN=1;
//	EvbRegs.GPTCONB.all = 0x0859;				
	EvbRegs.T3CMPR = 1300;

	EvbRegs.T4PR = 0xffff;
	EvbRegs.T4CNT = 0;
	EvbRegs.T4CON.all = 0x1400;//Tps=5,enable=0;GuweiGang P245					 

	EvbRegs.CMPR4 = 0;//设置比较寄存器,compare to T3
	EvbRegs.CMPR5 = 0;
	EvbRegs.CMPR6 = 0;

// test
//	EvbRegs.EXTCONB.bit.INDCOE=1;//what for?

	EvbRegs.COMCONB.bit.CENABLE = 1;  //设置比较单元??//enable;cld=2;
	EvbRegs.COMCONB.bit.FCOMPOE=1;//compare enable
	EvbRegs.COMCONB.bit.CLD=2;//instant
	EvbRegs.COMCONB.bit.ACTRLD=2;


	EvbRegs.ACTRB.all = 0;//0xfff;    //设置输出特性??//High effective// intial now is high (old is low,change it)

//CAP  -----------------------------------------------------------------------
	EvbRegs.CAPCONB.all = 0x30fc;//??//enable; capture the two sides

	EvbRegs.CAPFIFOB.all = 0;
}	
	
//===========================================================================
// No more.
//===========================================================================



























