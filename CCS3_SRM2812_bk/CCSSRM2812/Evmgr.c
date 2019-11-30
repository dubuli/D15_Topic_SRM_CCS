/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//File: EVMGR.C
//Target Processor: TMS320F240
//Compiler Version: 6.6
//Assembler Version: 6.6
//Created: 10/31/97
//
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
// This file contains the routines for initializing and using the event
// manager peripherials.
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*----------------------------------------------------------------- */
/*INCLUDE FILES */
/*----------------------------------------------------------------- */
#include "c240.h"
#include "constant.h"

#include "srm.h"
#include "DSP281x_Device.h"
#include "System.h"


interrupt void AdcInt_ISR(void);
interrupt void EvbCAPISR_INT(void);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*EVENT MANAGER INITIALIZATION */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
// Through appropriate programming of the event manager control
//registers, this routine sets up the event manager so that:
//
//all timers run in the continuous up count mode
//timer 1 provides the desired PWM frequency timebase
//timer 2 counts at 1/16 of the CPUCLK and is used as the time
// base for capture events. Prescaling prevents overflow
// except at only low shaft speeds.
//timer 3 provides the CPU interrupt
//A/D conversions are synchronized with timer 3 period occurences
//compare units are configured to the PWM mode
//PWMs 1,3, and 5 (used for high-side switching) are active low
//PWMs 2,4, and 6 (used for low-side switching) are forced hi/low
//sets up shared pins as capture inputs and digital inputs for
// interface with the opto-couplers
//initiates continuous A/D conversions.
//
//--------------------------------------------------------------------*/
// GPTCON Initialization parameters
// GPTCON = 0x1055
//
// xxx1 0000 0101 0101
// ___---__---_-- __--
// | | | | | | | |
// (15-13) Read-only status bits ---------| | | | | | | |
// (12-11) Start A/D on timer 3 period ------| | | | | | |
// (10-9) No timer 2 event starts A/D --------| | | | | |
// (8-7) No timer 1 event starts A/D -----------| | | | |
// (6) Enable timer compares -------------------| | | |
// (5-4) Timer 3 active low ------------------------| | |
// (3-2) Timer 2 active low ---------------------------| |
// (1-0) Timer 1 active low -----------------------------|
//
//--------------------------------------------------------------------*/
// T3CON Initialization parameters
// T3CON = 0x9040
//
// 1001 0000 0100 0000
// __----___ -_-- __-_
// | | | || | | ||
// (15-14) Stop on suspend --------------| | | || | | ||
// (13-11) Continuous up-count mode --------| | || | | ||
// (10-8) Clock prescaler = 1 -----------------| || | | ||
// (7) Use own TENABLE bit --------------------|| | | ||
// (6) Enable timer ---------------------------| | | ||
// (5-4) Use internal clock source -----------------| | ||
// (3-2) Reload at zero ------------------------------| ||
// (1) disable timer compare -------------------------||
// (0) Use own period register ------------------------|
//
//--------------------------------------------------------------------*/
// T2CON Initialization parameters
// T2CON = 0x9440
//
// 1001 0100 0100 0000
// __----___ -_-- __-_
// | | | || | | ||

