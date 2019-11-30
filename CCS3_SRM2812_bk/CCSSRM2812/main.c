/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
/*File: MAIN.C
/*Target Processor: TMS320F240
/*Compiler Version: 6.6
/*Assembler Version: 6.6
/*Created: 10/31/97
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* This file is the main program for the control of an SRM drive with a
/*position sensor
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*------------------------------------------------------------------*/
/*INCLUDE FILES */
/*------------------------------------------------------------------*/
#include "c240.h"
#include "srm.h"
#include "DSP281x_Device.h"
#include "System.h"
/*---------------------------------------------------------*/
/*GLOBAL VARIABLE DECLARATIONS */
/*---------------------------------------------------------*/
int count;
int slice;
int old_count;
int Update_Velocity;
int Toggle_LED;
int Msmt_Update;
anSRM_struct SRM;
int LEDvalue;
interrupt void AdcInt_ISR(void);
interrupt void EvbCAPISR_INT(void);
void eventmgr_init();
void initializeSRM(anSRM_struct *anSRM);
void Commutation_Algorithm(anSRM_struct *anSRM);
void Time_Update_Position(anSRM_struct *anSRM);
void velocityController(anSRM_struct *anSRM);
void currentController(anSRM_struct *anSRM);
void computePositionAndVelocity(anSRM_struct *anSRM);
void Msmt_Update_Velocity(anSRM_struct *anSRM, int mode);
void Msmt_Update_Position(anSRM_struct *anSRM);
void switch_lowside(int phaseactive);
void switch_mux(int adc1, int adc2);
void disable_interrupts();
void dsp_setup();
void initialize_counters_and_flags();
void enable_interrupts();
void start_background();
void check_for_stall();


/*-------------------------------------------------------*/
/*MAIN PROGRAM */
/*-------------------------------------------------------*/
void main() 
{
	InitSysCtrl();
	
	initializeSRM(&SRM);
	eventmgr_init();
	initialize_counters_and_flags();
	enable_interrupts();
	start_background();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*BACKGROUND TASKS */
/*--------------------------------------------------------- */
/*Upon completion of the required initialization, the main
/*program starts the background task. The background is
/*simply an infinite loop. Time critical motor control
/*processing is done via interrupt service routines and lower
/*priority processing is done in the background, when they
/*are needed. Two background operations are defined:
/*
/*1) Update_Velocity - when a capture interrupt occurs,
/* the ISR stores the capture data and then intiates
/* this task. The velocity update is done in
/* background, because it is doing a floating point
/* division.
/*2) Toggle_LED - this task toggles an LED on the EVM to
/* provide visual feedback to the user that the code
/* is running. This task is initiated at a fixed
/* rate set by the ONE_HALF_SECOND value.
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void start_background()
{
	while (1)
	{
		/*----------------------*/
		/* Velocity update task */
		/*----------------------*/
		if (Update_Velocity) 
		{
			if (Update_Velocity == 1) 
			{ /* use capture data */
				/* as time base */
				Msmt_Update_Velocity(&SRM, 1);
			}
			else { /* else shaft is rotating too slowly, capture
				   /* data may be in error by overflow.
				   /* use count of timer ISR’s between captures
				   /* as time base. */
				Msmt_Update_Velocity(&SRM, 2);
			}
			Update_Velocity = 0;
		}

		/*-----------------------*/
		/* Visual feedback task */
		/*-----------------------*/

		//下面语句没看懂。/////////////////////////////////////////////？？？？？

		if (Toggle_LED) 
		{
			LEDvalue = -LEDvalue;
			if (LEDvalue == 1) 
			{
			//	asm(" OUT 1, 000ch");
			}
			else 
			{
			//	asm(" OUT 0, 000ch");
			}
			Toggle_LED = 0;



			SRM.wDes_10xrpm = 6000; /* motor speed command units = (rpm x 10) */
			/* just hard-coded here, but setup */
			/* another background task to allow */
			/* command from an external input */
		}
	} /* infinite loop */
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*TIMER ISR */
/*-----------------------------------------------------------------*/
/*
/*This interrupt service routine is executed at each
/*occurence of the maskable CPU interrupt INT3. This CPU
/*interrupt corresponds to the event manager group B interrupts,
/*of which we enable only the timer #3 period interrupt, TPINT3.
/*The frequency, F, at which this routine is executed is specified
/*using the CPU_INT_FREQ parameter.
/*
/*The SRM control algorithms which are implemented during the
/*timer ISR are:
/*
/* 1. Current control (frequency = F)
/* 2. Rotor position estimation (frequency = F)
/* 3. Commutation (frequency = F/5)
/* 4. Velocity control (frequency = F/5)
/*
/*Additionally, time can be measured (coarsely) by counting
/*the number of executions of this ISR, which runs at a
/*known fixed rate. This measure of time is used for several
/*reasons, including:
/*
/*- For precaution against over-current, a simple
/*test is made to determine if the rotor has stalled.
/*
/*- Also, the visual feedback task is initiated if the correct
/*amount of time has elapsed.
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//void c_int3()
interrupt void AdcInt_ISR(void)		//2

{



	//*IFR_REG = 0x0004; /* clear interrupt flags */
	//*IFRB = 0xff;
	currentController(&SRM); /* current loop algorithm */
	if (Msmt_Update) 
	{ /* position estimation */
		Msmt_Update_Position(&SRM); /* if recent capture edge */
		Msmt_Update = 0; /* use this information */
	}
	else 
	{ /* else, propagate pos est */
		Time_Update_Position(&SRM); /* using algorithm */
	}
	check_for_stall();
	count = count + 1; /* increment count */
	slice = slice + 1; /* increment slicer */
	if (slice == 1) 
	{
		Commutation_Algorithm(&SRM); /* do commutation in the 1st */
	} /* slice. */
	else if (slice == 2) 
	{ /* velocity loop algorithm in */
		velocityController(&SRM); /* the 2nd */
	}
	else if (slice == 5) 
	{
		slice = 0; /* reset slicer */
	}
	if (count == ONE_HALF_SECOND) 
	{ /* set flag for toggling the */
		Toggle_LED = 1; /* EVM LED, if time */
		count = 0;
	}

	PieCtrlRegs.PIEACK.all = 0x0001;
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0;
	EINT;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*CAPTURE ISR */
