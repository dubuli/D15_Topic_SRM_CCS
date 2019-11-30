// Use Flash


//Jfl3PiTwoPhaseStart1 更改485为两个字节
//Jfl3PiTwoPhaseStart2TesPos1  在每个CAP处，输出所获得的pos
//Jfl3PiTwoPhaseStart2TesPos2  在每个CAP处，输出两个pos是否相同
//AD实验，采样全为0，未加外部信号。
#include "DSP281x_Device.h"
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

int watchdogcount;
int WatchdogFlag;

int count_old=0;//record count
int UpdateVelocityFlag=0;//flag
//int Toggle_LED=0;//flag

int LEDvalue;

int SpeedFlag;
int CapCount;

int SpeedPiFlag;

long speed_error;
long iDes;
int StartFlag;

int SciTemp=0;
int SCiRxData=0;

int CurrentControllerFlag;
int PhaseControlFlag;
int Time_Update_PositionFlag;

extern Uint16 RamfuncsLoadStart;		//flash++
extern Uint16 RamfuncsRunStart;
extern Uint16 RamfuncsLoadEnd;

anSRM_struct SRM;

/*-----------------------------**
** simulate the postion signal **
** attention                   **
**-----------------------------*/
//int iTest=0;
int simu6pos[6]={0x3,0x1,0x5,0x4,0x6,0x2};//simulate the postion signal	//simu6pos
int simu6count=0;							//simu6pos

unsigned int i;//for key input

void initializeSRM(anSRM_struct *anSRM);



interrupt void ad(void);
interrupt void EvbCAP4ISR_INT(void);
interrupt void EvbCAP5ISR_INT(void);
interrupt void EvbCAP6ISR_INT(void);


void currentController(anSRM_struct *anSRM);
void UpdateVelocity(anSRM_struct *anSRM, int mode);
void Time_Update_Position(anSRM_struct *anSRM);
void PhaseControl(anSRM_struct *anSRM);
void switch_lowside(int phaseactive);
void InitFlash(void);
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

int SciaTx_Ready(void);
void main(void)
{
	InitSysCtrl();			//初始化系统



	DINT;					//关中断
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//初始化PIE控制寄存器
	InitPieVectTable();		//初始化PIE参数表

	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);	//flash++
	InitFlash();//初始化Flash


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

	SpeedFlag=0;
	CapCount=0;

	SpeedPiFlag=0;
	speed_error=0;
	iDes=0;	//gfl1i-n2
	StartFlag=0;
	watchdogcount=0;
	WatchdogFlag=0;
	CurrentControllerFlag=0;
	PhaseControlFlag=0;
	Time_Update_PositionFlag=0;

	SRM.wDes_10xrpm=5000;	//Desninate rpm
/*---------------------------------**
** 	attention                      **
** 	add the nop, to wait stable	   **
**---------------------------------*/
	for(i=0;i<10000;i++)	asm(" NOP");

 	EvbRegs.EVBIFRC.bit.CAP4INT = 1;  //in order to clear the beginning ISR
 	EvbRegs.EVBIFRC.bit.CAP5INT = 1;
 	EvbRegs.EVBIFRC.bit.CAP6INT = 1;

 	EvbRegs.EVBIMRC.bit.CAP4INT = 1;
 	EvbRegs.EVBIMRC.bit.CAP5INT = 1;
 	EvbRegs.EVBIMRC.bit.CAP6INT = 1;

//	PieCtrlRegs.PIEIFR5.bit.INTx5=0;//CAP4 IFR
//	PieCtrlRegs.PIEIFR5.bit.INTx6=0;
//	PieCtrlRegs.PIEIFR5.bit.INTx7=0;

	PieCtrlRegs.PIEIER5.bit.INTx5 = 1;//CAP4 IER
	PieCtrlRegs.PIEIER5.bit.INTx6 = 1;//CAP5
	PieCtrlRegs.PIEIER5.bit.INTx7 = 1;//CAP6

/*---------------------------------**
after the above lines, the ACK5=1; IFR=0x10;
** 	attention                      **
** 	unknown why                    **
** 	always trigger the CAP5 ISR	   **
**---------------------------------*/


	IER |= M_INT5;  // 使能 CPU INT 5	//EV CAP