// (15-14) Stop on suspend --------------| | | || | | ||
// (13-11) Continuous up-count mode --------| | || | | ||
// (10-8) Clock prescaler = 1/16 --------------| || | | ||
// (7) Use own TENABLE bit --------------------|| | | ||
// (6) Enable timer ---------------------------| | | ||
// (5-4) Use internal clock source -----------------| | ||
// (3-2) Reload at zero ------------------------------| ||
// (1) disable timer compare -------------------------||
// (0) Use own period register ------------------------|
//
//--------------------------------------------------------------------*/
// T1CON Initialization parameters
// T1CON = 0x9040
//
// 1001 0000 x100 0000
// __----___ -_-- __-_
// | | | || | | ||
// (15-14) Stop on suspend --------------| | | || | | ||
// (13-11) Continuous up-count mode --------| | || | | ||
// (10-8) Clock prescaler = 1 -----------------| || | | ||
// (7) Reserved on timer 1 --------------------|| | | ||
// (6) Enable timer ---------------------------| | | ||
// (5-4) Use internal clock source -----------------| | ||
// (3-2) Reload at zero ------------------------------| ||
// (1) Disable timer compare -------------------------||
// (0) Use own period register ------------------------|
//
//--------------------------------------------------------------------*/
// COMCON Initialization parameters
//
// COMCON = 0x8207
//
// 1000 0010 xxxx x111
// _--_ --_- -__---_-_
// | || | || | | | |||
// (15) Enable compares --------------| || | || | | | |||
// (14-13) Reload compare at 0 ------------|| | || | | | |||
// (12) Disable Space Vector PWM --------| | || | | | |||
// (11-10) Reload ACTR at 0 ------------------| || | | | |||
// (9) Enable full compare output pins -----|| | | | |||
// (8) Hi-Z simple compare output pins ------| | | | |||
// (7) Simple compare time base ---------------| | | |||
// (6-5) Simple compare reload --------------------| | |||
// (4-3) Simple compare SACTR reload ----------------| |||
// (2) Compare #3 to PWM mode -----------------------|||
// (1) Compare #2 to PWM mode ------------------------||
// (0) Compare #1 to PWM mode -------------------------|
//
//--------------------------------------------------------------------*/
// ACTR Initialization parameters
// ACTR = 0x0111
//
// xxxx 0001 0001 0001
// ____ --__ --__ --__
// | | | | | | |
// (15-12) Space vector PWM related ------| | | | | | |
// (11-10) PWM6 = Force Low ------------------| | | | | |
// (9-8) PWM5 = Active Low --------------------| | | | |
// (7-6) PWM4 = Force Low -----------------------| | | |
// (5-4) PWM3 = Active Low ------------------------| | |
// (3-2) PWM2 = Force Low ----------------------------| |
// (1-0) PWM1 = Active Low ------------------------------|
//
//--------------------------------------------------------------------*/
// ADCTRL1 Initialization parameters
// ADCTRL1 = 0x2c00
//
// 0010 110x 0000 0000

