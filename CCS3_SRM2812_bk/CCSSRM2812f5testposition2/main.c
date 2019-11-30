/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : GPIO        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/27                                    */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 点亮一个发光二极管     					      */                       
/*  Description   : 								              */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/

/*****************头文件********************/  
#include "DSP281x_Device.h"
#include "System.h"

/****************端口宏定义*****************/

/****************常量宏定义*****************/ 

/***************全局变量定义****************/

/****************函数声明*******************/ 

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:主函数			                */
/*------------------------------------------*/ 

	int i;
	unsigned int iperiod1;
	unsigned int iperiod3;


interrupt void EvbCAP4ISR_INT(void);
interrupt void EvbCAP5ISR_INT(void);
interrupt void EvbCAP6ISR_INT(void);

void main(void)
{

	InitSysCtrl();  // 系统初始化子程序，在DSP28_sysctrl.c中
/* 	EALLOW;                                                             */
/* 	GpioMuxRegs.GPBDIR.bit.GPIOB0=1;//设置D1对应的DSP引脚为输出         */
/* 	GpioMuxRegs.GPBDIR.bit.GPIOB1=1;                                    */
/* 	EDIS;                                                               */
/* 	GpioDataRegs.GPBDAT.bit.GPIOB0=0;//D1对应输出低电平，发光二极管点亮 */
/* 	GpioDataRegs.GPBDAT.bit.GPIOB1=0;//D2对应输出低电平，发光二极管点亮 */
/*                                                                      */
/*                                                                      */
/* 	GpioDataRegs.GPBDAT.bit.GPIOB0=1;//D1对应输出高电平，发光二极管不亮 */
/* 	GpioDataRegs.GPBCLEAR.bit.GPIOB0=1;//写一清零GPIOB0                 */
/* 	GpioDataRegs.GPBSET.bit.GPIOB0=1;//写一置位GPIOB0                   */
/* 	GpioDataRegs.GPBTOGGLE.bit.GPIOB0=1;//写一取反GPIOB0输出            */
/* 	GpioDataRegs.GPBTOGGLE.bit.GPIOB0=1;//写一取反GPIOB0输出            */

	EALLOW;	

	PieVectTable.CAPINT4=&EvbCAP4ISR_INT;
	PieVectTable.CAPINT5=&EvbCAP5ISR_INT;
	PieVectTable.CAPINT6=&EvbCAP6ISR_INT;
	EDIS;
	
	
	EvbRegs.EVBIMRC.bit.CAP4INT = 0;    //because the cpu willnot reset
 	EvbRegs.EVBIMRC.bit.CAP5INT = 0;    
 	EvbRegs.EVBIMRC.bit.CAP6INT = 0;    

		EALLOW;
	GpioMuxRegs.GPAMUX.bit.CAP1Q1_GPIOA8=0;// IO simulate the CAP input
	GpioMuxRegs.GPAMUX.bit.CAP2Q2_GPIOA9=0;
	GpioMuxRegs.GPAMUX.bit.CAP3QI1_GPIOA10=0 ;

	GpioMuxRegs.GPAMUX.bit.TCLKINA_GPIOA12=0;//LED output

	GpioMuxRegs.GPADIR.bit.GPIOA10=1;//Test 设置D1对应的DSP引脚为输出
	GpioMuxRegs.GPADIR.bit.GPIOA9=1;//Test
	GpioMuxRegs.GPADIR.bit.GPIOA8=1;//Test,to be deleted
	GpioMuxRegs.GPADIR.bit.GPIOA12=1;//as LED output
	

	GpioMuxRegs.GPEMUX.bit.XNMI_XINT13_GPIOE2=0;
	GpioMuxRegs.GPEDIR.bit.GPIOE2=0;

	GpioDataRegs.GPADAT.bit.GPIOA10=0;//D1对应输出电平
	GpioDataRegs.GPADAT.bit.GPIOA9=1;//D1对应输出电平
	GpioDataRegs.GPADAT.bit.GPIOA8=0;
	GpioDataRegs.GPADAT.bit.GPIOA12=0;

	GpioMuxRegs.GPBMUX.bit.PWM7_GPIOB0 = 0;// PWM///to io 0
	GpioMuxRegs.GPBMUX.bit.PWM8_GPIOB1 = 0;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM9_GPIOB2 = 0;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM10_GPIOB3 = 0;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM11_GPIOB4 = 0;// PWM
	GpioMuxRegs.GPBMUX.bit.PWM12_GPIOB5 = 0;// PWM

	GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0=0;

	GpioMuxRegs.GPBMUX.bit.CAP4Q1_GPIOB8=1;
	GpioMuxRegs.GPBMUX.bit.CAP5Q2_GPIOB9=1;
	GpioMuxRegs.GPBMUX.bit.CAP6QI2_GPIOB10=1;

/*-------------------**
** 	//test the T3CMP ,**
attention!
**-------------------*/
	GpioMuxRegs.GPBMUX.bit.T3PWM_GPIOB6=1;
	GpioMuxRegs.GPBMUX.bit.T4PWM_GPIOB7=1;


/*----------------**
** 	oppo input    **
** 	initializeSRM **
** 	attention	  **
**----------------*/
			 
	GpioMuxRegs.GPFMUX.bit.SPISIMOA_GPIOF0=0;
	GpioMuxRegs.GPFMUX.bit.SPISOMIA_GPIOF1=0;
	GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2=0;
	GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3=0;

	GpioMuxRegs.GPFDIR.bit.GPIOF0=1;
	GpioMuxRegs.GPFDIR.bit.GPIOF1=1;
	GpioMuxRegs.GPFDIR.bit.GPIOF2=1;
	GpioMuxRegs.GPFDIR.bit.GPIOF3=1;

	GpioMuxRegs.GPDMUX.bit.T1CTRIP_PDPA_GPIOD0=0;
	GpioMuxRegs.GPDDIR.bit.GPIOD0=1;

	GpioMuxRegs.GPFMUX.bit.CANTXA_GPIOF6=0;
	GpioMuxRegs.GPFDIR.bit.GPIOF6=1;


	EDIS;







			
	iperiod1 = (30000000 / 5000) - 1;//5kHz



/*------**
** Test attentio**
**------*/	
/* 	EvaRegs.GPTCONA.all = 0x0859;	 */

	EvaRegs.T1PR = iperiod1;
	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	EvaRegs.T1CON.all = 0x1000;//TPS=0,enable=0,to be enabled;

	EvaRegs.GPTCONA.bit.T1TOADC = 2;//period to ADC


/*------**
** Test attentio**
test the EVA pwm
**------*/	
/* //	EvaRegs.GPTCONA.all = 0x0859; */
/* 	EvaRegs.T1CON.bit.TECMPR=1;       */
/* 	EvaRegs.T1CMPR=3000;              */






////EVB ------------------------------------------------
	iperiod3 = (30000000 / 20000) - 1;
	EvbRegs.T3PR = iperiod3;
	EvbRegs.T3CNT = 0;



	EvbRegs.T3CON.bit.TMODE = 2;//TPS=0,enable=0;
	EvbRegs.T3CON.bit.TPS=0;
	EvbRegs.T3CON.bit.TENABLE=0;//unenable the t3 count
	EvbRegs.T3CON.bit.TCLKS10=0;//divide 0
	EvbRegs.T3CON.bit.TECMPR=1;//enable the compare of PWM6-12


/*----------------------**
** 	attention,
T3PIN
t3cmpr    **
**----------------------*/	
	EvbRegs.GPTCONB.bit.TCMPOE=0;//test if 0,the CMPR will work or not
									//the test reasult is, when set 0, the T3 and T4 will not work
									//but the 6 PWM of CMPR will still work
	EvbRegs.GPTCONB.bit.T3PIN=1;
//	EvbRegs.GPTCONB.all = 0x0859;				
	EvbRegs.T3CMPR = 1300;


	EvbRegs.T4PR = 0xffff;
	EvbRegs.T4CNT = 0;

	EvbRegs.T4CON.all = 0x1400;//Tps=5,enable=0;GuweiGang P245


					 

	EvbRegs.CMPR4 = 0;//设置比较寄存器,compare to T3
	EvbRegs.CMPR5 = 0;
	EvbRegs.CMPR6 = 0;

// test
//	EvbRegs.EXTCONB.bit.INDCOE=1;//what for?

	EvbRegs.COMCONB.bit.CENABLE = 1;  //设置比较单元??//enable;cld=2;
	EvbRegs.COMCONB.bit.FCOMPOE=1;//compare enable
	EvbRegs.COMCONB.bit.CLD=2;//instant
	EvbRegs.COMCONB.bit.ACTRLD=2;


	EvbRegs.ACTRB.all = 0x0;    //设置输出特性??//High effective// intial is low

//CAP  -----------------------------------------------------------------------
	EvbRegs.CAPCONB.all = 0x30fc;//??//enable; capture the two sides

	EvbRegs.CAPFIFOB.all = 0;



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
	
//	PieCtrl.PIEIFR5.bit.INTx5=0;//CAP4 IFR
//	PieCtrl.PIEIFR5.bit.INTx6=0;
//	PieCtrl.PIEIFR5.bit.INTx7=0;


	

	PieCtrlRegs.PIEIER5.bit.INTx5 = 1;//CAP4 IER
	PieCtrlRegs.PIEIER5.bit.INTx6 = 1;//CAP5
	PieCtrlRegs.PIEIER5.bit.INTx7 = 1;//CAP6

/*---------------------------------**
after the above lines, the ACK5=1; IFR=0x10;
** 	attention                      **
** 	unknown why                    **
** 	always trigger the CAP5 ISR	   **
**---------------------------------*/
/* 	PieCtrl.PIEACK.all = 0x0010; */
/* 	PieCtrl.PIEACK.all = 0x0010; */
/* 	PieCtrl.PIEACK.all = 0x0010; */
/* 	IFR= 0;	                     */

	IER |= M_INT5;  // 使能 CPU INT 5	//EV CAP
	

//ADC------------------------------------------   
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;//ADCINT enable
	IER |= M_INT1;			// Enable INT14 which is connected to CPU-Timer 2:

	EINT;					// Enable INTM
	ERTM;					// Enable DBGM
	EvaRegs.T1CON.bit.TENABLE=1;
	EvbRegs.T3CON.bit.TENABLE=1;
	EvbRegs.T4CON.bit.TENABLE=1;




	


	EALLOW;
	GpioMuxRegs.GPADIR.bit.GPIOA0=1;//设置D1对应的DSP引脚为输出
	
	GpioMuxRegs.GPBDIR.bit.GPIOB0=1;
	GpioMuxRegs.GPBDIR.bit.GPIOB1=1;
	GpioMuxRegs.GPBDIR.bit.GPIOB2=1;
	GpioMuxRegs.GPBDIR.bit.GPIOB3=1;
	GpioMuxRegs.GPBDIR.bit.GPIOB4=1;
	GpioMuxRegs.GPBDIR.bit.GPIOB5=1;
	EDIS;


	GpioDataRegs.GPADAT.bit.GPIOA0=0;//D1对应输出低电平，发光二极管点亮
	GpioDataRegs.GPBDAT.bit.GPIOB0=1;//D2对应输出低电平，发光二极管点亮
	GpioDataRegs.GPBDAT.bit.GPIOB1=01;
	GpioDataRegs.GPBDAT.bit.GPIOB2=01;
	GpioDataRegs.GPBDAT.bit.GPIOB3=01;
	GpioDataRegs.GPBDAT.bit.GPIOB4=01;
	GpioDataRegs.GPBDAT.bit.GPIOB5=01;

	GpioDataRegs.GPBDAT.bit.GPIOB0=0;//D2对应输出低电平，发光二极管点亮
	GpioDataRegs.GPBDAT.bit.GPIOB1=0;
	GpioDataRegs.GPBDAT.bit.GPIOB2=0;
	GpioDataRegs.GPBDAT.bit.GPIOB3=0;
	GpioDataRegs.GPBDAT.bit.GPIOB4=0;
	GpioDataRegs.GPBDAT.bit.GPIOB5=0;

	GpioDataRegs.GPBDAT.bit.GPIOB0=1;//D2对应输出低电平，发光二极管点亮
	GpioDataRegs.GPBDAT.bit.GPIOB1=01;
	GpioDataRegs.GPBDAT.bit.GPIOB2=01;
	GpioDataRegs.GPBDAT.bit.GPIOB3=01;
	GpioDataRegs.GPBDAT.bit.GPIOB4=01;
	GpioDataRegs.GPBDAT.bit.GPIOB5=01;


	GpioDataRegs.GPADAT.bit.GPIOA0=1;//D1对应输出高电平，发光二极管不亮
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;//写一清零GPIOB0
	GpioDataRegs.GPASET.bit.GPIOA0=1;//写一置位GPIOB0
	GpioDataRegs.GPATOGGLE.bit.GPIOA0=1;//写一取反GPIOB0输出
	GpioDataRegs.GPATOGGLE.bit.GPIOA0=1;//写一取反GPIOB0输出

		GpioDataRegs.GPFDAT.bit.GPIOF0=0;
	GpioDataRegs.GPFDAT.bit.GPIOF1=0;

	GpioDataRegs.GPFDAT.bit.GPIOF2=0;

	GpioDataRegs.GPFDAT.bit.GPIOF3=0;


	GpioDataRegs.GPFDAT.bit.GPIOF0=1;
	GpioDataRegs.GPFDAT.bit.GPIOF1=01;
	GpioDataRegs.GPFDAT.bit.GPIOF2=01;
	GpioDataRegs.GPFDAT.bit.GPIOF3=01;

	GpioDataRegs.GPDDAT.bit.GPIOD0=0;
	GpioDataRegs.GPDDAT.bit.GPIOD0=1;
	GpioDataRegs.GPDDAT.bit.GPIOD0=0;
	GpioDataRegs.GPFDAT.bit.GPIOF6=0;
	GpioDataRegs.GPFDAT.bit.GPIOF6=1;
	GpioDataRegs.GPFDAT.bit.GPIOF6=0;
	GpioDataRegs.GPFDAT.bit.GPIOF6=1;
	
	while(1)
	{
		if(GpioDataRegs.GPFDAT.bit.GPIOF6==1)
		{
			GpioDataRegs.GPDDAT.bit.GPIOD0=0;
		}
		else
		{
			GpioDataRegs.GPDDAT.bit.GPIOD0=1;
		}
	} 
} 





