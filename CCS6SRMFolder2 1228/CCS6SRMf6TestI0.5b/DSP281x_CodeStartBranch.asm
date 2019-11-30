;******************************************************************
;* Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.
;*  Module Name   : System              
;*  File Name     : DSP281x_CodeStartBranch.asm	            
;*  Author   	  : 侯长波         
;*  Create Date   : 2009/12/1         
;*  Version   	  : 2.0                
;*  Function      : C运行环境的初始化函数                         
;*  Description   :                        
;*  Support       : www.LT430.com                  
;****************************************************************** 

;***********************************************************************

WD_DISABLE	.set	1		;置1禁止看门狗

    .ref _c_int00

;***********************************************************************
;* Function: codestart section
;* Description: Branch to code starting point
;***********************************************************************

    .sect "codestart"

code_start:
    .if WD_DISABLE == 1
        LB wd_disable       ;跳转至屏蔽看门狗代码
    .else
        LB _c_int00         ;跳转至引导程序_c_int00
    .endif

;***********************************************************************
;* Function: wd_disable
;* Description: Disables the watchdog timer
;***********************************************************************
    .if WD_DISABLE == 1

    .text
wd_disable:
    SETC OBJMODE        ;C28x目标模式
    EALLOW              ;允许访问受保护的寄存器
    MOVZ DP, #7029h>>6  ;加载看门狗控制寄存器
    MOV @7029h, #0068h  ;禁止看门狗
    EDIS                ;禁止访问受保护的寄存器
    LB _c_int00         ;跳转至运行库中的boot.asm

    .endif

	.end