// _-_- _-_- _--- ___-
// |||| |||| | | | |
// (15) Suspend - Soft ---------------|||| |||| | | | |
// (14) Suspend - Free ----------------||| |||| | | | |
// (13) Start A/D Conversions ----------|| |||| | | | |
// (12) Disable Channel 1 ---------------| |||| | | | |
// (11) Enable Channel 2 ------------------|||| | | | |
// (10) Continuous conversion -------------||| | | | |
// (9) Disable interrupt ------------------|| | | | |
// (8) ADC Interrupt flag -------------------| | | | |
// (7) Conversion status ----------------------| | | |
// (6-4) ADC1 mux select --------------------------| | |
// (3-1) ADC2 mux select ------------------------------| |
// (0) Start conversion bit ---------------------------|
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void eventmgr_init() {
	WORD iperiod1;
	WORD iperiod2;
	unsigned int i;

	/*--------------------------------------------------------*/
	/* Initialize GP timer 3 to provide desired CPU interrupt */
	/*--------------------------------------------------------*/
	iperiod1 = (SYSCLK_FREQ / CPU_INT_FREQ) - 1;
	//*GPTCON = 0x1055; /* Setup general-purpose control reg */
	//*T3PER = iperiod; /* Load timer #2 period register */
	//*T3CON = 0x9040; /* Initialize timer #3 control register */
	//10 操作受仿真挂起的影响  01（此处是连续增） (2812连续增/减模式)  1使能定时器操作
	/*---------------------------------------------------------*/
	/* Initialize GP timer 1 to provide a 20 kHz time base for */
	/* fixed frequency PWM generation */
	/*---------------------------------------------------------*/

	EALLOW;
	GpioMuxRegs.GPBMUX.all = 0x07FF; // EVA PWM 1-6,2PWM, CAP456
	EDIS;

	EvaRegs.T1PR = iperiod1;
	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	EvaRegs.T1CON.all = 0x1040;

	EvaRegs.GPTCONA.bit.T1TOADC = 2;


	iperiod2 = (SYSCLK_FREQ / PWM_FREQ) - 1;
	EvbRegs.T3PR = iperiod2;
	EvbRegs.T3CNT = 0;
	EvbRegs.T3CMPR = 0;
	EvbRegs.T3CON.all = 0x1042;

	EvbRegs.T4PR = 0xffff;
	EvbRegs.T4CNT = 0;

	EvbRegs.T4CON.all = 0x1440;

	EvbRegs.CMPR4 = 0;//设置比较寄存器
	EvbRegs.CMPR5 = 0;
	EvbRegs.CMPR6 = 0;

	EvbRegs.ACTRB.all = 0x0999;    //设置输出特性

	EvbRegs.COMCONB.all = 0xA600;  //设置比较单元


	EvbRegs.CAPCONB.all = 0x30fc;

	EvbRegs.CAPFIFOB.all = 0;

	EALLOW;
	PieVectTable.CAPINT1 = &EvbCAPISR_INT;//用CAP中断函数入口更新PIE向量表	//2    ！！！要把这个加到main中去
	EDIS;

	PieVectTable.CAPINT2 = &EvbCAPISR_INT;
	PieVectTable.CAPINT3 = &EvbCAPISR_INT;

	EvbRegs.EVBIFRC.bit.CAP4INT = 1;
	EvbRegs.EVBIFRC.bit.CAP5INT = 1;
	EvbRegs.EVBIFRC.bit.CAP6INT = 1;
	EvbRegs.EVBIMRC.bit.CAP4INT = 1;
	EvbRegs.EVBIMRC.bit.CAP5INT = 1;
	EvbRegs.EVBIMRC.bit.CAP6INT = 1;

	PieCtrlRegs.PIEIER5.bit.INTx5 = 1;
	PieCtrlRegs.PIEIER5.bit.INTx6 = 1;
	PieCtrlRegs.PIEIER5.bit.INTx7 = 1;

	IER |= M_INT5;  // 使能 CPU INT 5	    


	//ADC
	EALLOW;
	PieVectTable.ADCINT = &AdcInt_ISR;//用CAP中断函数入口更新PIE向量表	//2    ！！！要把这个加到main中去
	EDIS;


	AdcRegs.ADCTRL1.bit.RESET = 1;
//	asm("NOP");
	AdcRegs.ADCTRL1.bit.RESET = 0;

	AdcRegs.ADCTRL1.bit.SUSMOD = 3;
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0;
	AdcRegs.ADCTRL1.bit.CPS = 0;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;
	AdcRegs.ADCTRL3.bit.ADCBGRFDN = 3;
	for (i = 0; i < 10000; i++)
	{
	//	asm("NOP");
	}

	AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
	for (i = 0; i < 5000; i++)
	{
	//	asm("NOP");
	}
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 15;
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;
	AdcRegs.ADCMAXCONV.all = 0x000f;

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0;
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0;
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0;
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0;
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0;
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0;
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0;

	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1; 
	AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;


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
	AdcRegs.ADCTRL2.bit.EVB_SOC_SEQ2 = 1;
	AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 0;


	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;
	IER |= M_INT1;


	//ADCLO = 0;

	//*T1PER = iperiod; /* Load timer #1 period */
	//*T1CON = 0x9040; /* Initialize timer #1 control register */
	///*-----------------------------------------------------------*/
	///* Initialize GP timer 2 to provide time base for clocking */
	///* capture events */
	///*-----------------------------------------------------------*/
	//*T2PER = 0xffff; /* Load timer #2 period */
	//*T2CON = 0x9440; /* Initialize timer #2 control register */
	///*-------------------------------------*/
	///* Setup Compare units for PWM outputs */
	///*-------------------------------------*/
	//*ACTR = 0x0111; /* Initialize action on output pins */
	//*DBTCON = 0x0; /* Disable deadband */
	//*CMPR1 = 0x0; /* Clear period registers */
	//*CMPR2 = 0x0;
	//*CMPR3 = 0x0;
	//*COMCON = 0x0207; /* Setup COMCON w/o enable */
	//*COMCON = 0x8207; /* Setup COMCON and enable */
	///*-------------------*/
	///* Setup shared pins */
	///* ------------------*/
	//*OCRA = 0x0; /* pins IOPB0-IOPB7 & IOPA0-IOPA3 to I/O pins */
	//*OCRB = 0xf1; /* pins are: ADSOC, XF, /BIO, CAP1-CAP4 */
	//*PBDATDIR = 0xf0f0; /* inputs IOPB0-IOPB3 */
	///* outputs IOPB4-IOPB7, set high */
	///*---------------------*/
	///* Setup capture units */
	///*---------------------*/
	//*CAPCON = 0x0; /* reset capture control register */
	//*CAPFIFO = 0xff; /* Clear FIFO’s */


	//*CAPCON = 0xb0fc; /* enable #1-3, use Timer2, both edges *
	/////无动作，使能45，使能6,456都选择定时器（2）（2812为4），都检测两个边沿


	///*---------------------*/
	///* Setup A/D converter */
	///*---------------------*/
	//*ADCTRL1 = 0x2c00; /* Initialize A/D control register */
	//*ADCTRL2 = 0x0403; /* Clear FIFO’s, Pre-scaler = 4 */
}
/**************************************************************/
/*SWITCH A/D INPUT CHANNEL */
/*------------------------------------------------------------*/
/* Each A/D converter unit has an 8:1 input multiplexer which
/* must be selected to the desired channel, prior to sampling.
/* The channel is selected by manipulating bits
/* of the ADCTRL1 control register
/*
/* inputs: adc1 = desired input channel for A/D #1
/* range: 0-7
/* adc2 = desired input channel for A/D #2
/* range: 8-15
/*outputs: none
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void switch_mux(int adc1, int adc2)
{
//	WORD ctrl_word;
//	ctrl_word = 0x2c00; /* mask channel select bits */
//	ctrl_word = ctrl_word | (adc1 << 4); /* set ADC1 channel bits */
//	ctrl_word = ctrl_word | ((adc2-8) << 1); /* set ADC2 channel bits */
//	*ADCTRL1 = ctrl_word;
//	*ADCTRL2 = 0x0403;
}
/********************************************************** */
/*READ A/D FIFO REGISTER */
/*--------------------------------------------------------- */
/* This routine is used to read the sampled A/D data from the
/*appropriate FIFO. The 10-bit A/D data is stored in the
/*FIFO in bits 15-6. A right shift of 6, limits the data
/*to the range 0-1023.
/*
/*inputs: a2d_chan = which FIFO to read
/* range: 1-2
/*outputs: inval = A/D data
/* range: 0-1023
/* 0 VDC = 0 bits
/* 5 VDC = 1023 bits
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
WORD read_a2d(int a2d_chan)
{
	WORD inval;
	if (a2d_chan == 1) {
		//inval = (*ADCFIFO1 >> 6) & 0x03ff;
		inval = AdcRegs.ADCRESULT0;
	}
	else if (a2d_chan == 2) {
		//inval = (*ADCFIFO2 >> 6) & 0x03ff;
		inval = AdcRegs.ADCRESULT1;
	}
	return inval;
}
/***********************************************************/
/*SWITCH LOW-SIDE MOSFETS */

