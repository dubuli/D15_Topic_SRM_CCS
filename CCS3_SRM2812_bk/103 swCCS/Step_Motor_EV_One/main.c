/******************************************************************/
/*Copyright (C), 2008-2009, 力天电子，LiTian Tech.Co.Ltd.		  */
/*  Module Name   :  	        							  	  */
/*  File Name     : main.c	   									  */        
/*  Author   	  : 侯长波                                        */     
/*  Create Date   : 2010/4/4                                      */      
/*  Version   	  : 1.0                                           */          
/*  Function      : 采用事件管理器驱动步进电机				      */                       
/*  Description   : 								              */            
/*  Support       : www.LT430.com 				                  */             
/******************************************************************/

/*****************头文件********************/  
#include "DSP281x_Device.h"
#include "System.h"

/****************端口宏定义*****************/
#define IN1_DAT GpioDataRegs.GPADAT.bit.GPIOA0  //PWM1
#define IN1_DIR GpioMuxRegs.GPADIR.bit.GPIOA0   
#define IN2_DAT GpioDataRegs.GPADAT.bit.GPIOA1  //PWM2
#define IN2_DIR GpioMuxRegs.GPADIR.bit.GPIOA1
#define IN3_DAT GpioDataRegs.GPADAT.bit.GPIOA2  //PWM3
#define IN3_DIR GpioMuxRegs.GPADIR.bit.GPIOA2
#define IN4_DAT GpioDataRegs.GPADAT.bit.GPIOA3  //PWM4
#define IN4_DIR GpioMuxRegs.GPADIR.bit.GPIOA3

#define Up_Key GpioDataRegs.GPEDAT.bit.GPIOE2
#define Down_Key GpioDataRegs.GPBDAT.bit.GPIOB8 

/****************常量宏定义*****************/ 
#define Period  1000  //周期

#define IDLE 0x00;
#define Forward_Run1 0x01;
#define Forward_Run2 0x02;
#define Reverse_Run1 0x81;
#define Reverse_Run2 0x82;

/***************全局变量定义****************/
unsigned char stage ; //指示步进电机状态

/****************函数声明*******************/ 
void Init_Port(void);
void Init_EVA(void);
void Scan_Key(void);
void Manage_Forward(void);
void Manage_Reverse(void);
void Forward_Drive(void);
void Reverse_Drive(void);
interrupt void EVA_Timer1_ISR(void);

/*------------------------------------------*/
/*形式参数：void                            */
/*返回值:void				                */
/*函数描述:主函数			                */
/*------------------------------------------*/ 
void main(void)
{
	InitSysCtrl();  // 系统初始化子程序，在DSP28_sysctrl.c中
	Init_EVA();
	while(1)
	{
		if((Up_Key==0)|(Down_Key==0))//扫描是否按键按下
			Scan_Key();		
	}   
} 

/*------------------------------------------*/
/*形式参数：void		            		*/
/*返回值:void				    			*/
/*函数描述:初始化事件管理器A       	    	*/
/*------------------------------------------*/ 
void Init_EVA(void)
{
	//此段是用来设置引脚为复用功能
	EALLOW;
   	GpioMuxRegs.GPAMUX.all = 0x000F; // EVA PWM 1-4
   	EDIS;
   	 
   	EvaRegs.T1PR = Period;      // 设置Timer1 period
   	EvaRegs.T1CNT = 0x0000;     // 清零Timer1 counter
	
	EvaRegs.CMPR1 = Period/2; //设置比较寄存器1
	EvaRegs.CMPR2 = Period/2; //设置比较寄存器2    

	//设置比较单元
	EvaRegs.COMCONA.bit.CENABLE = 1; //使能比较器操作
	EvaRegs.COMCONA.bit.CLD = 2;   // 设置比较寄存器CMPRx重新装载条件，立即装载  
	EvaRegs.COMCONA.bit.ACTRLD =2; // 设置方式控制寄存器ACTRA重新装载条件，立即装载
	EvaRegs.COMCONA.bit.FCOMPOE = 1; //设置引脚由全比较器独立驱动

	EvaRegs.DBTCONA.bit.EDBT1 = 0; //禁止死区电路，默认
	EvaRegs.DBTCONA.bit.EDBT2 = 0; //禁止死区电路，默认
	EvaRegs.DBTCONA.bit.EDBT2 = 0; //禁止死区电路，默认

	EvaRegs.T1CON.bit.TMODE = 2; //连续增计数模式
   	EvaRegs.T1CON.bit.TPS= 7;    //设置高速时钟128分频
	EvaRegs.T1CON.bit.TCLKS10= 0; //选择内部时钟

	//使能中断（包含外设级、PIE级和CPU级），设置中断向量
	EvaRegs.EVAIMRA.bit.T1PINT = 1;// 使能EVA Time1周期中断 
	EvaRegs.EVAIFRA.bit.T1PINT = 1;// 清零标志位	  
	EALLOW;	// 解除寄存器保护
	PieVectTable.T1PINT = &EVA_Timer1_ISR;//用EVA_Timer1周期中断函数入口更新PIE向量表
	EDIS;   // 使能寄存器保护
    PieCtrlRegs.PIEIER2.bit.INTx4 = 1;//使能PIE内的EVA_Timer1周期中断 
    IER |= M_INT2;  // 使能 CPU INT 2	    
   	EINT;        	// 全局中断使能INTM
} 

