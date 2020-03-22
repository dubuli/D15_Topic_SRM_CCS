#define	CPUCLK		150000000L
#define	LSPCLK		(CPUCLK/4)
//#define	BAUDRATE	115200L  
#define	BAUDRATE	9600L
#define	BRR_VAL		(LSPCLK/(8*BAUDRATE)-1)

interrupt void scia_tx_isr(void);
interrupt void scia_rx_isr(void);

void SetDi_WatcDog(void)       ;
void Setup_PLLclks(Uint16 val) ;
void Setup_CpuCtrl()       ;
void Setup_PCLKCRs(void)  ;
void Setup_PIEvect(void) ;
void Setup_CpuTmr0(void)    ;
void Setup_TimeISR(struct CPUTIMER_VARS *Timer, float Freq, float Period)  ;


// Start Timer:
#define START_CpuTmr0()  CpuTm0Regs.TCR.bit.TSS = 0

// Stop Timer:
#define StopCpuTimer0()   CpuTm0Regs.TCR.bit.TSS = 1

// Reload Timer With period Value:
#define ReloadCpuTimer0() CpuTm0Regs.TCR.bit.TRB = 1

// Read 32-Bit Timer Value:
#define ReadCpuTimer0Counter() CpuTm0Regs.TIM.all

// Read 32-Bit Period Value:
#define ReadCpuTimer0Period() CpuTm0Regs.PRD.all

// CpuTimer 1 and CpuTimer2 are reserved for DSP BIOS & other RTOS
// Do not use these two timers if you ever plan on integrating 
// DSP-BIOS or another realtime OS. 
//
// For this reason, the code to manipulate these two timers is
// commented out and not used in these examples.

// Start Timer:
//#define StartCpuTimer1()  CpuTimer1Regs.TCR.bit.TSS = 0
//#define StartCpuTimer2()  CpuTimer2Regs.TCR.bit.TSS = 0

// Stop Timer:
//#define StopCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 1
//#define StopCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 1

// Reload Timer With period Value:
//#define ReloadCpuTimer1() CpuTimer1Regs.TCR.bit.TRB = 1
//#define ReloadCpuTimer2() CpuTimer2Regs.TCR.bit.TRB = 1

// Read 32-Bit Timer Value:
//#define ReadCpuTimer1Counter() CpuTimer1Regs.TIM.all
//#define ReadCpuTimer2Counter() CpuTimer2Regs.TIM.all

// Read 32-Bit Period Value:
//#define ReadCpuTimer1Period() CpuTimer1Regs.PRD.all
//#define ReadCpuTimer2Period() CpuTimer2Regs.PRD.all

void KickDog(void)
{
    EALLOW;
    SysCtrRegs.WDKEY = 0x0055;
    SysCtrRegs.WDKEY = 0x00AA;
    EDIS;
}


// This function disables the watchdog timer.
void SetDi_WatcDog(void)
{
    EALLOW ;
    SysCtrRegs.WDCR = 0x0068 ;
    // WDFLAG = 0, WDDIS = 0, WDCHK = 101, WDPS = 000(SYSCLK/512)
    EDIS   ;
}


// This function initializes the PLLCR register.
void Setup_PLLclks(Uint16 val)
{
  volatile Uint16 iVol  ;   
   
  if (SysCtrRegs.PLLCR.bit.DIV != val)
  {
    EALLOW ;
    SysCtrRegs.PLLCR.bit.DIV = val;
    EDIS   ;
   
   // Optional: Wait for PLL to lock.
   // During this time the CPU will switch to OSCCLK/2 until the PLL is 
   // stable.  Once the PLL is stable the CPU will switch to the new PLL value. 
   //
   // This switch time is 131072 CLKIN cycles as of Rev C silicon.  
   //   
   // Code is not required to sit and wait for the PLL to lock.   
   // However, if the code does anything that is timing critical, 
   // and requires the correct clock be locked, then it is best to 
   // wait until this switching has completed.  
   
   // If this function is run from waitstated memory, then the loop count can
   // be reduced as long as the minimum switch time is still met. 

   // iVol is volatile so the compiler will not optimize this loop out
   //
   // The watchdog should be disabled before this loop, or fed within 
   // the loop.   
   
    SetDi_WatcDog() ;
   
   // Wait lock cycles.  
   // Note,  This loop is tuned to 0-waitstate RAM memory.  If this
   // function is run from wait-stated memory such as Flash or XINTF,
   // then the number of times through the loop can be reduced 
   // accordingly. 
    for(iVol= 0; iVol< ( (131072/2)/12 ); iVol++)  {  }
  
  }
}


