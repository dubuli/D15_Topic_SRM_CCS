//BUS  LCD   
#include "DSP28_Device.h"

unsigned int * LED_COMM=(Uint16 *)0x3000;
unsigned int * LED_DATA=(Uint16 *)0x3080;


///GpioDataRegs.GPBDAT.bit.GPIOB10=NAND RNB
///////////////////////////////////////////////
unsigned int XPOS,YPOS;
/////////////////////////////////////////////////

void delay(unsigned int);
void ldelay(unsigned int); 
/////////////////////////////////////////////////
void lcdwc(unsigned int c)
{  
   ldelay(100);
   *LED_COMM=c;
}
/////////////////////////////////////
void lcdwd(unsigned int d)
{  
   ldelay(100);
   *LED_DATA=d;
  // ldelay(1000);
  // d=LED_RDATA;
}
///////////////////////////////////////////////
void lcdpos(void)
{  XPOS&=0x000f;
   YPOS&=0x0003;
   if(YPOS==0x0000)
      lcdwc(XPOS|0x80);
   else if(YPOS==0x0001)
      lcdwc((XPOS+0x40)|0x80);
}
///////////////////////////////////////////////////////
void lcdfill(unsigned int n)
{
   for(YPOS=0;YPOS<2;YPOS++)
      for(XPOS=0;XPOS<16;XPOS++)
      {  lcdpos();
         lcdwd(n);  }
}
///////////////////////////////////////////////////////
void lcdreset()
{  ldelay(1500); lcdwc(0x38);
   ldelay(1500); lcdwc(0x38);
   ldelay(1500); lcdwc(0x38);
   lcdwc(0x38);
   lcdwc(0x08);
   lcdwc(0x01);
   lcdwc(0x06);
   lcdwc(0x0c);
}
////////////////////////////////////////////////////////////////////
void lcdwda(unsigned int x,unsigned int y, char *s)
{  YPOS=y;
   for(XPOS=x;XPOS<16;XPOS++)
   {  lcdpos();
      lcdwd(*s);
      s++;
      delay(4000);
   }
}
////////////////////////////////////////////////////
void main(void)
{   
  //  unsigned int i;
 	
	InitSysCtrl();			//初始化系统

	DINT;				//关中断 
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//初始化PIE控制寄存器
	InitPieVectTable();		//初始化PIE参数表 
	InitPeripherals();		//初始化外设寄存器 
	InitGpio();				//初始化IO口

	EINT;				//Enable INTM
	ERTM;				//Enable DBGM
	lcdreset();
    lcdwda(0,0,"  www.00ic.com  ");  
    lcdwda(0,1,"I love TOP2812!!");    
} 	

	
void ldelay(unsigned int k)
{
	while(k>0)
	{
		k--;
		delay(500);
	}
}	

void delay(unsigned int t)
{
	while(t>0)
		t--;
}



	
