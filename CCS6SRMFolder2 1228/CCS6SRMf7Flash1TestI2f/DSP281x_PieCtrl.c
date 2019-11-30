/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_PieCtrl.c							  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : ��ʼ��PIE���ƼĴ���                           */                       
/*  Description   :                                               */            
/*  Support       : www.LT430.com                                 */             
/******************************************************************/ 
#include "DSP281x_Device.h"    

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:��ʼ��PIE���ƼĴ���              */
/*------------------------------------------*/ 
void InitPieCtrl(void)
{
    DINT;	//��ֹCPU���ж�

    PieCtrlRegs.PIECRTL.bit.ENPIE = 0;//����PIE�ж�������

	//�������PIEIER�Ĵ���
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	// �������PIEIFR�Ĵ���
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;
}	

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:ʹ�������ж�                     */
/*------------------------------------------*/  
void EnableInterrupts(void)
{
    //ʹ��PIE�ж�������
    PieCtrlRegs.PIECRTL.bit.ENPIE = 1;
    		
	// ��Ӧ�����ж� 
	PieCtrlRegs.PIEACK.all = 0xFFFF;

	//ʹ��CPU���ж�
    EINT;
}

