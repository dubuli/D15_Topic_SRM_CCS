/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* */
/*File: SRM.H */
/*Target Processor: TMS320F240 */
/*Compiler Version: */
/*Assembler Version: */
/*Created: 10/1/97 */
/* */
/*-----------------------------------------------------------------*/
/* Variable declarations for the SRM control algorithm */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* #ifndef _THIS_FILE_ */
/* #define _THIS_FILE_ */
/* #endif              */
#ifndef _MYMATH_H
#define _MYMATH_H


#include "constant.h"

#include "typedefs.h"
/*----------------------------------------------------------*/
/* position estimation state machine data structure */
/*----------------------------------------------------------*/
typedef struct 
{
	int state;
	WORD position;
	int direction;
} state_machine;


/*--------------------------------------------------------------------------------*/
/* SRM variables data structure: */
/*--------------------------------------------------------------------------------*/
//a2d_chan[i] -> sets which A/D pin is used for the ith phase current
//desiredTorque -> torque command (output of velocity loop)
//integral_speed_error -> velocity loop integrator for PI compensator
//iDes[i] -> current command for the ith phase
//capture_edge[i] -> timer #2 count value at the occurence of
// the most recent ith capture
//capture_delta[i][2] -> change in the timer #2 count value between
// the occurences of the ith capture events. The two most
// recent events are stored.
//delta_count -> change in the software counter of the timer ISR
// between occurences of any capture event.
/*wEst_10xrpm -> shaft velocity estimate (units of rpm*10)
/* wDes_10xrpm -> desired shaft velocity (units of rpm*10)
/* active[i] -> flag indicating whether the ith phase is ON (1 = on)
/* iFB[i] -> current feedback measurement for the ith phase
/* dutyRatio[i] -> commanded % duty ratio for the high-side FET of
/* the ith phase
/*position -> shaft position estimate (electrical degrees)
/* scaled: 2*pi (rad) = 65535 bits
/*position_state -> position state of the SRM (defined by opto-couplers)
/*shaft_direction -> direction which the shaft is rotating.
/*trans_lut[7][4] -> the position state machine
/*position_initial_guess[7] -> initial position guess, based on state
/*dp_remainder -> 16-bit remainder used in the position estimation alg
/*last_capture -> the most recent capture to occur
/*----------------------------------------------------------------------------*/
typedef struct 
{
	int a2d_chan[NUMBER_OF_PHASES];
	int desiredTorque;
	long integral_speed_error;
	WORD iDes[NUMBER_OF_PHASES];
	WORD capture_edge[NUMBER_OF_PHASES];
	WORD capture_delta[NUMBER_OF_PHASES][2];
	WORD delta_count;
	int wEst_10xrpm;
	int wDes_10xrpm;
	int active[NUMBER_OF_PHASES];
	WORD iFB[NUMBER_OF_PHASES];
	int dutyRatio[NUMBER_OF_PHASES];
	WORD position;
	int position_state;
	int shaft_direction;
	state_machine trans_lut[7][4];
	WORD position_initial_guess[7];
	long dp_remainder;
	int last_capture;
} anSRM_struct;

/*-----------------------------------------------------------------*/
/*PROTOTYPE DEFINITIONS */
/*-----------------------------------------------------------------*/

#endif
