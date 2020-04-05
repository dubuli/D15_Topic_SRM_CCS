//AD实验，采样全为0，未加外部信号。
#include "DSP28_Device.h"
#include "srm.h"

#include "System.h"
#include "typedefs.h"
/*---------------------------------------------------------*/
/*GLOBAL VARIABLE DECLARATIONS */
/*---------------------------------------------------------*/

/*----------------**
** test attention **
**----------------*/			  

float	adclo=0.0;

int count=0;//5000Hz
int slice=0;//1-5
int old_count=0;//record count
int Update_Velocity=0;//flag
//int Toggle_LED=0;//flag
int Msmt_Update=0;// position update
int LEDvalue;


anSRM_struct SRM;

/*-----------------------------**
** simulate the postion signal **
** attention                   **
**-----------------------------*/		 
//int iTest=0;
//int simu6pos[6]={0x3,0x1,0x5,0x4,0x6,0x2};//simulate the postion signal
//int simu6count=0;

unsigned int i;//for key input 

void initializeSRM(anSRM_struct *anSRM);



interrupt void ad(void);
interrupt void EvbCAP4ISR_INT(void);
interrupt void EvbCAP5ISR_INT(void);
interrupt void EvbCAP6ISR_INT(void);


void currentController(anSRM_struct *anSRM);
void Msmt_Update_Velocity(anSRM_struct *anSRM, int mode);
void Time_Update_Position(anSRM_struct *anSRM);
void Commutation_Algorithm(anSRM_struct *anSRM);
void switch_lowside(int phaseactive);

int SciaTx_Ready(void);
void main(void)
{
	InitSysCtrl();			//初始化系统

	DINT;					//关中断 
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//初始化PIE控制寄存器
	InitPieVectTable();		//初始化PIE参数表 

	EALLOW;	
	PieVectTable.ADCINT=&ad;
	PieVectTable.CAPINT4=&EvbCAP4ISR_INT;	//use this to change the default ISR service. DefaultIsr.c
	PieVectTable.CAPINT5=&EvbCAP5ISR_INT;
	PieVectTable.CAPINT6=&EvbCAP6ISR_INT;
	EDIS;   

 	EvbRegs.EVBIMRC.bit.CAP4INT = 0;    //because the cpu willnot reset
 	EvbRegs.EVBIMRC.bit.CAP5INT = 0;    
 	EvbRegs.EVBIMRC.bit.CAP6INT = 0;    

    InitGpio();//ddcap
	InitAdc();				//初始化ADC
	InitEv();//ddcap
	InitSci();
	initializeSRM(&SRM);// should be set after the InitGpio();
   	
/*---------------------------------**
** 	attention                      **
** 	add the nop, to wait stable	   **
**---------------------------------*/							   
	for(i=0;i<10000;i++)	NOP;

 	EvbRegs.EVBIFRC.bit.CAP4INT = 1;  //in order to clear the beginning ISR  
 	EvbRegs.EVBIFRC.bit.CAP5INT = 1;    
 	EvbRegs.EVBIFRC.bit.CAP6INT = 1;   
 	 
 	EvbRegs.EVBIMRC.bit.CAP4INT = 1;    
 	EvbRegs.EVBIMRC.bit.CAP5INT = 1;    
 	EvbRegs.EVBIMRC.bit.CAP6INT = 1;    
	
//	PieCtrl.PIEIFR5.bit.INTx5=0;//CAP4 IFR
//	PieCtrl.PIEIFR5.bit.INTx6=0;
//	PieCtrl.PIEIFR5.bit.INTx7=0;

	PieCtrl.PIEIER5.bit.INTx5 = 1;//CAP4 IER
	PieCtrl.PIEIER5.bit.INTx6 = 1;//CAP5
	PieCtrl.PIEIER5.bit.INTx7 = 1;//CAP6

/*---------------------------------**
after the above lines, the ACK5=1; IFR=0x10;
** 	attention                      **
** 	unknown why                    **
** 	always trigger the CAP5 ISR	   **
**---------------------------------*/


	IER |= M_INT5;  // 使能 CPU INT 5	//EV CAP
	

//ADC------------------------------------------   
	PieCtrl.PIEIER1.bit.INTx6 = 1;//ADCINT enable
	IER |= M_INT1;			// Enable INT14 which is connected to CPU-Timer 2:

	EINT;					// Enable INTM
	ERTM;					// Enable DBGM
	EvaRegs.T1CON.bit.TENABLE=1;
	EvbRegs.T3CON.bit.TENABLE=1;
	EvbRegs.T4CON.bit.TENABLE=1;

	for(;;)
	{
//		KickDog();

		if(SWITCH1==1 || PAOCUP==1 ||PAOCDN==1 || PBOCUP==1 || PBOCDN==1 || PCOCUP==1 ||PCOCDN==1)	{
			EvbRegs.ACTRB.all = 0xfff;
			//EvbRegs.ACTRB.bit.CMP7-12ACT=3; //forecd high, PWM is forbiddend
		}

//		while(SWITCH1==1 || PAOCUP==1 ||PAOCDN==1 || PBOCUP==1 || PBOCDN==1 || PCOCUP==1 ||PCOCDN==1)

		/*----------------------*/
		/* Velocity update task */
		/*----------------------*/

		if (Update_Velocity) //Update_Velocity intial is 0
		{
			if (Update_Velocity == 1) 
			{
				 /* use capture data */
				/* as time base */
				Msmt_Update_Velocity(&SRM, 1);
			}
			else 
			{ 

				Msmt_Update_Velocity(&SRM, 2);
			}
			Update_Velocity = 0;
		}


		//Improtant,need to check the GPIOA12 for what
		if(count==1000)		{
			if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
				SciaRegs.SCITXBUF = SRM.wEst_10xrpm;

			//GpioDataRegs.GPATOGGLE.bit.GPIOA12=1;//output led
		}
	}
} 	

