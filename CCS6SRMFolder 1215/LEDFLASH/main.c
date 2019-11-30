/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : GPIO        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/27                                    */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 发光二极管从右至左循环发光				      */                       
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
void Init_LED(void);

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:主函数			                */
/*------------------------------------------*/ 
void main(void)
{
	unsigned int i,j,temp;
	InitSysCtrl();  // 系统初始化子程序，在DSP28_sysctrl.c中
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);//将初始化Flash代码复制到RAM
	InitFlash();//初始化Flash
	Init_LED();
	temp=0x0001;
	while(1)
	{	
		GpioDataRegs.GPBCLEAR.all |=temp;
		for(i=0;i<10;i++)
			for(j=0;j<60000;j++);
		GpioDataRegs.GPBSET.all |=temp;
		temp<<=1;
		if(temp==0x0100)
			temp=0x0001;
	}	   
} 

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:初始化LED端口为输出              */
/*------------------------------------------*/ 
void Init_LED(void)
{
	EALLOW;
	GpioMuxRegs.GPBDIR.all |=0x00FF;
	EDIS;
} 



 
