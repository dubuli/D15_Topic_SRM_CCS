
#include "DSP28_Device.h"

unsigned int *LedADDR  = (unsigned int *) 0x2800;	//8����������ܼĴ�����ַ

unsigned int Count,Flag;
/////////////////��Ӧλ�͵�ƽ������λ���������
const	Uint16	LedCode[9]={0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE,0xFF};

interrupt void ISRTimer0(void);
	 	
void main(void)
{
	InitSysCtrl();					//��ʼ��ϵͳ

	DINT;						//���ж�
	IER = 0x0000;
	IFR = 0x0000;

	InitPieCtrl();					//��ʼ��PIE
	InitPieVectTable();				//��ʼ��PIE�ж�ʸ����
	InitPeripherals();				//��ʼ������
    InitGpio();
	EALLOW;	
	PieVectTable.TINT0 = &ISRTimer0;
	EDIS;   
	
 	Count = 0;					//��ʼ������
    Flag=0;
	ConfigCpuTimer(&CpuTimer0, 10, 1000000);	//����CPU
 	StartCpuTimer0();
    
	IER |= M_INT1;					//���ж�
	PieCtrl.PIEIER1.bit.INTx7=1;

	EINT;						// ����INTM
	ERTM;						// ����DBGM

	*LedADDR = 0x00;					// ����ȫ��8��LED��
	for(;;)
	{	;	}

} 	

interrupt void ISRTimer0(void)
{
	PieCtrl.PIEACK.bit.ACK7=1;
	*LedADDR = LedCode[Count];			//���ε����ƣ�����Ӧλ�͵�ƽ
	if (Flag==0) Count++; else Count--;
	if (Count>=8)//ѭ��	
	{
	   Flag=1;  }
	if (Count<=0)//ѭ��	
	{
	   Flag=0;
	   }		
}

