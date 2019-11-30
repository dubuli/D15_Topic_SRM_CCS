/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : EVA	        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2010/3/21                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 			         					      */                       
/*  Description   : 								              */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/

/*****************ͷ�ļ�********************/  
#include "DSP281x_Device.h"
#include "System.h"

/****************�˿ں궨��*****************/

/****************�����궨��*****************/ 
#define Period  0xffff  //PWM����
#define Pulse   1000  //������

/***************ȫ�ֱ�������****************/

/****************��������*******************/ 
void Init_EVA(void);
 
/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:������			                */
/*------------------------------------------*/ 
void main(void)
{
	InitSysCtrl();  // ϵͳ��ʼ���ӳ�����DSP28_sysctrl.c��
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
   	EvaRegs.T1CON.all = 0x1042; //����������ģʽ��ʹ�ܶ�ʱ�����Ƚ�ʹ��
   	EvaRegs.T1CON.bit.TPS=6;    //���ø���ʱ��64��Ƶ   
 
  	EvaRegs.T2PR = 2*Period;      // Timer2 period
  	EvaRegs.T2CMPR = Pulse;     // Timer2 compare
  	EvaRegs.T2CNT = 0x0000;     // Timer2 counter
	EvaRegs.T2CON.all = 0x1042; //����������ģʽ��ʹ�ܶ�ʱ�����Ƚ�ʹ��
	EvaRegs.T2CON.bit.TPS=6;    //���ø���ʱ��64��Ƶ 

	EvaRegs.GPTCONA.bit.TCMPOE = 1;//��������T1PWM_T1CMP��T2PWM_T2CMP�ɶ�ʱ��1��2��������
	EvaRegs.GPTCONA.bit.T1PIN = 2; //���õ���Ч
	EvaRegs.GPTCONA.bit.T2PIN = 1; //���ø���Ч

	EvaRegs.CMPR1 = 0x7fff;//���ñȽϼĴ���
	EvaRegs.CMPR2 = 0x0fff;
	EvaRegs.CMPR3 = 0x00ff;
	    
	EvaRegs.ACTRA.all = 0x0999;    //�����������
	EvaRegs.DBTCONA.bit.EDBT1 = 1; //ʹ��PWM1/2������·
	EvaRegs.DBTCONA.bit.EDBT2 = 1; //ʹ��PWM3/4������·
	EvaRegs.DBTCONA.bit.EDBT3 = 1; //ʹ��PWM5/6������·
	EvaRegs.DBTCONA.bit.DBTPS = 3; //����������·ʱ��Ԥ��Ƶ
	EvaRegs.DBTCONA.bit.DBT = 10;  //����������·����
	EvaRegs.COMCONA.all = 0xA600;  //���ñȽϵ�Ԫ
}



 