// This function initializes the clocks to the peripheral modules.
// First the high and low clock prescalers are set
// Second the clocks are enabled to each peripheral.
// To reduce power, leave clocks to unused peripherals disabled
// Note: If a peripherals clock is not enabled then you cannot 
// read or write to the registers for that peripheral 

void Setup_PCLKCRs(void)
{
  EALLOW ;
  // HISPCP/LOSPCP prescale register settings, normally it will be set to default values
  SysCtrRegs.HISPCP.all = 0x0001 ;         //HISPCP=SYSCLKOUT/(HISPCP*2)             
  SysCtrRegs.LOSPCP.all = 0x0002 ;          // //LISPCP=SYSCLKOUT/(LISPCP*2)
   	
 // Peripheral clock enables set for the selected peripherals.   
  SysCtrRegs.PCLKCR.bit.EVAENCLK = 1   ;
  SysCtrRegs.PCLKCR.bit.EVBENCLK = 1   ;
  SysCtrRegs.PCLKCR.bit.SCIAENCLK = 1  ;
  SysCtrRegs.PCLKCR.bit.SCIBENCLK = 1  ;
  SysCtrRegs.PCLKCR.bit.MCBSPENCLK = 1 ;
  SysCtrRegs.PCLKCR.bit.SPIENCLK = 1   ;
  SysCtrRegs.PCLKCR.bit.ECANENCLK = 1  ;
  SysCtrRegs.PCLKCR.bit.ADCENCLK = 1   ;
  EDIS   ;
}


void Setup_CpuCtrl()
{
  // On F2812/F2810 TMX samples prior to rev C this initialization was 
  // required.  For Rev C and after this is no longer required
  
   SetDi_WatcDog()   ;   // Disable the Watchdog
   
   // Initialize the PLLCR to 10 Times
   Setup_PLLclks(10) ;   // System Clock = 15MHz*10/2 = 75MHz ,HISPCP=37.5MHZ,LISPCP=18.75MHZ

   // Initialize the peripheral clocks
   Setup_PCLKCRs()   ;
}

// This function initializes the PIE control registers to a known state.
void Setup_PIEctrl(void)
{
  // Disable Interrupts at the CPU level:
  DINT;

  // Disable the PIE
  PieCtrRegs.PIECRTL.bit.ENPIE = 0 ;

	// Clear all PIEIER registers:
	PieCtrRegs.PIEIER01.all = 0 ;
	PieCtrRegs.PIEIER02.all = 0 ;
	PieCtrRegs.PIEIER03.all = 0 ;	
	PieCtrRegs.PIEIER04.all = 0 ;
	PieCtrRegs.PIEIER05.all = 0 ;
	PieCtrRegs.PIEIER06.all = 0 ;
	PieCtrRegs.PIEIER07.all = 0 ;
	PieCtrRegs.PIEIER08.all = 0 ;
	PieCtrRegs.PIEIER09.all = 0 ;
	PieCtrRegs.PIEIER10.all = 0 ;
	PieCtrRegs.PIEIER11.all = 0 ;
	PieCtrRegs.PIEIER12.all = 0 ;

	// Clear all PIEIFR registers:
	PieCtrRegs.PIEIFR01.all = 0 ;
	PieCtrRegs.PIEIFR02.all = 0 ;
	PieCtrRegs.PIEIFR03.all = 0 ;	
	PieCtrRegs.PIEIFR04.all = 0 ;
	PieCtrRegs.PIEIFR05.all = 0 ;
	PieCtrRegs.PIEIFR06.all = 0 ;
	PieCtrRegs.PIEIFR07.all = 0 ;
	PieCtrRegs.PIEIFR08.all = 0 ;
	PieCtrRegs.PIEIFR09.all = 0 ;
	PieCtrRegs.PIEIFR10.all = 0 ;
	PieCtrRegs.PIEIFR11.all = 0 ;
	PieCtrRegs.PIEIFR12.all = 0 ;
}	

//---------------------------------------------------------------------------
// EnableInterrupts: 
//---------------------------------------------------------------------------
// This function enables the PIE module and CPU interrupts
//
void EnableInterrupts()
{

    // Enable the PIE
    PieCtrRegs.PIECRTL.bit.ENPIE = 1;
    		
	// Enables PIE to drive a pulse into the CPU 
	PieCtrRegs.PIEACK.all = 0xFFFF;  

	// Enable Interrupts at the CPU level 
    EINT;

}