/*----------------------------------------------------------------- */
/*
/*This interrupt service routine is executed at each
/*occurence of the maskable CPU interrupt INT4. This CPU
/*interrupt corresponds to the event manager group C interrupts,
/*of which we enable the three capture event interrupts,
/*CAPINT1-3. This ISR executes asynchronously and the
/*frequency of execution is dependent on the shaft speed
/*of the SRM.
/*
/*The ISR performs the following processing:
/*
/* clear interrupt flags;
/* determine which capture has occured;
/* read the appropriate capture FIFO register;
/* store capture data;
/* set flag for position update using measurement;
/* set flag for initiating velocity estimate
/* update in background;
/* return;
/*
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//void c_int4()
interrupt void EvbCAPISR_INT(void)		//2
{
	int groupc_flags;
	int capture;
	int n;
	int delta_count;
	WORD edge_time;
	//*IFR_REG = 0x0008; /* clear CPU interrupt flag */
	///*--------------------------------------------------------*/
	///* determine which capture interrupt occured and read */
	///* the appropriate FIFO */
	///*--------------------------------------------------------*/
	//groupc_flags = *IFRC; /* read event manger interrupt */  //读取是哪个中断
	/* flag register */
	groupc_flags = EvbRegs.EVBIFRC.all; /* read event manger interrupt */

	if (groupc_flags & 0x1){ /* capture #1 */
		//*IFRC = 0xf9; /* clear flag register */ //1001
		EvbRegs.EVBIFRC.bit.CAP4INT = 1;//
		capture = 1; /* */
		edge_time = read_fifo(capture); /* read FIFO */
	}
	else if (groupc_flags & 0x2) { /* capture #2 */
		//*IFRC = 0xfa;								//1010
		
		EvbRegs.EVBIFRC.bit.CAP5INT = 1;//2
		capture = 2;
		edge_time = read_fifo(capture);
	}
	else if (groupc_flags & 0x4) { /* capture #3 */
		//*IFRC = 0xfc;								//1100
		EvbRegs.EVBIFRC.bit.CAP6INT = 1;	//2
		capture = 3;
		edge_time = read_fifo(capture);
	}
	else { /* not a valid capture */
		//*IFRC = 0xff;
		EvbRegs.EVBIFRC.all = 0xff;//2
		capture = 0;
	}
	/*---------------------------------------------------------------*/
	/* if a valid capture occured, store capture data and set flags */
	/* foor position and velocity estimate updates. The most */
	/* recent two time intervals between edges is saved */
	/* to allow for some filtering of the velocity estimate. */
	/* The number of timer ISR’s which occur between capture */
	/* interrupts is also checked. When this time exceeds a */
	/* certain value, then the capture data could be in error */
	/* by an overflow, so the lower resolution delta-time */
	/* associated with the ISR count is used in the velocity */
	/* estimate calculation. */

	/*--------------------------------------------------------------- */
	if (capture > 0) 
	{
		SRM.last_capture = capture; /* save capture data */
		n = capture-1;
		SRM.capture_delta[n][1] = SRM.capture_delta[n][0];
		SRM.capture_delta[n][0] = edge_time - SRM.capture_edge[n];
		SRM.capture_edge[n] = edge_time;
		Msmt_Update = 1; /* position update flag */
		/*-----------------------------------------------------------*/
		/* Set flags & select time base for use with velocity update */
		/*-----------------------------------------------------------*/
		delta_count = count - old_count;
		old_count = count;
		if (delta_count < 0) 
			delta_count = delta_count + ONE_HALF_SECOND;

		if (delta_count > 100) 
		{ /* low shaft speed use */
			/* ISR counter */
			SRM.delta_count = delta_count;
			Update_Velocity = 2;
		}
		else 
		{ /* else, shaft speed ok */
			/* use 1.25MHz clk */
			SRM.delta_count = delta_count;
			Update_Velocity = 1;
		}
	}
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*UTILITY SUBROUTINES */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*******************************************************************
void disable_interrupts()
{
	asm(" SETC INTM");
}
*****************************************************************/


