
/* File: SRM.C */

#include "srm.h"
//#include "c240.h"
#include "typedefs.h"

#include "DSP281x_Device.h"
#include "System.h"

extern int OprMode;//1:CCC 2:APC
//interrupt void AdcInt_ISR(void);
//interrupt void EvbCAPISR_INT(void);
extern void switch_lowside(int phaseactive);
extern WORD read_a2d(int a2d_chan);
//extern void switch_mux(int adc1, int adc2);


void Time_Update_Position(anSRM_struct *anSRM)
{
	long dp; /* delta-position in mechanical angle */
	int speed;
	int temp;
	if (anSRM->wEst_10xrpm > 0) 
	{
		dp = anSRM->wEst_10xrpm * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;
		temp = (int)(dp >> 16);
		anSRM->position = anSRM->position + (temp * NR);
	}
	else 
	{
		speed = -anSRM->wEst_10xrpm;
		dp = speed * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;
		temp = (int)(dp >> 16);
		anSRM->position = anSRM->position -(temp * NR);
	}
} /* end Time_Update_Position */

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
	if (new_state != 0) 
	{ /* valid transition, update data */
		anSRM->position = anSRM->trans_lut[old_state][cap].position;
		anSRM->shaft_direction = anSRM->trans_lut[old_state][cap].direction;
		anSRM->position_state = new_state;
	}
	else 
	{ /* else, not a valid transition, use opto-coupler */
		/* level & re-initialize position estimate */
		//anSRM->position_state = *PBDATDIR & 0x7;
		anSRM->position_state = GpioDataRegs.GPADAT.all & 0x7;
	}
}


