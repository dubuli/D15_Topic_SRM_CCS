/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : GPIO        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2009/12/27                                    */      
/*  Version   	  : 2.0                                           */          
/*  Function      : ����һ�����������     					      */                       
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

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:������			                */
/*------------------------------------------*/ 
void main(void)
{
	InitSysCtrl();  // ϵͳ��ʼ���ӳ�����DSP28_sysctrl.c��
/* 	EALLOW;                                                             */
/* 	GpioMuxRegs.GPBDIR.bit.GPIOB0=1;//����D1��Ӧ��DSP����Ϊ���         */
/* 	GpioMuxRegs.GPBDIR.bit.GPIOB1=1;                                    */
/* 	EDIS;                                                               */
/* 	GpioDataRegs.GPBDAT.bit.GPIOB0=0;//D1��Ӧ����͵�ƽ����������ܵ��� */
/* 	GpioDataRegs.GPBDAT.bit.GPIOB1=0;//D2��Ӧ����͵�ƽ����������ܵ��� */
/*                                                                      */
/*                                                                      */
/* 	GpioDataRegs.GPBDAT.bit.GPIOB0=1;//D1��Ӧ����ߵ�ƽ����������ܲ��� */
/* 	GpioDataRegs.GPBCLEAR.bit.GPIOB0=1;//дһ����GPIOB0                 */
/* 	GpioDataRegs.GPBSET.bit.GPIOB0=1;//дһ��λGPIOB0                   */
/* 	GpioDataRegs.GPBTOGGLE.bit.GPIOB0=1;//дһȡ��GPIOB0���            */
/* 	GpioDataRegs.GPBTOGGLE.bit.GPIOB0=1;//дһȡ��GPIOB0���            */


	EALLOW;
	GpioMuxRegs.GPADIR.bit.GPIOA0=1;//����D1��Ӧ��DSP����Ϊ���
	GpioMuxRegs.GPBDIR.bit.GPIOB1=1;
	EDIS;
	GpioDataRegs.GPADAT.bit.GPIOA0=0;//D1��Ӧ����͵�ƽ����������ܵ���
	GpioDataRegs.GPBDAT.bit.GPIOB1=0;//D2��Ӧ����͵�ƽ����������ܵ���


	GpioDataRegs.GPADAT.bit.GPIOA0=1;//D1��Ӧ����ߵ�ƽ����������ܲ���
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;//дһ����GPIOB0
	GpioDataRegs.GPASET.bit.GPIOA0=1;//дһ��λGPIOB0
	GpioDataRegs.GPATOGGLE.bit.GPIOA0=1;//дһȡ��GPIOB0���
	GpioDataRegs.GPATOGGLE.bit.GPIOA0=1;//дһȡ��GPIOB0���
	while(1); 
} 




 
