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
			
	iperiod1 = (HSCLK / T1FREQ) - 1;		//(HSCLK / CPU_INT_FREQ) - 1;//5kHz,T1,used to start ADC

/*------**
** Test attentio**
**------*/	
/* 	EvaRegs.GPTCONA.all = 0x0859;	 */

	EvaRegs.T1PR = iperiod1;
	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	EvaRegs.T1CON.all = 0x1000;//TPS=0,enable=0,to be enabled; enabled in main（）

	EvaRegs.GPTCONA.bit.T1TOADC = 2;//period to ADC


/*------**
** Test attentio**
test the EVA pwm
**------*/	
/* //	EvaRegs.GPTCONA.all = 0x0859; */
/* 	EvaRegs.T1CON.bit.TECMPR=1;       */
/* 	EvaRegs.T1CMPR=3000;              */

////EVB ------------------------------------------------
	iperiod3 = (HSCLK / PWM_FREQ) - 1;	//PWM	//=3749
	EvbRegs.T3PR = iperiod3;
	EvbRegs.T3CNT = 0;

	EvbRegs.T3CON.bit.TMODE = 2;//TPS=0,enable=0;
	EvbRegs.T3CON.bit.TPS=0;//divide 0
	EvbRegs.T3CON.bit.TENABLE=0;//unenable the t3 count
	EvbRegs.T3CON.bit.TCLKS10=0;
	EvbRegs.T3CON.bit.TECMPR=1;//enable the compare of PWM6-12


/*----------------------**
** 	attention,
T3PIN
t3cmpr    **
**----------------------*/	
	EvbRegs.GPTCONB.bit.TCMPOE=0;//test if 0,the CMPR will work,answer is CMPR works
									//the test reasult is, when set 0, the T3 and T4 will not work
									//but the 6 PWM of CMPR will still work
	EvbRegs.GPTCONB.bit.T3PIN=1;
//	EvbRegs.GPTCONB.all = 0x0859;				
	EvbRegs.T3CMPR = 1300;	//no use

	EvbRegs.CMPR4 = 0;//设置比较寄存器,compare to T3
	EvbRegs.CMPR5 = 0;
	EvbRegs.CMPR6 = 0;


	EvbRegs.T4CON.bit.TENABLE=0;	//enabled in main()
	EvbRegs.T4PR = 0xffff;
	EvbRegs.T4CNT = 0;
//	EvbRegs.T4CON.all = 0x1400;//Tps=5,enable=0;GuweiGang P245
	EvbRegs.T4CON.bit.TMODE=2;	//constant up;连续增
	EvbRegs.T4CON.bit.TPS=6;	//Tps=6; T4LCK=HS/64=75/64=1.171875M
	EvbRegs.T4CON.bit.SET3PR=0;	//use own T4PR
	EvbRegs.T4CON.bit.TECMPR=0;	//unable the cmpr
	EvbRegs.T4CON.bit.TCLD10=0;	//reload
	EvbRegs.T4CON.bit.TCLKS10=0;//input clock is HSCLK
	EvbRegs.T4CON.bit.T4SWT3=0;	//use own enable



// test
//	EvbRegs.EXTCONB.bit.INDCOE=1;//what for?//孙丽明 p363

	EvbRegs.COMCONB.bit.CENABLE = 1;  //设置比较单元??//enable;cld=2;
	EvbRegs.COMCONB.bit.FCOMPOE=1;//compare enable
	EvbRegs.COMCONB.bit.CLD=2;//instant
	EvbRegs.COMCONB.bit.ACTRLD=2;
//	EvbRegs.COMCONB.bit.C4TRIPE=0;
//	EvbRegs.COMCONB.bit.C5TRIPE=0;
//	EvbRegs.COMCONB.bit.C6TRIPE=0;

	EvbRegs.ACTRB.all =0xfff;    //设置输出特性??//High effective// intial now is high (old is low,change it)

//CAP  -----------------------------------------------------------------------
	EvbRegs.CAPCONB.all = 0x30fc;	//3 enable CAP 4 5 6
									//0 use T4 as base
									//fc both sides
									//??//enable; capture the two sides

	EvbRegs.CAPFIFOB.all = 0;
}	
	
//===========================================================================
// No more.
//===========================================================================



























