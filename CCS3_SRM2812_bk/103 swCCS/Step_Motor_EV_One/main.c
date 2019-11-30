/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   :  	        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2010/4/4                                      */      
/*  Version   	  : 1.0                                           */          
/*  Function      : �����¼������������������				      */                       
/*  Description   : 								              */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/

/*****************ͷ�ļ�********************/  
#include "DSP281x_Device.h"
#include "System.h"

/****************�˿ں궨��*****************/
#define IN1_DAT GpioDataRegs.GPADAT.bit.GPIOA0  //PWM1
#define IN1_DIR GpioMuxRegs.GPADIR.bit.GPIOA0   
#define IN2_DAT GpioDataRegs.GPADAT.bit.GPIOA1  //PWM2
#define IN2_DIR GpioMuxRegs.GPADIR.bit.GPIOA1
#define IN3_DAT GpioDataRegs.GPADAT.bit.GPIOA2  //PWM3
#define IN3_DIR GpioMuxRegs.GPADIR.bit.GPIOA2
#define IN4_DAT GpioDataRegs.GPADAT.bit.GPIOA3  //PWM4
#define IN4_DIR GpioMuxRegs.GPADIR.bit.GPIOA3

#define Up_Key GpioDataRegs.GPEDAT.bit.GPIOE2
#define Down_Key GpioDataRegs.GPBDAT.bit.GPIOB8 

/****************�����궨��*****************/ 
#define Period  1000  //����

#define IDLE 0x00;
#define Forward_Run1 0x01;
#define Forward_Run2 0x02;
#define Reverse_Run1 0x81;
#define Reverse_Run2 0x82;

/***************ȫ�ֱ�������****************/
unsigned char stage ; //ָʾ�������״̬

/****************��������*******************/ 
void Init_Port(void);
void Init_EVA(void);
void Scan_Key(void);
void Manage_Forward(void);
void Manage_Reverse(void);
void Forward_Drive(void);
void Reverse_Drive(void);
interrupt void EVA_Timer1_ISR(void);

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:������			                */
/*------------------------------------------*/ 
void main(void)
{
	InitSysCtrl();  // ϵͳ��ʼ���ӳ�����DSP28_sysctrl.c��
	Init_EVA();
	while(1)
	{
		if((Up_Key==0)|(Down_Key==0))//ɨ���Ƿ񰴼�����
			Scan_Key();		
	}   
} 

/*------------------------------------------*/
/*��ʽ������void		            		*/
/*����ֵ:void				    			*/
/*��������:��ʼ���¼�������A       	    	*/
/*------------------------------------------*/ 
void Init_EVA(void)
{
	//�˶���������������Ϊ���ù���
	EALLOW;
   	GpioMuxRegs.GPAMUX.all = 0x000F; // EVA PWM 1-4
   	EDIS;
   	 
   	EvaRegs.T1PR = Period;      // ����Timer1 period
   	EvaRegs.T1CNT = 0x0000;     // ����Timer1 counter
	
	EvaRegs.CMPR1 = Period/2; //���ñȽϼĴ���1
	EvaRegs.CMPR2 = Period/2; //���ñȽϼĴ���2    

	//���ñȽϵ�Ԫ
	EvaRegs.COMCONA.bit.CENABLE = 1; //ʹ�ܱȽ�������
	EvaRegs.COMCONA.bit.CLD = 2;   // ���ñȽϼĴ���CMPRx����װ������������װ��  
	EvaRegs.COMCONA.bit.ACTRLD =2; // ���÷�ʽ���ƼĴ���ACTRA����װ������������װ��
	EvaRegs.COMCONA.bit.FCOMPOE = 1; //����������ȫ�Ƚ�����������

	EvaRegs.DBTCONA.bit.EDBT1 = 0; //��ֹ������·��Ĭ��
	EvaRegs.DBTCONA.bit.EDBT2 = 0; //��ֹ������·��Ĭ��
	EvaRegs.DBTCONA.bit.EDBT2 = 0; //��ֹ������·��Ĭ��

	EvaRegs.T1CON.bit.TMODE = 2; //����������ģʽ
   	EvaRegs.T1CON.bit.TPS= 7;    //���ø���ʱ��128��Ƶ
	EvaRegs.T1CON.bit.TCLKS10= 0; //ѡ���ڲ�ʱ��

	//ʹ���жϣ��������輶��PIE����CPU�����������ж�����
	EvaRegs.EVAIMRA.bit.T1PINT = 1;// ʹ��EVA Time1�����ж� 
	EvaRegs.EVAIFRA.bit.T1PINT = 1;// �����־λ	  
	EALLOW;	// ����Ĵ�������
	PieVectTable.T1PINT = &EVA_Timer1_ISR;//��EVA_Timer1�����жϺ�����ڸ���PIE������
	EDIS;   // ʹ�ܼĴ�������
    PieCtrlRegs.PIEIER2.bit.INTx4 = 1;//ʹ��PIE�ڵ�EVA_Timer1�����ж� 
    IER |= M_INT2;  // ʹ�� CPU INT 2	    
   	EINT;        	// ȫ���ж�ʹ��INTM
} 