interrupt void ad(void)
{
/*-------------**
** //what for? **
** attention   **
delete in 2812f4
**-------------*/		 
//	IFR=0x0000;

//	PieCtrl.PIEIFR1.all = 0;
//	PieCtrl.PIEACK.all=0xffff;

/*----------------------------------**
** attention                        **
** may be will change the ADC input **
**----------------------------------*/								
	SRM.iFB[0]=(AdcRegs.RESULT0>>4) & 0x0fff;//define AdcRegs.ADCRESULT0 ADCRESULTPHASE1 !!!!!!!!!
	SRM.iFB[1]=(AdcRegs.RESULT2>>4) & 0x0fff;
	SRM.iFB[2]=(AdcRegs.RESULT4>>4) & 0x0fff;

	currentController(&SRM); /* current loop algorithm *///ddcap
	
	if (Msmt_Update) 
	{ /* position estimation */
		Msmt_Update = 0; /* use this information */
	}
	else 
	{ /* else, propagate pos est */
		Time_Update_Position(&SRM); /* using algorithm */
	}


/*-----------**
** what for? **
** attention **
**-----------*/		 
//	check_for_stall();


	count = count + 1; /* increment count */
	slice = slice + 1; /* increment slicer */
	if (slice == 1) 
	{
	
		
		Commutation_Algorithm(&SRM); /* do commutation in the 1st */

		//if (phaseactive & 0x1)
		//{
		//	//action = action | 0x000c;
		//	EvbRegs.ACTRB.bit.CMP7ACT = 1;
		//	if (SlowDownFlag == 1)
		//	{
		//		EvbRegs.ACTRB.bit.CMP8ACT = 0;
		//	}
		//	else
		//		EvbRegs.ACTRB.bit.CMP8ACT = 3;
		//}
		//else
		//{
		//	EvbRegs.ACTRB.bit.CMP7ACT = 0;
		//	EvbRegs.ACTRB.bit.CMP8ACT = 0;
		//}

	} /* slice. */

	else if (slice == 5) 
	{
		slice = 0; /* reset slicer */
	}
	if (count == ONE_HALF_SECOND) 
	{ /* set flag for toggling the */
//		Toggle_LED = 1; /* EVM LED, if time */
		count = 0;
	}



/*-------------------------------**
** 	attention                    **
** 	test the cap module,A8-10	 **
**-------------------------------*/	
/* Use GPADAT to give a simulate signal to the sensor*/ 						 
//		if(count%10==0)	{
//		GpioDataRegs.GPADAT.bit.GPIOA8=simu6pos[simu6count] & 1;
//		GpioDataRegs.GPADAT.bit.GPIOA9=(simu6pos[simu6count]>>1) & 1;
//		GpioDataRegs.GPADAT.bit.GPIOA10=(simu6pos[simu6count]>>2) & 1;
//
//		simu6count=simu6count+1;

//		if(simu6count>=6)//ddcap
//		{
//			simu6count=0;
//		} 		
//	}



	PieCtrl.PIEACK.all = 0x0001;

	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ1_CLR=1;

/*----------------------------------------------**
** in some examples,there is no next line ,why? **
** attention                                    **
**----------------------------------------------*/		 
	AdcRegs.ADCTRL2.bit.RST_SEQ1=1;//rest the SEQ1		//在这里设置断点


//	EINT;// what for? //delete in 2812f4
}