/*------------------------------------------*/
/*形式参数：void		            		*/
/*返回值:void				    			*/
/*函数描述:扫描键值             	    	*/
/*------------------------------------------*/
void Scan_Key(void)      
{
	unsigned int i;
	for(i=0;i<50000;i++);    //键盘消抖动	
	if(Up_Key==0)
		Manage_Forward();
	else if(Down_Key==0)
		Manage_Reverse();
	while((Up_Key==0)|(Down_Key==0));			  
}

/*------------------------------------------*/
/*形式参数：void		            		*/
/*返回值:void				    			*/
/*函数描述:按键的处理程序    	    		*/
/*------------------------------------------*/
void Manage_Forward(void) //正转
{
	Forward_Drive();
}

void Manage_Reverse(void)//反转
{
	Reverse_Drive();
} 
 
/*------------------------------------------*/
/*形式参数：void		            		*/
/*返回值:void				    			*/
/*函数描述:电机正转程序    	    			*/
/*------------------------------------------*/
void Forward_Drive(void) 
{
	EvaRegs.ACTRA.bit.CMP1ACT = 1; //低有效
	EvaRegs.ACTRA.bit.CMP2ACT = 0; //强制低
	EvaRegs.ACTRA.bit.CMP3ACT = 2; //高有效
	EvaRegs.ACTRA.bit.CMP4ACT = 0; //强制低
	stage = Forward_Run1; //设置电机旋转状态 
	EvaRegs.T1CON.bit.TENABLE = 1; //使能计数器
}

/*------------------------------------------*/
/*形式参数：void		            		*/
/*返回值:void				    			*/
/*函数描述:电机反转程序    	    			*/
/*------------------------------------------*/
void Reverse_Drive(void) 
{
	EvaRegs.ACTRA.bit.CMP1ACT = 0; //强制低
	EvaRegs.ACTRA.bit.CMP2ACT = 2; //高有效
	EvaRegs.ACTRA.bit.CMP3ACT = 0; //强制低
	EvaRegs.ACTRA.bit.CMP4ACT = 1; //低有效
	stage = Reverse_Run1; //设置电机旋转状态 
	EvaRegs.T1CON.bit.TENABLE = 1; //使能计数器
} 


interrupt void EVA_Timer1_ISR(void)
{
   	DINT;//关闭总中断
   	
	switch(stage)
	 {
		case 0x01: //Forward_Run1
			EvaRegs.ACTRA.bit.CMP1ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP2ACT = 1; //低有效
			EvaRegs.ACTRA.bit.CMP3ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP4ACT = 2; //高有效
			stage = Forward_Run2; //设置电机旋转状态
			break;//跳出
		case 0x02:  //Forward_Run2
			EvaRegs.ACTRA.bit.CMP1ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP2ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP3ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP4ACT = 0; //强制低
			stage = IDLE; //空闲状态
			EvaRegs.T1CON.bit.TENABLE = 0; //禁止计数器
        	break;//跳出

        case 0x81: //Reverse_Run1
			EvaRegs.ACTRA.bit.CMP1ACT = 2; //高有效
			EvaRegs.ACTRA.bit.CMP2ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP3ACT = 1; //低有效
			EvaRegs.ACTRA.bit.CMP4ACT = 0; //强制低
			stage = Reverse_Run2; //设置电机旋转状态
			break;//跳出
        case 0x82: //Reverse_Run2
			EvaRegs.ACTRA.bit.CMP1ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP2ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP3ACT = 0; //强制低
			EvaRegs.ACTRA.bit.CMP4ACT = 0; //强制低
			stage = IDLE; //空闲状态
          	EvaRegs.T1CON.bit.TENABLE = 0; //禁止计数器
        	break;//跳出
        default:break;
	 }

	EvaRegs.EVAIFRA.bit.T1PINT = 1;//清零标志位	
    PieCtrlRegs.PIEACK.all |= BIT2;   //响应中断
	EINT;   //开总中断
} 