void EvbCAP4ISR_INT(void)
{

//	int capdata1;
//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	unsigned int edge_time1;
//	WORD edge_time2;


	//*IFR_REG = 0x0008; /* clear CPU interrupt flag */

	//groupc_flags = *IFRC; /* read event manger interrupt */  //读取是哪个中断
	/* flag register */



//attentionmodify
//	do 
//	{
		//fifo_data = *FIFO1; /* read value */
//		edge_time = EvbRegs.CAP6FIFO; /* read value */

		//fifo_status = *CAPFIFO & 0x0300; /* read status register, mask bits */
		//fifo_status = EvbRegs.CAPFIFOB.bit.CAP4FIFO; /* read status register, mask bits */

//	} while (EvbRegs.CAPFIFOB.bit.CAP6FIFO != 0);

// modified in 2812f5
	edge_time1 = EvbRegs.CAP4FIFO; /* read value */
//	edge_time2 = EvbRegs.CAP4FIFO; /* read value */


	//need to change

	 
	EvbRegs.EVBIFRC.bit.CAP4INT = 1;//to clear the 

	PieCtrlRegs.PIEACK.all = 0x0010;
//need to add some commands to cleare IFRs
}


void EvbCAP5ISR_INT(void)
{
	//	int capdata1;
	//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	unsigned int edge_time1;
//	WORD edge_time2;


	//*IFR_REG = 0x0008; /* clear CPU interrupt flag */

	//groupc_flags = *IFRC; /* read event manger interrupt */  //读取是哪个中断
	/* flag register */

//attentionmodify
//	do 
//	{
		//fifo_data = *FIFO1; /* read value */
//		edge_time = EvbRegs.CAP6FIFO; /* read value */

		//fifo_status = *CAPFIFO & 0x0300; /* read status register, mask bits */
		//fifo_status = EvbRegs.CAPFIFOB.bit.CAP4FIFO; /* read status register, mask bits */

//	} while (EvbRegs.CAPFIFOB.bit.CAP6FIFO != 0);

// modified in 2812f5
	edge_time1 = EvbRegs.CAP5FIFO; /* read value */
//	edge_time2 = EvbRegs.CAP5FIFO; /* read value */




	EvbRegs.EVBIFRC.bit.CAP5INT = 1;


	PieCtrlRegs.PIEACK.all = 0x0010;
//need to add some commands to cleare IFRs
}



void EvbCAP6ISR_INT(void)
{
	//	int capdata1;
	//	capdata1 = EvbRegs.CAP4FIFO;

	int delta_count;
	unsigned int edge_time1;
//	WORD edge_time2;


	//*IFR_REG = 0x0008; /* clear CPU interrupt flag */

	//groupc_flags = *IFRC; /* read event manger interrupt */  //读取是哪个中断
	/* flag register */


//attentionmodify
//	do 
//	{
		//fifo_data = *FIFO1; /* read value */
//		edge_time = EvbRegs.CAP6FIFO; /* read value */

		//fifo_status = *CAPFIFO & 0x0300; /* read status register, mask bits */
		//fifo_status = EvbRegs.CAPFIFOB.bit.CAP4FIFO; /* read status register, mask bits */

//	} while (EvbRegs.CAPFIFOB.bit.CAP6FIFO != 0);

// modified in 2812f5
	edge_time1 = EvbRegs.CAP6FIFO; /* read value */
//	edge_time2 = EvbRegs.CAP6FIFO; /* read value */


	 

	EvbRegs.EVBIFRC.bit.CAP6INT = 1;

	PieCtrlRegs.PIEACK.all = 0x0010;
//need to add some commands to cleare IFRs
}