const struct PIE_VECT_TABLE PieVectTableInit = 
{
      PIE_RESERVED,  // Reserved space
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   


// Non-Peripheral Interrupts
      INT13_ISR,     // XINT13 or CPU-Timer 1
      INT14_ISR,     // CPU-Timer2
      DATALOG_ISR,   // Datalogging interrupt
      RTOSINT_ISR,   // RTOS interrupt
      EMUINT_ISR,    // Emulation interrupt
      NMI_ISR,       // Non-maskable interrupt
      ILLEGAL_ISR,   // Illegal operation TRAP
      USER1_ISR,     // User Defined trap 1
      USER2_ISR,     // User Defined trap 2
      USER3_ISR,     // User Defined trap 3
      USER4_ISR,     // User Defined trap 4
      USER5_ISR,     // User Defined trap 5
      USER6_ISR,     // User Defined trap 6
      USER7_ISR,     // User Defined trap 7
      USER8_ISR,     // User Defined trap 8
      USER9_ISR,     // User Defined trap 9
      USER10_ISR,    // User Defined trap 10
      USER11_ISR,    // User Defined trap 11
      USER12_ISR,     // User Defined trap 12

// Group 1 PIE Vectors
      PDPINTA_ISR,   // EV-A
      PDPINTB_ISR,   // EV-B
      rsvd_ISR,
      XINT1_ISR,     
      XINT2_ISR,
      ADCINT_ISR,    // ADC
      TINT0_ISR,     // Timer 0
      WAKEINT_ISR,   // WD

// Group 2 PIE Vectors
      CMP1INT_ISR,   // EV-A
      CMP2INT_ISR,   // EV-A
      CMP3INT_ISR,   // EV-A
      T1PINT_ISR,    // EV-A
      T1CINT_ISR,    // EV-A
      T1UFINT_ISR,   // EV-A
      T1OFINT_ISR,   // EV-A
      rsvd_ISR,
      
// Group 3 PIE Vectors
      T2PINT_ISR,    // EV-A
      T2CINT_ISR,    // EV-A
      T2UFINT_ISR,   // EV-A
      T2OFINT_ISR,   // EV-A
      CAPINT1_ISR,   // EV-A
      CAPINT2_ISR,   // EV-A
      CAPINT3_ISR,   // EV-A
      rsvd_ISR,
      
// Group 4 PIE Vectors
      CMP4INT_ISR,   // EV-B
      CMP5INT_ISR,   // EV-B
      CMP6INT_ISR,   // EV-B
      T3PINT_ISR,    // EV-B
      T3CINT_ISR,    // EV-B
      T3UFINT_ISR,   // EV-B
      T3OFINT_ISR,   // EV-B
      rsvd_ISR,      
     
// Group 5 PIE Vectors
      T4PINT_ISR,    // EV-B
      T4CINT_ISR,    // EV-B
      T4UFINT_ISR,   // EV-B
      T4OFINT_ISR,   // EV-B
      CAPINT4_ISR,   // EV-B
      CAPINT5_ISR,   // EV-B
      CAPINT6_ISR,   // EV-B
      rsvd_ISR,      

// Group 6 PIE Vectors
      SPIRXINTA_ISR,   // SPI-A
      SPITXINTA_ISR,   // SPI-A
      rsvd_ISR,
      rsvd_ISR,
      MRINTA_ISR,    // McBSP-A
      MXINTA_ISR,    // McBSP-A
      rsvd_ISR,
      rsvd_ISR,
      
// Group 7 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   

// Group 8 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      
// Group 9 PIE Vectors     
      SCIRXINTA_ISR, // SCI-A
      SCITXINTA_ISR, // SCI-A
      SCIRXINTB_ISR, // SCI-B
      SCITXINTB_ISR, // SCI-B
      ECAN0INTA_ISR, // eCAN
      ECAN1INTA_ISR, // eCAN
      rsvd_ISR,   
      rsvd_ISR,   
      
// Group 10 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
            
// Group 11 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   

// Group 12 PIE Vectors
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
};


//---------------------------------------------------------------------------
// Setup_PIEvect: 
//---------------------------------------------------------------------------
// This function initializes the PIE vector table to a known state.
// This function must be executed after boot time.
//

