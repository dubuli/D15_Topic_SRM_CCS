/***************************************************************************/
/***    This File is for Global Setup of F281x DSP Initializing          ***/
/***                                                                     ***/
/***************************************************************************/

//---------------------------------------------------------------------------
// User To Select Target Device:
#define   DSP28_F2810   (0)
#define   DSP28_F2812   (1)

//---------------------------------------------------------------------------
// Common CPU Definitions:

extern cregister volatile unsigned int IFR ;
extern cregister volatile unsigned int IER ;

#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define  EALLOW asm(" EALLOW")
#define  EDIS   asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")
#define	 NOP	  asm(" NOP")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT00    0x0001
#define BIT01    0x0002
#define BIT02    0x0004
#define BIT03    0x0008
#define BIT04    0x0010
#define BIT05    0x0020
#define BIT06    0x0040
#define BIT07    0x0080
#define BIT08    0x0100
#define BIT09    0x0200
#define BIT10    0x0400
#define BIT11    0x0800
#define BIT12    0x1000
#define BIT13    0x2000
#define BIT14    0x4000
#define BIT15    0x8000

#define FALSE	  (0)
#define TRUE	  (1)

#define NULL	(void *)0
#define HIGH	   1
#define LOW		   0
#define LF		   0x0A	 // Line feed
#define CR		   0x0D	 // Carrage return

//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use Following Data Type Size
// Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:

#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES

typedef char             Sint08  ;
typedef int              Sint16  ;
typedef long             Sint32  ;
typedef unsigned char    Uint08  ;
typedef unsigned int     Uint16  ;
typedef unsigned long    Uint32  ;
typedef float            float32 ;
typedef long double      float64 ;
#endif


#define	GetHiByte(val)		((val>>8)&0xff)
#define	GetLoByte(val)		(val&0xff)
#define	SetHiByte(val)		((val<<8)&0xff00)

#define	BIT_MASK(x)			(1 << (x))
#define GetBit(val, bit)	(((val) & BIT_MASK(bit))>>(bit))
#define	SetBit(val, bit)	((val) |= BIT_MASK(bit))
#define	ClearBit(val, bit)	((val) &= ~BIT_MASK(bit))
#define	ToggleBit(val, bit)	((val) ^=BIT_MASK(bit))

#define	CHK_BIT(x, bit)		((x) & (bit))
#define	SET_BIT(x, bit)		((x) |= (bit))
#define	CLR_BIT(x, bit)		((x) &= ~(bit))
#define	TOGGLE_BIT(x, bit)	((x) ^= (bit))

#define CPU_RATE    6.667L   // for a 150MHz CPU clock speed (SYSCLKOUT)
#define DELAY_US(A) DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)

