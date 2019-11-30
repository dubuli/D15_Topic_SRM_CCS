
//File: EVMGR.C
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

//#include "c240.h"
#include "constant.h"

#include "srm.h"
#include "DSP28_Device.h"
#include "System.h"
#include "typedefs.h"

interrupt void AdcInt_ISR(void);
extern int SlowDownFlag;
//interrupt void EvbCAPISR_INT(void);

void eventmgr_init() 
{
	WORD iperiod1;
	WORD iperiod2;
	unsigned int i;

	iperiod1 = (SYSCLK_FREQ / CPU_INT_FREQ) - 1;//5kHz

	EALLOW;
	GpioMuxRegs.GPBMUX.all = 0x07FF; // EVA PWM 1-6,2PWM, CAP456
	EDIS;

	EvaRegs.T1PR = iperiod1;
	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	EvaRegs.T1CON.all = 0x1040;//TPS=0

	EvaRegs.GPTCONA.bit.T1TOADC = 2;//period to ADC

	iperiod2 = (SYSCLK_FREQ / PWM_FREQ) - 1;
	EvbRegs.T3PR = iperiod2;
	EvbRegs.T3CNT = 0;
	EvbRegs.T3CMPR = 0;
	EvbRegs.T3CON.all = 0x1042;

	EvbRegs.T4PR = 0xffff;
	EvbRegs.T4CNT = 0;

	EvbRegs.T4CON.all = 0x1440;//Tps=5,GuweiGang P245

	EvbRegs.CMPR4 = 0;//设置比较寄存器
	EvbRegs.CMPR5 = 0;
	EvbRegs.CMPR6 = 0;

	EvbRegs.ACTRB.all = 0x0999;    //设置输出特性

	EvbRegs.COMCONB.all = 0xA600;  //设置比较单元


	EvbRegs.CAPCONB.all = 0x30fc;

	EvbRegs.CAPFIFOB.all = 0;

/* 	EALLOW;                                                                                                   */
/* 	PieVectTable.CAPINT1 = &EvbCAPISR_INT;//用CAP中断函数入口更新PIE向量表	//2    ！！！要把这个加到main中去 */
/*                                                                                                            */
/*                                                                                                            */
/* 	PieVectTable.CAPINT2 = &EvbCAPISR_INT;                                                                    */
/* 	PieVectTable.CAPINT3 = &EvbCAPISR_INT;                                                                    */
/* 	EDIS;	                                                                                                  */


	//ADC
	EALLOW;
	PieVectTable.ADCINT = &AdcInt_ISR;//用CAP中断函数入口更新PIE向量表	//2    ！！！要把这个加到main中去
	EDIS;


	AdcRegs.ADCTRL1.bit.RESET = 1;
	asm(" NOP");
	AdcRegs.ADCTRL1.bit.RESET = 0;

	AdcRegs.ADCTRL1.bit.SUSMOD = 3;
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0;
	AdcRegs.ADCTRL1.bit.CPS = 0;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
	for (i = 0; i < 10000; i++)
	{
		asm(" NOP");
	}

	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
	for (i = 0; i < 5000; i++)
	{
		asm(" NOP");
	}
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 15;
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;
	AdcRegs.MAX_CONV.all = 0x0007;

	AdcRegs.CHSELSEQ1.bit.CONV00 = 0;
	AdcRegs.CHSELSEQ1.bit.CONV01 = 1;
	AdcRegs.CHSELSEQ1.bit.CONV02 = 2;
	AdcRegs.CHSELSEQ1.bit.CONV03 = 3;
	AdcRegs.CHSELSEQ2.bit.CONV04 = 4;
	AdcRegs.CHSELSEQ2.bit.CONV05 = 5;
	AdcRegs.CHSELSEQ2.bit.CONV06 = 6;
	AdcRegs.CHSELSEQ2.bit.CONV07 = 7;

	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ1_CLR = 1; 
	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ2_CLR = 1;


	AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ = 0;
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
	AdcRegs.ADCTRL2.bit.EVA_SOC_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1 = 0;
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0;
	AdcRegs.ADCTRL2.bit.SOC_SEQ2 = 0;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 0;
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ2 = 0;
	AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ2 = 0;
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;


	PieCtrl.PIEIER1.bit.INTx6 = 1;
	IER |= M_INT1;

}

