/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : GPIO        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2009/12/27                                    */      
/*  Version   	  : 2.0                                           */          
/*  Function      : ��������ܴ�������ѭ������				      */                       
/*  Description   : 								              */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/

/*****************ͷ�ļ�********************/  
#include "DSP281x_Device.h"
#include "System.h"

/****************�˿ں궨��*****************/

/****************�����궨��*****************/ 

/***************ȫ�ֱ�������****************/

/****************��������*******************/ 
void Init_LED(void);

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:������			                */
/*------------------------------------------*/ 
void main(void)
{
	unsigned int i,j,temp;
	InitSysCtrl();  // ϵͳ��ʼ���ӳ�����DSP28_sysctrl.c��
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);//����ʼ��Flash���븴�Ƶ�RAM
	InitFlash();//��ʼ��Flash
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
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:��ʼ��LED�˿�Ϊ���              */
/*------------------------------------------*/ 
void Init_LED(void)
{
	EALLOW;
	GpioMuxRegs.GPBDIR.all |=0x00FF;
	EDIS;
} 



 
