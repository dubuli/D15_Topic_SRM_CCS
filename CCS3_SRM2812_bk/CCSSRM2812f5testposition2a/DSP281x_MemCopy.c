/******************************************************************/
/*Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.		  */
/*  Module Name   : system             							  */
/*  File Name     : DSP281x_MemCopy.c							  */        
/*  Author   	  : ���                                        */     
/*  Create Date   : 2009/12/1                                     */      
/*  Version   	  : 2.0                                           */          
/*  Function      : system                                        */                       
/*  Description   : ���ݸ���                                      */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/ 
#include "DSP281x_Device.h"

/*------------------------------------------*/
/*��ʽ������SourceAddr--Դ��ַ��ʼ��ַ      */
/*			SourceEndAddr--Դ��ַ������ַ   */
/*			DestAddr--Ŀ�ĵ�ַ   			*/
/*����ֵ:void				                */
/*��������:��Դ��ַ���ݸ��Ƶ�Ŀ�ĵ�ַ       */
/*------------------------------------------*/ 
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}
