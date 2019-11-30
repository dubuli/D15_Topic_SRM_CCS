/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : System             							  */
/*  File Name     : System.h    								  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : 系统头文件                                    */                       
/*  Description   : 			                                  */            
/*  Support       : www.LT430.com  				                  */             
/******************************************************************/ 
#ifndef System_H
#define System_H


#ifdef __cplusplus
extern "C" {
#endif


#include "DSP281x_GlobalPrototypes.h"  //包含系统初始化函数声明头文件

// Include files not used with DSP/BIOS
#ifndef DSP28_BIOS
#include "DSP281x_DefaultISR.h"
#endif

#ifdef __cplusplus
}
#endif

#endif