//ADC------------------------------------------
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;//ADCINT enable
	IER |= M_INT1;			// Enable INT14 which is connected to CPU-Timer 2:

	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
	IER |= M_INT9;


	EINT;					// Enable INTM
	ERTM;					// Enable DBGM
	EvaRegs.T1CON.bit.TENABLE=1;
	EvbRegs.T3CON.bit.TENABLE=1;
	EvbRegs.T4CON.bit.TENABLE=1;

	EALLOW;
	SysCtrlRegs.WDCR = 0x0028;
	EDIS;

	for(;;)
	{
		KickDog();

		if(SWITCH1==1 || PAOCUP==1 ||PAOCDN==1 || PBOCUP==1 || PBOCDN==1 || PCOCUP==1 ||PCOCDN==1 || WatchdogFlag==0)	{
			EvbRegs.ACTRB.all = 0xfff;
			//EvbRegs.ACTRB.bit.CMP7-12ACT=3; //forecd high, PWM is forbiddend
			StartFlag=0;
		}

		//limit the current to 3A	//Set a Flag, break when Flag==5
		else if(SRM.iFB[0]>CURRENT_1A*25 || SRM.iFB[1]>CURRENT_1A*25 || SRM.iFB[2]>CURRENT_1A*25)	{
			EvbRegs.ACTRB.all = 0xfff;
			StartFlag=0;

		}
		else
			StartFlag=1;


		if(Time_Update_PositionFlag)	{
			Time_Update_Position(&SRM); /* using algorithm */
			Time_Update_PositionFlag=0;
		}


		if(PhaseControlFlag && StartFlag)	{
			PhaseControl(&SRM); /* do commutation in the 1st */
										//there is some question about it, should recosider!!!
			PhaseControlFlag=0;
		}
		if(CurrentControllerFlag && StartFlag)	{
			currentController(&SRM); /* current loop algorithm *///ddcap
			CurrentControllerFlag=0;
		}

		/*----------------------*/
		/* Velocity update task */
		/*----------------------*/
		if (UpdateVelocityFlag) //UpdateVelocityFlag intial is 0
		{
			if (UpdateVelocityFlag == 1)
			{
				 /* use capture data */
				/* as time base */
				UpdateVelocity(&SRM, 1);
			}
			else
			{

				UpdateVelocity(&SRM, 2);
			}
			UpdateVelocityFlag = 0;
		}



		//speedpiFlag is 480Hz;
		if(SpeedPiFlag==1 && StartFlag==1)	{

			speed_error=SRM.wDes_10xrpm-SRM.wEst_10xrpm;
			SRM.integral_speed_error=SRM.integral_speed_error+speed_error*14*KI;	//136*480=65536  //KI=1/32768*1000=1/32,32768=1<<15
			if(SRM.integral_speed_error>((long)CURRENT_1A<<3<<16))	{		//>>3,8A
				SRM.integral_speed_error=(long)CURRENT_1A<<3<<16;
			}
			else if(SRM.integral_speed_error<-(long)CURRENT_1A<<3<<16)	{
				SRM.integral_speed_error=-(long)CURRENT_1A<<3<<16;
			}

			iDes=speed_error*KP+(SRM.integral_speed_error>>16);	//KP=10KP注意速度已经是10倍速度 ,KI
			if(iDes>CURRENT_1A*20)	{
				iDes=CURRENT_1A*20;
			}
			else if(iDes<0)	{
				iDes=0;
			}


			SpeedPiFlag=0;

				//changeto 9600Hz 480-20Hz			//%250 20Hz		//5Hz// 5000/100=50 Hz
//				GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//				if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//					SciaRegs.SCITXBUF=(SRM.wEst_10xrpm/50);


		}



		//Improtant,need to check the GPIOA12 for what

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

//	PieCtrlRegs.PIEIFR1.all = 0;
//	PieCtrlRegs.PIEACK.all=0xffff;

/*----------------------------------**
** attention                        **
** may be will change the ADC input **
**----------------------------------*/
	SRM.iFB[0]=(AdcRegs.ADCRESULT0>>4) & 0x0fff;//define AdcRegs.ADCRESULT0 ADCRESULTPHASE1 !!!!!!!!!
	SRM.iFB[1]=(AdcRegs.ADCRESULT2>>4) & 0x0fff;
	SRM.iFB[2]=(AdcRegs.ADCRESULT4>>4) & 0x0fff;

	CurrentControllerFlag=1;
	PhaseControlFlag=1;
	Time_Update_PositionFlag=1;


//	check_for_stall();


	count++;	// = count + 1; /* increment count */
//	slice++; 	//= slice + 1; /* increment slicer */
	watchdogcount++;//1-5
	if(watchdogcount==1600 || watchdogcount==1610)
		WatchdogFlag=1;

	if (count >= T1FREQ)
	{
		count = 0;
	}



	if (  !( count % (T1FREQ/480) )  )	{		//9600/20=480Hz PI
		SpeedPiFlag=1;
	}

	if (  !( count % (T1FREQ/6) )  )	{	//6Hz
		if(CapCount<3)	{			//check if the wEst_10xrpm==0 Every 0.25s.
			SpeedFlag=0;
			SRM.wEst_10xrpm=0;		//no speed,=0.
		}
//		else if(CapCount<25)
//			SpeedFlag=1;			//Low speed,use counts
		else
			SpeedFlag=1;			//High speed,use CapFIFO

//		GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//		if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//			SciaRegs.SCITXBUF=(SpeedFlag);

		CapCount=0;
	}

	//delete
	//SRM.wEst_10xrpm=count;
	//	485,transfer the wEst,OUTPUT the wEst
//		if(!((count+10)%480))		{				//changeto 9600Hz 480-20Hz			//%250 20Hz		//5Hz// 5000/100=50 Hz
//			GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//
//			if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//				SciTemp=(int)SRM.wEst_10xrpm;
//				SciaRegs.SCITXBUF=((SRM.wEst_10xrpm)>>8 ) & 0xff;// & 0xff);
//		}
//		if(!((count)%480))		{				//changeto 9600Hz 480-20Hz			//%250 20Hz		//5Hz// 5000/100=50 Hz
//			GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//
//			if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//				//SciTemp=SRM.wEst_10xrpm;
//				SciaRegs.SCITXBUF=((SciTemp) & 0xff );// & 0xff);
//		}


//		if(!((count+10)%480))		{				//changeto 9600Hz 480-20Hz			//%250 20Hz		//5Hz// 5000/100=50 Hz
//			GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//
//			if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//				SciTemp=(int)SRM.wEst_10xrpm;
//				SciaRegs.SCITXBUF=((SRM.wEst_10xrpm)>>8 ) & 0xff;// & 0xff);
//		}
//		if(!((count)%480))		{				//changeto 9600Hz 480-20Hz			//%250 20Hz		//5Hz// 5000/100=50 Hz
//			GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//
//			if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//				//SciTemp=SRM.wEst_10xrpm;
//				SciaRegs.SCITXBUF=((SciTemp) & 0xff );// & 0xff);
//		}

	//	GpioDataRegs.GPEDAT.bit.GPIOE1=0;




/*-------------------------------**
** 	attention                    **
** 	test the cap module,A8-10	 **
**-------------------------------*/
/* Use GPADAT to give a simulate signal to the sensor*/		//simu6pos
		if(count%48==0)	{				//%480 20HzCap = 25rpm  //%600 16Hz CAP = 20rpm;					// 0.5s per circle
			GpioDataRegs.GPADAT.bit.GPIOA8=simu6pos[simu6count] & 1;
			GpioDataRegs.GPADAT.bit.GPIOA9=(simu6pos[simu6count]>>1) & 1;
			GpioDataRegs.GPADAT.bit.GPIOA10=(simu6pos[simu6count]>>2) & 1;

			simu6count=simu6count+1;

			if(simu6count>=6)//ddcap
			{
				simu6count=0;
			}
		}



	PieCtrlRegs.PIEACK.all = 0x0001;

	AdcRegs.ADCST.bit.INT_SEQ1_CLR=1;

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
	int FlagFifo=0;
	//	WORD edge_time2;

	// modified in 2812f5
	edge_time1 = EvbRegs.CAP4FIFO; /* read value */
	//	edge_time2 = EvbRegs.CAP4FIFO; /* read value */

	CapCount++;

	//need to change

	SRM.capture_delta[0][3] = SRM.capture_delta[0][2];
	SRM.capture_delta[0][2] = SRM.capture_delta[0][1];
	SRM.capture_delta[0][1] = SRM.capture_delta[0][0];
	SRM.capture_delta[0][0] = edge_time1 - SRM.capture_edge[0];//edgetime=return fifo_data = EvbRegs.CAP4FIFO
	SRM.capture_edge[0] = edge_time1;


//	if(	SRM.capture_delta[0][0]>30000)
//		FlagFifo |=0x01;
//	else if(SRM.capture_delta[0][0]<2929)
//		FlagFifo |=0x10;
//
//	GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//	if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//		SciaRegs.SCITXBUF=FlagFifo;// & 0xff);

	SRM.last_capture = 1; /* save capture data *///capture=1 2 3//use to update the position//ddcap

/** 	added in 2812f5 **** 	attention	    **/
//	SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//get the state use the sensor signal

	SRM.position_state = SRM.trans_lut[SRM.position_state][1].state;
	if(SRM.position_state==0)	{

		SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//get

		GpioDataRegs.GPEDAT.bit.GPIOE1=0;

		if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
			SciaRegs.SCITXBUF=(0x40 + SRM.position_state);
	}

	SRM.position = SRM.trans_lut[SRM.position_state][1].position;//0 to PI //there is a time delay,not accurate
	SRM.shaft_direction_old=SRM.shaft_direction;
	SRM.shaft_direction = SRM.trans_lut[SRM.position_state][1].direction;//1 -1//attentionmodify

	//Added in f5a,if state is illegal (maybe because missing cap interrupt),
	//use guess position,and old direction
	if(SRM.shaft_direction==0)	{
		SRM.position = SRM.position_initial_guess[SRM.position_state];
		SRM.shaft_direction=SRM.shaft_direction_old;
	}




	/*-----------------------------------------------------------*/
	/* Set flags & select time base for use with velocity update */
	/*-----------------------------------------------------------*/
	delta_count = count - count_old;//attentionmodify
	count_old = count;

	if (delta_count <= 0)
		delta_count = delta_count + T1FREQ;	// ONE_HALF_SECOND;//in the ad "if (count == ONE_HALF_SECOND)"

	SRM.delta_count = delta_count;



	if (  SpeedFlag && (delta_count>80)  ) 	{		//use count to caculate the speed below 150r/min
		//the frequency of count is 5K, so it's 50/5000 second per 7.5degree here  .MYWORK
		//750 mechinal degree/s,about 2 n/s

		/* low shaft speed use *** ISR counter */
		UpdateVelocityFlag = 1;
	}
	else if(SpeedFlag)	{
		/* else, shaft speed ok */
		/* use 1.25MHz clk */
		UpdateVelocityFlag = 2;
	}


//	GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//	if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//		SciaRegs.SCITXBUF=(SRM.position_state);

	EvbRegs.EVBIFRC.bit.CAP4INT = 1;//to clear the 清除捕获中断4的标志位
	PieCtrlRegs.PIEACK.bit.ACK5 = 1; //origin: ACK.all=0x0010

}