void Msmt_Update_Velocity(anSRM_struct *anSRM, int mode)
{
	DWORD a1, a2, a3, a4, a5, a6;
	DWORD sum_cnt;
	int inst_velocity;
	long filt_velocity;
	/*----------------------------------------------- */
	/* Obtain instantaneous velocity estimate */
	/*----------------------------------------------- */
	if (mode == 1) 
	{ /* use timer #2 as time base */
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
	else 
	{ /* else, use timer ISR count as time base */
		/*---------------------------------------------------*/
		/* apply velocity = delta_theta/delta_time algorithm */
		/*---------------------------------------------------*/
		sum_cnt = K2_VELOCITY_EST / anSRM->delta_count;
		inst_velocity = ((int)sum_cnt) * anSRM->shaft_direction;
	}
	/*----------------------------------------------- */
	/* IIR filter for smoothing velocity estimate */
	/*----------------------------------------------- */

	filt_velocity = (ALPHA * anSRM->wEst_10xrpm)+ (ONE_MINUS_ALPHA * inst_velocity);
	anSRM->wEst_10xrpm = (int)(filt_velocity >> 3);
} /* end, velocity estimation */



void Commutation_Algorithm(anSRM_struct *anSRM)
{
	int phase;
	WORD electricalAngle;
	WORD angle;
	WORD anglem2pi;
	WORD anglep2pi;
	//int channel;
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
	else 
	{
		electricalAngle = anSRM->position + PI_16 -(int) advance;
		desiredCurrent = -anSRM->desiredTorque;
	}

	anglem2pi=electricalAngle - 2 * PI_16;

	anglep2pi=electricalAngle + 2 * PI_16;

	/*-------------------------------- */
	/* for each phase do ... */
	/*-------------------------------- */
	whats_active = 0x0;

	if(OprMode==1)
	{
		for (phase = 0; phase< NUMBER_OF_PHASES; phase++) 
		{
			/*------------------------------*/
			/* 120 degree offsets for phase */
			/*------------------------------*/
			angle = electricalAngle - phase * TWOPIBYTHREE_16;
			/*-----------------------------------------------------------*/
			/* turn phase on, if between desired angles and switch */
			/* the mux on the A/D to measure the desired */
			/* phase current */
			/*-----------------------------------------------------------*/

			

			if (((angle >= (PIBYSIX_16)) && (angle < (FIVEPIBYSIX_16))) || ((anglem2pi >= (PIBYSIX_16)) && (anglem2pi < (FIVEPIBYSIX_16))) || ((anglep2pi >= (PIBYSIX_16)) && (anglep2pi < (FIVEPIBYSIX_16)))) 
			{
				anSRM->active[phase] = 1;
				temp = 0x1 << phase;
				//channel = anSRM->a2d_chan[phase];
				//switch_mux(channel, channel + 8);
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
	}
	
	else if(OprMode==2)
	{
		for (phase = 0; phase< NUMBER_OF_PHASES; phase++) 
		{
			/*------------------------------*/
			/* 120 degree offsets for phase */
			/*------------------------------*/
			angle = electricalAngle - phase * TWOPIBYTHREE_16;
			/*-----------------------------------------------------------*/
			/* turn phase on, if between desired angles and switch */
			/* the mux on the A/D to measure the desired */
			/* phase current */
			/*-----------------------------------------------------------*/

			

			if (((angle >= (PIBYSIX_16)-anSRM->anglestep) && (angle < (FIVEPIBYSIX_16))) || ((anglem2pi >= (PIBYSIX_16)-anSRM->anglestep) && (anglem2pi < (FIVEPIBYSIX_16))) || ((anglep2pi >= (PIBYSIX_16)-anSRM->anglestep) && (anglep2pi < (FIVEPIBYSIX_16)))) 
			{
				anSRM->active[phase] = 1;
				temp = 0x1 << phase;
				//channel = anSRM->a2d_chan[phase];
				//switch_mux(channel, channel + 8);
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

	if (anSRM->integral_speed_error > INTEGRAL_LIMIT) 
	{
		anSRM->integral_speed_error = INTEGRAL_LIMIT;
	}
	if (anSRM->integral_speed_error < -INTEGRAL_LIMIT) 
	{
		anSRM->integral_speed_error = -INTEGRAL_LIMIT;
	}
/*------------------------------*/
/* PI filter */
/*------------------------------*/
	integral_error = (int)((KI*anSRM->integral_speed_error) >> 13);
	anSRM->desiredTorque = ((KP*speed_error) >> 1) + integral_error;
	

	if(OprMode==2)
	{
		integral_error = (int)((KI2*anSRM->integral_speed_error) >> 13);
		anSRM->cmprstep=((KP2*speed_error) >> 1) + integral_error;
		if (anSRM->cmprstep > CMPRSTEPLIMIT) 
		{
			anSRM->cmprstep = CMPRSTEPLIMIT;
		}
		if (anSRM->cmprstep < -CMPRSTEPLIMIT) 
		{
			anSRM->cmprstep = -CMPRSTEPLIMIT;
		}


		integral_error = (int)((KI3*anSRM->integral_speed_error) >> 13);
		anSRM->anglestep=((KP3*speed_error) >> 1) + integral_error;

		if (anSRM->anglestep > ANGLESTEPLIMIT) 
		{
			anSRM->anglestep = ANGLESTEPLIMIT;
		}
		if (anSRM->anglestep < -ANGLESTEPLIMIT) 
		{
			anSRM->anglestep = -ANGLESTEPLIMIT;
		}	

		
	}


} /* end velocityController */
/********************************************************** */
/*CURRENT CONTROL LOOP ALGORITHM */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void currentController(anSRM_struct *anSRM) 
{
	int phase;
//	int ierr;

	if(OprMode==1)
	{
		for (phase = 0; phase < NUMBER_OF_PHASES; phase++) 
		{
			/*----------------------------------------------*/
			/* for each active phase do ... */
			/*----------------------------------------------*/
			if (anSRM->active[phase] > 0) 
			{
				if(anSRM->iFB[phase]>=anSRM->iDes[phase] + iRANGE)
				{
					anSRM->dutyRatio[phase]=0xffff;
				}
				else if(anSRM->iFB[phase]<=anSRM->iDes[phase] - iRANGE)
				{
					anSRM->dutyRatio[phase]=0;
				}


				
				/*--------------------*/
				/* read A/D converter */
				/*--------------------*/

				//anSRM->iFB[phase] = read_a2d(1);
				


				/*---------------------------*/
				/* calculate error signal */
				/*---------------------------*/
			//	ierr = anSRM->iDes[phase] - anSRM->iFB[phase];
				/*---------------------------*/
				/* current loop compensation */
				/*---------------------------*/
			//	anSRM->dutyRatio[phase] = ILOOP_GAIN * ierr;
			//	anSRM->dutyRatio[phase] = (anSRM->dutyRatio[phase] >> 3);
				/*------------------*/
				/* limit duty ratio */
				/*------------------*/
			//	if (anSRM->dutyRatio[phase] < 0) {
			//		anSRM->dutyRatio[phase] = 0;
			//	}
			//	if (anSRM->dutyRatio[phase] > MAXIMUM_DUTYRATIO) {
			//		anSRM->dutyRatio[phase] = MAXIMUM_DUTYRATIO;
			//	}


			}
			/*----------------------------------------------*/
			/* else, phase is not active */
			/*----------------------------------------------*/
			else 
			{
				anSRM->iFB[phase] = 0;
				anSRM->dutyRatio[phase] = 0;
			}
		} /* end for loop */
		/*---------------------------------------*/
		/* output PWM signals to high-side FET’s */
		///*---------------------------------------*/
		//*CMPR1 = anSRM->dutyRatio[0];
		//*CMPR2 = anSRM->dutyRatio[1];
		//*CMPR3 = anSRM->dutyRatio[2];

		EvbRegs.CMPR4 = anSRM->dutyRatio[0];//设置比较寄存器
		EvbRegs.CMPR5 = anSRM->dutyRatio[1];
		EvbRegs.CMPR6 = anSRM->dutyRatio[2];
	} /* end currentController */

	else if(OprMode==2)
	{
		for (phase = 0; phase < NUMBER_OF_PHASES; phase++) 
		{
			/*----------------------------------------------*/
			/* for each active phase do ... */
			/*----------------------------------------------*/
			if (anSRM->active[phase] > 0) 
			
				anSRM->dutyRatio[phase]=CMPRBASE + anSRM->cmprstep;
			
			else 
			{
				anSRM->iFB[phase] = 0;
				anSRM->dutyRatio[phase] = 0;
			}
		} /* end for loop */
		/*---------------------------------------*/
		/* output PWM signals to high-side FET’s */
		///*---------------------------------------*/
		//*CMPR1 = anSRM->dutyRatio[0];
		//*CMPR2 = anSRM->dutyRatio[1];
		//*CMPR3 = anSRM->dutyRatio[2];

		EvbRegs.CMPR4 += anSRM->dutyRatio[0];//设置比较寄存器
		EvbRegs.CMPR5 += anSRM->dutyRatio[1];
		EvbRegs.CMPR6 += anSRM->dutyRatio[2];

	}
}
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


	for (i = 0; i<7; i++) 
	{
		for (j = 0; j<4; j++) {
			anSRM->trans_lut[i][j].state = 0;
			anSRM->trans_lut[i][j].position = 0;
			anSRM->trans_lut[i][j].direction = 0;
		}
	}
	/*------------------------------*/
	/* ’new-state’ definitions */
	//用来更新state
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
	/* ’shaft direction’ definitions */
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
	/* ’shaft position’ definitions */
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
	//guessed by the state, MIDPOINT
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
	for (i = 0; i < NUMBER_OF_PHASES; i++) 
	{
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
