/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : EVA	        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2010/3/21                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 			         					      */                       
/*  Description   : 								              */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/

/*****************头文件********************/  
#include "DSP281x_Device.h"
#include "System.h"

/****************端口宏定义*****************/

/****************常量宏定义*****************/ 
#define Period  0xffff  //PWM周期
#define Pulse   1000  //脉冲宽度

/***************全局变量定义****************/

/****************函数声明*******************/ 
void Init_EVA(void);
 
/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:主函数			                */
/*------------------------------------------*/ 
void main(void)
{
	InitSysCtrl();  // 系统初始化子程序，在DSP28_sysctrl.c中
	Init_EVA();
	while(1);   
} 

void Init_EVA(void)
{
	EALLOW;
   	GpioMuxRegs.GPAMUX.all = 0x00FF; // EVA PWM 1-6
   	EDIS;
   	 
   	EvaRegs.T1PR = Period;      // Timer1 period
   	EvaRegs.T1CMPR = Pulse;     // Timer1 compare
   	EvaRegs.T1CNT = 0x0000;     // Timer1 counter
   	EvaRegs.T1CON.all = 0x1042; //连续增计数模式，使能定时器，比较使能
   	EvaRegs.T1CON.bit.TPS=6;    //设置高速时钟64分频   
 
  	EvaRegs.T2PR = 2*Period;      // Timer2 period
  	EvaRegs.T2CMPR = Pulse;     // Timer2 compare
  	EvaRegs.T2CNT = 0x0000;     // Timer2 counter
	EvaRegs.T2CON.all = 0x1042; //连续增计数模式，使能定时器，比较使能
	EvaRegs.T2CON.bit.TPS=6;    //设置高速时钟64分频 

	EvaRegs.GPTCONA.bit.TCMPOE = 1;//设置引脚T1PWM_T1CMP、T2PWM_T2CMP由定时器1和2独立驱动
	EvaRegs.GPTCONA.bit.T1PIN = 2; //设置低有效
	EvaRegs.GPTCONA.bit.T2PIN = 1; //设置高有效

	EvaRegs.CMPR1 = 0x7fff;//设置比较寄存器
	EvaRegs.CMPR2 = 0x0fff;
	EvaRegs.CMPR3 = 0x00ff;
	    
	EvaRegs.ACTRA.all = 0x0999;    //设置输出特性
	EvaRegs.DBTCONA.bit.EDBT1 = 1; //使能PWM1/2死区电路
	EvaRegs.DBTCONA.bit.EDBT2 = 1; //使能PWM3/4死区电路
	EvaRegs.DBTCONA.bit.EDBT3 = 1; //使能PWM5/6死区电路
	EvaRegs.DBTCONA.bit.DBTPS = 3; //设置死区电路时间预分频
	EvaRegs.DBTCONA.bit.DBT = 10;  //设置死区电路周期
	EvaRegs.COMCONA.all = 0xA600;  //设置比较单元
}



 