void EvbCAP5ISR_INT(void)
{
	//	int capdata1;
	//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	WORD edge_time1;
	//	WORD edge_time2;

	CapCount++;

	// modified in 2812f5
	edge_time1 = EvbRegs.CAP5FIFO; /* read value */
	//	edge_time2 = EvbRegs.CAP5FIFO; /* read value */

	//need to change
	SRM.capture_delta[1][3] = SRM.capture_delta[1][2];
	SRM.capture_delta[1][2] = SRM.capture_delta[1][1];
	SRM.capture_delta[1][1] = SRM.capture_delta[1][0];
	SRM.capture_delta[1][0] = edge_time1 - SRM.capture_edge[1];//edgetime=return fifo_data = EvbRegs.CAP5FIFO
	SRM.capture_edge[1] = edge_time1;


	SRM.last_capture = 2; /* save capture data *///capture=1 2 3//use to update the position//ddcap

	/*------------------**
	** 	added in 2812f5 **
	** 	attention	    **
	**------------------*/
//	SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//attentiondelete ,need to delete
	SRM.position_state = SRM.trans_lut[SRM.position_state][2].state;
	if(SRM.position_state==0)	{

		SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//get

		GpioDataRegs.GPEDAT.bit.GPIOE1=0;

		if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
			SciaRegs.SCITXBUF=(0x50 + SRM.position_state);
	}
	SRM.position = SRM.trans_lut[SRM.position_state][2].position;//0 to PI //there is a time delay,not accurate
	SRM.shaft_direction_old=SRM.shaft_direction;
	SRM.shaft_direction = SRM.trans_lut[SRM.position_state][2].direction;//1 -1//attentionmodify

	if(SRM.shaft_direction==0)	{
		SRM.position = SRM.position_initial_guess[SRM.position_state];
		SRM.shaft_direction=SRM.shaft_direction_old;
	}



	/*-----------------------------------------------------------*/
	/* Set flags & select time base for use with velocity update */
	/*-----------------------------------------------------------*/
	delta_count = count - count_old;
	count_old = count;

	if (delta_count <= 0)
		delta_count = delta_count + T1FREQ;	// ONE_HALF_SECOND;//in the ad "if (count == ONE_HALF_SECOND)"

	SRM.delta_count = delta_count;



	if (  SpeedFlag && (delta_count>80)  ) 	{		//use count to caculate the speed below 150r/min
		//the frequency of count is 5K, so it's 50/5000 second per 7.5degree here  .MYWORK
		//750 mechinal degree/s,about 2 n/s

		/* low shaft speed use *** ISR counter */
		UpdateVelocityFlag = 1;
	}
	else if(SpeedFlag)	{
		/* else, shaft speed ok */
		/* use 1.25MHz clk */
		UpdateVelocityFlag = 2;
	}

//	GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//	if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//		SciaRegs.SCITXBUF=(SRM.position_state);

	EvbRegs.EVBIFRC.bit.CAP5INT = 1;
	PieCtrlRegs.PIEACK.bit.ACK5 = 1; //origin: ACK.all=0x0010
}



