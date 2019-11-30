/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_SysCtrl.c							  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      :初始化系统，包括看门狗、系统时钟、外设时钟     */
/*                 中断积存器、中断向量表                         */                       
/*  Description   :                                               */            
/*  Support       : www.LT430.com  			                      */             
/******************************************************************/  
#include "DSP281x_Device.h"
#include "System.h" 

#pragma CODE_SECTION(InitFlash, "ramfuncs");

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:初始化系统                       */
/*------------------------------------------*/ 
void InitSysCtrl(void)
{
   DisableDog();//禁止看门狗
   InitPll(0x8);//设置系统时钟=XCLKIN*8/2
   InitPeripheralClocks();	//设置外设时钟
   DINT;           		 	// 关闭总中断
   IER = 0x0000;   			// 关闭外设中断
   IFR = 0x0000;   			// 清中断标志	
   InitPieCtrl();			//初始化PIE控制寄存器
   InitPieVectTable();		//使能PIE向量表
} 

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:禁止看门狗                       */
/*------------------------------------------*/  
void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}
/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:喂看门狗                         */
/*------------------------------------------*/ 
void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
} 
/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:设置锁相环倍频系数               */
/*------------------------------------------*/  
void InitPll(Uint16 val)
{
   volatile Uint16 iVol;

   if (SysCtrlRegs.PLLCR.bit.DIV != val)
   {

      EALLOW;
      SysCtrlRegs.PLLCR.bit.DIV = val;
      EDIS;

      for(iVol= 0; iVol<4096; iVol++);
   }
}

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:初始化外设时钟                   */
/*------------------------------------------*/  
void InitPeripheralClocks(void)
{
   EALLOW;

   SysCtrlRegs.HISPCP.all = 0x0001;//设置高速时钟 2分频
   SysCtrlRegs.LOSPCP.all = 0x0002;//设置低速时钟 4分频

   //使能外围模块时钟
   SysCtrlRegs.PCLKCR.bit.EVAENCLK=1;
   SysCtrlRegs.PCLKCR.bit.EVBENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SCIAENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SCIBENCLK=1;
   SysCtrlRegs.PCLKCR.bit.MCBSPENCLK=1;
   SysCtrlRegs.PCLKCR.bit.SPIENCLK=1;
   SysCtrlRegs.PCLKCR.bit.ECANENCLK=1;
   SysCtrlRegs.PCLKCR.bit.ADCENCLK=1;
   EDIS;
}
/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:初始化Flash		                */
/*------------------------------------------*/ 
void InitFlash(void)
{
   EALLOW;
   FlashRegs.FPWR.bit.PWR = 3;	//设置Flash为正常工作状态
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;//设置随机存取等待时间
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;//设置页面存取等待时间
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;		//设置从睡眠到等待的转换时间
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;	//设置从等待到激活的转换时间
   FlashRegs.FOPT.bit.ENPIPE = 1;		//使能流水线模式
   EDIS;
   asm(" RPT #7 || NOP");//软件延时，等待流水线刷新
}

/*------------------------------------------*/
/*形式参数：void	                        */
/*返回值:状态值				                */
/*函数描述:unlocks the CSM                  */
/*------------------------------------------*/  
#define STATUS_FAIL          0
#define STATUS_SUCCESS       1

Uint16 CsmUnlock()
{
    volatile Uint16 temp;

    // 写入密钥，应将0xFFFF替换成密钥值
    EALLOW;
    CsmRegs.KEY0 = 0xFFFF;
    CsmRegs.KEY1 = 0xFFFF;
    CsmRegs.KEY2 = 0xFFFF;
    CsmRegs.KEY3 = 0xFFFF;
    CsmRegs.KEY4 = 0xFFFF;
    CsmRegs.KEY5 = 0xFFFF;
    CsmRegs.KEY6 = 0xFFFF;
    CsmRegs.KEY7 = 0xFFFF;
    EDIS;

    /// 执行空读
    temp = CsmPwl.PSWD0;
    temp = CsmPwl.PSWD1;
    temp = CsmPwl.PSWD2;
    temp = CsmPwl.PSWD3;
    temp = CsmPwl.PSWD4;
    temp = CsmPwl.PSWD5;
    temp = CsmPwl.PSWD6;
    temp = CsmPwl.PSWD7;

    if (CsmRegs.CSMSCR.bit.SECURE == 0) 
    	return STATUS_SUCCESS;
    else 
    	return STATUS_FAIL;
} 
