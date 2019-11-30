/*File: MAIN.C---------------------*/
//#include "c240.h"
#include "srm.h"
#include "DSP281x_Device.h"
#include "System.h"
#include "typedefs.h"
/*---------------------------------------------------------*/
/*GLOBAL VARIABLE DECLARATIONS */
/*---------------------------------------------------------*/
void WriteLED(unsigned char data);					//送给数码管的数据函数
unsigned long int a;

Uint16	SpiCode[]={0x7E7E,0x2929,0x2c2c,0x6666,0xa4a4,0xa0a0,0x3e3e,0x2020,0x2424,0x2222,0xe0e0,0xb1b1,0x6868,0xa1a1,0xa3a3,0xffff,0xdfdf};


/*-------------------------------------------------------*/
/*MAIN PROGRAM */
/*-------------------------------------------------------*/
/****************************************************************************
*
*文件名：DSP28_Spi.c
*
*功  能：对2812的SPI模块进行初始化
*
*作  者: likyo from hellodsp
*
****************************************************************************/

#include "DSP281x_Device.h"

/****************************************************************************
*
*名    称：InitSpi()
*
*功    能：该函数对2812的SPI进行初始化
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitSpi(void)
{

    /*配置控制寄存器设置*/
	SpiaRegs.SPICCR.all = 0x07;///进入初始状态，数据在上升沿输出，自测禁止，8位数据模式
	
	/*操作控制寄存器设置*/
	SpiaRegs.SPICTL.all = 0x06;///正常的SPI时钟方式,主动模式，使能发送,禁止中断
	
	/*波特率的设置*/
	SpiaRegs.SPIBRR = 0x7F;//波特率 = LSPCLK/（SPIBRR+1）= 30/30 = 1M
	
	SpiaRegs.SPICCR.all = 0x87; //退出初始状态
	
}

/****************************************************************************
*
*名    称：Spi_TxReady()
*
*功    能：查询SPISTS寄存器的BUFFULL_FLAG，来确认发送准备是否就绪
*
*入口参数：无
*
*出口参数：i，即TXRDY的状态
*          1：发送准备已经就绪
*          0：发送准备尚未就绪
*       
****************************************************************************/

unsigned int Spi_TxReady(void)
{
	unsigned int i;
	if(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1)//根据SPI的状态寄存器的缓冲标志位是否满,来确定发送函数是否可进行,学习时自己看下即可
	{
		i = 0;
	}
	else
	{
		i = 1;
	}
	return(i);
}

/****************************************************************************
*
*名    称：Spi_RxReady()
*
*功    能：查询SPISTS寄存器的INT_FLAG位，来确认接收准备是否就绪
*
*入口参数：无
*
*出口参数：i，即RXRDY的状态
*          1：接收准备已经就绪
*          0：接收准备尚未就绪
*       
****************************************************************************/

unsigned int Spi_RxReady(void)
{
	unsigned int i;
	if(SpiaRegs.SPISTS.bit.INT_FLAG == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);	
}

/*SPI中断服务寄存器.此实验未使用*/

interrupt void SPIRXINTA_ISR(void);   // SPI
interrupt void SPITXINTA_ISR(void);    // SPI


void InitGpio(void)
{
  EALLOW;
    
  ///设置SPI口外设功能
  GpioMuxRegs.GPFMUX.bit.SPISIMOA_GPIOF0 = 1;//选择SPISIMO引脚为功能引脚
  GpioMuxRegs.GPFMUX.bit.SPISOMIA_GPIOF1 = 1;
  GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2  = 1;//选择SPICLK引脚为功能引脚
  GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3=0;   //选择SPISTE引脚为通用I/O



 /* GpioMuxRegs.GPFDIR.bit.GPIOF0=1;   */
/* 	GpioMuxRegs.GPFDIR.bit.GPIOF1=1;    */
/* 	GpioMuxRegs.GPFDIR.bit.GPIOF2=1;    */
  GpioMuxRegs.GPFDIR.bit.GPIOF3=1; //方向为输出，低电平时选中74HC595
     	 
  EDIS;
}	


void main() 
{
	int k;
	int l;
	k=0;
	l=0;
    
	/*初始化系统*/
	InitSysCtrl();
	
	/* 关中断 */
	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	
	/* 初始化PIE控制寄存器 */
	InitPieCtrl();
	
	/* 初始化PIE参数表 */
	InitPieVectTable();	
	
	/* 初始化外设寄存器 */
	InitGpio();

	InitSpi();
   


   SpiaRegs.SPIFFTX.all=0xa040;
	SpiaRegs.SPIFFRX.all=0x205f;
	SpiaRegs.SPIFFCT.all=0;


	/*设置CPU*/
	
	EINT; // 开全局中断
	ERTM; // 开实时中断

	for(;;)
	 {  
	    for(k=0x1001;k<0x1333;k++)			//循环发送16个数据
      	{
			 GpioDataRegs.GPFDAT.bit.GPIOF0=1; //输出低电平选中74HC595 
			 k=0x66;
			if(SpiaRegs.SPISTS.bit.BUFFULL_FLAG==0)
			{
				SpiaRegs.SPITXBUF= (k);
			}


//			while(SpiaRegs.SPIFFRX.bit.RXFFST!=1)
			while(SpiaRegs.SPISTS.bit.BUFFULL_FLAG==1)
			{
			}
			while(SpiaRegs.SPISTS.bit.INT_FLAG==0)
			{
			}
			l=SpiaRegs.SPIRXBUF;
			GpioDataRegs.GPFDAT.bit.GPIOF0=0;

/*       	   GpioDataRegs.GPFDAT.bit.GPIOF0=0; //输出低电平选中74HC595 */
/* 			GpioDataRegs.GPFDAT.bit.GPIOF2=0;                            */
/* 			GpioDataRegs.GPFDAT.bit.GPIOF1=0;                            */
/* 			GpioDataRegs.GPFDAT.bit.GPIOF3=0;                            */
/*       	   //WriteLED(SpiCode[k]);	//发送数据函数                   */
/* 		  // for(a=0;a<500;a++);   //延时                                */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF0=1;                          */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF2=1;                          */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF1=1;                          */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF3=1;	                         */
		//   for(a=0;a<500;a++);
/* 			GpioDataRegs.GPFDAT.bit.GPIOF3=0; //输出低电平选中74HC595 */
/*       	   WriteLED(SpiCode[k]);	//发送数据函数                */
/* 		   for(a=0;a<500000;a++);   //延时	                          */
        }
	 }

}

/****************************************************************************
*
*名    称：WriteLED()
*
*功    能：SPI发送数据
*
*入口参数：char data，需要发送的数据
*
*出口参数：无
*
****************************************************************************/
void WriteLED(unsigned char data)
{   
   if(Spi_TxReady() == 1)		//当检测到SPI发送准备信号致1时,开始发送数据
   {   
      SpiaRegs.SPITXBUF = data;	//把数据写如SPI发送缓冲区
   }

   while(Spi_TxReady()!=1);		//一直等待直到数据发送完成
   {
   }  
   
   GpioDataRegs.GPFDAT.bit.GPIOF3=1; //退出时关片选
}