void EvbCAP6ISR_INT(void)
{
	//	int capdata1;
	//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	WORD edge_time1;
	//	WORD edge_time2;

	CapCount++;

	// modified in 2812f5
	edge_time1 = EvbRegs.CAP6FIFO; /* read value */
//	edge_time2 = EvbRegs.CAP6FIFO; /* read value */

	//need to change
	SRM.capture_delta[2][3] = SRM.capture_delta[2][2];
	SRM.capture_delta[2][2] = SRM.capture_delta[2][1];
	SRM.capture_delta[2][1] = SRM.capture_delta[2][0];
	SRM.capture_delta[2][0] = edge_time1 - SRM.capture_edge[2];//edgetime=return fifo_data = EvbRegs.CAP6FIFO
	SRM.capture_edge[2] = edge_time1;

	SRM.last_capture = 3; /* save capture data *///capture=1 2 3//use to update the position//ddcap

	/*------------------**
	** 	added in 2812f5 **
	** 	attention	    **
	**------------------*/
//	SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//attentiondelete ,need to delete
	SRM.position_state = SRM.trans_lut[SRM.position_state][3].state;
	if(SRM.position_state==0)	{

		SRM.position_state = (GpioDataRegs.GPFDAT.all>>11) & 0x7;//get

		GpioDataRegs.GPEDAT.bit.GPIOE1=0;

		if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
			SciaRegs.SCITXBUF=(0x60 + SRM.position_state);
	}
	SRM.position = SRM.trans_lut[SRM.position_state][3].position;//0 to PI //there is a time delay,not accurate
	SRM.shaft_direction_old=SRM.shaft_direction;
	SRM.shaft_direction = SRM.trans_lut[SRM.position_state][3].direction;//1 -1//attentionmodify

	if(SRM.shaft_direction==0)	{
		SRM.position = SRM.position_initial_guess[SRM.position_state];
		SRM.shaft_direction=SRM.shaft_direction_old;
	}



	/*-----------------------------------------------------------*/
	/* Set flags & select time base for use with velocity update */
	/*-----------------------------------------------------------*/
	delta_count = count - count_old;
	count_old = count;

	if (delta_count <= 0)
		delta_count = delta_count + T1FREQ;	// ONE_HALF_SECOND;//in the ad "if (count == ONE_HALF_SECOND)"

	SRM.delta_count = delta_count;



	if (  SpeedFlag && (delta_count>80)  ) 	{		//use count to caculate the speed below 150r/min
		//the frequency of count is 5K, so it's 50/5000 second per 7.5degree here  .MYWORK
		//750 mechinal degree/s,about 2 n/s

		/* low shaft speed use *** ISR counter */
		UpdateVelocityFlag = 1;
	}
	else if(SpeedFlag)	{
		/* else, shaft speed ok */
		/* use 1.25MHz clk */
		UpdateVelocityFlag = 2;
	}


//	GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//	if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//		SciaRegs.SCITXBUF=(SRM.position_state);


	EvbRegs.EVBIFRC.bit.CAP6INT = 1;
	PieCtrlRegs.PIEACK.bit.ACK5 = 1; //origin: ACK.all=0x0010
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
	//	anSRM->trans_lut[1][2].position = TWOPIBYTHREE_16;
	//	anSRM->trans_lut[1][3].position = PI_16;
	//	anSRM->trans_lut[2][1].position = PIBYTHREE_16;
	//	anSRM->trans_lut[2][3].position = 0;
	//	anSRM->trans_lut[3][1].position = PIBYTHREE_16;
	//	anSRM->trans_lut[3][2].position = TWOPIBYTHREE_16;
	//	anSRM->trans_lut[4][1].position = FOURPIBYTHREE_16;
	//	anSRM->trans_lut[4][2].position = FIVEPIBYTHREE_16;
	//	anSRM->trans_lut[5][1].position = FOURPIBYTHREE_16;
	//	anSRM->trans_lut[5][3].position = PI_16;
	//	anSRM->trans_lut[6][2].position = FIVEPIBYTHREE_16;
	//	anSRM->trans_lut[6][3].position = 0;

		anSRM->trans_lut[1][2].position = PIBYTHREE_16;
		anSRM->trans_lut[1][3].position = TWOPIBYTHREE_16;
		anSRM->trans_lut[2][1].position = 0;
		anSRM->trans_lut[2][3].position = FIVEPIBYTHREE_16;
		anSRM->trans_lut[3][1].position = 0;
		anSRM->trans_lut[3][2].position = PIBYTHREE_16;
		anSRM->trans_lut[4][1].position = PI_16;
		anSRM->trans_lut[4][2].position = FOURPIBYTHREE_16;
		anSRM->trans_lut[5][1].position = PI_16;
		anSRM->trans_lut[5][3].position = TWOPIBYTHREE_16;
		anSRM->trans_lut[6][2].position = FOURPIBYTHREE_16;
		anSRM->trans_lut[6][3].position = FIVEPIBYTHREE_16;

	/*--------------------------------------------------------------------- */
	/* define initial guesses for each state. The initial position */
	/* is assumed at the midpoint of each state */
	/*--------------------------------------------------------------------- */
	//guessed by the state, MIDPOINT
//	anSRM->position_initial_guess[1] = TWOPIBYTHREE_16 + PIBYSIX_16;
//	anSRM->position_initial_guess[2] = PIBYSIX_16;
//	anSRM->position_initial_guess[3] = PIBYTHREE_16 + PIBYSIX_16;
//	anSRM->position_initial_guess[4] = FOURPIBYTHREE_16 + PIBYSIX_16;
//	anSRM->position_initial_guess[5] = PI_16 + PIBYSIX_16;
//	anSRM->position_initial_guess[6] = FIVEPIBYTHREE_16 + PIBYSIX_16;


	anSRM->position_initial_guess[5] = TWOPIBYTHREE_16 + PIBYSIX_16;
	anSRM->position_initial_guess[3] = PIBYSIX_16;
	anSRM->position_initial_guess[1] = PIBYTHREE_16 + PIBYSIX_16;
	anSRM->position_initial_guess[6] = FOURPIBYTHREE_16 + PIBYSIX_16;
	anSRM->position_initial_guess[4] = PI_16 + PIBYSIX_16;
	anSRM->position_initial_guess[2] = FIVEPIBYTHREE_16 + PIBYSIX_16;

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
		anSRM->capture_delta[i][2] = 65535;
		anSRM->capture_delta[i][3] = 65535;
	}
	anSRM->wEst_10xrpm = 0;
	anSRM->shaft_direction = 0;
	anSRM->shaft_direction_old = 0;
	anSRM->dp_remainder = 0;
	anSRM->integral_speed_error = 0;
	anSRM->wDes_10xrpm = 0;
}