/*------------------------------------------*/
/*��ʽ������void		            		*/
/*����ֵ:void				    			*/
/*��������:ɨ���ֵ             	    	*/
/*------------------------------------------*/
void Scan_Key(void)      
{
	unsigned int i;
	for(i=0;i<50000;i++);    //����������	
	if(Up_Key==0)
		Manage_Forward();
	else if(Down_Key==0)
		Manage_Reverse();
	while((Up_Key==0)|(Down_Key==0));			  
}

/*------------------------------------------*/
/*��ʽ������void		            		*/
/*����ֵ:void				    			*/
/*��������:�����Ĵ������    	    		*/
/*------------------------------------------*/
void Manage_Forward(void) //��ת
{
	Forward_Drive();
}

void Manage_Reverse(void)//��ת
{
	Reverse_Drive();
} 
 
/*------------------------------------------*/
/*��ʽ������void		            		*/
/*����ֵ:void				    			*/
/*��������:�����ת����    	    			*/
/*------------------------------------------*/
void Forward_Drive(void) 
{
	EvaRegs.ACTRA.bit.CMP1ACT = 1; //����Ч
	EvaRegs.ACTRA.bit.CMP2ACT = 0; //ǿ�Ƶ�
	EvaRegs.ACTRA.bit.CMP3ACT = 2; //����Ч
	EvaRegs.ACTRA.bit.CMP4ACT = 0; //ǿ�Ƶ�
	stage = Forward_Run1; //���õ����ת״̬ 
	EvaRegs.T1CON.bit.TENABLE = 1; //ʹ�ܼ�����
}

/*------------------------------------------*/
/*��ʽ������void		            		*/
/*����ֵ:void				    			*/
/*��������:�����ת����    	    			*/
/*------------------------------------------*/
void Reverse_Drive(void) 
{
	EvaRegs.ACTRA.bit.CMP1ACT = 0; //ǿ�Ƶ�
	EvaRegs.ACTRA.bit.CMP2ACT = 2; //����Ч
	EvaRegs.ACTRA.bit.CMP3ACT = 0; //ǿ�Ƶ�
	EvaRegs.ACTRA.bit.CMP4ACT = 1; //����Ч
	stage = Reverse_Run1; //���õ����ת״̬ 
	EvaRegs.T1CON.bit.TENABLE = 1; //ʹ�ܼ�����
} 


interrupt void EVA_Timer1_ISR(void)
{
   	DINT;//�ر����ж�
   	
	switch(stage)
	 {
		case 0x01: //Forward_Run1
			EvaRegs.ACTRA.bit.CMP1ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP2ACT = 1; //����Ч
			EvaRegs.ACTRA.bit.CMP3ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP4ACT = 2; //����Ч
			stage = Forward_Run2; //���õ����ת״̬
			break;//����
		case 0x02:  //Forward_Run2
			EvaRegs.ACTRA.bit.CMP1ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP2ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP3ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP4ACT = 0; //ǿ�Ƶ�
			stage = IDLE; //����״̬
			EvaRegs.T1CON.bit.TENABLE = 0; //��ֹ������
        	break;//����

        case 0x81: //Reverse_Run1
			EvaRegs.ACTRA.bit.CMP1ACT = 2; //����Ч
			EvaRegs.ACTRA.bit.CMP2ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP3ACT = 1; //����Ч
			EvaRegs.ACTRA.bit.CMP4ACT = 0; //ǿ�Ƶ�
			stage = Reverse_Run2; //���õ����ת״̬
			break;//����
        case 0x82: //Reverse_Run2
			EvaRegs.ACTRA.bit.CMP1ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP2ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP3ACT = 0; //ǿ�Ƶ�
			EvaRegs.ACTRA.bit.CMP4ACT = 0; //ǿ�Ƶ�
			stage = IDLE; //����״̬
          	EvaRegs.T1CON.bit.TENABLE = 0; //��ֹ������
        	break;//����
        default:break;
	 }

	EvaRegs.EVAIFRA.bit.T1PINT = 1;//�����־λ	
    PieCtrlRegs.PIEACK.all |= BIT2;   //��Ӧ�ж�
	EINT;   //�����ж�
} 
