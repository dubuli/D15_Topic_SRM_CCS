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
	WORD iperiod2;

			
	iperiod1 = (SYSCLK_FREQ / CPU_INT_FREQ) - 1;//5kHz

	EALLOW;
	GpioMuxRegs.GPBMUX.all = 0x07FF; // EVA PWM 1-6,2PWM, CAP456
	EDIS;

	EvaRegs.T1PR = iperiod1;
	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	EvaRegs.T1CON.all = 0x1000;//TPS=0,enable=0,to be enabled;

	EvaRegs.GPTCONA.bit.T1TOADC = 2;//period to ADC

	iperiod2 = (SYSCLK_FREQ / PWM_FREQ) - 1;
	EvbRegs.T3PR = iperiod2;
	EvbRegs.T3CNT = 0;
	EvbRegs.T3CMPR = 0;
	EvbRegs.T3CON.all = 0x1042;//TPS=0,enable=1;

	EvbRegs.T4PR = 0xffff;
	EvbRegs.T4CNT = 0;

	EvbRegs.T4CON.all = 0x1440;//Tps=5,enable;GuweiGang P245

	EvbRegs.CMPR4 = 0;//设置比较寄存器
	EvbRegs.CMPR5 = 0;
	EvbRegs.CMPR6 = 0;

	EvbRegs.ACTRB.all = 0x0999;    //设置输出特性??

	EvbRegs.COMCONB.all = 0xA600;  //设置比较单元??


	EvbRegs.CAPCONB.all = 0x30fc;//??

	EvbRegs.CAPFIFOB.all = 0;

/* 	EALLOW;                                                                                                   */
/* 	PieVectTable.CAPINT1 = &EvbCAPISR_INT;//用CAP中断函数入口更新PIE向量表	//2    ！！！要把这个加到main中去 */
/*                                                                                                            */
/*                                                                                                            */
/* 	PieVectTable.CAPINT2 = &EvbCAPISR_INT;                                                                    */
/* 	PieVectTable.CAPINT3 = &EvbCAPISR_INT;                                                                    */
/* 	EDIS;	                                                                                                  */

}	
	
//===========================================================================
// No more.
//===========================================================================
