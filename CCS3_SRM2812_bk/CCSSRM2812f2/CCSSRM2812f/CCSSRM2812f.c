//ADʵ�飬����ȫΪ0��δ���ⲿ�źš�
#include "DSP28_Device.h"
#include "srm.h"

#include "System.h"
#include "typedefs.h"

float	ADResult[16];
unsigned int k=0;

float	adclo=0.0;

int count=0;
int slice=0;
int old_count=0;
int Update_Velocity=0;
int Toggle_LED=0;
int Msmt_Update=0;
anSRM_struct SRM;
int LEDvalue;

int iTest;
int simu6pos[6]={0x2,0x3,0x1,0x5,0x4,0x6};//simulate the postion signal
int simu6count;

unsigned int i;//for key input 


interrupt void ad(void);
interrupt void EvbCAP4ISR_INT(void);
interrupt void EvbCAP5ISR_INT(void);
interrupt void EvbCAP6ISR_INT(void);

void main(void)
{
	InitSysCtrl();			//��ʼ��ϵͳ

	DINT;					//���ж� 
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();			//��ʼ��PIE���ƼĴ���
	InitPieVectTable();		//��ʼ��PIE������ 

	EALLOW;	
	PieVectTable.ADCINT=&ad;
	PieVectTable.CAPINT4=&EvbCAP4ISR_INT;
	PieVectTable.CAPINT5=&EvbCAP5ISR_INT;
	PieVectTable.CAPINT6=&EvbCAP6ISR_INT;

	EDIS;   

    InitGpio();
	InitAdc();				//��ʼ��ADC

	InitEv();
   	
	EvbRegs.EVBIFRC.bit.CAP4INT = 1;
	EvbRegs.EVBIFRC.bit.CAP5INT = 1;
	EvbRegs.EVBIFRC.bit.CAP6INT = 1;
	EvbRegs.EVBIMRC.bit.CAP4INT = 1;
	EvbRegs.EVBIMRC.bit.CAP5INT = 1;
	EvbRegs.EVBIMRC.bit.CAP6INT = 1;
	
//	PieCtrl.PIEIFR5.bit.INTx5=0;//CAP4 IFR
//	PieCtrl.PIEIFR5.bit.INTx6=0;
//	PieCtrl.PIEIFR5.bit.INTx7=0;

	PieCtrl.PIEIER5.bit.INTx5 = 1;//CAP4 IER
	PieCtrl.PIEIER5.bit.INTx6 = 1;//CAP5
	PieCtrl.PIEIER5.bit.INTx7 = 1;//CAP6

	IER |= M_INT5;  // ʹ�� CPU INT 5	//EV CAP

	PieCtrl.PIEIER1.bit.INTx6 = 1;//ADCINT enable
	IER |= M_INT1;			// Enable INT14 which is connected to CPU-Timer 2:

	EINT;					// Enable INTM
	ERTM;					// Enable DBGM
	EvaRegs.T1CON.bit.TENABLE=1;
	EvbRegs.T3CON.bit.TENABLE=1;
	EvbRegs.T4CON.bit.TENABLE=1;

	for(;;)
	{
		KickDog();
		if(k>=5000)
		{
/*-----------------------------**
** 			test the LEDoutput 
attention  **
**-----------------------------*/
			GpioDataRegs.GPATOGGLE.bit.GPIOA12=1;//output led

/*------------------------------**
** 			test the CAP module 
attention**
**------------------------------*/
			GpioDataRegs.GPATOGGLE.bit.GPIOA8=1;//test the CAP 4
			GpioDataRegs.GPATOGGLE.bit.GPIOA9=1;//test the CAP 5
			GpioDataRegs.GPATOGGLE.bit.GPIOA10=1;//test the CAP 6

			k=0;
			
/*------------------------------**
** 			test the EVB PWM Compare module 
attention**
**------------------------------*/
			EvbRegs.CMPR4 = EvbRegs.CMPR4 ^ 750;//���ñȽϼĴ���
			EvbRegs.CMPR5 = 1499;
			EvbRegs.CMPR6 = EvbRegs.CMPR6 ^ 375;//test the PWM1-6 output,failed??
		}
	}
} 	

interrupt void ad(void)
{
	IFR=0x0000;
//	PieCtrl.PIEIFR1.all = 0;
//	PieCtrl.PIEACK.all=0xffff;

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

	PieCtrl.PIEACK.all = 0x0001;

	AdcRegs.ADC_ST_FLAG.bit.INT_SEQ1_CLR=1;
//	AdcRegs.ADCTRL2.bit.SOC_SEQ1=1;			//���������öϵ�
	AdcRegs.ADCTRL2.bit.RST_SEQ1=1;//rest the SEQ1
	EINT;
}



void EvbCAP4ISR_INT(void)
{
	int capdata1;
	NOP;
	capdata1 = EvbRegs.CAP4FIFO;
	 
	EvbRegs.EVBIFRC.bit.CAP4INT = 1;


	PieCtrl.PIEACK.all = 0x0010;
//need to add some commands to cleare IFRs
}


void EvbCAP5ISR_INT(void)
{
	int capdata1;
	NOP;
	capdata1 = EvbRegs.CAP5FIFO;


	EvbRegs.EVBIFRC.bit.CAP5INT = 1;


	PieCtrl.PIEACK.all = 0x0010;
//need to add some commands to cleare IFRs
}



void EvbCAP6ISR_INT(void)
{
	int capdata1;
	NOP;
	capdata1 = EvbRegs.CAP6FIFO;
	 

	EvbRegs.EVBIFRC.bit.CAP6INT = 1;

	PieCtrl.PIEACK.all = 0x0010;
//need to add some commands to cleare IFRs
}