//void dsp_setup() 
//{
//	int temp;
//	/*------------------------*/
//	/* Disable watchdog timer */
//	/*------------------------*/
//	temp = *WDCR;
//	temp = temp | 0x68;
//	*WDCR = temp;
//
//
//
//
//	/*--------------------------------------*/
//	/* initialize PLL module (10 MHz XTAL1) */
//	/*--------------------------------------*/
//	*CKCR1 = 0xb1; /* 20MHz CPUCLK = 10MHz crystal */
//	/* and 2x PLL mult ratio */
//	*CKCR0 = 0xc3; /* low-power mode 0, */
//	/* ACLK enabled, */
//	/* PLL enabled, */
//	/* SYSCLK=CPUCLK/2 */
//	*SYSCR = 0x40c0;
//}

/************************************************************************/
void initialize_counters_and_flags() {
	count = 0; /* current timer ISR count */
	slice = 0; /* ISR slice count */
	old_count = 0; /* timer ISR count at last */
	/* capture edge */
	Toggle_LED = 0; /* flag for visual feedback */
	/* background task */
	LEDvalue = 1; /* current LED value */
	Update_Velocity = 0; /* flag for velocity update */
	/* background task */
	Msmt_Update = 0; /* flag for mode of position */
	/* estimate update */
}
/************************************************************************/
void enable_interrupts() 
{
	EINT;
	ERTM;




	//*IFR_REG = 0xffff; /* Clear pending interrupts */
	//*IFRA = 0xffff;
	//*IFRB = 0xffff;
	//*IFRC = 0xffff;
	//*IMR_REG = 0x000c; /* Enable CPU Interrupts: */
	///* INT4 & INT3 */
	//*IMRA = 0x0000; /* Disable all event manager */
	///* Group A interrupts */
	//*IMRB = 0x0010; /* Enable timer 3 period */
	///* interrupt */
	//*IMRC = 0x0007; /* Enable CAP1-CAP3 interrupts*/
	//asm(" CLRC INTM"); /* Global interrupt enable */
}
/************************************************************************/
void check_for_stall()
{
	int delta_count;
	/*---------------------------------------------------------------*/
	/* The SRM is assumed to have stalled if the number of timer */
	/* ISR’s which are executed exceeds 1000. At F = 5 kHz */
	/* this corresponds to roughly 6 rpm. If this condition */
	/* is detected, the opto-coupler levels are read and the */
	/* rotor position is re-initialized */
	/*---------------------------------------------------------------*/
	delta_count = count - old_count;
	if (delta_count < 0) delta_count = delta_count + ONE_HALF_SECOND;
	if (delta_count > 1000) 
	{
		SRM.wEst_10xrpm = 0;
		//SRM.position_state = *PBDATDIR & 0x7;
		SRM.position_state = GpioDataRegs.GPADAT.all & 0x7;
		SRM.position = SRM.position_initial_guess[SRM.position_state];
	}


}