void Setup_PIEvect(void)
{
	Sint16	xi ;
	Uint32 *Source = (void *) &PieVectTableInit ;
	Uint32 *Dest = (void *) &PieVecRegs ;
		
	EALLOW  ;	
	for(xi=0 ; xi < 128 ; xi++)  { *Dest++ = *Source++ ;  }
	EDIS    ;

	// Enable the PIE Vector Table
	PieCtrRegs.PIECRTL.bit.ENPIE = 1 ;	
}


//---------------------------------------------------------------------------
// Setup_CpuTmr0: 
//---------------------------------------------------------------------------
// This function initializes all three CPU timers to a known state.

void Setup_CpuTmr0(void)
{
	// Initialize address pointers to respective timer registers:
	CpuTmr0.RegsAddr = &CpuTm0Regs   ;
	// Initialize timer period to maximum:	
	CpuTm0Regs.PRD.all  = 0xFFFFFFFF ;
	// Initialize pre-scale counter to divide by 1 (SYSCLKOUT):	
	CpuTm0Regs.TPR.all  = 0  ;
	CpuTm0Regs.TPRH.all = 0  ;
	// Make sure timer is stopped:
	CpuTm0Regs.TCR.bit.TSS = 1 ;
	// Reload all counter register with period value:
	CpuTm0Regs.TCR.bit.TRB = 1 ;
	// Reset interrupt counters:
	CpuTmr0.INT_Count = 0 ;	             	
	
	
// CpuTimer 1 and CpuTimer2 are reserved for DSP BIOS & other RTOS
// Do not use these two timers if you ever plan on integrating 
// DSP-BIOS or another realtime OS. 
//
// For this reason, the code to manipulate these two timers is
// commented out and not used in these examples.

// Initialize address pointers to respective timer registers:
//	CpuTimer1.RegsAddr = &CpuTimer1Regs;
//	CpuTimer2.RegsAddr = &CpuTimer2Regs;
	// Initialize timer period to maximum:
//	CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
//	CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;
	// Make sure timers are stopped:
//	CpuTimer1Regs.TCR.bit.TSS = 1;             
//	CpuTimer2Regs.TCR.bit.TSS = 1;             
	// Reload all counter register with period value:
//	CpuTimer1Regs.TCR.bit.TRB = 1;             
//	CpuTimer2Regs.TCR.bit.TRB = 1;             
	// Reset interrupt counters:
//	CpuTimer1.INT_Count = 0;
//	CpuTimer2.INT_Count = 0;

}	
	
///---------------------------------------------------------------------------
// Setup_TimeISR: 
//---------------------------------------------------------------------------
// This function initializes the selected timer to the period specified
// by the "Freq" and "Period" parameters. The "Freq" is entered as "MHz"
// and the period in "uSeconds". The timer is held in the stopped state
// after configuration.
//

Uint32  PERD_TMR0;
Uint16  PERD_TMR1, PERD_TMR3 ;

void Setup_TimeISR(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
	Uint32 	temp ;
	
	// Initialize timer period:	
	Timer->CPU_FrqMh = Freq       ;
	Timer->PER_Usecs = Period     ;
	temp = (long) (Freq * Period) ;
	PERD_TMR0 = temp              ;
	Timer->RegsAddr->PRD.all = temp;

	// Set pre-scale counter to divide by 1 (SYSCLKOUT):	
	Timer->RegsAddr->TPR.all  = 0     ;
	Timer->RegsAddr->TPRH.all  = 0    ;
	
	// Initialize timer control register:
	Timer->RegsAddr->TCR.bit.TSS = 1  ;      // 1 = Stop timer, 0 = Start/Restart Timer 
	Timer->RegsAddr->TCR.bit.TRB = 1  ;      // 1 = reload timer
	Timer->RegsAddr->TCR.bit.SOFT = 1 ;
	Timer->RegsAddr->TCR.bit.FREE = 1 ;     // Timer Free Run
	Timer->RegsAddr->TCR.bit.TIE = 1  ;      // 0 = Disable/ 1 = Enable Timer Interrupt
	
	// Reset interrupt counter:
	Timer->INT_Count = 0 ;
}

typedef	unsigned char	BYTE   ;
typedef	unsigned short	WORD ;
typedef	unsigned long	LONG;

typedef union 
	{
		WORD	w[2];
		LONG	l;
	}ltype;
	
typedef union 
	{
		WORD	w[16];
		LONG	l[8];
	}htype;

#define	DEBUG_BUF_SIZE	100