void UpdateVelocity(anSRM_struct *anSRM, int mode)
{
	DWORD a[12];
	long sum_cnt;
	long inst_velocity;
	long filt_velocity;
	int FlagSum=0;
	int i;
	/*----------------------------------------------- */
	/* Obtain instantaneous velocity estimate */
	/*----------------------------------------------- */
	if (mode == 2)
	{
		/* use timer #2 as time base */
		/*------------------------------------------------------------*/
		/* FIR filter for removing once per electrical cycle effects */
		/*------------------------------------------------------------*/

		a[0] = (DWORD)anSRM->capture_delta[0][0];
		a[1] = (DWORD)anSRM->capture_delta[0][1];
		a[2] = (DWORD)anSRM->capture_delta[0][2];
		a[3] = (DWORD)anSRM->capture_delta[0][3];
		a[4] = (DWORD)anSRM->capture_delta[1][0];
		a[5] = (DWORD)anSRM->capture_delta[1][1];
		a[6] = (DWORD)anSRM->capture_delta[1][2];
		a[7] = (DWORD)anSRM->capture_delta[1][3];
		a[8] = (DWORD)anSRM->capture_delta[2][0];
		a[9] = (DWORD)anSRM->capture_delta[2][1];
		a[10] = (DWORD)anSRM->capture_delta[2][2];
		a[11] = (DWORD)anSRM->capture_delta[2][3];
//		for(i=0;i<12;i++)
//			a[i]=12-i;



		QuickSort(&a[0],12);
//		if(a1>30000)
//			FlagSum |=0x01;
//		else if(a1<2929)
//			FlagSum |=0x10;
//
//		if(a2>30000)
//			FlagSum |=0x02;
//		else if(a2<2929)
//			FlagSum |=0x20;
//
//		if(a3>30000)
//			FlagSum |=0x04;
//		else if(a3<2929)
//			FlagSum |=0x40;
//
//		if(a4>30000)
//			FlagSum |=0x08;
//		else if(a4<2929)
//			FlagSum |=0x80;

//		if(a1>30000)
//			FlagSum |=0x01;
//		else if(a1<2929)
//			FlagSum |=0x10;
//
//		if(a1>30000)
//			FlagSum |=0x01;
//		else if(a1<2929)
//			FlagSum |=0x10;



//		GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//		if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//			SciaRegs.SCITXBUF=FlagSum;// & 0xff);

		sum_cnt = a[3] + a[4] + a[5] + a[6] + a[7] + a[8];
		/*---------------------------------------------------*/
		/* apply velocity = delta_theta/delta_time algorithm */
		/*---------------------------------------------------*/
		sum_cnt = K1_VELOCITY_EST / sum_cnt;
		inst_velocity = (sum_cnt) * anSRM->shaft_direction;//10*rpm
	}
	else
	{ /* else, use timer ISR count as time base */
		/*---------------------------------------------------*/
		/* apply velocity = delta_theta/delta_time algorithm */
		/*---------------------------------------------------*/
		sum_cnt = K2_VELOCITY_EST / anSRM->delta_count;
		inst_velocity = (sum_cnt) * anSRM->shaft_direction;

	}
	/*----------------------------------------------- */
	/* IIR filter for smoothing velocity estimate */
	/*----------------------------------------------- */

	if(inst_velocity<12000 && inst_velocity>-12000)	{

		filt_velocity = (ALPHA * anSRM->wEst_10xrpm)+ (ONE_MINUS_ALPHA * inst_velocity);

		anSRM->wEst_10xrpm = filt_velocity >> 3;
	}

//	GpioDataRegs.GPEDAT.bit.GPIOE1=0;
//
//	if((SciaTx_Ready() == 1) )//&& (SendFlag == 1))
//		SciaRegs.SCITXBUF=(anSRM->shaft_direction);

// set to 0
//	anSRM->wEst_10xrpm=0;
} /* end, velocity estimation */








