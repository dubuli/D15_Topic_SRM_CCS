/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_PieVect.c							  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 初始化PIE向量表                               */                       
/*  Description   :                                               */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/  
#include "DSP281x_Device.h" 
#include "DSP281x_DefaultIsr.h"  

//中断向量入口值，和DSP281x_DefaultIsr文件中定义的中断函数相对应 
const struct PIE_VECT_TABLE PieVectTableInit = {

      PIE_RESERVED,  // Reserved space
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   

// Non-Peripheral Interrupts
      INT13_ISR,     // XINT13 or CPU-Timer 1
      INT14_ISR,     // CPU-Timer2
      DATALOG_ISR,   // Datalogging interrupt
      RTOSINT_ISR,   // RTOS interrupt
      EMUINT_ISR,    // Emulation interrupt
      NMI_ISR,       // Non-maskable interrupt
      ILLEGAL_ISR,   // Illegal operation TRAP
      USER1_ISR,     // User Defined trap 1
      USER2_ISR,     // User Defined trap 2
      USER3_ISR,     // User Defined trap 3
      USER4_ISR,     // User Defined trap 4
      USER5_ISR,     // User Defined trap 5
      USER6_ISR,     // User Defined trap 6
      USER7_ISR,     // User Defined trap 7
      USER8_ISR,     // User Defined trap 8
      USER9_ISR,     // User Defined trap 9
      USER10_ISR,    // User Defined trap 10
      USER11_ISR,    // User Defined trap 11
      USER12_ISR,     // User Defined trap 12

// Group 1 PIE Vectors
      PDPINTA_ISR,   // EV-A
      PDPINTB_ISR,   // EV-B
      rsvd_ISR,
      XINT1_ISR,     
      XINT2_ISR,
      ADCINT_ISR,    // ADC
      TINT0_ISR,     // Timer 0
      WAKEINT_ISR,   // WD

// Group 2 PIE Vectors
      CMP1INT_ISR,   // EV-A
      CMP2INT_ISR,   // EV-A
      CMP3INT_ISR,   // EV-A
      T1PINT_ISR,    // EV-A
      T1CINT_ISR,    // EV-A
      T1UFINT_ISR,   // EV-A
      T1OFINT_ISR,   // EV-A
      rsvd_ISR,
      
// Group 3 PIE Vectors
      T2PINT_ISR,    // EV-A
      T2CINT_ISR,    // EV-A
      T2UFINT_ISR,   // EV-A
      T2OFINT_ISR,   // EV-A
      CAPINT1_ISR,   // EV-A
      CAPINT2_ISR,   // EV-A
      CAPINT3_ISR,   // EV-A
      rsvd_ISR,
      
// Group 4 PIE Vectors
      CMP4INT_ISR,   // EV-B
      CMP5INT_ISR,   // EV-B
      CMP6INT_ISR,   // EV-B
      T3PINT_ISR,    // EV-B
      T3CINT_ISR,    // EV-B
      T3UFINT_ISR,   // EV-B
      T3OFINT_ISR,   // EV-B
      rsvd_ISR,      
     
// Group 5 PIE Vectors
      T4PINT_ISR,    // EV-B
      T4CINT_ISR,    // EV-B
      T4UFINT_ISR,   // EV-B
      T4OFINT_ISR,   // EV-B
      CAPINT4_ISR,   // EV-B
      CAPINT5_ISR,   // EV-B
      CAPINT6_ISR,   // EV-B
      rsvd_ISR,      

// Group 6 PIE Vectors
      SPIRXINTA_ISR,   // SPI-A
      SPITXINTA_ISR,   // SPI-A
      rsvd_ISR,
      rsvd_ISR,
      MRINTA_ISR,    // McBSP-A
      MXINTA_ISR,    // McBSP-A
      rsvd_ISR,
      rsvd_ISR,
      
// Group 7 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   

// Group 8 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      
// Group 9 PIE Vectors     
      SCIRXINTA_ISR, // SCI-A
      SCITXINTA_ISR, // SCI-A
      SCIRXINTB_ISR, // SCI-B
      SCITXINTB_ISR, // SCI-B
      ECAN0INTA_ISR, // eCAN
      ECAN1INTA_ISR, // eCAN
      rsvd_ISR,   
      rsvd_ISR,   
      
// Group 10 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
            
// Group 11 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   

// Group 12 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
};


/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:初始化PIE向量表                  */
/*------------------------------------------*/ 
void InitPieVectTable(void)
{
	int16	i;
	Uint32 *Source = (void *) &PieVectTableInit;
	Uint32 *Dest = (void *) &PieVectTable;
		
	EALLOW;	
	for(i=0; i < 128; i++)
		*Dest++ = *Source++;	
	EDIS;

	// 使能中断向量表
	PieCtrlRegs.PIECRTL.bit.ENPIE = 1;
			
}

