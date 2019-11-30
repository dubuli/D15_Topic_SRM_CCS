/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_SysCtrl.c							  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      :��ʼ��ϵͳ���������Ź���ϵͳʱ�ӡ�����ʱ��     */
/*                 �жϻ��������ж�������                         */                       
/*  Description   :                                               */            
/*  Support       : www.LT430.com  			                      */             
/******************************************************************/  
#include "DSP281x_Device.h"
#include "System.h" 

#pragma CODE_SECTION(InitFlash, "ramfuncs");

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:��ʼ��ϵͳ                       */
/*------------------------------------------*/ 
void InitSysCtrl(void)
{
	Uint16 i;
	   EALLOW;

	// On TMX samples, to get the best performance of on chip RAM blocks M0/M1/L0/L1/H0 internal
	// control registers bit have to be enabled. The bits are in Device emulation registers.
//	   DevEmuRegs.M0RAMDFT = 0x0300;
	//   DevEmuRegs.M1RAMDFT = 0x0300;
	//   DevEmuRegs.L0RAMDFT = 0x0300;
	//   DevEmuRegs.L1RAMDFT = 0x0300;
	  // DevEmuRegs.H0RAMDFT = 0x0300;


	// Disable watchdog module
	   SysCtrlRegs.WDCR= 0x0068;//ban the dog

	// Initalize PLL
	   SysCtrlRegs.PLLCR.all = 0x0a;	//changed, new syslck is 150M
	   // Wait for PLL to lock
	   for(i= 0; i< 5000; i++){}

	// HISPCP/LOSPCP prescale register settings, normally it will be set to default values
	   SysCtrlRegs.HISPCP.all = 0x0001;	//srmf6
	   SysCtrlRegs.LOSPCP.all = 0x0002;
	// Peripheral clock enables set for the selected peripherals.
	   SysCtrlRegs.PCLKCR.bit.EVAENCLK=1;
	   SysCtrlRegs.PCLKCR.bit.EVBENCLK=1;
	   SysCtrlRegs.PCLKCR.bit.SCIAENCLK=1;
	// SysCtrlRegs.PCLKCR.bit.SCIENCLKB=1;
	   SysCtrlRegs.PCLKCR.bit.ADCENCLK=1;

	   EDIS;
} 

/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:��ֹ���Ź�                       */
/*------------------------------------------*/  
void DisableDog(void)
{
    EALLOW;
    SysCtrlRegs.WDCR= 0x0068;
    EDIS;
}
/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:ι���Ź�                         */
/*------------------------------------------*/ 
void KickDog(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
} 
/*------------------------------------------*/
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:�������໷��Ƶϵ��               */
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
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:��ʼ������ʱ��                   */
/*------------------------------------------*/  
void InitPeripheralClocks(void)
{
   EALLOW;
   	   	   	   	   	   	   	   	   //30M OSCCLK����	DOG	30M
   SysCtrlRegs.HISPCP.all = 0x0001;//���ø���ʱ�� 2��Ƶ	EV��ADC��McBSP	75M
   SysCtrlRegs.LOSPCP.all = 0x0002;//���õ���ʱ�� 4��Ƶ	SCI��SPI			37.5M

   //ʹ����Χģ��ʱ��
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
/*��ʽ������void                            */
/*����ֵ:void				                */
/*��������:��ʼ��Flash		                */
/*------------------------------------------*/ 
void InitFlash(void)
{
   EALLOW;
   FlashRegs.FPWR.bit.PWR = 3;	//����FlashΪ��������״̬
   FlashRegs.FBANKWAIT.bit.RANDWAIT = 5;//���������ȡ�ȴ�ʱ��
   FlashRegs.FBANKWAIT.bit.PAGEWAIT = 5;//����ҳ���ȡ�ȴ�ʱ��
   FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;		//���ô�˯�ߵ��ȴ���ת��ʱ��
   FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;	//���ôӵȴ��������ת��ʱ��
   FlashRegs.FOPT.bit.ENPIPE = 1;		//ʹ����ˮ��ģʽ
   EDIS;
   asm(" RPT #7 || NOP");//�����ʱ���ȴ���ˮ��ˢ��
}

/*------------------------------------------*/
/*��ʽ������void	                        */
/*����ֵ:״ֵ̬				                */
/*��������:unlocks the CSM                  */
/*------------------------------------------*/  
#define STATUS_FAIL          0
#define STATUS_SUCCESS       1

Uint16 CsmUnlock()
{
    volatile Uint16 temp;

    // д����Կ��Ӧ��0xFFFF�滻����Կֵ
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

    /// ִ�пն�
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