void Time_Update_Position(anSRM_struct *anSRM)
{
	long dp; // change to electrical angle  /* delta-position in mechanical angle */
	int speed;
	int temp;
	if (anSRM->wEst_10xrpm >0)
	{
		dp = anSRM->wEst_10xrpm * K_POSITION_EST + anSRM->dp_remainder;	//use reminder to protect the low bits ,very clever
		anSRM->dp_remainder = dp & 0xffff;/* delta-position in mechanical angle */
//		temp = (int)(dp >> 16);//to convert to Electrial Angle
//		anSRM->position = anSRM->position + (temp * NR);
		temp = (int)(dp >> 16);
		anSRM->position = anSRM->position + temp;

		if(anSRM->position_state==3)	{
			if(anSRM->position>PIBYTHREE_16)
				anSRM->position=PIBYTHREE_16-6;
		}
		else if(anSRM->position_state==1)	{
			if(anSRM->position>TWOPIBYTHREE_16)
				anSRM->position=TWOPIBYTHREE_16-6;
		}
		else if(anSRM->position_state==5)	{
			if(anSRM->position>PI_16)
				anSRM->position=PI_16-6;
		}
		else if(anSRM->position_state==4)	{
			if(anSRM->position>FOURPIBYTHREE_16)
				anSRM->position=FOURPIBYTHREE_16-6;
		}
		else if(anSRM->position_state==6)	{
			if(anSRM->position>FIVEPIBYTHREE_16)
				anSRM->position=FIVEPIBYTHREE_16-6;
		}
		else if(anSRM->position_state==2)	{
			if(anSRM->position<FIVEPIBYTHREE_16)
				anSRM->position=0xffff-6;
		}


	}
	else
	{
		speed = -anSRM->wEst_10xrpm;
		dp = speed * K_POSITION_EST + anSRM->dp_remainder;
		anSRM->dp_remainder = dp & 0xffff;
//		temp = (int)(dp >> 16);
//		anSRM->position = anSRM->position - (temp * NR);
		temp = (int)(dp >> 13);
		anSRM->position = anSRM->position - temp;
	}
} /* end Time_Update_Position */