void EvbCAP4ISR_INT(void)
{
	int delta_count;
	WORD edge_time1;
	//	WORD edge_time2;

	// modified in 2812f5
	edge_time1 = EvbRegs.CAP4FIFO; /* read value */
	//	edge_time2 = EvbRegs.CAP4FIFO; /* read value */

	//need to change
	SRM.capture_delta[0][1] = SRM.capture_delta[0][0];
	SRM.capture_delta[0][0] = edge_time1 - SRM.capture_edge[0];//edgetime=return fifo_data = EvbRegs.CAP4FIFO
	SRM.capture_edge[0] = edge_time1;

	SRM.last_capture = 1; /* save capture data *///capture=1 2 3//use to update the position//ddcap

/** 	added in 2812f5 **** 	attention	    **/			 
	SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//get the state use the sensor signal
	SRM.position = SRM.trans_lut[SRM.position_state][1].position;//0 to PI //there is a time delay,not accurate
	SRM.shaft_direction_old=SRM.shaft_direction;
	SRM.shaft_direction = SRM.trans_lut[SRM.position_state][1].direction;//1 -1//attentionmodify

	//Added in f5a,if state is illegal (maybe because missing cap interrupt),
	//use guess position,and old direction
	if(SRM.position==0 || SRM.shaft_direction==0)	{
		SRM.position = SRM.position_initial_guess[SRM.position_state];
		SRM.shaft_direction=SRM.shaft_direction_old;
	}


	Msmt_Update = 1; /* position update flag */

	/*-----------------------------------------------------------*/
	/* Set flags & select time base for use with velocity update */
	/*-----------------------------------------------------------*/
	delta_count = count - old_count;//attentionmodify
	old_count = count;

	if (delta_count < 0) 
		delta_count = delta_count + ONE_HALF_SECOND;//in the ad "if (count == ONE_HALF_SECOND)"

	SRM.delta_count = delta_count;

	if (delta_count > 50) 	{ 
		//the frequency of count is 5K, so it's 50/5000 second per 7.5degree here  .MYWORK
		//750 mechinal degree/s,about 2 n/s

		/* low shaft speed use *** ISR counter */
		Update_Velocity = 2;
	}
	else 	{ 
		/* else, shaft speed ok */
		/* use 1.25MHz clk */
		Update_Velocity = 1;
	}
	 
	EvbRegs.EVBIFRC.bit.CAP4INT = 1;//to clear the 清除捕获中断4的标志位
	PieCtrl.PIEACK.bit.ACK5 = 1; //origin: ACK.all=0x0010

}