/* Variables for Serial Communication Debug */
LONG	debug_rd_addr=0,debug_rd_addr_tmp=0;
LONG	debug_wr_addr;
htype	debug_wr_data;
WORD    debug_sum=0,debug_sum_temp=0;               
BYTE	debug_state=0,debug_cnt=0,debug_wr_size=0;
BYTE	debug_tx_buf[DEBUG_BUF_SIZE+1];
BYTE	debug_tx_pos=0,debug_tx_end=0;
BYTE	debug_wr_sum_flag=1;

#define	DEBUG_TX_START	{	SciAstRegs.SCICTL2.bit.TXINTENA=1;						\
							SciAstRegs.SCITXBUF = debug_tx_buf[debug_tx_pos++];		\
							if(debug_tx_pos >= DEBUG_BUF_SIZE) debug_tx_pos=0;		\
						}

#define	DEBUG_TX_STOP	SciAstRegs.SCICTL2.bit.TXINTENA=0

#define	ASC_HEX_ERROR	0xff

// Transmit a character from the SCI'
//void send_char(char c){
//    while(!SciAstRegs.SCICTL2.bit.TXRDY);
//    SciAstRegs.SCITXBUF=c;
//}    

void sci_debug_init(void){
// SCI(UART) init.

    // Note: Clocks were turned on to the SCIA peripheral
    // in the Setup_CpuCtrl() function
	
// 	SciAstRegs.SCIFFTX.all = 0xa000;		// FIFO reset
// 	SciAstRegs.SCIFFCT.all = 0x4000;		// Clear ABD(Auto baud bit)
 	
 	SciAstRegs.SCICCR.all =0x0007;   		// 1 stop bit,  No loopback 
                                   		// No parity,8 char bits,
                                   		// async mode, idle-line protocol
	SciAstRegs.SCICTL1.all =0x0003;  		// enable TX, RX, internal SCICLK, 
                                   		// Disable RX ERR, SLEEP, TXWAKE

	SciAstRegs.SCICTL2.bit.RXBKINTENA =1;	// RX/BK INT ENA=1,½ÓÊÕÖÐ¶ÏÊ¹ÄÜ
	SciAstRegs.SCICTL2.bit.TXINTENA =1;	    // TX INT ENA=1,   ·¢ËÍÖÐ¶ÏÊ¹ÄÜ

   // SciAstRegs.SCIHBAUD = BRR_VAL >> 8;	// High Value
    SciAstRegs.SCIHBAUD = BRR_VAL >> 8;
    SciAstRegs.SCILBAUD = BRR_VAL & 0xff;	// Low Value

	SciAstRegs.SCICTL1.all =0x0023;		// Relinquish SCI from Reset 


	// User specific functions, Reassign vectors (optional), Enable Interrupts:
	
    // Initialize SCI_A RX interrupt
    // Reassign SCI_A RX ISR. 
    // Reassign the PIE vector for RXAINT to point to a different ISR then
    // the shell routine found in DSP28_DefaultIsr.c.
    // This is done if the user does not want to use the shell ISR routine
    // but instead wants to use their own ISR.  This step is optional:
	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVecRegs.RXAINT = &scia_rx_isr;
	PieVecRegs.TXAINT = &scia_tx_isr;
	EDIS;       // This is needed to disable write to EALLOW protected registers


    // Enable CPU INT9 for SCI-A
	IER |= M_INT9;
	
    // Enable SCI-A RX INT in the PIE: Group 9 interrupt 1
	PieCtrRegs.PIEIER09.bit.INTx1 = 1;

    // Enable SCI-A TX INT in the PIE: Group 9 interrupt 2
	PieCtrRegs.PIEIER09.bit.INTx2 = 1;
}

BYTE	asc2hex(BYTE asc){
    if((asc >= '0') && (asc <= '9'))    return (asc - '0');
    else if((asc >= 'A') && (asc <= 'F'))   return (asc - 'A' + 0x0a);
    else if((asc >= 'a') && (asc <= 'f'))    return (asc - 'a' + 0x0a);
    else return ASC_HEX_ERROR;
}
BYTE	hex2asc(BYTE hex){
int	da;
	da = hex & 0x0f;
    if((da >= 0) && (da <= 9))    return  ('0' + da);
    else    return  ('A' + da - 0x0a);
}

void	write_txbuf_string(char *p){
char    rd;
	while(rd = *p++){             
		debug_tx_buf[debug_tx_end++] = rd;
		if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	}
}

void	write_txbuf_asc(BYTE d){
	debug_tx_buf[debug_tx_end++] = d;
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
}

