/*File: MAIN.C-------------------haha-vcx-*/
//#include "c240.h"
#include "srm.h"
#include "DSP28_Device.h"
#include "System.h"
#include "typedefs.h"
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
int Error1;//if there is a Position error or Current Sensor Error
int PosError;//Position Error
int SlowDownFlag;//ir Slow Down or NOT
int BrakeFlag;//zhidong

int simu6pos[6]={0x2,0x3,0x1,0x5,0x4,0x6};//simulate the postion signal
int simu6count;

unsigned int i;//for key input 

int StartEn;

interrupt void AdcInt_ISR(void);//ADC interrupt
void EvbCAPISR_INT(void);
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
//void switch_mux(int adc1, int adc2);
void disable_interrupts();
void dsp_setup();
void initialize_counters_and_flags();
void enable_interrupts();
void start_background();
void check_for_stall();
extern WORD read_fifo(int capture);

/*-------------------------------------------------------*/
/*MAIN PROGRAM */
/*-------------------------------------------------------*/
void main() 
{
	InitSysCtrl();
	

	EALLOW;
	GpioMuxRegs.GPADIR.bit.GPIOA10=1;//Test 设置D1对应的DSP引脚为输出
	GpioMuxRegs.GPADIR.bit.GPIOA9=1;//Test
	GpioMuxRegs.GPADIR.bit.GPIOA8=1;//Test,to be deleted
	GpioMuxRegs.GPADIR.bit.GPIOA12=1;

	GpioDataRegs.GPADAT.bit.GPIOA10=0;//D1对应输出电平
	GpioDataRegs.GPADAT.bit.GPIOA9=1;//D1对应输出电平
	GpioDataRegs.GPADAT.bit.GPIOA8=0;
	GpioDataRegs.GPADAT.bit.GPIOA12=0;
	EDIS;
	initializeSRM(&SRM);
	eventmgr_init();


	initialize_counters_and_flags();
	Error1=1;
	PosError=0;
	SlowDownFlag=0;
	BrakeFlag=0;
	StartEn=0;
	
	simu6count=0;
//	enable_interrupts();
	EINT;
	ERTM;

	start_background();
}

void start_background()
{	

	SRM.position_state = 2;
	SRM.position = SRM.position_initial_guess[SRM.position_state];
	
	//Big loop
	while(1) //change to: while (!Errors)
	{

		/*----------------------*/
		/* Velocity update task */
		/*----------------------*/

		if (Update_Velocity) //Update_Velocity intial is 0
		{
			if (Update_Velocity == 1) 
			{ /* use capture data */
				/* as time base */
				Msmt_Update_Velocity(&SRM, 1);
			}
			else 
			{ 

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

			GpioDataRegs.GPATOGGLE.bit.GPIOA12=1;

			Toggle_LED = 0;



			SRM.wDes_10xrpm = 6000; /* motor speed command units = (rpm x 10) */
			/* just hard-coded here, but setup */
			/* another background task to allow */
			/* command from an external input */
		}

	}/* infinite loop */
}

interrupt void AdcInt_ISR(void)		//2

{



	//*IFR_REG = 0x0004; /* clear interrupt flags */
	//*IFRB = 0xff;
	
	SRM.iFB[0]=AdcRegs.RESULT0 * 3.0/65520.0;//define AdcRegs.ADCRESULT0 ADCRESULTPHASE1 !!!!!!!!!
	SRM.iFB[1]=AdcRegs.RESULT2 * 3.0/65520.0;
	SRM.iFB[2]=AdcRegs.RESULT4 * 3.0/65520.0;

	
	currentController(&SRM); /* current loop algorithm */
	
	
		//????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	

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
		Toggle_LED = 1; /* EVM LED, if time */
		count = 0;
	}

	PieCtrl.PIEACK.all = 0x0001;
	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ1_CLR = 1;
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
	EINT;

		if(count%10==0)
	{
		//GpioDataRegs.GPADAT.all=GpioDataRegs.GPADAT.all & 0x8f;
		//GpioDataRegs.GPADAT.all=(GpioDataRegs.GPADAT.all | simu6pos[simu6count]);
		GpioDataRegs.GPADAT.bit.GPIOA8=simu6pos[simu6count] & 1;
		GpioDataRegs.GPADAT.bit.GPIOA9=(simu6pos[simu6count]>>1) & 1;
		GpioDataRegs.GPADAT.bit.GPIOA10=(simu6pos[simu6count]>>2) & 1;

		simu6count=simu6count+1;
	
		if(simu6count>=6)
		{
			simu6count=0;
		} 
		
	}

}

void EvbCAPISR_INT(void)		//2
{
	int groupc_flags;
	int capture;
	int n;
	int delta_count;
	WORD edge_time;
	//*IFR_REG = 0x0008; /* clear CPU interrupt flag */

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
		edge_time = read_fifo(capture);//return fifo_data = EvbRegs.CAP6FIFO
	}
	else { /* not a valid capture */
		//*IFRC = 0xff;
		EvbRegs.EVBIFRC.all = 0xff;//2
		capture = 0;
	}


	if (capture > 0) 
	{
		SRM.last_capture = capture; /* save capture data *///capture=1 2 3
		n = capture-1;
		SRM.capture_delta[n][1] = SRM.capture_delta[n][0];
		SRM.capture_delta[n][0] = edge_time - SRM.capture_edge[n];//edgetime=return fifo_data = EvbRegs.CAP6FIFO
		SRM.capture_edge[n] = edge_time;
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
	}
	PieCtrl.PIEACK.all = 0x0010;
}

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


void enable_interrupts() 
{
	EINT;
	ERTM;

}
/************************************************************************/
void check_for_stall()
{
	int delta_count;

	delta_count = count - old_count;
	if (delta_count < 0) 
	delta_count = delta_count + ONE_HALF_SECOND;
	if (delta_count > 1000) 
	{
		SRM.wEst_10xrpm = 0;
		//SRM.position_state = *PBDATDIR & 0x7;
		SRM.position_state = GpioDataRegs.GPADAT.all & 0x7;
		SRM.position = SRM.position_initial_guess[SRM.position_state];
	}


}

