

/*File: SRM.H */


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

/*----------------------------------------------------------------------------*/
typedef struct 
{
	int a2d_chan[NUMBER_OF_PHASES];
	int desiredTorque;
	long integral_speed_error;
	WORD iDes[NUMBER_OF_PHASES];
	WORD capture_edge[NUMBER_OF_PHASES];
	WORD capture_delta[NUMBER_OF_PHASES][4];
	WORD delta_count;
	long wEst_10xrpm;//edit in 2812f5
	long wDes_10xrpm;//edit in 2812f5
	int active[NUMBER_OF_PHASES];
	WORD iFB[NUMBER_OF_PHASES];
	int dutyRatio[NUMBER_OF_PHASES];
	WORD position;
	int position_state;
	long shaft_direction;
	int shaft_direction_old;
	state_machine trans_lut[7][4];
	WORD position_initial_guess[7];
	long dp_remainder;
	int last_capture;

/*-------------------------**
** 	attention              **
** 	to be check if used	   **
**-------------------------*/				   
/* 	int cmprstep;     */
/* 	int anglestep;	  */


} anSRM_struct;

/*-----------------------------------------------------------------*/
/*PROTOTYPE DEFINITIONS */
/*-----------------------------------------------------------------*/

#endif