void	write_txbuf_byte(BYTE d){
	debug_tx_buf[debug_tx_end++] = hex2asc(d >> 4);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(d);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
}

void	write_txbuf_word(WORD d){
	debug_tx_buf[debug_tx_end++] = hex2asc(d >> 12);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(d >> 8);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(d >> 4);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(d);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
}

void	write_txbuf_long(LONG d){
ltype	l;
	l.l = d;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[1]>>12);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[1]>>8);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[1]>>4);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[1]);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[0]>>12);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[0]>>8);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[0]>>4);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
	debug_tx_buf[debug_tx_end++] = hex2asc(l.w[0]);
	if(debug_tx_end >= DEBUG_BUF_SIZE)	debug_tx_end = 0;
}

void state0_proc(BYTE rxd){                              
ltype	d;
int		i;
	switch(rxd){
		case '!':
			write_txbuf_asc('!');		/* for BPS & Exist check */
			DEBUG_TX_START;
			break;                             
		case '@': 
			debug_cnt=0;
			debug_rd_addr_tmp=0;
			debug_state=1;
			break;
		case 'R': 
		case 'r':
			d.w[0] = *(WORD *)(debug_rd_addr);
			write_txbuf_word(d.w[0]);
			write_txbuf_asc(CR);
			if(rxd =='r') debug_rd_addr++;
			DEBUG_TX_START;
			break;
		case 'L': 
		case 'l': 
			d.l = *(LONG *)(debug_rd_addr);
			write_txbuf_long(d.l);
			write_txbuf_asc(CR);
			if(rxd == 'l') debug_rd_addr += 2;
			DEBUG_TX_START;
			break;
		case 'O':
		case 'o':
			for(i=0; i<8; i+=2){
				d.l = *(LONG *)(debug_rd_addr + i);
				write_txbuf_long(d.l);
			}
			write_txbuf_asc(CR);	 
			if(rxd == 'o') debug_rd_addr += 8;
			DEBUG_TX_START;
			break;
		case '?':
			write_txbuf_long(debug_rd_addr);
			write_txbuf_string("_DSP28x");
			write_txbuf_asc(CR);
			DEBUG_TX_START;
			break;
		case 'W':
			debug_sum_temp=0;         
			debug_sum='W';
			debug_wr_sum_flag=1;
			debug_state=3;               	
		    debug_wr_data.l[0]=0;
		    debug_wr_data.l[1]=0;
		    debug_wr_data.l[2]=0;
		    debug_wr_data.l[3]=0;
		    debug_wr_addr=0;
		    debug_cnt=0;
			break;                 
		case 'w':
			debug_sum_temp=0;         
			debug_sum='w';
			debug_wr_sum_flag=0;
			debug_state=3;               	
		    debug_wr_data.l[0]=0;
		    debug_wr_data.l[1]=0;
		    debug_wr_data.l[2]=0;
		    debug_wr_data.l[3]=0;
		    debug_wr_addr=0;
		    debug_cnt=0;
			break;                 
			
		default: 
			break;
	}
}     

void state1_proc(BYTE rxd){                           
BYTE temp ;
	temp = asc2hex(rxd);
	if( temp == ASC_HEX_ERROR ){
		 debug_state=0;	
		 return;
	}
	debug_rd_addr_tmp =(debug_rd_addr_tmp<<4) + (temp & 0xf);
	debug_cnt++;    
	if(debug_cnt >= 6) debug_state=2;
}

void state2_proc(BYTE rxd){
	debug_state=0;
	switch(rxd){
		case CR:
			debug_rd_addr=debug_rd_addr_tmp;
			write_txbuf_asc('!');
			DEBUG_TX_START;
			break;
		case 'R':
		case 'r':
		case 'L':
		case 'l':
		case 'O':
		case 'o':
			debug_rd_addr=debug_rd_addr_tmp;
			state0_proc(rxd);
			break;
		default:
			write_txbuf_string("X");
			DEBUG_TX_START;
			break;
	}

}		
			
void state3_proc(BYTE rxd){                     
	if((rxd == '1') || (rxd == '2')){
		 debug_wr_size = asc2hex(rxd)*4;
		 debug_state=4;
	}
	else debug_state=0;
	
	debug_cnt = 0;                             
	debug_sum += rxd;
}                                      

