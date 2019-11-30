//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_Spi.c
//
// TITLE:	DSP28 SPI Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//###########################################################################

#include "DSP28_Device.h"

//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSpi(void)
{
	// Initialize SPI-A:
	EALLOW;
	GpioMuxRegs.GPFMUX.all = 0x000F;
	EDIS;

	SpiaRegs.SPICCR.all = 0x0a;///进入初始状态，数据在上升沿输出，自测禁止，11位数据模式
	
	SpiaRegs.SPICTL.all = 0x06;   //主动模式，禁止中断
	
	SpiaRegs.SPIBRR = 0x1D;//波特率 = LSPCLK/（SPIBRR+1）= 30/30 = 1M
	
	SpiaRegs.SPICCR.all = 0x8a; //退出初始状态
	

//	PieCtrl.PIEIER6.bit.INTx1 = 1;
//	PieCtrl.PIEIER6.bit.INTx2 = 1;
	//tbd...
	//tbd...
	
}

unsigned int Spi_TxReady(void)
{
	unsigned int i;
	if(SpiaRegs.SPISTS.bit.BUFFULL_FLAG == 1)
	{
		i = 0;
	}
	else
	{
		i = 1;
	}
	return(i);
}

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

interrupt void SPIRXINTA_ISR(void);   // SPI
interrupt void SPITXINTA_ISR(void);    // SPI
	
//===========================================================================
// No more.
//===========================================================================
