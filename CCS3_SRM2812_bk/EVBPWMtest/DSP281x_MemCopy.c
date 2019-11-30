/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_MemCopy.c							  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : system                                        */                       
/*  Description   : 数据复制                                      */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/ 
#include "DSP281x_Device.h"

/*------------------------------------------*/
/*形式参数：SourceAddr--源地址起始地址      */
/*			SourceEndAddr--源地址结束地址   */
/*			DestAddr--目的地址   			*/
/*返回值:void				                */
/*函数描述:将源地址数据复制到目的地址       */
/*------------------------------------------*/ 
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}