/*-------------------------------------------------------- */
/* The state of the low-side power MOSFETS is controlled by the
/*level on the PWM2, PWM4, and PWM6 output pins, for phases
/*A, B, and C, respectively. Active high logic is used,
/*but since the low-side switches are used for commutation
/*instead of PWM control, we just use the force-low or
/*force-high action options.
/*
/*inputs: phaseactive = bits 0,1, and 2 control
/* the state of the PWM2, PWM4, and
/* PWM6 output pins, respectively.
/*
/* (ex. phaseactive = 0x5 will force PWM2 &
/* PWM6 high, PWM4 low )
/*outputs: none
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void switch_lowside(int phaseactive)
{
	WORD action;
	/*----------------------------------------------------*/
	/* load action register and mask PWM2, PWM4, and PWM6 */
	/* to force low */
	/*----------------------------------------------------*/
	//action = *ACTR;
	//action = action & 0xf333;
	/*---------------------------------------*/
	/* Force hi PWM2 if phase0 (A) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x1) 
	{
		//action = action | 0x000c;
		EvbRegs.ACTRB.bit.CMP7ACT = 3;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP7ACT = 0;
	}
	/*---------------------------------------*/
	/* Force hi PWM4 if phase1 (B) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x2) 
	{
		//action = action | 0x00c0;
		EvbRegs.ACTRB.bit.CMP9ACT = 3;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP9ACT = 0;
	}
	/*---------------------------------------*/
	/* Force hi PWM6 if phase2 (C) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x4) 
	{
		//action = action | 0x0c00;
		EvbRegs.ACTRB.bit.CMP10ACT = 3;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP10ACT = 0;
	}
	/*-----------------------------------*/
	/* Write new word to action register */
	/*-----------------------------------*/
	//*ACTR = action;
}
/********************************************************** */
/*READ CAPTURE FIFO REGISTERS */
/*--------------------------------------------------------- */
/* This routine is used to read the data from the capture FIFO
/*registers.
/*
/*inputs: capture = which FIFO to read?
/* range = 1-3
/*outputs fifo_data =
/* range = 0-65535
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
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