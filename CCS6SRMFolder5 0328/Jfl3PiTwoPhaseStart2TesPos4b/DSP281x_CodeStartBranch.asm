;******************************************************************
;* Copyright (C), 2008-2009, ������ӣ�LiTian Tech.Co.Ltd.
;*  Module Name   : System              
;*  File Name     : DSP281x_CodeStartBranch.asm	            
;*  Author   	  : ���         
;*  Create Date   : 2009/12/1         
;*  Version   	  : 2.0                
;*  Function      : C���л����ĳ�ʼ������                         
;*  Description   :                        
;*  Support       : www.LT430.com                  
;****************************************************************** 

;***********************************************************************

WD_DISABLE	.set	1		;��1��ֹ���Ź�

    .ref _c_int00

;***********************************************************************
;* Function: codestart section
;* Description: Branch to code starting point
;***********************************************************************

    .sect "codestart"

code_start:
    .if WD_DISABLE == 1
        LB wd_disable       ;��ת�����ο��Ź�����
    .else
        LB _c_int00         ;��ת����������_c_int00
    .endif

;***********************************************************************
;* Function: wd_disable
;* Description: Disables the watchdog timer
;***********************************************************************
    .if WD_DISABLE == 1

    .text
wd_disable:
    SETC OBJMODE        ;C28xĿ��ģʽ
    EALLOW              ;��������ܱ����ļĴ���
    MOVZ DP, #7029h>>6  ;���ؿ��Ź����ƼĴ���
    MOV @7029h, #0068h  ;��ֹ���Ź�
    EDIS                ;��ֹ�����ܱ����ļĴ���
    LB _c_int00         ;��ת�����п��е�boot.asm

    .endif

	.end
