/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_PieCtrl.c							  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 初始化PIE控制寄存器                           */                       
/*  Description   :                                               */            
/*  Support       : www.LT430.com                                 */             
/******************************************************************/ 
#include "DSP281x_Device.h"    

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:初始化PIE控制寄存器              */
/*------------------------------------------*/ 
void InitPieCtrl(void)
{
    DINT;	//禁止CPU级中断

    PieCtrlRegs.PIECRTL.bit.ENPIE = 0;//屏蔽PIE中断向量表

	//清除所有PIEIER寄存器
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

	// 清除所有PIEIFR寄存器
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
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:使能所有中断                     */
/*------------------------------------------*/  
void EnableInterrupts(void)
{
    //使能PIE中断向量表
    PieCtrlRegs.PIECRTL.bit.ENPIE = 1;
    		
	// 响应所有中断 
	PieCtrlRegs.PIEACK.all = 0xFFFF;  

	//使能CPU级中断
    EINT;
}

