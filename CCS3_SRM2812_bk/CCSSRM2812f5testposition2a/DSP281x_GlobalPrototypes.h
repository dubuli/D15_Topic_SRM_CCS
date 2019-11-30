/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_GlobalPrototypes.c					  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : ϵͳ��ʼ����������	                          */                       
/*  Description   :                                               */            
/*  Support       : www.LT430.com                                 */             
/******************************************************************/  
#ifndef _System_H_
#define _System_H_

#ifdef __cplusplus
extern "C" {
#endif

//ϵͳ��ʼ����غ�������
extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void EnableInterrupts(void);
extern void InitSysCtrl(void);
extern void InitPll(Uint16 val);
extern void InitPeripheralClocks(void);
extern void KickDog(void);
extern void DisableDog(void);
extern Uint16 CsmUnlock(void);
extern void InitFlash(void);

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

//�����ⲿ��������������������������������ȫ�ֱ���
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;

#ifdef __cplusplus
}
#endif

#endif

