/***********************************************************
* File: C240.H *
* TMS320x240 Test Bed Code *
* Texas Instruments, Inc. *
* Copyright (c) 1996 Texas Instruments Inc. *
* 11/05/96 Version 1.0 *
* Jeff Crankshaw *
* *
* TMS320C240 Peripheral Register Addresses *
* *
***********************************************************/
//#ifndef c240_h
//#define c240_h
#include "typedefs.h"
/*----------------------------------------------------------*/
/* definitions of I/O space macros */
/*----------------------------------------------------------*/
//#define STR(x) #x
//#define OUTMAC(address,data) \
//	asm(" LDPK _"STR(data)); \
//	asm(" OUT _"STR(data) ", " STR(address))
//#define INMAC(address,data) \
//	asm(" LDPK _"STR(data)); \
//	asm(" IN _"STR(data) ", " STR(address))
//#define LED_LOC 000ch /* F240 EVM I/O space location for LEDs */
///*----------------------------------------------------------*/
///* definitions of CPU core registers */
///*----------------------------------------------------------*/
//#define IMR_REG (( PORT )0x0004 )
//#define IFR_REG (( PORT )0x0006 )
///*----------------------------------------------------------*/
///* External Memory Interface Registers */
///*----------------------------------------------------------*/
//#define WSGR 0x0ffff
///* Wait State Generator Register */
///*----------------------------------------------------------*/
///* System Module Registers */
///*----------------------------------------------------------*/
//#define SYSCR (( PORT )0x07018) /* System Module Control Register */
//#define SYSSR (( PORT )0x0701A) /* System Module Status Register */
//#define SYSIVR (( PORT )0x0701E) /* System Interrupt Vector Register */
//#define XINT1_CR (( PORT )0x07070) /* Int1 (type A) Control reg */
//#define NMI_CR (( PORT )0x07072) /* Non maskable Int (type A) Control reg */
//#define XINT2_CR (( PORT )0x07078) /* Int2 (type C) Control reg */
//#define XINT3_CR (( PORT )0x0707A) /* Int3 (type C) Control reg */
//#define PDPINT_CR (( PORT )0x0742C) /* Power Drive Protection Int cntl reg */
///* System Interrupt Vector Register - Address offsets */
//#define PHANTOM_INT_VECTOR 0x00
//#define NMI_INT_VECTOR 0x02
//#define XINT1_INT_VECTOR 0x01
//#define XINT2_INT_VECTOR 0x11
//#define XINT3_INT_VECTOR 0x1f
//#define SPI_INT_VECTOR 0x05
//#define SCI_RX_INT_VECTOR 0x06
//#define SCI_TX_INT_VECTOR 0x07
//#define RTI_INT_VECTOR 0x10
//#define PDP_INT_VECTOR 0x20
//#define EV_CMP1_INT_VECTOR 0x21
//#define EV_CMP2_INT_VECTOR 0x22
//#define EV_CMP3_INT_VECTOR 0x23
//#define EV_SCMP1_INT_VECTOR 0x24
//#define EV_SCMP2_INT_VECTOR 0x25
//#define EV_SCMP3_INT_VECTOR 0x26
//#define EV_T1PER_INT_VECTOR 0x27
//#define EV_T1CMP_INT_VECTOR 0x28
//#define EV_T1UF_INT_VECTOR 0x29
//#define EV_T1OF_INT_VECTOR 0x2a
//#define EV_T2PER_INT_VECTOR 0x2b
//#define EV_T2CMP_INT_VECTOR 0x2c
//#define EV_T2UF_INT_VECTOR 0x2d
//#define EV_T2OF_INT_VECTOR 0x2e
//#define EV_T3PER_INT_VECTOR 0x2f
//#define EV_T3CMP_INT_VECTOR 0x30
//#define EV_T3UF_INT_VECTOR 0x31
//#define EV_T3OF_INT_VECTOR 0x32
//#define EV_CAP1_INT_VECTOR 0x33
//#define EV_CAP2_INT_VECTOR 0x34
//#define EV_CAP3_INT_VECTOR 0x35
//#define EV_CAP4_INT_VECTOR 0x36
//#define AC2_INT_VECTOR 0x04
///*----------------------------------------------------------*/
///* Digital I/O Registers */
///*----------------------------------------------------------*/
//#define OCRA (( PORT )0x07090) /* Output Control Reg A */
//#define OCRB (( PORT )0x07092) /* Output Control Reg B */
//#define PADATDIR (( PORT )0x07098) /* I/O port A Data & Direction reg. */
//#define PBDATDIR (( PORT )0x0709A) /* I/O port B Data & Direction reg. */
//#define PCDATDIR (( PORT )0x0709C) /* I/O port C Data & Direction reg. */
///*-------------------------------------------------------------------------*/
///* Watch-Dog(WD) / Real Time Int(RTI) / Phase Lock Loop(PLL) Registers */
///*-------------------------------------------------------------------------*/
//#define RTICNTR (( PORT )0x07021) /* RTI Counter reg */
//#define WDTCNTR (( PORT )0x07023) /* WD Counter reg */
//#define WDTKEY (( PORT )0x07025) /* WD Key reg */
//#define RTICR (( PORT )0x07027) /* RTI Control reg */
//#define WDCR (( PORT )0x07029) /* WD Control reg */
//#define CKCR0 (( PORT )0x0702B) /* PLL control reg 1 */
//#define CKCR1 (( PORT )0x0702D) /* PLL control reg 2 */
///*----------------------------------------------------------*/
///* Analog-to-Digital Converter(ADC) registers */
///*----------------------------------------------------------*/
//#define ADCTRL1 (( PORT )0x07032) /* ADC Control & Status reg */
//#define ADCTRL2 (( PORT )0x07034) /* ADC Configuration reg */
//#define ADCFIFO1 (( PORT )0x07036) /* ADC Channel 1 Result Data */
//#define ADCFIFO2 (( PORT )0x07038) /* ADC Channel 2 Result Data */
///*----------------------------------------------------------*/
///* Serial Peripheral Interface (SPI) Registers */
///*----------------------------------------------------------*/
//#define SPICCR (( PORT )0x07040) /* SPI Config Control Reg */
//#define SPICTL (( PORT )0x07041) /* SPI Operation Control Reg */
//#define SPISTS (( PORT )0x07042) /* SPI Status Reg */
//#define SPIBRR (( PORT )0x07044) /* SPI Baud rate control reg */
//#define SPIEMU (( PORT )0x07046) /* SPI Emulation buffer reg */
//#define SPIBUF (( PORT )0x07047) /* SPI Serial Input buffer reg */
//#define SPIDAT (( PORT )0x07049) /* SPI Serial Data reg */
//#define SPIPC1 (( PORT )0x0704D) /* SPI Port control reg1 */
//#define SPIPC2 (( PORT )0x0704E) /* SPI Port control reg2 */
//#define SPIPRI (( PORT )0x0704F) /* SPI Priority control reg */
///*--------------------------------------------------------*/
///* Serial Communications Interface (SCI) Registers */
///*--------------------------------------------------------*/
//#define SCICCR (( PORT )0x07050) /* SCI Comms Control Reg */
//#define SCICTL1 (( PORT )0x07051) /* SCI Control Reg 1 */
//#define SCIHBAUD (( PORT )0x07052) /* SCI Baud rate control */
//#define SCILBAUD (( PORT )0x07053) /* SCI Baud rate control */
//#define SCICTL2 (( PORT )0x07054) /* SCI Control Reg 2 */
//#define SCIRXST (( PORT )0x07055) /* SCI Receive status reg */
//#define SCIRXEMU (( PORT )0x07056) /* SCI EMU data buffer */
//#define SCIRXBUF (( PORT )0x07057) /* SCI Receive data buffer */
//#define SCITXBUF (( PORT )0x07059) /* SCI Transmit data buffer */
//#define SCIPC1 (( PORT )0x0705D) /* SCI Port control reg1 */
//#define SCIPC2 (( PORT )0x0705E) /* SCI Port control reg2 */
//#define SCIPRI (( PORT )0x0705F) /* SCI Priority control reg */
//
///*--------------------------------------------------------*/
///* Event Manager (EV) Registers */
///*--------------------------------------------------------*/
//#define GPTCON (( PORT )0x07400) /* General Timer Controls */
//#define T1CNT (( PORT )0x07401) /* T1 Counter Register */
//#define T1CMP (( PORT )0x07402) /* T1 Compare Register */
//#define T1PER (( PORT )0x07403) /* T1 Period Register */
//#define T1CON (( PORT )0x07404) /* T1 Control Register */
//#define T2CNT (( PORT )0x07405) /* T2 Counter Register */
//#define T2CMP (( PORT )0x07406) /* T2 Compare Register */
//#define T2PER (( PORT )0x07407) /* T2 Period Register */
//#define T2CON (( PORT )0x07408) /* T2 Control Register */
//#define T3CNT (( PORT )0x07409) /* T3 Counter Register */
//#define T3CMP (( PORT )0x0740a) /* T3 Compare Register */
//#define T3PER (( PORT )0x0740b) /* T3 Period Register */
//#define T3CON (( PORT )0x0740c) /* T3 Control Register */
//#define COMCON (( PORT )0x07411) /* Compare Unit Control */
//#define ACTR (( PORT )0x07413) /* Full Compare Unit Output Action Ctrl */
//#define SACTR (( PORT )0x07414) /* Simple Comp Unit Output Action Ctrl */
//#define DBTCON (( PORT )0x07415) /* Dead Band Timer Control */
//#define CMPR1 (( PORT )0x07417) /* Full Compare Channel 1 Threshold */
//#define CMPR2 (( PORT )0x07418) /* Full Compare Channel 2 Threshold */
//#define CMPR3 (( PORT )0x07419) /* Full Compare Channel 3 Threshold */
//#define SCMPR1 (( PORT )0x0741a) /* Simple Comp Channel 1 Threshold */
//#define SCMPR2 (( PORT )0x0741b) /* Simple Comp Channel 2 Threshold */
//#define SCMPR3 (( PORT )0x0741c) /* Simple Comp Channel 3 Threshold */
//#define CAPCON (( PORT )0x07420) /* Capture Unit Control */
//#define CAPFIFO (( PORT )0x07422) /* FIFO1-4 Status Register */
//#define FIFO1 (( PORT )0x07423) /* Capture Channel 1 FIFO Top */
//#define FIFO2 (( PORT )0x07424) /* Capture Channel 2 FIFO Top */
//#define FIFO3 (( PORT )0x07425) /* Capture Channel 3 FIFO Top */
//#define FIFO4 (( PORT )0x07426) /* Capture Channel 4 FIFO Top */
//#define IMRA (( PORT )0x0742c) /* Group A Interrupt Mask Register */
//#define IMRB (( PORT )0x0742d) /* Group B Interrupt Mask Register */
//#define IMRC (( PORT )0x0742e) /* Group C Interrupt Mask Register */
//#define IFRA (( PORT )0x0742f) /* Group A Interrupt Flag Register */
//#define IFRB (( PORT )0x07430) /* Group B Interrupt Flag Register */
//#define IFRC (( PORT )0x07431) /* Group C Interrupt Flag Register */
//#define IVRA (( PORT )0x07432) /* Group A Int. Vector Offset Register */
//#define IVRB (( PORT )0x07433) /* Group B Int. Vector Offset Register */
//#define IVRC (( PORT )0x07434) /* Group C Int. Vector Offset Register */
//#endif
