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
	GpioMuxRegs.GPADIR.bit.GPIOA0=1;//设置D1对应的DSP引脚为输出
	GpioMuxRegs.GPBDIR.bit.GPIOB1=1;
	EDIS;
	GpioDataRegs.GPADAT.bit.GPIOA0=0;//D1对应输出低电平，发光二极管点亮
	GpioDataRegs.GPBDAT.bit.GPIOB1=0;//D2对应输出低电平，发光二极管点亮


	GpioDataRegs.GPADAT.bit.GPIOA0=1;//D1对应输出高电平，发光二极管不亮
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;//写一清零GPIOB0
	GpioDataRegs.GPASET.bit.GPIOA0=1;//写一置位GPIOB0
	GpioDataRegs.GPATOGGLE.bit.GPIOA0=1;//写一取反GPIOB0输出
	GpioDataRegs.GPATOGGLE.bit.GPIOA0=1;//写一取反GPIOB0输出
	while(1); 
} 




 