void PhaseControl(anSRM_struct *anSRM)	//int the ADC interrupt
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

		if ((anSRM->wEst_10xrpm<3000) && (angle >= (PIBYSIX_16/8)) && (angle < FIVEPIBYSIX_16))
		{
			anSRM->active[phase] = 1;
			temp = 0x1 << phase;
			anSRM->iDes[phase] = DESCURRENT;//Important!!
		}
		else if ((angle >= (3640)) && (angle < FIVEPIBYSIX_16-3641))
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
		switch_lowside(whats_active);


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


			if(anSRM->iFB[phase] > (iDes ))		//184-800mA,92-400mA	//chopcurrent
			{
				anSRM->dutyRatio[phase]=0;//compare to output LOW
			}
			else if(anSRM->iFB[phase] < (iDes))	//172-750mA,86-375mA
			{
				anSRM->dutyRatio[phase]=0xffff;//compare to output HIGH
			}
		}
		/*----------------------------------------------*/
		/* else, phase is not active */
		/*----------------------------------------------*/
		else
		{
			anSRM->iDes[phase] = 0;
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

//void　QuickSort(DWORD　&a,int　numsize)/*a是整形数组，numsize是元素个数*/
//{
//　	 int　i=0;
//　	 int j=numsize-1;
//　	 DWORD　val=a[0];/*指定参考值val大小*/
//　	 if(numsize>1)/*确保数组长度至少为2，否则无需排序*/　	 {
//
//　		 while(i<j)/*循环结束条件*/		 {
//　		 /*从后向前搜索比val小的元素，找到后填到a[i]中并跳出循环*/
//　			 for(;j>i;j--)
//　				 if(a[j]<val)	 {
//　					 a[i++]=a[j];
//　					 break;
//　				 }
//　				 /*从前往后搜索比val大的元素，找到后填到a[j]中并跳出循环*/
//　			 for(;i<j;i++)
//　				 if(a[i]>val)	 {
//　					 a[j--]=a[i];
//　					 break;
//　				 }
//　		 }
//　		 a[i]=val;/*将保存在val中的数放到a[i]中*/
//　		 QuickSort(a,i);/*递归，对前i个数排序*/
//　		 QuickSort(a+i+1,numsize-i-1);/*对i+2到numsize这numsize-1-i个数排序*/
//　	 }
//}


void QuickSort(unsigned long *a, int numsize)	//QuickSort(int a, int　numsize)/*a是整形数组，numsize是元素个数*/
{
	int i=0;
	int j=numsize-1;
	DWORD val=a[0];
	if(numsize>1)	{
		while(i<j)	{
			for(; j>i;j--)
				if(a[j]<val)	{
					a[i++]=a[j];
					break;
				}
			for(;i<j;i++)
				if(a[i]>val)	{
					a[j--]=a[i];
					break;
				}
		}
		a[i]=val;
		QuickSort(&a[0],i);
		QuickSort(&a[i+1],numsize-i-1);

	}
}

//　	 int　i=0;
//　	 int j=numsize-1;
//　	 DWORD　val=a[0];/*指定参考值val大小*/
//　	 if(numsize>1)/*确保数组长度至少为2，否则无需排序*/　	 {
//
//　		 while(i<j)/*循环结束条件*/		 {
//　		 /*从后向前搜索比val小的元素，找到后填到a[i]中并跳出循环*/
//　			 for(;j>i;j--)
//　				 if(a[j]<val)	 {
//　					 a[i++]=a[j];
//　					 break;
//　				 }
//　				 /*从前往后搜索比val大的元素，找到后填到a[j]中并跳出循环*/
//　			 for(;i<j;i++)
//　				 if(a[i]>val)	 {
//　					 a[j--]=a[i];
//　					 break;
//　				 }
//　		 }
//　		 a[i]=val;/*将保存在val中的数放到a[i]中*/
//　		 QuickSort(a,i);/*递归，对前i个数排序*/
//　		 QuickSort(a+i+1,numsize-i-1);/*对i+2到numsize这numsize-1-i个数排序*/
//　	 }