void EvbCAP5ISR_INT(void)
{
	//	int capdata1;
	//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	WORD edge_time1;
	//	WORD edge_time2;

	// modified in 2812f5
	edge_time1 = EvbRegs.CAP5FIFO; /* read value */
	//	edge_time2 = EvbRegs.CAP5FIFO; /* read value */

	//need to change
	SRM.capture_delta[1][1] = SRM.capture_delta[1][0];
	SRM.capture_delta[1][0] = edge_time1 - SRM.capture_edge[1];//edgetime=return fifo_data = EvbRegs.CAP5FIFO
	SRM.capture_edge[1] = edge_time1;


	SRM.last_capture = 2; /* save capture data *///capture=1 2 3//use to update the position//ddcap

	/*------------------**
	** 	added in 2812f5 **
	** 	attention	    **
	**------------------*/			 
	SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//attentiondelete ,need to delete
	SRM.position = SRM.trans_lut[SRM.position_state][2].position;//0 to PI //there is a time delay,not accurate
	SRM.shaft_direction_old=SRM.shaft_direction;
	SRM.shaft_direction = SRM.trans_lut[SRM.position_state][2].direction;//1 -1//attentionmodify

	if(SRM.position==0 || SRM.shaft_direction==0)	{
		SRM.position = SRM.position_initial_guess[SRM.position_state];
		SRM.shaft_direction=SRM.shaft_direction_old;
	}

	Msmt_Update = 1; /* position update flag */

	/*-----------------------------------------------------------*/
	/* Set flags & select time base for use with velocity update */
	/*-----------------------------------------------------------*/
	delta_count = count - old_count;
	old_count = count;

	if (delta_count < 0) 
		delta_count = delta_count + ONE_HALF_SECOND;

	if (delta_count > 50) 
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

	EvbRegs.EVBIFRC.bit.CAP5INT = 1;
	PieCtrl.PIEACK.bit.ACK5 = 1; //origin: ACK.all=0x0010
}



void EvbCAP6ISR_INT(void)
{
	//	int capdata1;
	//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	WORD edge_time1;
	//	WORD edge_time2;

	// modified in 2812f5
	edge_time1 = EvbRegs.CAP6FIFO; /* read value */
//	edge_time2 = EvbRegs.CAP6FIFO; /* read value */

	//need to change
	SRM.capture_delta[2][1] = SRM.capture_delta[2][0];
	SRM.capture_delta[2][0] = edge_time1 - SRM.capture_edge[2];//edgetime=return fifo_data = EvbRegs.CAP6FIFO
	SRM.capture_edge[2] = edge_time1;

	SRM.last_capture = 3; /* save capture data *///capture=1 2 3//use to update the position//ddcap

	/*------------------**
	** 	added in 2812f5 **
	** 	attention	    **
	**------------------*/			 
	SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//attentiondelete ,need to delete
	SRM.position = SRM.trans_lut[SRM.position_state][3].position;//0 to PI //there is a time delay,not accurate
	SRM.shaft_direction_old=SRM.shaft_direction;
	SRM.shaft_direction = SRM.trans_lut[SRM.position_state][3].direction;//1 -1//attentionmodify

	if(SRM.position==0 || SRM.shaft_direction==0)	{
		SRM.position = SRM.position_initial_guess[SRM.position_state];
		SRM.shaft_direction=SRM.shaft_direction_old;
	}


	Msmt_Update = 1; /* position update flag */

	/*-----------------------------------------------------------*/
	/* Set flags & select time base for use with velocity update */
	/*-----------------------------------------------------------*/
	delta_count = count - old_count;
	old_count = count;

	if (delta_count < 0) 
		delta_count = delta_count + ONE_HALF_SECOND;

	if (delta_count > 50) 
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
	 

	EvbRegs.EVBIFRC.bit.CAP6INT = 1;
	PieCtrl.PIEACK.bit.ACK5 = 1; //origin: ACK.all=0x0010
}





