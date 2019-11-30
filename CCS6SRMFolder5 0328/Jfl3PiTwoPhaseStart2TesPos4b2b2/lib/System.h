/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : System             							  */
/*  File Name     : System.h    								  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/10/1                                     */      
/*  Version   	  : 1.0                                           */          
/*  Function      : 系统头文件                                    */                       
/*  Description   : 			                                  */            
/*  Support       : www.LT430.com  QQ:903175306                   */             
/******************************************************************/ 
#ifndef System_H
#define System_H


#ifdef __cplusplus
extern "C" {
#endif

//#define CPU_RATE    6.667L   // for a 150MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE    7.143L   // for a 140MHz CPU clock speed (SYSCLKOUT)
#define CPU_RATE    8.333L   // for a 120MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   10.000L   // for a 100MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   13.330L   // for a 75MHz CPU clock speed (SYSCLKOUT)
//#define CPU_RATE   20.000L   // for a 50MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   33.333L   // for a 30MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   41.667L   // for a 24MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   50.000L   // for a 20MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   66.667L   // for a 15MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE  100.000L   // for a 10MHz CPU clock speed  (SYSCLKOUT)
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "DSP281x_GlobalPrototypes.h"    //系统函数声明

// Include files not used with DSP/BIOS
#ifndef DSP28_BIOS
#include "DSP281x_DefaultISR.h"
#endif

// DO NOT MODIFY THIS LINE.
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L) 

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP281x_EXAMPELS_H definition


//===========================================================================
// No more.
//===========================================================================