void state4_proc(BYTE rxd){
BYTE temp ;
	temp = asc2hex(rxd);
	if( temp == ASC_HEX_ERROR){
		 debug_state=0;	
		 return;
	}
	
	debug_wr_addr = (debug_wr_addr<<4) + (temp & 0xf);
	debug_cnt++;    
	if(debug_cnt >= 6){
		debug_state = 5;
		debug_cnt = 0;
	}
	debug_sum += rxd;
}
	
void state5_proc(BYTE rxd){
BYTE hex,i;
	hex = asc2hex(rxd);
	if(hex == ASC_HEX_ERROR){
		 debug_state=0;	
		 return;
	}                                                 
	
	i = debug_cnt >> 3;
	debug_cnt++;
	debug_wr_data.l[i] = (debug_wr_data.l[i] << 4) + hex;
	if(debug_cnt >= debug_wr_size){
		debug_cnt = 0;
		debug_state=6;
	}
	debug_sum += rxd;
}	
	            
void state6_proc(BYTE rxd){
BYTE temp ;
	temp = asc2hex(rxd);
	if( temp == ASC_HEX_ERROR ){
		 debug_state=0;	
		 return;
	}
	
	debug_sum_temp = (debug_sum_temp << 4) + temp;
	debug_cnt++;
	if(debug_cnt >= 2)	debug_state=7;
}                         

void state7_proc(BYTE rxd){
	if(rxd != CR)	write_txbuf_string("X");
	else if((debug_sum & 0xff) != (debug_sum_temp & 0xff)){
		if(debug_wr_sum_flag){
			write_txbuf_string("X");
			DEBUG_TX_START;
		    debug_state=0;
		    return;
		}
		
	}

   	if(debug_wr_size == 4){
   		*(WORD *)(debug_wr_addr) = debug_wr_data.l[0];
   	}
   	else if(debug_wr_size == 8){
   		*(LONG *)(debug_wr_addr) = debug_wr_data.l[0];
   	}
   	write_txbuf_asc('!');
	DEBUG_TX_START;

    debug_state=0;
}

interrupt void scia_tx_isr(void){
	if(debug_tx_pos != debug_tx_end){
		SciAstRegs.SCITXBUF = debug_tx_buf[debug_tx_pos++];
		if(debug_tx_pos >= DEBUG_BUF_SIZE)	debug_tx_pos = 0;
	}
	else{                              
		DEBUG_TX_STOP;
	}

	// Acknowledge this interrupt to recieve more interrupts from group 9
	PieCtrRegs.PIEACK.all = PIEACK_GROUP9;	
}
int numb=0;
unsigned char Data[4];
unsigned char Head;

Uint16 angle_real;
unsigned char angle_sign;
short dta1;	
short add,adddsp,dspadd;
int ch=0;
interrupt void scia_rx_isr(void)
{
  

/*   BYTE	rxd;            
	rxd = SciAstRegs.SCIRXBUF.all;
	switch(debug_state){
		case 0:		state0_proc(rxd);	break;
		case 1:		state1_proc(rxd);	break;
		case 2:		state2_proc(rxd);	break;
		case 3:		state3_proc(rxd);	break;
		case 4:		state4_proc(rxd);	break;
		case 5:		state5_proc(rxd);	break;
		case 6:		state6_proc(rxd);	break;
		case 7:		state7_proc(rxd);	break;
		default:	debug_state = 0;	break;
*/
Head=SciAstRegs.SCIRXBUF.all;

	switch(numb)
	{
		case 0:		Data[0]=Head;
		if (Data[0]=='$')
		{
		  numb++;
		}
		else
		{
		  numb=0;
		}break;
		case 1:		Data[1]=Head; numb++;	break;
		case 2:		Data[2]=Head; numb++;	break;
		case 3:		Data[3]=Head; numb++;   break;
//	      	  angle_real=(Data[3]<<8)|Data[2];
//		      angle_sign=Data[1];  break;
      
       case 4:	    add=Head;numb=0; adddsp=0;
//	    case 4:		Data[4]=Head; numb++;	break;
//		case 5:		Data[5]=Head; numb=0; 
         dta1=Data[0];
         for(ch=0;ch<8;ch++)
         {
              if(dta1&1)
         {
               adddsp+=1;
         }
            dta1=dta1>>1;
         }
          
          dta1=Data[1];  
          for(ch=0;ch<8;ch++)
         {
              if(dta1&1)
         {
               adddsp+=1;
         }
            dta1=dta1>>1;
         }  
            
          dta1=Data[2];  
          for(ch=0;ch<8;ch++)
         {
              if(dta1&1)
         {
               adddsp+=1;
         }
            dta1=dta1>>1;
         }  
            
           dta1=Data[3];  
          for(ch=0;ch<8;ch++)
         {
              if(dta1&1)
         {
              adddsp+=1;
         }
            dta1=dta1>>1;
         }  
         dspadd=adddsp;    
         if(add==adddsp)   
          {
              angle_real=(Data[3]<<8)|Data[2];
		      angle_sign=Data[1]; 
              break;			 
		  }
          else{
          adddsp=0;
		  break;
         }

		
        
		default:	break;

     }
	 

  /* Head=SciAstRegs.SCIRXBUF.all;
   if(Head==0xaa)
  {
   k=0;
   Data[k]=Head;
   k++;
  }
   if(k==2)
  {
   Data[k]=Head;
   k=3;
   angle_int=Data[2]&&0xff;
   angle_int=angle_int<<8;
   angle_int=angle_int+(Data[1]&&0xff);
   k=0;
  }

  */


/***************** ÉÏÃæÎª×Ôø³ÌÐò£¬ÏÂÃæÎª×ÔÐ´³ÌÐò£¬Í¨¹ý×Ö·ûÊý×é´«Êä£¬Í¨¹ý¸ß¡¢µÍ×Ö½Ú·Ö±ð´«Êä£¬×îºóÒÆÎ»×ª»¯ÎªÕûÐÍ*******************************/

/* if(k==1)
  Data[k]=SciAstRegs.SCIRXBUF.all; 
  k--;
  if(k==0)
  {
    Data[k]=SciAstRegs.SCIRXBUF.all; 
    angle_int=Data[0]&&0xff;
    angle_int=angle_int<<8;
    angle_int=angle_int+(Data[1]&&0xff);
    k=1;
  }
  
 
*/

	// Acknowledge this interrupt to recieve more interrupts from group 9
	PieCtrRegs.PIEACK.all = PIEACK_GROUP9 ;	
}


