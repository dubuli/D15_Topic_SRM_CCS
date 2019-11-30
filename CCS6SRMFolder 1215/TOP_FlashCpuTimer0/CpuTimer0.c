
#include "DSP28_Device.h"

unsigned int *LedADDR  = (unsigned int *) 0x2800;	//8个发光二极管寄存器地址

unsigned int Count,Flag;
/////////////////对应位低电平点亮该位发光二极管
const	Uint16	LedCode[9]={0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE,0xFF};

interrupt void ISRTimer0(void);
	 	
void main(void)
{
	InitSysCtrl();					//初始化系统

	DINT;						//关中断
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();					//初始化PIE
	InitPieVectTable();				//初始化PIE中断矢量表
	InitPeripherals();				//初始化外设
    InitGpio();
	EALLOW;	
	PieVectTable.TINT0 = &ISRTimer0;
	EDIS;   
	
 	Count = 0;					//初始化变量
    Flag=0;
	ConfigCpuTimer(&CpuTimer0, 10, 1000000);	//设置CPU
 	StartCpuTimer0();
    
	IER |= M_INT1;					//开中断
	PieCtrl.PIEIER1.bit.INTx7=1;

	EINT;						// 允许INTM
	ERTM;						// 允许DBGM

	*LedADDR = 0x00;					// 点亮全部8个LED灯
	for(;;)
	{	;	}

} 	

interrupt void ISRTimer0(void)
{
	PieCtrl.PIEACK.bit.ACK7=1;
	*LedADDR = LedCode[Count];			//依次点亮灯，置相应位低电平
	if (Flag==0) Count++; else Count--;
	if (Count>=8)//循环	
	{
	   Flag=1;  }
	if (Count<=0)//循环	
	{
	   Flag=0;
	   }		
}

