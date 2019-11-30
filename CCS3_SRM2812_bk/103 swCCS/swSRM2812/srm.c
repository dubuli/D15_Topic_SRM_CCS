/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* File: SRM.C */
/*Target Processor: TMS320F240 */
/*Compiler Version: 6.6 */
/*Assembler Version: 6.6 */
/*Created: 10/31/97 */
/*----------------------------------------------------------------- */
/* This file contains the algorithms for control of anSRM using */
/*a position sensor. The position sensor consists of a slotted */
/*disk and opto-couplers. */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*----------------------------------------------------------------- */
/*INCLUDE FILES */
/*---------------------------------------------------------------- */
#include "srm.h"
#include "c240.h"


#include "DSP281x_Device.h"
#include "System.h"
interrupt void AdcInt_ISR(void);
interrupt void EvbCAPISR_INT(void);
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*TIME UPDATE OF THE ROTOR POSITION ESTIMATE */
/*---------------------------------------------------------------- */
/* Between the capture events, which provide a shaft position */
/*measurement, position is estimated according to the equation */
/* */
/* theta(k) = theta(k-1) + w * delta_t; */
/* */
/*where theta = the position measurement (electrical angle) */
/* w = the current shaft velocity estimate */
/* delta_t = the execution frequency of the algorithm */
/* */
/*The arithmetic is performed using double precision. */
/* */
/*input: old position (where 2^16 = 2*pi radians) */
/* w (units of rpm * 10) */
/* K (constant incorporate delta_t and units) */
/* */
/*output: new position (where 2^16 = 2*pi radians) */
/* */
/*pseudo-code: dp = w * K; */
/* position = position + (dp * NR) */
/* */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void Time_Update_Position(anSRM_struct *anSRM)
{
	long dp; /* delta-position in mechanical angle */
	int speed;
	int temp;
	if (anSRM->wEst_10xrpm > 0) {
		dp = anSRM->wEst_10xrpm * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;
		temp = (int)(dp >> 16);
		anSRM->position = anSRM->position + (temp * NR);
	}
	else {
		speed = -anSRM->wEst_10xrpm;
		dp = speed * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;
		temp = (int)(dp >> 16);
		anSRM->position = anSRM->position -(temp * NR);
	}
} /* end Time_Update_Position */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*MEASUREMENT UPDATE OF THE ROTOR POSITION ESTIMATE */
/*----------------------------------------------------------------- */
/* At a capture interrupt, the rotor is at 1 of 6 positions. */
/* In between interrupts, the pickoff will be at 1 of six states, */
/* defined by the opto-couplers. The states are defined by [zyx] */
/* where: z = output of opto-coupler #3 */
/* y = output of opto-coupler #2 */
/* x = output of opto-coupler #1 */
/* */
/*State 2: 010 */
/*State 3: 011 */
/*State 1: 001 */
/*State 5: 101 */
/*State 4: 100 */
/*State 6: 110 */
/* */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void Msmt_Update_Position(anSRM_struct *anSRM)
{
	int old_state, new_state;
	int cap;
	/*-------------------------------------------------------------- */
	/* Based on capture and current state, get new state from the */
	/* state-machine look-up table */
	/*-------------------------------------------------------------- */
	cap = anSRM->last_capture;
	old_state = anSRM->position_state;
	new_state = anSRM->trans_lut[old_state][cap].state;
	/*----------------------------------------------------*/
	/* If transition is valid, update position and state */
	/*----------------------------------------------------*/
	if (new_state != 0) { /* valid transition, update data */
		anSRM->position = anSRM->trans_lut[old_state][cap].position;
		anSRM->shaft_direction = anSRM->trans_lut[old_state][cap].direction;
		anSRM->position_state = new_state;
	}
	else { /* else, not a valid transition, use opto-coupler */
		/* level & re-initialize position estimate */
		//anSRM->position_state = *PBDATDIR & 0x7;
		anSRM->position_state = GpioDataRegs.GPADAT.all & 0x7;
	}
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*VELOCITY ESTIMATION ALGORITHM */
/*----------------------------------------------------------------- */
/* This algorithm estimates the SRM shaft velocity. It is executed */
/*after each capture interrupt is received. If the shaft is */
/*moving fast enough, this routine is called with mode = 1 and */
/*the capture data is used. Otherwise, the # of timer ISRs */
/*which are executed between capture events is used in the */
/*velocity calculation. */
/* */
/*Velocity is calculated according to the equation: */
/* */
/* w = delta_theta / delta_t */
/* */
/*where delta_theta is known: */
/* (7.5 mech deg between each capture) */
/* (22.5 mech deg between the same capture) */
/*and delta_t is the measured number of clock cycles. */
/* */
/*The algorithm is implemented in double precision and is of */
/*the form: */
/* w = Kx_VELOCITY_EST/count */
/* */
/*where the constant Kx_VELOCITY_ESTIMATE (x=1,2) incorporates */
/*delta_theta and other units so that */
/*w has units of (rpm * 10). */
/* */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void Msmt_Update_Velocity(anSRM_struct *anSRM, int mode)
{
	DWORD a1, a2, a3, a4, a5, a6;
	DWORD sum_cnt;
	int inst_velocity;
	long filt_velocity;
	/*----------------------------------------------- */
	/* Obtain instantaneous velocity estimate */
	/*----------------------------------------------- */
	if (mode == 1) { /* use timer #2 as time base */
		/*------------------------------------------------------------*/
		/* FIR filter for removing once per electrical cycle effects */
		/*------------------------------------------------------------*/
		a1 = (DWORD)anSRM->capture_delta[0][0];
		a2 = (DWORD)anSRM->capture_delta[0][1];
		a3 = (DWORD)anSRM->capture_delta[1][0];
		a4 = (DWORD)anSRM->capture_delta[1][1];
		a5 = (DWORD)anSRM->capture_delta[2][0];
		a6 = (DWORD)anSRM->capture_delta[2][1];
		sum_cnt = a1 + a2 + a3 + a4 + a5 + a6;
		/*---------------------------------------------------*/
		/* apply velocity = delta_theta/delta_time algorithm */
		/*---------------------------------------------------*/
		sum_cnt = K1_VELOCITY_EST / sum_cnt;
		inst_velocity = ((int)sum_cnt) * anSRM->shaft_direction;
	}
	else { /* else, use timer ISR count as time base */
		/*---------------------------------------------------*/
		/* apply velocity = delta_theta/delta_time algorithm */
		/*---------------------------------------------------*/
		sum_cnt = K2_VELOCITY_EST / anSRM->delta_count;
		inst_velocity = ((int)sum_cnt) * anSRM->shaft_direction;
	}
	/*----------------------------------------------- */
	/* IIR filter for smoothing velocity estimate */
	/*----------------------------------------------- */

	filt_velocity = (ALPHA * anSRM->wEst_10xrpm)
		+ (ONE_MINUS_ALPHA * inst_velocity);
	anSRM->wEst_10xrpm = (int)(filt_velocity >> 3);
} /* end, velocity estimation */



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*COMMUTATION ALGORITHM */
/*------------------------------------------------------------------------ */
/* A four quadrant commutation algorithm, using a fixed-dwell angle */
/* of 120 electrical degrees and a variable turn on angle. With */
/*a fixed dwell of 120 electrical degrees, only a single phase */
/*is active at any one time. The advance angle is calculated as */
/*a function of speed and desired current. */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void Commutation_Algorithm(anSRM_struct *anSRM)
{
	int phase;
	WORD electricalAngle;
	WORD angle;
	int channel;
	long advance;
	int whats_active;
	int desiredCurrent;
	int temp;
	/*---------------------------*/
	/* Advance angle calculation */
	/*---------------------------*/
	advance = (anSRM->wEst_10xrpm * anSRM->desiredTorque);
	advance = advance >> 9;
	/*-------------------------------------------------------*/
	/* Offset for advance angle negative torque, if required */
	/*-------------------------------------------------------*/
	if (anSRM->desiredTorque > 0) 
	{
		electricalAngle = anSRM->position + (int)advance;
		desiredCurrent = anSRM->desiredTorque;
	}
	else {
		electricalAngle = anSRM->position + PI_16 -(int) advance;
		desiredCurrent = -anSRM->desiredTorque;
	}
	/*-------------------------------- */
	/* for each phase do ... */
	/*-------------------------------- */
	whats_active = 0x0;
	for (phase = 0; phase< NUMBER_OF_PHASES; phase++) {
		/*------------------------------*/
		/* 120 degree offsets for phase */
		/*------------------------------*/
		angle = electricalAngle - phase * TWOPIBYTHREE_16;
		/*-----------------------------------------------------------*/
		/* turn phase on, if between desired angles and switch */
		/* the mux on the A/D to measure the desired */
		/* phase current */
		/*-----------------------------------------------------------*/
		if ((angle >= (PIBYSIX_16)) && (angle < (FIVEPIBYSIX_16))) 
		{
			anSRM->active[phase] = 1;
			temp = 0x1 << phase;
			channel = anSRM->a2d_chan[phase];
			switch_mux(channel, channel + 8);
			anSRM->iDes[phase] = desiredCurrent;
			if (anSRM->iDes[phase] > ILIMIT) anSRM->iDes[phase] = ILIMIT;
		}
		else 
		{
			anSRM->active[phase] = 0;
			temp = 0;
			anSRM->iDes[phase] = 0;
		}
		whats_active = whats_active | temp;
	}
	/*------------------------------------*/
	/* switch low-side FETs, as required */
	/*------------------------------------*/
	switch_lowside(whats_active);
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*VELOCITY CONTROL LOOP ALGORITHM */
/*------------------------------------------------------------------------ */
/* The algorithm implements a PI compensator for the velocity */
/*control of the SRM. The PI filter limits the integrator */
/*to prevent windup */
/* */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void velocityController(anSRM_struct *anSRM)
{
	int speed_error;
	int integral_error;
	/*------------------------------*/
	/* calculate error signal */
	/*------------------------------*/
	speed_error = anSRM->wDes_10xrpm - anSRM->wEst_10xrpm;
	/*------------------------------*/
	/* integrate error */
	/*------------------------------*/
	anSRM->integral_speed_error = anSRM->integral_speed_error + (long)speed_error;
	/*------------------------------*/
	/* apply integrator limit */
	/*------------------------------*/
	if (anSRM->integral_speed_error > INTEGRAL_LIMIT) {
		anSRM->integral_speed_error = INTEGRAL_LIMIT;
	}
	if (anSRM->integral_speed_error < -INTEGRAL_LIMIT) {
		anSRM->integral_speed_error = -INTEGRAL_LIMIT;
	}
	/*------------------------------*/
	/* PI filter */
	/*------------------------------*/
	integral_error = (int)((KI*anSRM->integral_speed_error) >> 13);
	anSRM->desiredTorque = ((KP*speed_error) >> 1) + integral_error;
} /* end velocityController */
/********************************************************** */
/*CURRENT CONTROL LOOP ALGORITHM */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void currentController(anSRM_struct *anSRM) {
	int phase;
	int ierr;
	for (phase = 0; phase < NUMBER_OF_PHASES; phase++) {
		/*----------------------------------------------*/
		/* for each active phase do ... */
		/*----------------------------------------------*/
		if (anSRM->active[phase] > 0) {
			/*--------------------*/
			/* read A/D converter */
			/*--------------------*/
			anSRM->iFB[phase] = read_a2d(1);
			/*---------------------------*/
			/* calculate error signal */
			/*---------------------------*/
			ierr = anSRM->iDes[phase] - anSRM->iFB[phase];
			/*---------------------------*/
			/* current loop compensation */
			/*---------------------------*/
			anSRM->dutyRatio[phase] = ILOOP_GAIN * ierr;
			anSRM->dutyRatio[phase] = (anSRM->dutyRatio[phase] >> 3);
			/*------------------*/
			/* limit duty ratio */
			/*------------------*/
			if (anSRM->dutyRatio[phase] < 0) {
				anSRM->dutyRatio[phase] = 0;
			}
			if (anSRM->dutyRatio[phase] > MAXIMUM_DUTYRATIO) {
				anSRM->dutyRatio[phase] = MAXIMUM_DUTYRATIO;
			}
		}
		/*----------------------------------------------*/
		/* else, phase is not active */
		/*----------------------------------------------*/
		else {
			anSRM->iFB[phase] = 0;
			anSRM->dutyRatio[phase] = 0;
		}
	} /* end for loop */
	/*---------------------------------------*/
	/* output PWM signals to high-side FET¡¯s */
	///*---------------------------------------*/
	//*CMPR1 = anSRM->dutyRatio[0];
	//*CMPR2 = anSRM->dutyRatio[1];
	//*CMPR3 = anSRM->dutyRatio[2];

	EvbRegs.CMPR4 = anSRM->dutyRatio[0];//ÉèÖÃ±È½Ï¼Ä´æÆ÷
	EvbRegs.CMPR5 = anSRM->dutyRatio[1];
	EvbRegs.CMPR6 = anSRM->dutyRatio[2];
} /* end currentController */
/****************************************************************** */
/*SRM ALGORITHM INITIALIZATION */
/*----------------------------------------------------------------- */
void initializeSRM(anSRM_struct *anSRM)
{
	int i, j;


	EALLOW;
	GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0 = 0;
	GpioMuxRegs.GPAMUX.bit.PWM2_GPIOA1 = 0;
	GpioMuxRegs.GPAMUX.bit.PWM3_GPIOA2 = 0;

	GpioMuxRegs.GPADIR.bit.GPIOA0 = 0;
	GpioMuxRegs.GPADIR.bit.GPIOA1 = 0;
	GpioMuxRegs.GPADIR.bit.GPIOA2 = 0;

	EDIS;

	

	/*---------------------------------------------------------*/
	/* define mux positions for current feedback of each phase */
	/*---------------------------------------------------------*/
	anSRM->a2d_chan[0] = 1; /* phase A current on pin ADCIN1 */
	anSRM->a2d_chan[1] = 2; /* phase B current on pin ADCIN2 */
	anSRM->a2d_chan[2] = 3; /* phase C current on pin ADCIN3 */
	/*-------------------------------------------------------------- */
	/* Define position estimation state machine. */
	/* */
	/* Given current state, i, and capture event, j, with */
	/* every transition (capture event), 3 parameters are defined: */
	/* 1. trans_lut[i][j].state = the new state */
	/* 2. trans_lut[i][j].position = the shaft position */
	/* 3. trans_lut[i][j].direction = the shaft direction */
	/*-------------------------------------------------------------- */
	/*---------------------------------------------------*/
	/* fill table with zeros. zeros will define illegal */
	/* transitions */
	/*---------------------------------------------------*/
	for (i = 0; i<7; i++) {
		for (j = 0; j<4; j++) {
			anSRM->trans_lut[i][j].state = 0;
			anSRM->trans_lut[i][j].position = 0;
			anSRM->trans_lut[i][j].direction = 0;
		}
	}
	/*------------------------------*/
	/* ¡¯new-state¡¯ definitions */
	/*------------------------------*/
	anSRM->trans_lut[1][2].state = 3;
	anSRM->trans_lut[1][3].state = 5;
	anSRM->trans_lut[2][1].state = 3;
	anSRM->trans_lut[2][3].state = 6;
	anSRM->trans_lut[3][1].state = 2;
	anSRM->trans_lut[3][2].state = 1;
	anSRM->trans_lut[4][1].state = 5;
	anSRM->trans_lut[4][2].state = 6;
	anSRM->trans_lut[5][1].state = 4;
	anSRM->trans_lut[5][3].state = 1;
	anSRM->trans_lut[6][2].state = 4;
	anSRM->trans_lut[6][3].state = 2;
	/*--------------------------------------*/
	/* ¡¯shaft direction¡¯ definitions */
	/*--------------------------------------*/
	anSRM->trans_lut[1][2].direction = -1;
	anSRM->trans_lut[1][3].direction = 1;
	anSRM->trans_lut[2][1].direction = 1;
	anSRM->trans_lut[2][3].direction = -1;
	anSRM->trans_lut[3][1].direction = -1;
	anSRM->trans_lut[3][2].direction = 1;
	anSRM->trans_lut[4][1].direction = -1;
	anSRM->trans_lut[4][2].direction = 1;
	anSRM->trans_lut[5][1].direction = 1;
	anSRM->trans_lut[5][3].direction = -1;
	anSRM->trans_lut[6][2].direction = -1;
	anSRM->trans_lut[6][3].direction = 1;
	/*--------------------------------------*/
	/* ¡¯shaft position¡¯ definitions */
	/*--------------------------------------*/
	anSRM->trans_lut[1][2].position = TWOPIBYTHREE_16;
	anSRM->trans_lut[1][3].position = PI_16;
	anSRM->trans_lut[2][1].position = PIBYTHREE_16;
	anSRM->trans_lut[2][3].position = 0;
	anSRM->trans_lut[3][1].position = PIBYTHREE_16;
	anSRM->trans_lut[3][2].position = TWOPIBYTHREE_16;
	anSRM->trans_lut[4][1].position = FOURPIBYTHREE_16;
	anSRM->trans_lut[4][2].position = FIVEPIBYTHREE_16;
	anSRM->trans_lut[5][1].position = FOURPIBYTHREE_16;
	anSRM->trans_lut[5][3].position = PI_16;
	anSRM->trans_lut[6][2].position = FIVEPIBYTHREE_16;
	anSRM->trans_lut[6][3].position = 0;
	/*--------------------------------------------------------------------- */
	/* define initial guesses for each state. The initial position */
	/* is assumed at the midpoint of each state */
	/*--------------------------------------------------------------------- */
	anSRM->position_initial_guess[1] = TWOPIBYTHREE_16 + PIBYSIX_16;
	anSRM->position_initial_guess[2] = PIBYSIX_16;
	anSRM->position_initial_guess[3] = PIBYTHREE_16 + PIBYSIX_16;
	anSRM->position_initial_guess[4] = FOURPIBYTHREE_16 + PIBYSIX_16;
	anSRM->position_initial_guess[5] = PI_16 + PIBYSIX_16;
	anSRM->position_initial_guess[6] = FIVEPIBYTHREE_16 + PIBYSIX_16;
	/*------------------------------------------------------*/
	/* read opto-couplers and get initial position estimate */
	/*------------------------------------------------------*/
	//anSRM->position_state = *PBDATDIR & 0x7;
	anSRM->position_state = GpioDataRegs.GPADAT.all & 0x7;
	anSRM->position = anSRM->position_initial_guess[anSRM->position_state];
	/*-------------------------*/
	/* set initial conditions */
	/*-------------------------*/
	for (i = 0; i < NUMBER_OF_PHASES; i++) {
		anSRM->iDes[i] = 0;
		anSRM->active[i] = 0;
		anSRM->iFB[i] = 0;
		anSRM->capture_delta[i][0] = 65535;
		anSRM->capture_delta[i][1] = 65535;
	}
	anSRM->wEst_10xrpm = 0;
	anSRM->shaft_direction = 0;
	anSRM->dp_remainder = 0;
	anSRM->integral_speed_error = 0;
	anSRM->wDes_10xrpm = 0;
}
