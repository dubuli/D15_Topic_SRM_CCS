/*File: MAIN.C---------------------*/
//#include "c240.h"
#include "srm.h"
#include "DSP281x_Device.h"
#include "System.h"
#include "typedefs.h"
/*---------------------------------------------------------*/
/*GLOBAL VARIABLE DECLARATIONS */
/*---------------------------------------------------------*/
void WriteLED(unsigned char data);					//�͸�����ܵ����ݺ���
unsigned long int a;

Uint16	SpiCode[]={0x7E7E,0x2929,0x2c2c,0x6666,0xa4a4,0xa0a0,0x3e3e,0x2020,0x2424,0x2222,0xe0e0,0xb1b1,0x6868,0xa1a1,0xa3a3,0xffff,0xdfdf};


/*-------------------------------------------------------*/
/*MAIN PROGRAM */
/*-------------------------------------------------------*/
/****************************************************************************
*
*�ļ�����DSP28_Spi.c
*
*��  �ܣ���2812��SPIģ����г�ʼ��
*
*��  ��: likyo from hellodsp
*
****************************************************************************/

#include "DSP281x_Device.h"

/****************************************************************************
*
*��    �ƣ�InitSpi()
*
*��    �ܣ��ú�����2812��SPI���г�ʼ��
*
*��ڲ�������
*
*���ڲ�������
*
****************************************************************************/

void InitSpi(void)
{

    /*���ÿ��ƼĴ�������*/
	SpiaRegs.SPICCR.all = 0x07;///�����ʼ״̬��������������������Բ��ֹ��8λ����ģʽ
	
	/*�������ƼĴ�������*/
	SpiaRegs.SPICTL.all = 0x06;///������SPIʱ�ӷ�ʽ,����ģʽ��ʹ�ܷ���,��ֹ�ж�
	
	/*�����ʵ�����*/
	SpiaRegs.SPIBRR = 0x7F;//������ = LSPCLK/��SPIBRR+1��= 30/30 = 1M
	
	SpiaRegs.SPICCR.all = 0x87; //�˳���ʼ״̬
	
}

/****************************************************************************
*
*��    �ƣ�Spi_TxReady()
*
*��    �ܣ���ѯSPISTS�Ĵ�����BUFFULL_FLAG����ȷ�Ϸ���׼���Ƿ����
*
*��ڲ�������
*
*���ڲ�����i����TXRDY��״̬
*          1������׼���Ѿ�����
*          0������׼����δ����
*       
****************************************************************************/

unsigned int Spi_TxReady(void)
{
	unsigned int i;
	if(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1)//����SPI��״̬�Ĵ����Ļ����־λ�Ƿ���,��ȷ�����ͺ����Ƿ�ɽ���,ѧϰʱ�Լ����¼���
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
*��    �ƣ�Spi_RxReady()
*
*��    �ܣ���ѯSPISTS�Ĵ�����INT_FLAGλ����ȷ�Ͻ���׼���Ƿ����
*
*��ڲ�������
*
*���ڲ�����i����RXRDY��״̬
*          1������׼���Ѿ�����
*          0������׼����δ����
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

/*SPI�жϷ���Ĵ���.��ʵ��δʹ��*/

interrupt void SPIRXINTA_ISR(void);   // SPI
interrupt void SPITXINTA_ISR(void);    // SPI


void InitGpio(void)
{
  EALLOW;
    
  ///����SPI�����蹦��
  GpioMuxRegs.GPFMUX.bit.SPISIMOA_GPIOF0 = 1;//ѡ��SPISIMO����Ϊ��������
  GpioMuxRegs.GPFMUX.bit.SPISOMIA_GPIOF1 = 1;
  GpioMuxRegs.GPFMUX.bit.SPICLKA_GPIOF2  = 1;//ѡ��SPICLK����Ϊ��������
  GpioMuxRegs.GPFMUX.bit.SPISTEA_GPIOF3=0;   //ѡ��SPISTE����Ϊͨ��I/O



 /* GpioMuxRegs.GPFDIR.bit.GPIOF0=1;   */
/* 	GpioMuxRegs.GPFDIR.bit.GPIOF1=1;    */
/* 	GpioMuxRegs.GPFDIR.bit.GPIOF2=1;    */
  GpioMuxRegs.GPFDIR.bit.GPIOF3=1; //����Ϊ������͵�ƽʱѡ��74HC595
     	 
  EDIS;
}	


void main() 
{
	int k;
	int l;
	k=0;
	l=0;
    
	/*��ʼ��ϵͳ*/
	InitSysCtrl();
	
	/* ���ж� */
	DINT;
	IER = 0x0000;
	IFR = 0x0000;
	
	/* ��ʼ��PIE���ƼĴ��� */
	InitPieCtrl();
	
	/* ��ʼ��PIE������ */
	InitPieVectTable();	
	
	/* ��ʼ������Ĵ��� */
	InitGpio();

	InitSpi();
   


   SpiaRegs.SPIFFTX.all=0xa040;
	SpiaRegs.SPIFFRX.all=0x205f;
	SpiaRegs.SPIFFCT.all=0;


	/*����CPU*/
	
	EINT; // ��ȫ���ж�
	ERTM; // ��ʵʱ�ж�

	for(;;)
	 {  
	    for(k=0x1001;k<0x1333;k++)			//ѭ������16������
      	{
			 GpioDataRegs.GPFDAT.bit.GPIOF0=1; //����͵�ƽѡ��74HC595 
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

/*       	   GpioDataRegs.GPFDAT.bit.GPIOF0=0; //����͵�ƽѡ��74HC595 */
/* 			GpioDataRegs.GPFDAT.bit.GPIOF2=0;                            */
/* 			GpioDataRegs.GPFDAT.bit.GPIOF1=0;                            */
/* 			GpioDataRegs.GPFDAT.bit.GPIOF3=0;                            */
/*       	   //WriteLED(SpiCode[k]);	//�������ݺ���                   */
/* 		  // for(a=0;a<500;a++);   //��ʱ                                */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF0=1;                          */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF2=1;                          */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF1=1;                          */
/* 		   GpioDataRegs.GPFTOGGLE.bit.GPIOF3=1;	                         */
		//   for(a=0;a<500;a++);
/* 			GpioDataRegs.GPFDAT.bit.GPIOF3=0; //����͵�ƽѡ��74HC595 */
/*       	   WriteLED(SpiCode[k]);	//�������ݺ���                */
/* 		   for(a=0;a<500000;a++);   //��ʱ	                          */
        }
	 }

}

/****************************************************************************
*
*��    �ƣ�WriteLED()
*
*��    �ܣ�SPI��������
*
*��ڲ�����char data����Ҫ���͵�����
*
*���ڲ�������
*
****************************************************************************/
void WriteLED(unsigned char data)
{   
   if(Spi_TxReady() == 1)		//����⵽SPI����׼���ź���1ʱ,��ʼ��������
   {   
      SpiaRegs.SPITXBUF = data;	//������д��SPI���ͻ�����
   }

   while(Spi_TxReady()!=1);		//һֱ�ȴ�ֱ�����ݷ������
   {
   }  
   
   GpioDataRegs.GPFDAT.bit.GPIOF3=1; //�˳�ʱ��Ƭѡ
}