void initializeSRM(anSRM_struct *anSRM)
{
	int i, j;

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
	

	/*--------------------------------------*/
	/* ’shaft direction’ definitions (OLD)(ORIGIN)*/
	/*--------------------------------------*/
/* 	anSRM->trans_lut[1][2].direction = -1;   */
/* 	anSRM->trans_lut[1][3].direction = 1;    */
/* 	anSRM->trans_lut[2][1].direction = 1;    */
/* 	anSRM->trans_lut[2][3].direction = -1;   */
/* 	anSRM->trans_lut[3][1].direction = -1;   */
/* 	anSRM->trans_lut[3][2].direction = 1;    */
/* 	anSRM->trans_lut[4][1].direction = -1;   */
/* 	anSRM->trans_lut[4][2].direction = 1;    */
/* 	anSRM->trans_lut[5][1].direction = 1;    */
/* 	anSRM->trans_lut[5][3].direction = -1;   */
/* 	anSRM->trans_lut[6][2].direction = -1;   */
/* 	anSRM->trans_lut[6][3].direction = 1;	 */



	/*------------------------------*/
	/* ’new-state’ definitions */
	//用来更新state
/* 	attention            */
/* 	changed in 2812f5	.MYWORK	 */
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
	anSRM->trans_lut[1][2].direction = 1;
	anSRM->trans_lut[1][3].direction = -1;
	anSRM->trans_lut[2][1].direction = -1;
	anSRM->trans_lut[2][3].direction = 1;
	anSRM->trans_lut[3][1].direction = 1;
	anSRM->trans_lut[3][2].direction = -1;
	anSRM->trans_lut[4][1].direction = 1;
	anSRM->trans_lut[4][2].direction = -1;
	anSRM->trans_lut[5][1].direction = -1;
	anSRM->trans_lut[5][3].direction = 1;
	anSRM->trans_lut[6][2].direction = 1;
	anSRM->trans_lut[6][3].direction = -1;
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

/*-------------------------------------**
** 	attention                          **
** 	the oppo is set to GPADAT & 0x7	   **
change to F11 12 13  origin.old:8 A9 A10
**-------------------------------------*/								   
	anSRM->position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;
//	anSRM->position_state>>=8;
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
	anSRM->shaft_direction_old = 0;
	anSRM->dp_remainder = 0;
	anSRM->integral_speed_error = 0;
	anSRM->wDes_10xrpm = 0;
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
	{ 
		/* use timer #2 as time base */
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
		inst_velocity = ((int)sum_cnt) * anSRM->shaft_direction;//10*rpm 
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


// set to 0
//	anSRM->wEst_10xrpm=0;
} /* end, velocity estimation */




void currentController(anSRM_struct *anSRM) 
{
	int phase;
//	int ierr;


	for (phase = 0; phase < NUMBER_OF_PHASES; phase++) 
	{
		/*----------------------------------------------*/
		/* for each active phase do ... */
		/*----------------------------------------------*/
		if (anSRM->active[phase] > 0) 
		{
			if(anSRM->iFB[phase]>=229)		//184-800mA,92-400mA	//chopcurrent
			{
				anSRM->dutyRatio[phase]=0;//compare to output LOW 
			}
			else if(anSRM->iFB[phase]<=200)	//172-750mA,86-375mA
			{
				anSRM->dutyRatio[phase]=0xffff;//compare to output HIGH 
			}
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
	EvbRegs.CMPR4 = anSRM->dutyRatio[0];//设置比较寄存器
	EvbRegs.CMPR5 = anSRM->dutyRatio[1];
	EvbRegs.CMPR6 = anSRM->dutyRatio[2];
	/* end currentController */

}






void Time_Update_Position(anSRM_struct *anSRM)
{
	long dp; /* delta-position in mechanical angle */
	int speed;
	int temp;
	if (anSRM->wEst_10xrpm >0)
	{
		dp = anSRM->wEst_10xrpm * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;/* delta-position in mechanical angle */
		temp = (int)(dp >> 16);//to convert to Electrial Angle 
//		anSRM->position = anSRM->position + (temp * NR);
	}
	else 
	{
		speed = -anSRM->wEst_10xrpm;
		dp = speed * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;
		temp = (int)(dp >> 16);
//		anSRM->position = anSRM->position -(temp * NR);
	}
} /* end Time_Update_Position */




void Commutation_Algorithm(anSRM_struct *anSRM)	//int the ADC interrupt
{
	int phase;
	WORD electricalAngle;//update in position update
	WORD angle;
	//int channel;
	int whats_active;
	int temp;

	whats_active = 0x0;
	electricalAngle = anSRM->position;
	
	for (phase = 0; phase< NUMBER_OF_PHASES; phase++) 
	{
		/*------------------------------*/
		/* 120 degree offsets for phase */
		/*------------------------------*/
		angle = electricalAngle + phase * TWOPIBYTHREE_16;
		/*-----------------------------------------------------------*/
		/* turn phase on, if between desired angles and switch */
		/* the mux on the A/D to measure the desired */
		/* phase current */
		/*-----------------------------------------------------------*/			

		if ((angle > PIBYSIX_16) && (angle < FIVEPIBYSIX_16))	//chopposition
		{
			anSRM->active[phase] = 1;
			temp = 0x1 << phase;
			anSRM->iDes[phase] = DESCURRENT;//Important!!
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
	if(SWITCH1==1 || PAOCUP==1 ||PAOCDN==1 || PBOCUP==1 || PBOCDN==1 || PCOCUP==1 ||PCOCDN==1)	{
		EvbRegs.ACTRB.all = 0xfff;
		//EvbRegs.ACTRB.bit.CMP7ACT=3;		EvbRegs.ACTRB.bit.CMP8ACT=3;		EvbRegs.ACTRB.bit.CMP9ACT=3;
		//EvbRegs.ACTRB.bit.CMP10ACT=3;		EvbRegs.ACTRB.bit.CMP11ACT=3;		EvbRegs.ACTRB.bit.CMP12ACT=3;
	}
	else	{
		switch_lowside(whats_active);
	}

}




void switch_lowside(int phaseactive)
{
	//WORD action;


	if (phaseactive & 0x1) 
	{
		//action = action | 0x000c;
		EvbRegs.ACTRB.bit.CMP7ACT = 2;//low effective

/*--------------**
** SlowDownFlag **
** attention    **
**--------------*/		 
/* 		if(SlowDownFlag==1)                */
/* 		{                                  */
/* 			EvbRegs.ACTRB.bit.CMP8ACT = 0; */
/* 		}                                  */
/* 		else                               */

		EvbRegs.ACTRB.bit.CMP8ACT = 0;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP7ACT = 3;
		EvbRegs.ACTRB.bit.CMP8ACT = 3;
	}
	/*---------------------------------------*/
	/* Force hi PWM4 if phase1 (B) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x2) 
	{
		//action = action | 0x00c0;
		EvbRegs.ACTRB.bit.CMP9ACT = 2;

/* 		if(SlowDownFlag==1)                 */
/* 		{                                   */
/* 			EvbRegs.ACTRB.bit.CMP10ACT = 0; */
/* 		}                                   */
/* 		else                                */

		EvbRegs.ACTRB.bit.CMP10ACT = 0;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP9ACT = 3;
		EvbRegs.ACTRB.bit.CMP10ACT = 3;
	}
	/*---------------------------------------*/
	/* Force hi PWM6 if phase2 (C) is active */
	/*---------------------------------------*/
	if (phaseactive & 0x4) 
	{
		//action = action | 0x0c00;
		EvbRegs.ACTRB.bit.CMP11ACT = 2;

/* 		if(SlowDownFlag==1)                 */
/* 		{                                   */
/* 			EvbRegs.ACTRB.bit.CMP12ACT = 0; */
/* 		}                                   */
/* 		else                                */

		EvbRegs.ACTRB.bit.CMP12ACT = 0;
	}
	else
	{
		EvbRegs.ACTRB.bit.CMP11ACT = 3;
		EvbRegs.ACTRB.bit.CMP12ACT = 3;
	}

}