//void switch_mux(int adc1, int adc2)
//{
//	WORD ctrl_word;
//	ctrl_word = 0x2c00; /* mask channel select bits */
//	ctrl_word = ctrl_word | (adc1 << 4); /* set ADC1 channel bits */
//	ctrl_word = ctrl_word | ((adc2-8) << 1); /* set ADC2 channel bits */
//	*ADCTRL1 = ctrl_word;
//	*ADCTRL2 = 0x0403;
//}

WORD read_a2d(int a2d_chan)
{
	WORD inval;
	if (a2d_chan == 1) {
		//inval = (*ADCFIFO1 >> 6) & 0x03ff;
		inval = AdcRegs.RESULT0;
	}
	else if (a2d_chan == 2) {
		//inval = (*ADCFIFO2 >> 6) & 0x03ff;
		inval = AdcRegs.RESULT1;
	}
	return inval;
}


void switch_lowside(int phaseactive)
{
	//WORD action;
	if (phaseactive & 0x1) 
	{
		//action = action | 0x000c;
		EvbRegs.ACTRB.bit.CMP7ACT = 1;
		if(SlowDownFlag==1)
		{
			EvbRegs.ACTRB.bit.CMP8ACT = 0;
		}
		else
		EvbRegs.ACTRB.bit.CMP8ACT = 3;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP7ACT = 0;
		EvbRegs.ACTRB.bit.CMP8ACT = 0;
	}
	/*---------------------------------------*/
	/* Force hi PWM4 if phase1 (B) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x2) 
	{
		//action = action | 0x00c0;
		EvbRegs.ACTRB.bit.CMP9ACT = 1;
		if(SlowDownFlag==1)
		{
			EvbRegs.ACTRB.bit.CMP10ACT = 0;
		}
		else
		EvbRegs.ACTRB.bit.CMP10ACT = 3;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP9ACT = 0;
		EvbRegs.ACTRB.bit.CMP10ACT = 0;
	}
	/*---------------------------------------*/
	/* Force hi PWM6 if phase2 (C) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x4) 
	{
		//action = action | 0x0c00;
		EvbRegs.ACTRB.bit.CMP11ACT = 1;
		if(SlowDownFlag==1)
		{
			EvbRegs.ACTRB.bit.CMP12ACT = 0;
		}
		else
		EvbRegs.ACTRB.bit.CMP12ACT = 3;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP11ACT = 0;
		EvbRegs.ACTRB.bit.CMP12ACT = 0;
	}

}

WORD read_fifo(int capture)
{
	WORD fifo_data;
	int fifo_status;
	if (capture == 1) {
		do {
			//fifo_data = *FIFO1; /* read value */
			fifo_data = EvbRegs.CAP4FIFO; /* read value */

			//fifo_status = *CAPFIFO & 0x0300; /* read status register, mask bits */
			fifo_status = EvbRegs.CAPFIFOB.bit.CAP4FIFO; /* read status register, mask bits */

		} while (fifo_status != 0);
	}
	else if (capture == 2) {
		do {
			fifo_data = EvbRegs.CAP5FIFO; /* read value */
			fifo_status = EvbRegs.CAPFIFOB.bit.CAP5FIFO; /* read status register, mask bits */
		} while (fifo_status != 0);
	}
	else if (capture == 3) {
		do {
			fifo_data = EvbRegs.CAP6FIFO; /* read value */
			fifo_status = EvbRegs.CAPFIFOB.bit.CAP6FIFO; /* read status register, mask bits */
		} while (fifo_status != 0);
	}
	else {
		fifo_data = 0xffff; /* error, not a valid capture */
	}
	return fifo_data;
}