// These are defined by the linker (see F2812.cmd)
extern Uint16 RamfuncsLoadStart ;
extern Uint16 RamfuncsLoadEnd   ;
extern Uint16 RamfuncsRunStart  ;

void Opera_MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr) ;

void Opera_MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{

  while(SourceAddr < SourceEndAddr)
  { *DestAddr++ = *SourceAddr++ ;  }
  return  ;

}

// This function initializes the Flash Control registers
//                   CAUTION 
// This function MUST be executed out of RAM. Executing it
// out of OTP/Flash will yield unpredictable results
void Setup_FlashRM(void)  ;
#pragma CODE_SECTION(Setup_FlashRM, "RamFncRegsFile") ;

void Setup_FlashRM(void)
{
   EALLOW ;
   //Enable Flash Pipeline mode to improve performance
   //of code executed from Flash.
   Flash_Regs.FOPT.bit.ENPIPE = 1;  //Á÷Ë®Ïß²Ù×÷Ä£Ê½Ê¹ÄÜ
   
   //                CAUTION
   //Minimum waitstates required for the flash operating
   //at a given CPU rate must be characterized by TI. 
   //Refer to the datasheet for the latest information.  

   //Set the Random Waitstate for the Flash
   Flash_Regs.FBANKWAIT.bit.RANDWAIT = 5;
   
   //Set the Paged Waitstate for the Flash
   Flash_Regs.FBANKWAIT.bit.PAGEWAIT = 5;
   
   //                CAUTION
   //Minimum cycles required to move between power states
   //at a given CPU rate must be characterized by TI. 
   //Refer to the datasheet for the latest information.
     
   //For now use the default count
   //Set number of cycles to transition from sleep to standby
   Flash_Regs.FSTDBYWAIT.bit.STDBYWAIT = 0x01FF;       
   
   //Set number of cycles to transition from standby to active
   Flash_Regs.FACTIVEWAIT.bit.ACTIVEWAIT = 0x01FF;   
   EDIS   ;

   //Force a pipeline flush to ensure that the write to 
   //the last register configured occurs before returning.  

   asm(" RPT #7 || NOP");
}

#define ASM_DELAY_1us    asm(" RPT #146 || NOP ") ;	 /* 6.667ns * 150 = 1usec */

void  Delay_usec(unsigned int us), Delay_msec(unsigned int ms) ;

void	Delay_usec(unsigned int us)
{
	while(us--)  { ASM_DELAY_1us  ;  }
}

void	Delay_msec(unsigned int ms)
{
	while(ms--)  { Delay_usec(992) ; }
}
