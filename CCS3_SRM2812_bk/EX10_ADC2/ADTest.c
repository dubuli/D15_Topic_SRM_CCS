//ADʵ�飬����ȫΪ0��δ���ⲿ�źš�
#include "DSP28_Device.h"

float	ADResult[16];
unsigned int k=0;
float	adclo=0.0;

//interrupt void ad(void);

void main(void)
{
	InitSysCtrl();			//��ʼ��ϵͳ

	DINT;					//���ж� 
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//��ʼ��PIE���ƼĴ���
	InitPieVectTable();		//��ʼ��PIE������ 

//	EALLOW;	
//	PieVectTable.ADCINT=&ad;
//	EDIS;   
    
	InitAdc();				//��ʼ��ADC

	EvaRegs.T1CON.bit.TMODE=2;
   	EvaRegs.T1CON.bit.TPS=1;
	EvaRegs.T1CON.bit.TENABLE=0;
	EvaRegs.T1CON.bit.TCLKS10=0;
	EvaRegs.GPTCONA.bit.T1TOADC=2;
	EvaRegs.EVAIMRA.bit.T1PINT=0;
	EvaRegs.EVAIFRA.bit.T1PINT=1;
	EvaRegs.T1PR=0x0ea5;
	EvaRegs.T1CNT=0;


	IER |= M_INT1;			// Enable INT14 which is connected to CPU-Timer 2:

	EINT;					// Enable INTM
	ERTM;					// Enable DBGM
	
	EvaRegs.T1CON.bit.TENABLE=1;
/* 	while(AdcRegs.ADC_ST_FLAG.bit.SEQ1_BSY==0) */
/* 	{			                               */
/* 		AdcRegs.ADCTRL2.bit.SOC_SEQ1=1;        */
/* 	}	                                       */

	for(;;)
	{
		KickDog();
	}
} 	

 interrupt void ad(void)                                   
{                                                         
 	IFR=0x0000;                                              
	PieCtrl.PIEIFR1.all = 0;                             
 	PieCtrl.PIEACK.all=0xffff;                               
 	k++;                                                     
 	ADResult[0]=((AdcRegs.RESULT0>>4)*3)/4095.0+adclo;       
 	ADResult[1]=((AdcRegs.RESULT1>>4)*3)/4095.0+adclo;     
 	ADResult[2]=((AdcRegs.RESULT2>>4)*3)/4095.0+adclo;       
 	ADResult[3]=((AdcRegs.RESULT3>>4)*3)/4095.0+adclo;       
 	ADResult[4]=((AdcRegs.RESULT4>>4)*3)/4095.0+adclo;       
 	ADResult[5]=((AdcRegs.RESULT5>>4)*3)/4095.0+adclo;       
 	ADResult[6]=((AdcRegs.RESULT6>>4)*3)/4095.0+adclo;       
 	ADResult[7]=((AdcRegs.RESULT7>>4)*3)/4095.0+adclo;       
 	ADResult[8]=((AdcRegs.RESULT8>>4)*3)/4095.0+adclo;       
 	ADResult[9]=((AdcRegs.RESULT9>>4)*3)/4095.0+adclo;       
 	ADResult[10]=((AdcRegs.RESULT10>>4)*3)/4095.0+adclo;     
 	ADResult[11]=((AdcRegs.RESULT11>>4)*3)/4095.0+adclo;     
 	ADResult[12]=((AdcRegs.RESULT12>>4)*3)/4095.0+adclo;     
 	ADResult[13]=((AdcRegs.RESULT13>>4)*3)/4095.0+adclo;     
 	ADResult[14]=((AdcRegs.RESULT14>>4)*3)/4095.0+adclo;     
 	ADResult[15]=((AdcRegs.RESULT15>>4)*3)/4095.0+adclo;     
 	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ1_CLR=1;                  
 	AdcRegs.ADCTRL2.bit.SOC_SEQ1=1;			//���������öϵ� 
 	EINT;                                                    
 }                                                         
