//数码管程序   
#include "DSP28_Device.h"

#define SPI_SEL_REG *(Uint16 *)0x2c00
#define LED_SPI  0X00
const   Uint16  LedCode[]={0X7E7E,0X2929,0X2C2C,0X6666,0XA4A4,0XA0A0,0X3E3E,0X2020,0X2424};

unsigned int count;

void delay(unsigned int);
void ldelay(unsigned int);
void WriteLED(unsigned int);

void main(void)
{   
    unsigned int temp;
	InitSysCtrl();			//初始化系统

	DINT;					//关中断 
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//初始化PIE控制寄存器
	InitPieVectTable();		//初始化PIE参数表 
	InitPeripherals();		//初始化外设寄存器 
	InitGpio();           	//初始化IO口
   	InitSpi();	          	//初始化SPI	

	EINT;					//Enable INTM
	ERTM;					//Enable DBGM
	GpioDataRegs.GPASET.all|=0x0000;	//previous Program is 0x8000, unknown affects. Attention!
   
	temp = 0;
	count=0;
	SPI_SEL_REG=LED_SPI;	//使能LED SPI
   	
	while(1)
	{ 
		WriteLED(temp);//temp);
		ldelay(50);
		count++;	   	   	   
		temp=(count)%9;
	}
} 	

void WriteLED(unsigned int index)
{

     
	if(Spi_TxReady() == 1)
		SpiaRegs.SPITXBUF =(unsigned int)( LedCode[index]);//检查发送寄存器是否为空
	delay(50000);  
	GpioDataRegs.GPACLEAR.all|=0x8000;
	delay(1000);
	GpioDataRegs.GPASET.all|=0x8000;
}
	
void ldelay(unsigned int k)
{
    while(k>0)
    {
        k--;
        delay(50000);
	}
}	

void delay(unsigned int t)
{
	while(t>0)
		t--;
}
