/***************************************************************************/
/***    This File is for Global Setup of F281x DSP Initializing          ***/
/***    Peripheral Frame 0, 1, 2 Register Setup                          ***/
/***    Copyright 2005. 09. 25, KEMPEL                                   ***/
/***************************************************************************/

/***************************************************************************/
/***  Peripheral Frame 0 Register Structure Setup                          */
/***************************************************************************/

//===========================================================================
// Device Emulation Register Bit Definitions : DevEmuRegs
// ADDRESS : 0x00 0880 - 0x00 09FF
// EALLOW Protected 
//===========================================================================


// Device Configuration Register Bit Definitions
struct DEVICECNF_BITS  
{     // bits  description
  Uint16  rsvd1	 :  3 ;   // 2:0   reserved
  Uint16  VMAPS	 :  1 ;   // 3     VMAP Status
  Uint16  rsvd2	 :  1 ;   // 4     reserved
  Uint16  XRSn	 :  1 ;   // 5     XRSn Signal Status
  Uint16  rsvd3	 : 10 ;   // 15:6
  Uint16  rsvd4	 :  3 ;   // 18:6
  Uint16  ENPROT :  1 ;   // 19    Enable/Disable pipeline protection
  Uint16  rsvd5	 : 12 ;   // 31:20 reserved
} ;

union DEVICECNF_REG 
{
   Uint32                 all ;
   struct DEVICECNF_BITS  bit ;
} ;


// Device ID Register Bit Definitions
struct DEVICEID_BITS  
{ 
  Uint16 REVID  : 16 ;          // 15:0  Silicon revision
}  ;

union DEVICEID_REG 
{
  Uint32                all ;
  struct DEVICEID_BITS  bit ;
} ;

//---------------------------------------------------------------------------
// Refer to SPRU078 - 3.4 Device Emulation Registers
struct DEV_EMU_REGS 
{
  union  DEVICECNF_REG  DEVICECNF  ;  // device configuration Register
  Uint16                rsvd1 : 1  ;  // reserved(0x00 0882)
  union  DEVICEID_REG   DEVICEID   ;  // Device ID Register
  Uint16                PROTSTART  ;  // Write-Read protection start
  Uint16                PROTRANGE  ;  // Write-Read protection range
  Uint16                rsvd2[202] ;
// These registers are no longer needed for Rev C and beyond
// Uint16              M0RAMDFT;
// Uint16              M1RAMDFT;
// Uint16              L0RAMDFT;
// Uint16              L1RAMDFT;
// Uint16              H0RAMDFT;
} ;

volatile struct DEV_EMU_REGS  DevEmuRegs ;
#pragma DATA_SECTION(DevEmuRegs,"DevEmuRegsFile")  ;

//===========================================================================
// Flash Register Bit Definitions : Flash_Regs
// ADDRESS : 0x00 0A00 - 0x00 0A7F
// EALLOW Protected, CSM Protected
//===========================================================================

#define  FLASH_SLEEP    0x0000 ;
#define  FLASH_STANDBY  0x0001 ;
#define  FLASH_ACTIVE   0x0003 ;

// Flash Option Register bit definitions 
struct  FOPT_BITS 
{ 
  Uint16     ENPIPE :  1 ;   // 0     Enable Pipeline Mode
  Uint16     rsvd   : 15 ;   // 1-15  reserved
} ;

/* Allow access to the bit fields or entire register */
union  FOPT_REG 
{
  Uint16            all ;
  struct FOPT_BITS  bit ;
} ;

// Flash Power Modes Register bit definitions 
struct  FPWR_BITS 
{
  Uint16     PWR  :  2 ;   // 0-1   Power Mode bits
  Uint16     rsvd : 14 ;   // 2-15  reserved
} ;

// Allow access to the bit fields or entire register
union  FPWR_REG 
{
  Uint16             all ;
  struct  FPWR_BITS  bit ;
} ;

// Flash Status Register bit definitions
struct  FSTATUS_BITS 
{ 
  Uint16   PWRS        : 2 ;   // 0-1   Power Mode Status bits
  Uint16   STDBYWAITS  : 1 ;   // 2     Bank/Pump Sleep to Standby Wait Counter Status bits
  Uint16   ACTIVEWAITS : 1 ;   // 3     Bank/Pump Standby to Active Wait Counter Status bits
  Uint16   rsvd1       : 4 ;   // 4-7   reserved
  Uint16   V3STAT      : 1 ;   // 8     VDD3V Status Latch bit
  Uint16   rsvd2       : 7 ;   // 9-15  reserved
} ;

// Allow access to the bit fields or entire register
union FSTATUS_REG 
{
  Uint16               all ;
  struct FSTATUS_BITS  bit ;
};

// Flash Sleep to Standby Wait Counter Register bit definitions
struct  FSTDBYWAIT_BITS 
{ 
  Uint16  STDBYWAIT : 8 ;   // 0-7   Bank/Pump Sleep to Standby Wait Count bits
  Uint16  rsvd      : 8 ;        // 8-15  reserved
} ;

// Allow access to the bit fields or entire register
union FSTDBYWAIT_REG 
{
  Uint16                  all ;
  struct FSTDBYWAIT_BITS  bit ;
} ;

// Flash Standby to Active Wait Counter Register bit definitions
struct  FACTIVEWAIT_BITS 
{
  Uint16  ACTIVEWAIT : 8 ;  // 0-7   Bank/Pump Standby to Active Wait Count bits
  Uint16  rsvd       : 8 ;  // 8-15  reserved
} ;

// Allow access to the bit fields or entire register
union FACTIVEWAIT_REG 
{
  Uint16                    all ;
  struct  FACTIVEWAIT_BITS  bit ;
} ;

// Bank Read Access Wait State Register bit definitions
struct  FBANKWAIT_BITS 
{
  Uint16  RANDWAIT : 4 ;  // 0-3   Flash Random Read Wait State bits
  Uint16  rsvd1    : 4 ;  // 4-7   reserved
  Uint16  PAGEWAIT : 4 ;  // 8-11  Flash Paged Read Wait State bits
  Uint16  rsvd2    : 4 ;  // 12-15 reserved
} ;

// Allow access to the bit fields or entire register
union FBANKWAIT_REG 
{
  Uint16                  all ;
  struct  FBANKWAIT_BITS  bit ;
} ;

// OTP Read Access Wait State Register bit definitions
struct  FOTPWAIT_BITS 
{
  Uint16     OTPWAIT :  5 ;  // 0-4   OTP Read Wait State bits
  Uint16     rsvd    : 11 ;  // 5-15  reserved
} ;

// Allow access to the bit fields or entire register
union FOTPWAIT_REG 
{
  Uint16                 all ;
  struct  FOTPWAIT_BITS  bit ;
} ;

//---------------------------------------------------------------------------
// Refer to SPRU078 - 1.1 Flash OTP Memory Configuration Registers
struct FLASH_REGS 
{
  union  FOPT_REG         FOPT        ;  // Option Register
  Uint16                  rsvd1       ;  // reserved
  union  FPWR_REG         FPWR        ;  // Power Modes Register
  union  FSTATUS_REG      FSTATUS     ;  // Status Register
  union  FSTDBYWAIT_REG   FSTDBYWAIT  ;  // Pump/Bank Sleep to Standby Wait State Register
  union  FACTIVEWAIT_REG  FACTIVEWAIT ;  // Pump/Bank Standby to Active Wait State Register
  union  FBANKWAIT_REG    FBANKWAIT   ;  // Bank Read Access Wait State Register
  union  FOTPWAIT_REG     FOTPWAIT    ;  // OTP Read Access Wait State Register
} ;

volatile struct FLASH_REGS Flash_Regs  ;
#pragma DATA_SECTION(Flash_Regs,"Flash_RegsFile") ;

//===========================================================================
// Code Security Module Register Bit Definitions : CodSecRegs
// ADDRESS : 0x00 0AE0 - 0x00 0AEF
// EALLOW Protected
//===========================================================================

// CSM Status & Control register bit definitions
struct  CSMSCR_BITS 
{
  Uint16  SECURE   :  1 ;  // 0     Secure flag
  Uint16  rsvd1    : 14 ;  // 14-1  reserved
  Uint16  FORCESEC :  1 ;  // 15    Force Secure control bit
} ; 

// Allow access to the bit fields or entire register
union CSMSCR_REG 
{
  Uint16               all ;
  struct  CSMSCR_BITS  bit ;
} ;

// Password locations
struct  CSM_PWL 
{
  Uint16  PSWD0 ;  // PSWD bits 15-0
  Uint16  PSWD1 ;  // PSWD bits 31-16
  Uint16  PSWD2 ;  // PSWD bits 47-32
  Uint16  PSWD3 ;  // PSWD bits 63-48
  Uint16  PSWD4 ;  // PSWD bits 79-64
  Uint16  PSWD5 ;  // PSWD bits 95-80
  Uint16  PSWD6 ;  // PSWD bits 111-96
  Uint16  PSWD7 ;  // PSWD bits 127-112
} ;

//---------------------------------------------------------------------------
// Refer to SPRU078 - 2.1 Code Sercurity Module Registers
struct  CSM_REGS 
{      
  Uint16              KEY0   ;  // KEY reg bits 15-0 
  Uint16              KEY1   ;  // KEY reg bits 31-16 
  Uint16              KEY2   ;  // KEY reg bits 47-32
  Uint16              KEY3   ;  // KEY reg bits 63-48
  Uint16              KEY4   ;  // KEY reg bits 79-64
  Uint16              KEY5   ;  // KEY reg bits 95-80
  Uint16              KEY6   ;  // KEY reg bits 111-96
  Uint16              KEY7   ;  // KEY reg bits 127-112
  Uint16              rsvd1  ;  // reserved
  Uint16              rsvd2  ;  // reserved
  Uint16              rsvd3  ;  // reserved
  Uint16              rsvd4  ;  // reserved
  Uint16              rsvd5  ;  // reserved
  Uint16              rsvd6  ;  // reserved
  Uint16              rsvd7  ;  // reserved 
  union   CSMSCR_REG  CSMSCR ;  // CSM Status & Control register
} ;

volatile struct CSM_REGS CodSecRegs ;
volatile struct CSM_PWL  CsmPwlRegs ;
#pragma DATA_SECTION(CodSecRegs,"CodSecRegsFile") ;
#pragma DATA_SECTION(CsmPwlRegs,"CsmPwlRegsFile") ;

//===========================================================================
// External Interface Register Bit Definitions : Xintf_Regs
// ADDRESS : 0x00 0B20 - 0x00 0B3F
// Not EALLOW Protected
//===========================================================================

// XINTF timing register bit definitions:
struct  XTIMING_BITS 
{ 
  Uint16  XWRTRAIL  : 2 ;  // 1:0   Write access trail timing
  Uint16  XWRACTIVE : 3 ;  // 4:2   Write access active timing
  Uint16  XWRLEAD   : 2 ;  // 6:5   Write access lead timing
  Uint16  XRDTRAIL  : 2 ;  // 8:7   Read access trail timing
  Uint16  XRDACTIVE : 3 ;  // 11:9  Read access active timing
  Uint16  XRDLEAD   : 2 ;  // 13:12 Read access lead timing
  Uint16  USEREADY  : 1 ;  // 14    Extend access using HW waitstates
  Uint16  READYMODE : 1 ;  // 15    Ready mode
  Uint16  XSIZE     : 2 ;  // 17:16 XINTF bus width - must be written as 11b
  Uint16  rsvd1     : 4 ;  // 21:18 reserved
  Uint16  X2TIMING  : 1 ;  // 22    Double lead/active/trail timing
  Uint16  rsvd3     : 9 ;  // 31:23 reserved
} ;

union XTIMING_REG 
{
  Uint32                all ;
  struct  XTIMING_BITS  bit ;
} ;

// XINTF control register bit definitions:
struct XINTCNF2_BITS 
{
  Uint16  WRBUFF  :  2 ;  // 1:0   Write buffer depth
  Uint16  CLKMODE :  1 ;  // 2     Ratio for XCLKOUT with respect to XTIMCLK
  Uint16  CLKOFF  :  1 ;  // 3     Disable XCLKOUT
  Uint16  rsvd1   :  2 ;  // 5:4   reserved
  Uint16  WLEVEL  :  2 ;  // 7:6   Current level of the write buffer
  Uint16  MPNMC   :  1 ;  // 8     Micro-processor/micro-computer mode
  Uint16  HOLD    :  1 ;  // 9     Hold enable/disable
  Uint16  HOLDS   :  1 ;  // 10    Current state of HOLDn input
  Uint16  HOLDAS  :  1 ;  // 11    Current state of HOLDAn output
  Uint16  rsvd2   :  4 ;  // 15:12 reserved
  Uint16  XTIMCLK :  3 ;  // 18:16 Ratio for XTIMCLK
  Uint16  rsvd3   : 13 ;  // 31:19 reserved
} ;

union XINTCNF2_REG 
{
  Uint32                 all ;
  struct  XINTCNF2_BITS  bit ;
} ;

// XINTF bank switching register bit definitions:
struct XBANK_BITS 
{
  Uint16  BANK :  2 ;  // 2:0   Zone for which banking is enabled
  Uint16  BCYC :  3 ;  // 5:3   XTIMCLK cycles to add
  Uint16  rsvd : 10 ;  // 15:6  reserved
} ;

union XBANK_REG 
{
  Uint16              all ;
  struct  XBANK_BITS  bit ;
} ;

//---------------------------------------------------------------------------
// Refer to SPRU067C - 4. XINTF Registers
struct XINTF_REGS 
{
  union   XTIMING_REG   XTIMING0 ;
  union   XTIMING_REG   XTIMING1 ;
  union   XTIMING_REG   XTIMING2 ;
  Uint32  rsvd1[3]               ;
  union   XTIMING_REG   XTIMING6 ;
  union   XTIMING_REG   XTIMING7 ;
  Uint32  rsvd2[2]               ;
  union   XINTCNF2_REG  XINTCNF2 ;
  Uint32  rsvd3                  ;
  union   XBANK_REG     XBANK    ;
  Uint16  rsvd4                  ;
  Uint16  XREVISION              ;
  Uint16  rsvd5[5]               ;
} ;

volatile struct XINTF_REGS  Xintf_Regs ;
#pragma DATA_SECTION(Xintf_Regs,"Xintf_RegsFile") ;

//===========================================================================
// Cpu Timer 0, 1, 2 Register Bit Definitions : Xintf_Regs
// ADDRESS : 0x00 0C00 - 0x00 0C3F
// Not EALLOW Protected
//===========================================================================

// TCR: Control register bit definitions:
struct  TCR_BITS 
{
  Uint16  rsvd1 : 4 ;  // 3:0   reserved
  Uint16  TSS   : 1 ;  // 4     Timer Start/Stop
  Uint16  TRB   : 1 ;  // 5     Timer reload
  Uint16  rsvd2 : 4 ;  // 9:6   reserved
  Uint16  SOFT  : 1 ;  // 10    Emulation modes
  Uint16  FREE  : 1 ;  // 11
  Uint16  rsvd3 : 2 ;  // 12:13 reserved
  Uint16  TIE   : 1 ;  // 14    Output enable
  Uint16  TIF   : 1 ;  // 15    Interrupt flag
} ; 

union TCR_REG 
{
  Uint16            all ;
  struct  TCR_BITS  bit ;
} ;

// TPR: Pre-scale low bit definitions:
struct  TPR_BITS 
{
  Uint16  TDDR : 8 ;  // 7:0   Divide-down low
  Uint16  PSC  : 8 ;  // 15:8  Prescale counter low
} ;

union TPR_REG 
{
  Uint16            all ;
  struct  TPR_BITS  bit ;
} ;

// TPRH: Pre-scale high bit definitions:
struct  TPRH_BITS 
{
  Uint16  TDDRH : 8 ;  // 7:0   Divide-down high
  Uint16  PSCH  : 8 ;  // 15:8  Prescale counter high
} ;

union TPRH_REG 
{
  Uint16             all ;
  struct  TPRH_BITS  bit ;
} ;

// TIM, TIMH: Timer register definitions:
struct TIM_REG 
{
  Uint16  LSW ;
  Uint16  MSW ;
} ;

union TIM_GROUP 
{
  Uint32           all  ;
  struct TIM_REG   half ;
} ;

// PRD, PRDH: Period register definitions:
struct PRD_REG 
{
  Uint16  LSW ;
  Uint16  MSW ;
} ;

union PRD_GROUP 
{
  Uint32           all  ;
  struct  PRD_REG  half ;
} ;

//---------------------------------------------------------------------------
// Refer to SPRS174L - 4. Cpu Timer Registers
struct CPUTIMER_REGS 
{
  union   TIM_GROUP  TIM  ;  // Timer counter register
  union   PRD_GROUP  PRD  ;  // Period register
  union   TCR_REG    TCR  ;  // Timer control register
  Uint16  rsvd1           ;  // reserved
  union   TPR_REG    TPR  ;  // Timer pre-scale low
  union   TPRH_REG   TPRH ;  // Timer pre-scale high
} ;

//---------------------------------------------------------------------------
// CPU Timer Support Variables:

struct CPUTIMER_VARS 
{
  volatile struct  CPUTIMER_REGS  *RegsAddr ;
  Uint32    INT_Count  ;
  float     CPU_FrqMh  ;
  float     PER_Usecs  ;
} ;

volatile struct CPUTIMER_REGS CpuTm0Regs ;

#pragma DATA_SECTION(CpuTm0Regs,"CpuTm0RegsFile") ;

// volatile struct CPUTIMER_REGS CpuTm1Regs ;
// volatile struct CPUTIMER_REGS CpuTm2Regs ;
struct CPUTIMER_VARS CpuTmr0 ;



//---------------------------------------------------------------------------
// PIE Interrupt Vector Table Definition:
//
// Create a user type called PINT (pointer to interrupt):


//===========================================================================
// Peripheral Interrupt Expansion(PIE) Register Bit Definitions : PieCtrRegs
// ADDRESS : 0x00 0CE0 - 0x00 0CFF
// Not EALLOW Protected
//===========================================================================

// PIECTRL: Register bit definitions:
struct PIECTRL_BITS 
{ 
  Uint16  ENPIE   :  1 ;  // 0    Enable PIE block
  Uint16  PIEVECT : 15 ;  // 15:1 Fetched vector address
} ;

union PIECTRL_REG 
{
  Uint16                all ;
  struct  PIECTRL_BITS  bit ;
} ;  

// PIEIER: Register bit definitions:
struct PIEIER_BITS 
{
  Uint16  INTx1 : 1 ;  // 0    INTx.1
  Uint16  INTx2 : 1 ;  // 1    INTx.2
  Uint16  INTx3 : 1 ;  // 2    INTx.3
  Uint16  INTx4 : 1 ;  // 3    INTx.4
  Uint16  INTx5 : 1 ;  // 4    INTx.5
  Uint16  INTx6 : 1 ;  // 5    INTx.6
  Uint16  INTx7 : 1 ;  // 6    INTx.7
  Uint16  INTx8 : 1 ;  // 7    INTx.8
  Uint16  rsvd  : 8 ;  // 15:8 reserved
} ;

union PIEIER_REG 
{
  Uint16               all ;
  struct  PIEIER_BITS  bit ;
} ; 

// PIEIFR: Register bit definitions:
struct PIEIFR_BITS 
{ 
  Uint16  INTx1 : 1 ;  // 0    INTx.1
  Uint16  INTx2 : 1 ;  // 1    INTx.2
  Uint16  INTx3 : 1 ;  // 2    INTx.3
  Uint16  INTx4 : 1 ;  // 3    INTx.4
  Uint16  INTx5 : 1 ;  // 4    INTx.5
  Uint16  INTx6 : 1 ;  // 5    INTx.6
  Uint16  INTx7 : 1 ;  // 6    INTx.7
  Uint16  INTx8 : 1 ;  // 7    INTx.8
  Uint16  rsvd  : 8 ;  // 15:8 reserved
} ;

union PIEIFR_REG 
{
  Uint16               all ;
  struct  PIEIFR_BITS  bit ;
} ;

// PIEACK: Register bit definitions:
struct PIEACK_BITS 
{
  Uint16  ACK01 : 1 ;  // 0    Acknowledge PIE interrupt group 1
  Uint16  ACK02 : 1 ;  // 1    Acknowledge PIE interrupt group 2
  Uint16  ACK03 : 1 ;  // 2    Acknowledge PIE interrupt group 3
  Uint16  ACK04 : 1 ;  // 3    Acknowledge PIE interrupt group 4
  Uint16  ACK05 : 1 ;  // 4    Acknowledge PIE interrupt group 5
  Uint16  ACK06 : 1 ;  // 5    Acknowledge PIE interrupt group 6
  Uint16  ACK07 : 1 ;  // 6    Acknowledge PIE interrupt group 7
  Uint16  ACK08 : 1 ;  // 7    Acknowledge PIE interrupt group 8
  Uint16  ACK09 : 1 ;  // 8    Acknowledge PIE interrupt group 9
  Uint16  ACK10 : 1 ;  // 9    Acknowledge PIE interrupt group 10
  Uint16  ACK11 : 1 ;  // 10   Acknowledge PIE interrupt group 11
  Uint16  ACK12 : 1 ;  // 11   Acknowledge PIE interrupt group 12
  Uint16  rsvd  : 4 ;  // 15:12 reserved
} ;

union PIEACK_REG 
{
  Uint16               all ;
  struct  PIEACK_BITS  bit ;
} ;

//---------------------------------------------------------------------------
// PIE Control Register File:
struct PIE_CTRL_REGS 
{
  union  PIECTRL_REG  PIECRTL  ;  // PIE control register
  union  PIEACK_REG   PIEACK   ;  // PIE acknowledge
  union  PIEIER_REG   PIEIER01 ;  // PIE INT1 IER register  
  union  PIEIFR_REG   PIEIFR01 ;  // PIE INT1 IFR register
  union  PIEIER_REG   PIEIER02 ;  // PIE INT2 IER register 
  union  PIEIFR_REG   PIEIFR02 ;  // PIE INT2 IFR register
  union  PIEIER_REG   PIEIER03 ;  // PIE INT3 IER register 
  union  PIEIFR_REG   PIEIFR03 ;  // PIE INT3 IFR register
  union  PIEIER_REG   PIEIER04 ;  // PIE INT4 IER register             
  union  PIEIFR_REG   PIEIFR04 ;  // PIE INT4 IFR register
  union  PIEIER_REG   PIEIER05 ;  // PIE INT5 IER register  
  union  PIEIFR_REG   PIEIFR05 ;  // PIE INT5 IFR register
  union  PIEIER_REG   PIEIER06 ;  // PIE INT6 IER register 
  union  PIEIFR_REG   PIEIFR06 ;  // PIE INT6 IFR register
  union  PIEIER_REG   PIEIER07 ;  // PIE INT7 IER register 
  union  PIEIFR_REG   PIEIFR07 ;  // PIE INT7 IFR register
  union  PIEIER_REG   PIEIER08 ;  // PIE INT8 IER register
  union  PIEIFR_REG   PIEIFR08 ;  // PIE INT8 IFR register
  union  PIEIER_REG   PIEIER09 ;  // PIE INT9 IER register  
  union  PIEIFR_REG   PIEIFR09 ;  // PIE INT9 IFR register
  union  PIEIER_REG   PIEIER10 ;  // PIE INT10 IER register 
  union  PIEIFR_REG   PIEIFR10 ;  // PIE INT10 IFR register
  union  PIEIER_REG   PIEIER11 ;  // PIE INT11 IER register 
  union  PIEIFR_REG   PIEIFR11 ;  // PIE INT11 IFR register
  union  PIEIER_REG   PIEIER12 ;  // PIE INT12 IER register
  union  PIEIFR_REG   PIEIFR12 ;  // PIE INT12 IFR register
} ;     

#define PIEACK_GROUP1   0x0001 ;
#define PIEACK_GROUP2   0x0002 ;
#define PIEACK_GROUP3   0x0004 ;
#define PIEACK_GROUP4   0x0008 ;
#define PIEACK_GROUP5   0x0010 ;
#define PIEACK_GROUP6   0x0020 ;
#define PIEACK_GROUP7   0x0040 ;
#define PIEACK_GROUP8   0x0080 ;
#define PIEACK_GROUP9   0x0100 ;
#define PIEACK_GROUP10  0x0200 ;
#define PIEACK_GROUP11  0x0400 ;
#define PIEACK_GROUP12  0x0800 ;

//---------------------------------------------------------------------------
// PIE Control Registers External References & Function Declarations:
//
volatile struct PIE_CTRL_REGS PieCtrRegs ;
#pragma DATA_SECTION(PieCtrRegs,"PieCtrRegsFile") ;

//===========================================================================
// Peripheral Interrupt Expansion Vector Table Bit Definitions : PieCtrRegs
// ADDRESS : 0x00 0D00 - 0x00 0DFF
// EALLOW Protected
//===========================================================================

typedef interrupt void(*PINT)(void) ;

// Define Vector Table:
struct PIE_VECT_TABLE 
{
// Reset is never fetched from this table.  
// It will always be fetched from 0x3FFFC0 in either
// boot ROM or XINTF Zone 7 depending on the state of
// the XMP/MC input signal.  On the F2810 it is always
// fetched from boot ROM. 
   PINT  PIE1_RESERVED  ;  
   PINT  PIE2_RESERVED  ;
   PINT  PIE3_RESERVED  ;
   PINT  PIE4_RESERVED  ;
   PINT  PIE5_RESERVED  ;
   PINT  PIE6_RESERVED  ;
   PINT  PIE7_RESERVED  ;
   PINT  PIE8_RESERVED  ;
   PINT  PIE9_RESERVED  ;
   PINT  PIE10_RESERVED ;
   PINT  PIE11_RESERVED ;
   PINT  PIE12_RESERVED ;
   PINT  PIE13_RESERVED ;

// Non-Peripheral Interrupts:
   PINT  XINT13  ;  // XINT13
   PINT  TINT2   ;  // CPU-Timer2
   PINT  DATALOG ;  // Datalogging interrupt
   PINT  RTOSINT ;  // RTOS interrupt
   PINT  EMUINT  ;  // Emulation interrupt
   PINT  XNMI    ;  // Non-maskable interrupt
   PINT  ILLEGAL ;  // Illegal operation TRAP
   PINT  USER1   ;  // User Defined trap 1
   PINT  USER2   ;  // User Defined trap 2
   PINT  USER3   ;  // User Defined trap 3
   PINT  USER4   ;  // User Defined trap 4
   PINT  USER5   ;  // User Defined trap 5
   PINT  USER6   ;  // User Defined trap 6
   PINT  USER7   ;  // User Defined trap 7
   PINT  USER8   ;  // User Defined trap 8
   PINT  USER9   ;  // User Defined trap 9
   PINT  USER10  ;  // User Defined trap 10
   PINT  USER11  ;  // User Defined trap 11
   PINT  USER12  ;  // User Defined trap 12
      
// Group 1 PIE Peripheral Vectors:
   PINT  PDPINTA ;  // EV-A
   PINT  PDPINTB ;  // EV-B
   PINT  rsvd1_3 ;
   PINT  XINT1   ;     
   PINT  XINT2   ;
   PINT  ADCINT  ;  // ADC
   PINT  TINT0   ;  // Timer 0
   PINT  WAKEINT ;  // WD
        
// Group 2 PIE Peripheral Vectors:
   PINT  CMP1INT ;  // EV-A
   PINT  CMP2INT ;  // EV-A
   PINT  CMP3INT ;  // EV-A
   PINT  T1PINT  ;  // EV-A
   PINT  T1CINT  ;  // EV-A
   PINT  T1UFINT ;  // EV-A
   PINT  T1OFINT ;  // EV-A
   PINT  rsvd2_8 ;
   
// Group 3 PIE Peripheral Vectors:
   PINT   T2PINT  ;  // EV-A
   PINT   T2CINT  ;  // EV-A
   PINT   T2UFINT ;  // EV-A
   PINT   T2OFINT ;  // EV-A
   PINT   CAPINT1 ;  // EV-A
   PINT   CAPINT2 ;  // EV-A
   PINT   CAPINT3 ;  // EV-A
   PINT   rsvd3_8 ;
   
// Group 4 PIE Peripheral Vectors:
   PINT   CMP4INT ;  // EV-B
   PINT   CMP5INT ;  // EV-B
   PINT   CMP6INT ;  // EV-B
   PINT   T3PINT  ;  // EV-B
   PINT   T3CINT  ;  // EV-B
   PINT   T3UFINT ;  // EV-B
   PINT   T3OFINT ;  // EV-B
   PINT   rsvd4_8 ;      
     
// Group 5 PIE Peripheral Vectors:
   PINT   T4PINT  ;  // EV-B
   PINT   T4CINT  ;  // EV-B
   PINT   T4UFINT ;  // EV-B
   PINT   T4OFINT ;  // EV-B
   PINT   CAPINT4 ;  // EV-B
   PINT   CAPINT5 ;  // EV-B
   PINT   CAPINT6 ;  // EV-B
   PINT   rsvd5_8 ;      

// Group 6 PIE Peripheral Vectors:
   PINT  SPIRXINTA ;  // SPI-A
   PINT  SPITXINTA ;  // SPI-A
   PINT  rsvd6_3   ;
   PINT  rsvd6_4   ;
   PINT  MRINTA    ;  // McBSP-A
   PINT  MXINTA    ;  // McBSP-A
   PINT  rsvd6_7   ;
   PINT  rsvd6_8   ;
   
// Group 7 PIE Peripheral Vectors:
   PINT  rsvd7_1 ;
   PINT  rsvd7_2 ;
   PINT  rsvd7_3 ;
   PINT  rsvd7_4 ;
   PINT  rsvd7_5 ;
   PINT  rsvd7_6 ;
   PINT  rsvd7_7 ;
   PINT  rsvd7_8 ;

// Group 8 PIE Peripheral Vectors:
   PINT  rsvd8_1 ;
   PINT  rsvd8_2 ;
   PINT  rsvd8_3 ;
   PINT  rsvd8_4 ;
   PINT  rsvd8_5 ;
   PINT  rsvd8_6 ;
   PINT  rsvd8_7 ;
   PINT  rsvd8_8 ; 

// Group 9 PIE Peripheral Vectors:   
   PINT  RXAINT    ;  // SCI-A
   PINT  TXAINT    ;  // SCI-A
   PINT  RXBINT    ;  // SCI-B
   PINT  TXBINT    ;  // SCI-B
   PINT  ECAN0INTA ;  // eCAN
   PINT  ECAN1INTA ;  // eCAN
   PINT  rsvd9_7   ;
   PINT  rsvd9_8   ;

// Group 10 PIE Peripheral Vectors:
   PINT  rsvd10_1 ;
   PINT  rsvd10_2 ;
   PINT  rsvd10_3 ;
   PINT  rsvd10_4 ;
   PINT  rsvd10_5 ;
   PINT  rsvd10_6 ;
   PINT  rsvd10_7 ;
   PINT  rsvd10_8 ;
         
// Group 11 PIE Peripheral Vectors:
   PINT  rsvd11_1 ;
   PINT  rsvd11_2 ;
   PINT  rsvd11_3 ;
   PINT  rsvd11_4 ;
   PINT  rsvd11_5 ;
   PINT  rsvd11_6 ;
   PINT  rsvd11_7 ;
   PINT  rsvd11_8 ;

// Group 12 PIE Peripheral Vectors:
   PINT  rsvd12_1 ;
   PINT  rsvd12_2 ;
   PINT  rsvd12_3 ;
   PINT  rsvd12_4 ;
   PINT  rsvd12_5 ;
   PINT  rsvd12_6 ;
   PINT  rsvd12_7 ;
   PINT  rsvd12_8 ;
} ;

struct PIE_VECT_TABLE PieVecRegs  ;
#pragma DATA_SECTION(PieVecRegs,"PieVecRegsFile") ;

/***************************************************************************/
/***  Peripheral Frame 1 Register Structure Setup                          */
/***************************************************************************/

//===========================================================================
// Enhanced Controller Area Network(eCAN) Module Bit Definitions : DevEmuRegs
// ADDRESS : 0x00 6000 - 0x00 60FF
// Some Registers are EALLOW Protected 
//===========================================================================

// eCAN Mailbox enable register (CANME) bit definitions
struct  CANME_BITS 
{
  Uint16  ME0  : 1 ;   // 0   Enable Mailbox 0
  Uint16  ME1  : 1 ;   // 1   Enable Mailbox 1
  Uint16  ME2  : 1 ;   // 2   Enable Mailbox 2
  Uint16  ME3  : 1 ;   // 3   Enable Mailbox 3
  Uint16  ME4  : 1 ;   // 4   Enable Mailbox 4
  Uint16  ME5  : 1 ;   // 5   Enable Mailbox 5
  Uint16  ME6  : 1 ;   // 6   Enable Mailbox 6
  Uint16  ME7  : 1 ;   // 7   Enable Mailbox 7
  Uint16  ME8  : 1 ;   // 8   Enable Mailbox 8
  Uint16  ME9  : 1 ;   // 9   Enable Mailbox 9
  Uint16  ME10 : 1 ;   // 10  Enable Mailbox 10
  Uint16  ME11 : 1 ;   // 11  Enable Mailbox 11
  Uint16  ME12 : 1 ;   // 12  Enable Mailbox 12
  Uint16  ME13 : 1 ;   // 13  Enable Mailbox 13
  Uint16  ME14 : 1 ;   // 14  Enable Mailbox 14
  Uint16  ME15 : 1 ;   // 15  Enable Mailbox 15
  Uint16  ME16 : 1 ;   // 16  Enable Mailbox 16
  Uint16  ME17 : 1 ;   // 17  Enable Mailbox 17
  Uint16  ME18 : 1 ;   // 18  Enable Mailbox 18
  Uint16  ME19 : 1 ;   // 19  Enable Mailbox 19
  Uint16  ME20 : 1 ;   // 20  Enable Mailbox 20
  Uint16  ME21 : 1 ;   // 21  Enable Mailbox 21
  Uint16  ME22 : 1 ;   // 22  Enable Mailbox 22
  Uint16  ME23 : 1 ;   // 23  Enable Mailbox 23
  Uint16  ME24 : 1 ;   // 24  Enable Mailbox 24
  Uint16  ME25 : 1 ;   // 25  Enable Mailbox 25
  Uint16  ME26 : 1 ;   // 26  Enable Mailbox 26
  Uint16  ME27 : 1 ;   // 27  Enable Mailbox 27
  Uint16  ME28 : 1 ;   // 28  Enable Mailbox 28
  Uint16  ME29 : 1 ;   // 29  Enable Mailbox 29
  Uint16  ME30 : 1 ;   // 30  Enable Mailbox 30
  Uint16  ME31 : 1 ;   // 31  Enable Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANME_REG 
{
  Uint32              all ;
  struct  CANME_BITS  bit ;
} ;

// eCAN Mailbox direction register (CANMD) bit definitions
struct  CANMD_BITS 
{
  Uint16  MD0  : 1 ;  // 0   0 -> Tx 1 -> Rx
  Uint16  MD1  : 1 ;  // 1   0 -> Tx 1 -> Rx
  Uint16  MD2  : 1 ;  // 2   0 -> Tx 1 -> Rx
  Uint16  MD3  : 1 ;  // 3   0 -> Tx 1 -> Rx
  Uint16  MD4  : 1 ;  // 4   0 -> Tx 1 -> Rx
  Uint16  MD5  : 1 ;  // 5   0 -> Tx 1 -> Rx
  Uint16  MD6  : 1 ;  // 6   0 -> Tx 1 -> Rx
  Uint16  MD7  : 1 ;  // 7   0 -> Tx 1 -> Rx
  Uint16  MD8  : 1 ;  // 8   0 -> Tx 1 -> Rx
  Uint16  MD9  : 1 ;  // 9   0 -> Tx 1 -> Rx
  Uint16  MD10 : 1 ;  // 10  0 -> Tx 1 -> Rx
  Uint16  MD11 : 1 ;  // 11  0 -> Tx 1 -> Rx
  Uint16  MD12 : 1 ;  // 12  0 -> Tx 1 -> Rx
  Uint16  MD13 : 1 ;  // 13  0 -> Tx 1 -> Rx
  Uint16  MD14 : 1 ;  // 14  0 -> Tx 1 -> Rx
  Uint16  MD15 : 1 ;  // 15  0 -> Tx 1 -> Rx
  Uint16  MD16 : 1 ;  // 16  0 -> Tx 1 -> Rx
  Uint16  MD17 : 1 ;  // 17  0 -> Tx 1 -> Rx
  Uint16  MD18 : 1 ;  // 18  0 -> Tx 1 -> Rx
  Uint16  MD19 : 1 ;  // 19  0 -> Tx 1 -> Rx
  Uint16  MD20 : 1 ;  // 20  0 -> Tx 1 -> Rx
  Uint16  MD21 : 1 ;  // 21  0 -> Tx 1 -> Rx
  Uint16  MD22 : 1 ;  // 22  0 -> Tx 1 -> Rx
  Uint16  MD23 : 1 ;  // 23  0 -> Tx 1 -> Rx
  Uint16  MD24 : 1 ;  // 24  0 -> Tx 1 -> Rx
  Uint16  MD25 : 1 ;  // 25  0 -> Tx 1 -> Rx
  Uint16  MD26 : 1 ;  // 26  0 -> Tx 1 -> Rx
  Uint16  MD27 : 1 ;  // 27  0 -> Tx 1 -> Rx
  Uint16  MD28 : 1 ;  // 28  0 -> Tx 1 -> Rx
  Uint16  MD29 : 1 ;  // 29  0 -> Tx 1 -> Rx
  Uint16  MD30 : 1 ;  // 30  0 -> Tx 1 -> Rx
  Uint16  MD31 : 1 ;  // 31  0 -> Tx 1 -> Rx
} ; 

// Allow access to the bit fields or entire register
union CANMD_REG 
{
  Uint32              all ;
  struct  CANMD_BITS  bit ;
} ;

// eCAN Transmit Request Set register (CANTRS) bit definitions
struct  CANTRS_BITS 
{
  Uint16  TRS0  : 1 ;  // 0   TRS for Mailbox 0
  Uint16  TRS1  : 1 ;  // 1   TRS for Mailbox 1
  Uint16  TRS2  : 1 ;  // 2   TRS for Mailbox 2
  Uint16  TRS3  : 1 ;  // 3   TRS for Mailbox 3
  Uint16  TRS4  : 1 ;  // 4   TRS for Mailbox 4
  Uint16  TRS5  : 1 ;  // 5   TRS for Mailbox 5
  Uint16  TRS6  : 1 ;  // 6   TRS for Mailbox 6
  Uint16  TRS7  : 1 ;  // 7   TRS for Mailbox 7
  Uint16  TRS8  : 1 ;  // 8   TRS for Mailbox 8
  Uint16  TRS9  : 1 ;  // 9   TRS for Mailbox 9
  Uint16  TRS10 : 1 ;  // 10  TRS for Mailbox 10
  Uint16  TRS11 : 1 ;  // 11  TRS for Mailbox 11
  Uint16  TRS12 : 1 ;  // 12  TRS for Mailbox 12
  Uint16  TRS13 : 1 ;  // 13  TRS for Mailbox 13
  Uint16  TRS14 : 1 ;  // 14  TRS for Mailbox 14
  Uint16  TRS15 : 1 ;  // 15  TRS for Mailbox 15
  Uint16  TRS16 : 1 ;  // 16  TRS for Mailbox 16
  Uint16  TRS17 : 1 ;  // 17  TRS for Mailbox 17
  Uint16  TRS18 : 1 ;  // 18  TRS for Mailbox 18
  Uint16  TRS19 : 1 ;  // 19  TRS for Mailbox 19
  Uint16  TRS20 : 1 ;  // 20  TRS for Mailbox 20
  Uint16  TRS21 : 1 ;  // 21  TRS for Mailbox 21
  Uint16  TRS22 : 1 ;  // 22  TRS for Mailbox 22
  Uint16  TRS23 : 1 ;  // 23  TRS for Mailbox 23
  Uint16  TRS24 : 1 ;  // 24  TRS for Mailbox 24
  Uint16  TRS25 : 1 ;  // 25  TRS for Mailbox 25
  Uint16  TRS26 : 1 ;  // 26  TRS for Mailbox 26
  Uint16  TRS27 : 1 ;  // 27  TRS for Mailbox 27
  Uint16  TRS28 : 1 ;  // 28  TRS for Mailbox 28
  Uint16  TRS29 : 1 ;  // 29  TRS for Mailbox 29
  Uint16  TRS30 : 1 ;  // 30  TRS for Mailbox 30
  Uint16  TRS31 : 1 ;  // 31  TRS for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANTRS_REG 
{
  Uint32               all ;
  struct  CANTRS_BITS  bit ;
} ;

// eCAN Transmit Request Reset register (CANTRR) bit definitions
struct  CANTRR_BITS 
{
  Uint16  TRR0  : 1 ;  // 0   TRR for Mailbox 0
  Uint16  TRR1  : 1 ;  // 1   TRR for Mailbox 1
  Uint16  TRR2  : 1 ;  // 2   TRR for Mailbox 2
  Uint16  TRR3  : 1 ;  // 3   TRR for Mailbox 3
  Uint16  TRR4  : 1 ;  // 4   TRR for Mailbox 4
  Uint16  TRR5  : 1 ;  // 5   TRR for Mailbox 5
  Uint16  TRR6  : 1 ;  // 6   TRR for Mailbox 6
  Uint16  TRR7  : 1 ;  // 7   TRR for Mailbox 7
  Uint16  TRR8  : 1 ;  // 8   TRR for Mailbox 8
  Uint16  TRR9  : 1 ;  // 9   TRR for Mailbox 9
  Uint16  TRR10 : 1 ;  // 10  TRR for Mailbox 10
  Uint16  TRR11 : 1 ;  // 11  TRR for Mailbox 11
  Uint16  TRR12 : 1 ;  // 12  TRR for Mailbox 12
  Uint16  TRR13 : 1 ;  // 13  TRR for Mailbox 13
  Uint16  TRR14 : 1 ;  // 14  TRR for Mailbox 14
  Uint16  TRR15 : 1 ;  // 15  TRR for Mailbox 15
  Uint16  TRR16 : 1 ;  // 16  TRR for Mailbox 16
  Uint16  TRR17 : 1 ;  // 17  TRR for Mailbox 17
  Uint16  TRR18 : 1 ;  // 18  TRR for Mailbox 18
  Uint16  TRR19 : 1 ;  // 19  TRR for Mailbox 19
  Uint16  TRR20 : 1 ;  // 20  TRR for Mailbox 20
  Uint16  TRR21 : 1 ;  // 21  TRR for Mailbox 21
  Uint16  TRR22 : 1 ;  // 22  TRR for Mailbox 22
  Uint16  TRR23 : 1 ;  // 23  TRR for Mailbox 23
  Uint16  TRR24 : 1 ;  // 24  TRR for Mailbox 24
  Uint16  TRR25 : 1 ;  // 25  TRR for Mailbox 25
  Uint16  TRR26 : 1 ;  // 26  TRR for Mailbox 26
  Uint16  TRR27 : 1 ;  // 27  TRR for Mailbox 27
  Uint16  TRR28 : 1 ;  // 28  TRR for Mailbox 28
  Uint16  TRR29 : 1 ;  // 29  TRR for Mailbox 29
  Uint16  TRR30 : 1 ;  // 30  TRR for Mailbox 30
  Uint16  TRR31 : 1 ;  // 31  TRR for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANTRR_REG 
{
  Uint32               all ;
  struct  CANTRR_BITS  bit ;
} ;

// eCAN Transmit Acknowledge register (CANTA) bit definitions
struct  CANTA_BITS 
{ 
  Uint16  TA0  : 1 ;  // 0   TA for Mailbox 0
  Uint16  TA1  : 1 ;  // 1   TA for Mailbox 1
  Uint16  TA2  : 1 ;  // 2   TA for Mailbox 2
  Uint16  TA3  : 1 ;  // 3   TA for Mailbox 3
  Uint16  TA4  : 1 ;  // 4   TA for Mailbox 4
  Uint16  TA5  : 1 ;  // 5   TA for Mailbox 5
  Uint16  TA6  : 1 ;  // 6   TA for Mailbox 6
  Uint16  TA7  : 1 ;  // 7   TA for Mailbox 7
  Uint16  TA8  : 1 ;  // 8   TA for Mailbox 8
  Uint16  TA9  : 1 ;  // 9   TA for Mailbox 9
  Uint16  TA10 : 1 ;  // 10  TA for Mailbox 10
  Uint16  TA11 : 1 ;  // 11  TA for Mailbox 11
  Uint16  TA12 : 1 ;  // 12  TA for Mailbox 12
  Uint16  TA13 : 1 ;  // 13  TA for Mailbox 13
  Uint16  TA14 : 1 ;  // 14  TA for Mailbox 14
  Uint16  TA15 : 1 ;  // 15  TA for Mailbox 15
  Uint16  TA16 : 1 ;  // 16  TA for Mailbox 16
  Uint16  TA17 : 1 ;  // 17  TA for Mailbox 17
  Uint16  TA18 : 1 ;  // 18  TA for Mailbox 18
  Uint16  TA19 : 1 ;  // 19  TA for Mailbox 19
  Uint16  TA20 : 1 ;  // 20  TA for Mailbox 20
  Uint16  TA21 : 1 ;  // 21  TA for Mailbox 21
  Uint16  TA22 : 1 ;  // 22  TA for Mailbox 22
  Uint16  TA23 : 1 ;  // 23  TA for Mailbox 23
  Uint16  TA24 : 1 ;  // 24  TA for Mailbox 24
  Uint16  TA25 : 1 ;  // 25  TA for Mailbox 25
  Uint16  TA26 : 1 ;  // 26  TA for Mailbox 26
  Uint16  TA27 : 1 ;  // 27  TA for Mailbox 27
  Uint16  TA28 : 1 ;  // 28  TA for Mailbox 28
  Uint16  TA29 : 1 ;  // 29  TA for Mailbox 29
  Uint16  TA30 : 1 ;  // 30  TA for Mailbox 30
  Uint16  TA31 : 1 ;  // 31  TA for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANTA_REG 
{
  Uint32              all ;
  struct  CANTA_BITS  bit ;
} ;

// eCAN Transmit Abort Acknowledge register (CANAA) bit definitions
struct  CANAA_BITS 
{
  Uint16  AA0  : 1 ;  // 0   AA for Mailbox 0
  Uint16  AA1  : 1 ;  // 1   AA for Mailbox 1
  Uint16  AA2  : 1 ;  // 2   AA for Mailbox 2
  Uint16  AA3  : 1 ;  // 3   AA for Mailbox 3
  Uint16  AA4  : 1 ;  // 4   AA for Mailbox 4
  Uint16  AA5  : 1 ;  // 5   AA for Mailbox 5
  Uint16  AA6  : 1 ;  // 6   AA for Mailbox 6
  Uint16  AA7  : 1 ;  // 7   AA for Mailbox 7
  Uint16  AA8  : 1 ;  // 8   AA for Mailbox 8
  Uint16  AA9  : 1 ;  // 9   AA for Mailbox 9
  Uint16  AA10 : 1 ;  // 10  AA for Mailbox 10
  Uint16  AA11 : 1 ;  // 11  AA for Mailbox 11
  Uint16  AA12 : 1 ;  // 12  AA for Mailbox 12
  Uint16  AA13 : 1 ;  // 13  AA for Mailbox 13
  Uint16  AA14 : 1 ;  // 14  AA for Mailbox 14
  Uint16  AA15 : 1 ;  // 15  AA for Mailbox 15
  Uint16  AA16 : 1 ;  // 16  AA for Mailbox 16
  Uint16  AA17 : 1 ;  // 17  AA for Mailbox 17
  Uint16  AA18 : 1 ;  // 18  AA for Mailbox 18
  Uint16  AA19 : 1 ;  // 19  AA for Mailbox 19
  Uint16  AA20 : 1 ;  // 20  AA for Mailbox 20
  Uint16  AA21 : 1 ;  // 21  AA for Mailbox 21
  Uint16  AA22 : 1 ;  // 22  AA for Mailbox 22
  Uint16  AA23 : 1 ;  // 23  AA for Mailbox 23
  Uint16  AA24 : 1 ;  // 24  AA for Mailbox 24
  Uint16  AA25 : 1 ;  // 25  AA for Mailbox 25
  Uint16  AA26 : 1 ;  // 26  AA for Mailbox 26
  Uint16  AA27 : 1 ;  // 27  AA for Mailbox 27
  Uint16  AA28 : 1 ;  // 28  AA for Mailbox 28
  Uint16  AA29 : 1 ;  // 29  AA for Mailbox 29
  Uint16  AA30 : 1 ;  // 30  AA for Mailbox 30
  Uint16  AA31 : 1 ;  // 31  AA for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANAA_REG 
{
  Uint32              all ;
  struct  CANAA_BITS  bit ;
} ;

// eCAN Received Message Pending register (CANRMP) bit definitions
struct  CANRMP_BITS 
{
  Uint16  RMP0:1;     // 0   RMP for Mailbox 0
  Uint16  RMP1:1;     // 1   RMP for Mailbox 1
  Uint16  RMP2:1;     // 2   RMP for Mailbox 2
  Uint16  RMP3:1;     // 3   RMP for Mailbox 3
  Uint16  RMP4:1;     // 4   RMP for Mailbox 4
  Uint16  RMP5:1;     // 5   RMP for Mailbox 5
  Uint16  RMP6:1;     // 6   RMP for Mailbox 6
  Uint16  RMP7:1;     // 7   RMP for Mailbox 7
  Uint16  RMP8:1;     // 8   RMP for Mailbox 8
  Uint16  RMP9:1;     // 9   RMP for Mailbox 9
  Uint16  RMP10:1;    // 10  RMP for Mailbox 10
  Uint16  RMP11:1;    // 11  RMP for Mailbox 11
  Uint16  RMP12:1;    // 12  RMP for Mailbox 12
  Uint16  RMP13:1;    // 13  RMP for Mailbox 13
  Uint16  RMP14:1;    // 14  RMP for Mailbox 14
  Uint16  RMP15:1;    // 15  RMP for Mailbox 15
  Uint16  RMP16:1;    // 16  RMP for Mailbox 16
  Uint16  RMP17:1;    // 17  RMP for Mailbox 17
  Uint16  RMP18:1;    // 18  RMP for Mailbox 18
  Uint16  RMP19:1;    // 19  RMP for Mailbox 19
  Uint16  RMP20:1;    // 20  RMP for Mailbox 20
  Uint16  RMP21:1;    // 21  RMP for Mailbox 21
  Uint16  RMP22:1;    // 22  RMP for Mailbox 22
  Uint16  RMP23:1;    // 23  RMP for Mailbox 23
  Uint16  RMP24:1;    // 24  RMP for Mailbox 24
  Uint16  RMP25:1;    // 25  RMP for Mailbox 25
  Uint16  RMP26:1;    // 26  RMP for Mailbox 26
  Uint16  RMP27:1;    // 27  RMP for Mailbox 27
  Uint16  RMP28:1;    // 28  RMP for Mailbox 28
  Uint16  RMP29:1;    // 29  RMP for Mailbox 29
  Uint16  RMP30:1;    // 30  RMP for Mailbox 30
  Uint16  RMP31:1;    // 31  RMP for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANRMP_REG 
{
  Uint32               all ;
  struct  CANRMP_BITS  bit ;
} ;

// eCAN Received Message Lost register (CANRML) bit definitions
struct  CANRML_BITS 
{
   Uint16      RML0:1;     // 0   RML for Mailbox 0
   Uint16      RML1:1;     // 1   RML for Mailbox 1
   Uint16      RML2:1;     // 2   RML for Mailbox 2
   Uint16      RML3:1;     // 3   RML for Mailbox 3
   Uint16      RML4:1;     // 4   RML for Mailbox 4
   Uint16      RML5:1;     // 5   RML for Mailbox 5
   Uint16      RML6:1;     // 6   RML for Mailbox 6
   Uint16      RML7:1;     // 7   RML for Mailbox 7
   Uint16      RML8:1;     // 8   RML for Mailbox 8
   Uint16      RML9:1;     // 9   RML for Mailbox 9
   Uint16      RML10:1;    // 10  RML for Mailbox 10
   Uint16      RML11:1;    // 11  RML for Mailbox 11
   Uint16      RML12:1;    // 12  RML for Mailbox 12
   Uint16      RML13:1;    // 13  RML for Mailbox 13
   Uint16      RML14:1;    // 14  RML for Mailbox 14
   Uint16      RML15:1;    // 15  RML for Mailbox 15
   Uint16      RML16:1;    // 16  RML for Mailbox 16
   Uint16      RML17:1;    // 17  RML for Mailbox 17
   Uint16      RML18:1;    // 18  RML for Mailbox 18
   Uint16      RML19:1;    // 19  RML for Mailbox 19
   Uint16      RML20:1;    // 20  RML for Mailbox 20
   Uint16      RML21:1;    // 21  RML for Mailbox 21
   Uint16      RML22:1;    // 22  RML for Mailbox 22
   Uint16      RML23:1;    // 23  RML for Mailbox 23
   Uint16      RML24:1;    // 24  RML for Mailbox 24
   Uint16      RML25:1;    // 25  RML for Mailbox 25
   Uint16      RML26:1;    // 26  RML for Mailbox 26
   Uint16      RML27:1;    // 27  RML for Mailbox 27
   Uint16      RML28:1;    // 28  RML for Mailbox 28
   Uint16      RML29:1;    // 29  RML for Mailbox 29
   Uint16      RML30:1;    // 30  RML for Mailbox 30
   Uint16      RML31:1;    // 31  RML for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANRML_REG 
{
   Uint32              all;
   struct CANRML_BITS  bit;
} ;

// eCAN Remote Frame Pending register (CANRFP) bit definitions
struct  CANRFP_BITS 
{
   Uint16      RFP0:1;     // 0   RFP for Mailbox 0
   Uint16      RFP1:1;     // 1   RFP for Mailbox 1
   Uint16      RFP2:1;     // 2   RFP for Mailbox 2
   Uint16      RFP3:1;     // 3   RFP for Mailbox 3
   Uint16      RFP4:1;     // 4   RFP for Mailbox 4
   Uint16      RFP5:1;     // 5   RFP for Mailbox 5
   Uint16      RFP6:1;     // 6   RFP for Mailbox 6
   Uint16      RFP7:1;     // 7   RFP for Mailbox 7
   Uint16      RFP8:1;     // 8   RFP for Mailbox 8
   Uint16      RFP9:1;     // 9   RFP for Mailbox 9
   Uint16      RFP10:1;    // 10  RFP for Mailbox 10
   Uint16      RFP11:1;    // 11  RFP for Mailbox 11
   Uint16      RFP12:1;    // 12  RFP for Mailbox 12
   Uint16      RFP13:1;    // 13  RFP for Mailbox 13
   Uint16      RFP14:1;    // 14  RFP for Mailbox 14
   Uint16      RFP15:1;    // 15  RFP for Mailbox 15
   Uint16      RFP16:1;    // 16  RFP for Mailbox 16
   Uint16      RFP17:1;    // 17  RFP for Mailbox 17
   Uint16      RFP18:1;    // 18  RFP for Mailbox 18
   Uint16      RFP19:1;    // 19  RFP for Mailbox 19
   Uint16      RFP20:1;    // 20  RFP for Mailbox 20
   Uint16      RFP21:1;    // 21  RFP for Mailbox 21
   Uint16      RFP22:1;    // 22  RFP for Mailbox 22
   Uint16      RFP23:1;    // 23  RFP for Mailbox 23
   Uint16      RFP24:1;    // 24  RFP for Mailbox 24
   Uint16      RFP25:1;    // 25  RFP for Mailbox 25
   Uint16      RFP26:1;    // 26  RFP for Mailbox 26
   Uint16      RFP27:1;    // 27  RFP for Mailbox 27
   Uint16      RFP28:1;    // 28  RFP for Mailbox 28
   Uint16      RFP29:1;    // 29  RFP for Mailbox 29
   Uint16      RFP30:1;    // 30  RFP for Mailbox 30
   Uint16      RFP31:1;    // 31  RFP for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANRFP_REG 
{
   Uint32              all;
   struct CANRFP_BITS  bit;
} ;

// eCAN Global Acceptance Mask register (CANGAM) bit definitions
struct  CANGAM_BITS 
{
  Uint16  GAM150  : 16 ;  // 15:0  Global acceptance mask bits 0-15
  Uint16  GAM2816 : 13 ;  // 28:16 Global acceptance mask bits 16-28    
  Uint16  rsvd    :  2 ;  // 30:29 reserved        
  Uint16  AMI     :  1 ;  // 31    AMI bit
} ;

// Allow access to the bit fields or entire register
union CANGAM_REG 
{
  Uint32               all ;
  struct  CANGAM_BITS  bit ;
} ;

// eCAN Master Control register (CANMC) bit definitions
struct  CANMC_BITS 
{       // bits  description
  Uint16  MBNR :  5 ;  // 4:0   MBX # for CDR bit
  Uint16  SRES :  1 ;  // 5     Soft reset
  Uint16  STM  :  1 ;  // 6     Self-test mode
  Uint16  ABO  :  1 ;  // 7     Auto bus-on
  Uint16  CDR  :  1 ;  // 8     Change data request
  Uint16  WUBA :  1 ;  // 9     Wake-up on bus activity
  Uint16  DBO  :  1 ;  // 10    Data-byte order
  Uint16  PDR  :  1 ;  // 11    Power-down mode request
  Uint16  CCR  :  1 ;  // 12    Change configuration request
  Uint16  SCB  :  1 ;  // 13    SCC compatibility bit      
  Uint16  TCC  :  1 ;  // 14    TSC MSB clear bit
  Uint16  MBCC :  1 ;  // 15    TSC clear bit thru mailbox 16      
  Uint16  SUSP :  1 ;  // 16    SUSPEND free/soft bit
  Uint16  rsvd : 15 ;  // 31:17  reserved   
} ;

// Allow access to the bit fields or entire register
union CANMC_REG 
{
  Uint32              all ;
  struct  CANMC_BITS  bit ;
} ;

// eCAN Bit -timing configuration register (CANBTC) bit definitions
struct  CANBTC_BITS 
{
  Uint16  TSEG2REG : 3 ;  // 2:0   TSEG2 register value
  Uint16  TSEG1REG : 4 ;  // 6:3   TSEG1 register value
  Uint16  SAM      : 1 ;  // 7     Sample-point setting
  Uint16  SJWREG   : 2 ;  // 9:8   Synchroniztion Jump Width register value
  Uint16  rsvd1    : 6 ;  // 15:10 reserved   
  Uint16  BRPREG   : 8 ;  // 23:16 Baudrate prescaler register value
  Uint16  rsvd2    : 8 ;  // 31:24 reserved   
} ;

// Allow access to the bit fields or entire register
union CANBTC_REG 
{
  Uint32               all ;
  struct  CANBTC_BITS  bit ;
} ;

// eCAN Error & Status register (CANES) bit definitions
struct  CANES_BITS 
{
  Uint16   TM    :  1 ;  // 0     Transmit Mode
  Uint16   RM    :  1 ;  // 1     Receive Mode
  Uint16   rsvd1 :  1 ;  // 2     reserved   
  Uint16   PDA   :  1 ;  // 3     Power-down acknowledge
  Uint16   CCE   :  1 ;  // 4     Change Configuration Enable
  Uint16   SMA   :  1 ;  // 5     Suspend Mode Acknowledge
  Uint16   rsvd2 : 10 ;  // 15:6  reserved   
  Uint16   EW    :  1 ;  // 16    Warning status
  Uint16   EP    :  1 ;  // 17    Error Passive status
  Uint16   BO    :  1 ;  // 18    Bus-off status
  Uint16   ACKE  :  1 ;  // 19    Acknowledge error
  Uint16   SE    :  1 ;  // 20    Stuff error
  Uint16   CRCE  :  1 ;  // 21    CRC error
  Uint16   SA1   :  1 ;  // 22    Stuck at Dominant error
  Uint16   BE    :  1 ;  // 23    Bit error
  Uint16   FE    :  1 ;  // 24    Framing error
  Uint16   rsvd3 :  7 ;  // 31:25 reserved   
} ;

// Allow access to the bit fields or entire register
union CANES_REG 
{
  Uint32              all ;
  struct  CANES_BITS  bit ;
} ;


// eCAN Transmit Error Counter register (CANTEC) bit definitions
struct  CANTEC_BITS 
{
  Uint16  TEC   :  8 ;  // 7:0   TEC
  Uint16  rsvd1 :  8 ;  // 15:8  reserved
  Uint16  rsvd2 : 16 ;  // 31:16  reserved      
} ;

// Allow access to the bit fields or entire register
union CANTEC_REG 
{
  Uint32               all ;
  struct  CANTEC_BITS  bit ;
} ;

// eCAN Receive Error Counter register (CANREC) bit definitions
struct  CANREC_BITS 
{
  Uint16  REC   :  8 ;  // 7:0   REC
  Uint16  rsvd1 :  8 ;  // 15:8  reserved
  Uint16  rsvd2 : 16 ;  // 31:16 reserved      
} ;

// Allow access to the bit fields or entire register
union CANREC_REG 
{
  Uint32               all ;
  struct  CANREC_BITS  bit ;
} ;

// eCAN Global Interrupt Flag 0 (CANGIF0) bit definitions
struct  CANGIF0_BITS 
{
  Uint16   MIV0   :  5 ;  // 4:0   Mailbox Interrupt Vector
  Uint16   rsvd1  :  3 ;  // 7:5   reserved   
  Uint16   WLIF0  :  1 ;  // 8     Warning level interrupt flag
  Uint16   EPIF0  :  1 ;  // 9     Error-passive interrupt flag
  Uint16   BOIF0  :  1 ;  // 10    Bus-off interrupt flag
  Uint16   RMLIF0 :  1 ;  // 11    Received message lost interrupt flag
  Uint16   WUIF0  :  1 ;  // 12    Wakeup interrupt flag
  Uint16   WDIF0  :  1 ;  // 13    Write denied interrupt flag
  Uint16   AAIF0  :  1 ;  // 14    Abort Ack interrupt flag
  Uint16   GMIF0  :  1 ;  // 15    Global MBX interrupt flag
  Uint16   TCOF0  :  1 ;  // 16    TSC Overflow flag
  Uint16   MTOF0  :  1 ;  // 17    Mailbox Timeout flag
  Uint16   rsvd2  : 14 ;  // 31:18 reserved   
} ;

// Allow access to the bit fields or entire register
union CANGIF0_REG 
{
  Uint32                all ;
  struct  CANGIF0_BITS  bit ;
} ;

// eCAN Global Interrupt Mask register (CANGIM) bit definitions
struct  CANGIM_BITS 
{
  Uint16  I0EN  :  1 ;  // 0      Interrupt 0 enable
  Uint16  I1EN  :  1 ;  // 1      Interrupt 1 enable
  Uint16  GIL   :  1 ;  // 2      Global Interrupt Level
  Uint16  rsvd1 :  5 ;  // 7:3    reserved   
  Uint16  WLIM  :  1 ;  // 8      Warning level interrupt mask 
  Uint16  EPIM  :  1 ;  // 9      Error-passive interrupt mask
  Uint16  BOIM  :  1 ;  // 10     Bus-off interrupt mask
  Uint16  RMLIM :  1 ;  // 11     Received message lost interrupt mask
  Uint16  WUIM  :  1 ;  // 12     Wakeup interrupt mask
  Uint16  WDIM  :  1 ;  // 13     Write denied interrupt mask
  Uint16  AAIM  :  1 ;  // 14     Abort Ack interrupt mask
  Uint16  rsvd2 :  1 ;  // 15     reserved 
  Uint16  TCOM  :  1 ;  // 16     TSC overflow interrupt mask
  Uint16  MTOM  :  1 ;  // 17     MBX Timeout interrupt mask
  Uint16  rsvd3 : 14 ;  // 31:18  reserved   
} ;

// Allow access to the bit fields or entire register
union CANGIM_REG 
{
  Uint32               all ;
  struct  CANGIM_BITS  bit ;
} ;

// eCAN Global Interrupt Flag 1 (eCANGIF1) bit definitions
struct  CANGIF1_BITS 
{ 
  Uint16   MIV1   :  5 ;  // 4:0   Mailbox Interrupt Vector
  Uint16   rsvd1  :  3 ;  // 7:5   reserved   
  Uint16   WLIF1  :  1 ;  // 8     Warning level interrupt flag
  Uint16   EPIF1  :  1 ;  // 9     Error-passive interrupt flag
  Uint16   BOIF1  :  1 ;  // 10    Bus-off interrupt flag
  Uint16   RMLIF1 :  1 ;  // 11    Received message lost interrupt flag
  Uint16   WUIF1  :  1 ;  // 12    Wakeup interrupt flag
  Uint16   WDIF1  :  1 ;  // 13    Write denied interrupt flag
  Uint16   AAIF1  :  1 ;  // 14    Abort Ack interrupt flag
  Uint16   GMIF1  :  1 ;  // 15    Global MBX interrupt flag
  Uint16   TCOF1  :  1 ;  // 16    TSC Overflow flag
  Uint16   MTOF1  :  1 ;  // 17    Mailbox Timeout flag
  Uint16   rsvd2  : 14 ;  // 31:18 reserved   
} ;

// Allow access to the bit fields or entire register
union CANGIF1_REG 
{
  Uint32                all ;
  struct  CANGIF1_BITS  bit ;
} ;

// eCAN Mailbox Interrupt Mask register (CANMIM) bit definitions
struct  CANMIM_BITS 
{
   Uint16      MIM0:1;     // 0   MIM for Mailbox 0
   Uint16      MIM1:1;     // 1   MIM for Mailbox 1
   Uint16      MIM2:1;     // 2   MIM for Mailbox 2
   Uint16      MIM3:1;     // 3   MIM for Mailbox 3
   Uint16      MIM4:1;     // 4   MIM for Mailbox 4
   Uint16      MIM5:1;     // 5   MIM for Mailbox 5
   Uint16      MIM6:1;     // 6   MIM for Mailbox 6
   Uint16      MIM7:1;     // 7   MIM for Mailbox 7
   Uint16      MIM8:1;     // 8   MIM for Mailbox 8
   Uint16      MIM9:1;     // 9   MIM for Mailbox 9
   Uint16      MIM10:1;    // 10  MIM for Mailbox 10
   Uint16      MIM11:1;    // 11  MIM for Mailbox 11
   Uint16      MIM12:1;    // 12  MIM for Mailbox 12
   Uint16      MIM13:1;    // 13  MIM for Mailbox 13
   Uint16      MIM14:1;    // 14  MIM for Mailbox 14
   Uint16      MIM15:1;    // 15  MIM for Mailbox 15
   Uint16      MIM16:1;    // 16  MIM for Mailbox 16
   Uint16      MIM17:1;    // 17  MIM for Mailbox 17
   Uint16      MIM18:1;    // 18  MIM for Mailbox 18
   Uint16      MIM19:1;    // 19  MIM for Mailbox 19
   Uint16      MIM20:1;    // 20  MIM for Mailbox 20
   Uint16      MIM21:1;    // 21  MIM for Mailbox 21
   Uint16      MIM22:1;    // 22  MIM for Mailbox 22
   Uint16      MIM23:1;    // 23  MIM for Mailbox 23
   Uint16      MIM24:1;    // 24  MIM for Mailbox 24
   Uint16      MIM25:1;    // 25  MIM for Mailbox 25
   Uint16      MIM26:1;    // 26  MIM for Mailbox 26
   Uint16      MIM27:1;    // 27  MIM for Mailbox 27
   Uint16      MIM28:1;    // 28  MIM for Mailbox 28
   Uint16      MIM29:1;    // 29  MIM for Mailbox 29
   Uint16      MIM30:1;    // 30  MIM for Mailbox 30
   Uint16      MIM31:1;    // 31  MIM for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANMIM_REG 
{
  Uint32               all ;
  struct  CANMIM_BITS  bit ;
} ;

// eCAN Mailbox Interrupt Level register (CANMIL) bit definitions
struct  CANMIL_BITS 
{
   Uint16      MIL0:1;     // 0   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL1:1;     // 1   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL2:1;     // 2   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL3:1;     // 3   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL4:1;     // 4   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL5:1;     // 5   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL6:1;     // 6   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL7:1;     // 7   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL8:1;     // 8   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL9:1;     // 9   0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL10:1;    // 10  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL11:1;    // 11  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL12:1;    // 12  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL13:1;    // 13  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL14:1;    // 14  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL15:1;    // 15  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL16:1;    // 16  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL17:1;    // 17  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL18:1;    // 18  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL19:1;    // 19  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL20:1;    // 20  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL21:1;    // 21  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL22:1;    // 22  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL23:1;    // 23  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL24:1;    // 24  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL25:1;    // 25  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL26:1;    // 26  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL27:1;    // 27  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL28:1;    // 28  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL29:1;    // 29  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL30:1;    // 30  0 -> Int 9.5   1 -> Int 9.6
   Uint16      MIL31:1;    // 31  0 -> Int 9.5   1 -> Int 9.6
} ;

// Allow access to the bit fields or entire register
union CANMIL_REG 
{
  Uint32               all ;
  struct  CANMIL_BITS  bit ;
} ;

// eCAN Overwrite Protection Control register (CANOPC) bit definitions
struct  CANOPC_BITS 
{ 
   Uint16      OPC0:1;     // 0   OPC for Mailbox 0
   Uint16      OPC1:1;     // 1   OPC for Mailbox 1
   Uint16      OPC2:1;     // 2   OPC for Mailbox 2
   Uint16      OPC3:1;     // 3   OPC for Mailbox 3
   Uint16      OPC4:1;     // 4   OPC for Mailbox 4
   Uint16      OPC5:1;     // 5   OPC for Mailbox 5
   Uint16      OPC6:1;     // 6   OPC for Mailbox 6
   Uint16      OPC7:1;     // 7   OPC for Mailbox 7
   Uint16      OPC8:1;     // 8   OPC for Mailbox 8
   Uint16      OPC9:1;     // 9   OPC for Mailbox 9
   Uint16      OPC10:1;    // 10  OPC for Mailbox 10
   Uint16      OPC11:1;    // 11  OPC for Mailbox 11
   Uint16      OPC12:1;    // 12  OPC for Mailbox 12
   Uint16      OPC13:1;    // 13  OPC for Mailbox 13
   Uint16      OPC14:1;    // 14  OPC for Mailbox 14
   Uint16      OPC15:1;    // 15  OPC for Mailbox 15
   Uint16      OPC16:1;    // 16  OPC for Mailbox 16
   Uint16      OPC17:1;    // 17  OPC for Mailbox 17
   Uint16      OPC18:1;    // 18  OPC for Mailbox 18
   Uint16      OPC19:1;    // 19  OPC for Mailbox 19
   Uint16      OPC20:1;    // 20  OPC for Mailbox 20
   Uint16      OPC21:1;    // 21  OPC for Mailbox 21
   Uint16      OPC22:1;    // 22  OPC for Mailbox 22
   Uint16      OPC23:1;    // 23  OPC for Mailbox 23
   Uint16      OPC24:1;    // 24  OPC for Mailbox 24
   Uint16      OPC25:1;    // 25  OPC for Mailbox 25
   Uint16      OPC26:1;    // 26  OPC for Mailbox 26
   Uint16      OPC27:1;    // 27  OPC for Mailbox 27
   Uint16      OPC28:1;    // 28  OPC for Mailbox 28
   Uint16      OPC29:1;    // 29  OPC for Mailbox 29
   Uint16      OPC30:1;    // 30  OPC for Mailbox 30
   Uint16      OPC31:1;    // 31  OPC for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANOPC_REG 
{
  Uint32              all ;
  struct CANOPC_BITS  bit ;
} ;

// eCAN TX I/O Control Register (CANTIOC) bit definitions 
struct  CANTIOC_BITS 
{
  Uint16  rsvd1  :  3 ;  // 2:0   reserved
  Uint16  TXFUNC :  1 ;  // 3     TXFUNC
  Uint16  rsvd2  : 12 ;  // 15:4  reserved   
  Uint16  rsvd3  : 16 ;  // 31:16 reserved   
} ;

// Allow access to the bit fields or entire register
union CANTIOC_REG {
   Uint32               all;
   struct CANTIOC_BITS  bit;
} ;

// eCAN RX I/O Control Register (CANRIOC) bit definitions
struct  CANRIOC_BITS 
{ 
  Uint16  rsvd1  :  3 ;  // 2:0   reserved
  Uint16  RXFUNC :  1 ;  // 3     RXFUNC
  Uint16  rsvd2  : 12 ;  // 15:4  reserved   
  Uint16  rsvd3  : 16 ;  // 31:16 reserved   
} ;

// Allow access to the bit fields or entire register
union CANRIOC_REG 
{
  Uint32               all ;
  struct CANRIOC_BITS  bit ;
} ;

// eCAN Time-out Control register (CANTOC) bit definitions
struct  CANTOC_BITS 
{ 
   Uint16      TOC0:1;     // 0   TOC for Mailbox 0
   Uint16      TOC1:1;     // 1   TOC for Mailbox 1
   Uint16      TOC2:1;     // 2   TOC for Mailbox 2
   Uint16      TOC3:1;     // 3   TOC for Mailbox 3
   Uint16      TOC4:1;     // 4   TOC for Mailbox 4
   Uint16      TOC5:1;     // 5   TOC for Mailbox 5
   Uint16      TOC6:1;     // 6   TOC for Mailbox 6
   Uint16      TOC7:1;     // 7   TOC for Mailbox 7
   Uint16      TOC8:1;     // 8   TOC for Mailbox 8
   Uint16      TOC9:1;     // 9   TOC for Mailbox 9
   Uint16      TOC10:1;    // 10  TOC for Mailbox 10
   Uint16      TOC11:1;    // 11  TOC for Mailbox 11
   Uint16      TOC12:1;    // 12  TOC for Mailbox 12
   Uint16      TOC13:1;    // 13  TOC for Mailbox 13
   Uint16      TOC14:1;    // 14  TOC for Mailbox 14
   Uint16      TOC15:1;    // 15  TOC for Mailbox 15
   Uint16      TOC16:1;    // 16  TOC for Mailbox 16
   Uint16      TOC17:1;    // 17  TOC for Mailbox 17
   Uint16      TOC18:1;    // 18  TOC for Mailbox 18
   Uint16      TOC19:1;    // 19  TOC for Mailbox 19
   Uint16      TOC20:1;    // 20  TOC for Mailbox 20
   Uint16      TOC21:1;    // 21  TOC for Mailbox 21
   Uint16      TOC22:1;    // 22  TOC for Mailbox 22
   Uint16      TOC23:1;    // 23  TOC for Mailbox 23
   Uint16      TOC24:1;    // 24  TOC for Mailbox 24
   Uint16      TOC25:1;    // 25  TOC for Mailbox 25
   Uint16      TOC26:1;    // 26  TOC for Mailbox 26
   Uint16      TOC27:1;    // 27  TOC for Mailbox 27
   Uint16      TOC28:1;    // 28  TOC for Mailbox 28
   Uint16      TOC29:1;    // 29  TOC for Mailbox 29
   Uint16      TOC30:1;    // 30  TOC for Mailbox 30
   Uint16      TOC31:1;    // 31  TOC for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANTOC_REG 
{
  Uint32              all ;
  struct CANTOC_BITS  bit ;
} ;

// eCAN Time-out Status register (CANTOS) bit definitions
struct  CANTOS_BITS 
{
   Uint16      TOS0:1;     // 0   TOS for Mailbox 0
   Uint16      TOS1:1;     // 1   TOS for Mailbox 1
   Uint16      TOS2:1;     // 2   TOS for Mailbox 2
   Uint16      TOS3:1;     // 3   TOS for Mailbox 3
   Uint16      TOS4:1;     // 4   TOS for Mailbox 4
   Uint16      TOS5:1;     // 5   TOS for Mailbox 5
   Uint16      TOS6:1;     // 6   TOS for Mailbox 6
   Uint16      TOS7:1;     // 7   TOS for Mailbox 7
   Uint16      TOS8:1;     // 8   TOS for Mailbox 8
   Uint16      TOS9:1;     // 9   TOS for Mailbox 9
   Uint16      TOS10:1;    // 10  TOS for Mailbox 10
   Uint16      TOS11:1;    // 11  TOS for Mailbox 11
   Uint16      TOS12:1;    // 12  TOS for Mailbox 12
   Uint16      TOS13:1;    // 13  TOS for Mailbox 13
   Uint16      TOS14:1;    // 14  TOS for Mailbox 14
   Uint16      TOS15:1;    // 15  TOS for Mailbox 15
   Uint16      TOS16:1;    // 16  TOS for Mailbox 16
   Uint16      TOS17:1;    // 17  TOS for Mailbox 17
   Uint16      TOS18:1;    // 18  TOS for Mailbox 18
   Uint16      TOS19:1;    // 19  TOS for Mailbox 19
   Uint16      TOS20:1;    // 20  TOS for Mailbox 20
   Uint16      TOS21:1;    // 21  TOS for Mailbox 21
   Uint16      TOS22:1;    // 22  TOS for Mailbox 22
   Uint16      TOS23:1;    // 23  TOS for Mailbox 23
   Uint16      TOS24:1;    // 24  TOS for Mailbox 24
   Uint16      TOS25:1;    // 25  TOS for Mailbox 25
   Uint16      TOS26:1;    // 26  TOS for Mailbox 26
   Uint16      TOS27:1;    // 27  TOS for Mailbox 27
   Uint16      TOS28:1;    // 28  TOS for Mailbox 28
   Uint16      TOS29:1;    // 29  TOS for Mailbox 29
   Uint16      TOS30:1;    // 30  TOS for Mailbox 30
   Uint16      TOS31:1;    // 31  TOS for Mailbox 31
} ;

// Allow access to the bit fields or entire register
union CANTOS_REG 
{
  Uint32              all ;
  struct CANTOS_BITS  bit ;
} ;

//--------------------------------------------------------------------------
// eCAN Control and Status Register
//
struct ECAN_REGS 
{
  union  CANME_REG   CANME   ;  // Mailbox Enable
  union  CANMD_REG   CANMD   ;  // Mailbox Direction
  union  CANTRS_REG  CANTRS  ;  // Transmit Request Set
  union  CANTRR_REG  CANTRR  ;  // Transmit Request Reset
  union  CANTA_REG   CANTA   ;  // Transmit Acknowledge
  union  CANAA_REG   CANAA   ;  // Abort Acknowledge
  union  CANRMP_REG  CANRMP  ;  // Received Message Pending
  union  CANRML_REG  CANRML  ;  // Received Message Lost
  union  CANRFP_REG  CANRFP  ;  // Remote Frame Pending
  union  CANGAM_REG  CANGAM  ;  // Global Acceptance Mask       
  union  CANMC_REG   CANMC   ;  // Master Control
  union  CANBTC_REG  CANBTC  ;  // Bit Timing
  union  CANES_REG   CANES   ;  // Error Status
  union  CANTEC_REG  CANTEC  ;  // Transmit Error Counter
  union  CANREC_REG  CANREC  ;  // Receive Error Counter
  union  CANGIF0_REG CANGIF0 ;  // Global Interrupt Flag 0
  union  CANGIM_REG  CANGIM  ;  // Global Interrupt Mask 0
  union  CANGIF1_REG CANGIF1 ;  // Global Interrupt Flag 1
  union  CANMIM_REG  CANMIM  ;  // Mailbox Interrupt Mask
  union  CANMIL_REG  CANMIL  ;  // Mailbox Interrupt Level
  union  CANOPC_REG  CANOPC  ;  // Overwrite Protection Control
  union  CANTIOC_REG CANTIOC ;  // TX I/O Control
  union  CANRIOC_REG CANRIOC ;  // RX I/O Control
  Uint32 CANTSC              ;  // Time-stamp counter
  union  CANTOC_REG  CANTOC  ;  // Time-out Control
  union  CANTOS_REG  CANTOS  ;  // Time-out Status               
} ;


//===========================================================================
// eCAN Mailbox Register Bit Definitions : 
// ADDRESS : 0x00 6100 - 0x00 61FF
// Not EALLOW Protected 
//===========================================================================

// eCAN Message ID (MSGID) bit definitions
struct  CANMSGID_BITS 
{ 
  Uint16  EXTMSGID_L : 16 ;  // 0:15
  Uint16  EXTMSGID_H :  2 ;  // 16:17
  Uint16  STDMSGID   : 11 ;  // 18:28  
  Uint16  AAM        :  1 ;  // 29   
  Uint16  AME        :  1 ;  // 30
  Uint16  IDE        :  1 ;  // 31   
} ;

// Allow access to the bit fields or entire register 
union CANMSGID_REG 
{
  Uint32                all ;
  struct CANMSGID_BITS  bit ;
} ;

// eCAN Message Control Field (MSGCTRL) bit definitions
struct  CANMSGCTRL_BITS 
{ 
  Uint16  DLC   :  4 ;  // 0:3  
  Uint16  RTR   :  1 ;  // 4  
  Uint16  rsvd1 :  3 ;  // 7:5   reserved   
  Uint16  TPL   :  5 ;  // 12:8  
  Uint16  rsvd2 :  3 ;  // 15:13 reserved 
  Uint16  rsvd3 : 16 ;  // 31:16 reserved     
} ;

// Allow access to the bit fields or entire register 
union CANMSGCTRL_REG 
{
  Uint32                  all ;
  struct CANMSGCTRL_BITS  bit ;
} ;

// eCAN Message Data Register low (MDR_L) word definitions
struct  CANMDL_WORDS 
{
  Uint16  LOW_WORD : 16 ;  // 0:15  
  Uint16  HI_WORD  : 16 ;  // 31:16  
} ;

// eCAN Message Data Register low (MDR_L) byte definitions
struct  CANMDL_BYTES 
{ 
  Uint16   BYTE1 : 8 ;  // 0:7
  Uint16   BYTE2 : 8 ;  // 8:15
  Uint16   BYTE3 : 8 ;  // 16:23
  Uint16   BYTE4 : 8 ;  // 24:31      
} ;

// Allow access to the bit fields or entire register
union CANMDL_REG 
{
  Uint32                all  ;
  struct CANMDL_WORDS   word ;
  struct CANMDL_BYTES   byte ;      
} ;

// eCAN Message Data Register high  (MDR_H) word definitions
struct  CANMDH_WORDS 
{
  Uint16  LOW_WORD : 16 ;  // 0:15  
  Uint16  HI_WORD  : 16 ;  // 31:16  
} ;

// eCAN Message Data Register low (MDR_H) byte definitions
struct  CANMDH_BYTES 
{
  Uint16  BYTE5 : 8 ;  // 0:7  
  Uint16  BYTE6 : 8 ;  // 8:15
  Uint16  BYTE7 : 8 ;  // 16:23    
  Uint16  BYTE8 : 8 ;  // 24:31  
} ;

// Allow access to the bit fields or entire register
union CANMDH_REG 
{
  Uint32               all  ;
  struct CANMDH_WORDS  word ;
  struct CANMDH_BYTES  byte ;
} ;

struct MBOX 
{
  union CANMSGID_REG     MSGID   ; 
  union CANMSGCTRL_REG   MSGCTRL ;
  union CANMDL_REG       MDL     ;
  union CANMDH_REG       MDH     ;
} ;

//--------------------------------------------------------------------------
// eCAN Mailbox Register
//
struct ECAN_MBOXES 
{
   struct MBOX MBOX0;
   struct MBOX MBOX1;
   struct MBOX MBOX2;
   struct MBOX MBOX3;
   struct MBOX MBOX4;
   struct MBOX MBOX5;
   struct MBOX MBOX6;
   struct MBOX MBOX7;
   struct MBOX MBOX8;
   struct MBOX MBOX9;
   struct MBOX MBOX10;
   struct MBOX MBOX11;
   struct MBOX MBOX12;
   struct MBOX MBOX13;
   struct MBOX MBOX14;
   struct MBOX MBOX15;
   struct MBOX MBOX16;
   struct MBOX MBOX17;
   struct MBOX MBOX18;
   struct MBOX MBOX19;
   struct MBOX MBOX20;
   struct MBOX MBOX21;
   struct MBOX MBOX22;
   struct MBOX MBOX23;
   struct MBOX MBOX24;
   struct MBOX MBOX25;
   struct MBOX MBOX26;
   struct MBOX MBOX27;
   struct MBOX MBOX28;
   struct MBOX MBOX29;
   struct MBOX MBOX30;
   struct MBOX MBOX31;
} ;   

// eCAN Local Acceptance Mask (LAM) bit definitions
struct  CANLAM_BITS 
{
  Uint16  LAM_L : 16 ;  // 0:15  
  Uint16  LAM_H : 13 ;  // 16:28  
  Uint16  rsvd1 :  2 ;  // 29:30   reserved   
  Uint16  LAMI  :  1 ;  // 31 
} ;

// Allow access to the bit fields or entire register 
union CANLAM_REG 
{
  Uint32              all ;
  struct CANLAM_BITS  bit ;
} ;

// eCAN LAM File
struct LAM_REGS 
{
   union CANLAM_REG LAM0;
   union CANLAM_REG LAM1;
   union CANLAM_REG LAM2;
   union CANLAM_REG LAM3;
   union CANLAM_REG LAM4;
   union CANLAM_REG LAM5;
   union CANLAM_REG LAM6;
   union CANLAM_REG LAM7;
   union CANLAM_REG LAM8;
   union CANLAM_REG LAM9;
   union CANLAM_REG LAM10;
   union CANLAM_REG LAM11;
   union CANLAM_REG LAM12;
   union CANLAM_REG LAM13;
   union CANLAM_REG LAM14;
   union CANLAM_REG LAM15;
   union CANLAM_REG LAM16;
   union CANLAM_REG LAM17;
   union CANLAM_REG LAM18;
   union CANLAM_REG LAM19;
   union CANLAM_REG LAM20;
   union CANLAM_REG LAM21;
   union CANLAM_REG LAM22;
   union CANLAM_REG LAM23;
   union CANLAM_REG LAM24;
   union CANLAM_REG LAM25;
   union CANLAM_REG LAM26;
   union CANLAM_REG LAM27;
   union CANLAM_REG LAM28;
   union CANLAM_REG LAM29;
   union CANLAM_REG LAM30;
   union CANLAM_REG LAM31;
} ;

// Mailbox MOTS File

struct MOTS_REGS 
{
   Uint32 MOTS0;
   Uint32 MOTS1;
   Uint32 MOTS2;
   Uint32 MOTS3;
   Uint32 MOTS4;
   Uint32 MOTS5;
   Uint32 MOTS6;
   Uint32 MOTS7;
   Uint32 MOTS8;
   Uint32 MOTS9;
   Uint32 MOTS10;
   Uint32 MOTS11;
   Uint32 MOTS12;
   Uint32 MOTS13;
   Uint32 MOTS14;
   Uint32 MOTS15;
   Uint32 MOTS16;
   Uint32 MOTS17;
   Uint32 MOTS18;
   Uint32 MOTS19;
   Uint32 MOTS20;
   Uint32 MOTS21;
   Uint32 MOTS22;
   Uint32 MOTS23;
   Uint32 MOTS24;
   Uint32 MOTS25;
   Uint32 MOTS26;
   Uint32 MOTS27;
   Uint32 MOTS28;
   Uint32 MOTS29;
   Uint32 MOTS30;
   Uint32 MOTS31;
} ;

// Mailbox MOTO File
struct MOTO_REGS 
{
   Uint32 MOTO0;
   Uint32 MOTO1;
   Uint32 MOTO2;
   Uint32 MOTO3;
   Uint32 MOTO4;
   Uint32 MOTO5;
   Uint32 MOTO6;
   Uint32 MOTO7;
   Uint32 MOTO8;
   Uint32 MOTO9;
   Uint32 MOTO10;
   Uint32 MOTO11;
   Uint32 MOTO12;
   Uint32 MOTO13;
   Uint32 MOTO14;
   Uint32 MOTO15;
   Uint32 MOTO16;
   Uint32 MOTO17;
   Uint32 MOTO18;
   Uint32 MOTO19;
   Uint32 MOTO20;
   Uint32 MOTO21;
   Uint32 MOTO22;
   Uint32 MOTO23;
   Uint32 MOTO24;
   Uint32 MOTO25;
   Uint32 MOTO26;
   Uint32 MOTO27;
   Uint32 MOTO28;
   Uint32 MOTO29;
   Uint32 MOTO30;
   Uint32 MOTO31;
} ;

//---------------------------------------------------------------------------
// eCAN External References & Function Declarations:
//
volatile struct ECAN_REGS   CanCtrRegs ;
volatile struct ECAN_MBOXES CanMboRegs ;
volatile struct LAM_REGS    CanLamRegs ;
volatile struct MOTO_REGS   CanMtoRegs ;
volatile struct MOTS_REGS   CanMtsRegs ;

#pragma DATA_SECTION(CanCtrRegs,"CanCtrRegsFile") ;
#pragma DATA_SECTION(CanMboRegs,"CanMboRegsFile") ;
#pragma DATA_SECTION(CanLamRegs,"CanLamRegsFile") ;
#pragma DATA_SECTION(CanMtoRegs,"CanMtoRegsFile") ;
#pragma DATA_SECTION(CanMtsRegs,"CanMtsRegsFile") ;

/***************************************************************************/
/***  Peripheral Frame 2 Register Structure Setup                          */
/***************************************************************************/

//===========================================================================
// System Control Registers : SysCtrRegs
// ADDRESS : 0x00 7010 - 0x00 702F
// EALLOW Protected 
//===========================================================================

// High speed peripheral clock register bit definitions:
struct HISPCP_BITS  
{
  Uint16  HSPCLK :  3 ;   // 2:0   Rate relative to SYSCLKOUT
  Uint16  rsvd1  : 13 ;   // 15:3  reserved
} ;

union HISPCP_REG 
{
  Uint16              all ;
  struct HISPCP_BITS  bit ;
} ;

// Low speed peripheral clock register bit definitions:
struct LOSPCP_BITS  
{
  Uint16  LSPCLK :  3 ;  // 2:0   Rate relative to SYSCLKOUT
  Uint16  rsvd1  : 13 ;  // 15:3  reserved
} ;

union LOSPCP_REG 
{
  Uint16              all ;
  struct LOSPCP_BITS  bit ;
} ;

// Peripheral clock control register bit definitions:
struct PCLKCR_BITS  
{
  Uint16  EVAENCLK   : 1 ;  // 0     Enable high speed clk to EV-A
  Uint16  EVBENCLK   : 1 ;  // 1     Enable high speed clk to EV-B
  Uint16  rsvd1      : 1 ;  // 2 
  Uint16  ADCENCLK   : 1 ;  // 3     Enable high speed clk to ADC
  Uint16  rsvd2      : 4 ;  // 7:4   reserved
  Uint16  SPIENCLK   : 1 ;  // 8     Enable low speed clk to SPI
  Uint16  rsvd3      : 1 ;  // 9     reserved
  Uint16  SCIAENCLK  : 1 ;  // 10    Enable low speed clk to SCI-A
  Uint16  SCIBENCLK  : 1 ;  // 11    Enable low speed clk to SCI-B
  Uint16  MCBSPENCLK : 1 ;  // 12    Enable low speed clk to McBSP
  Uint16  rsvd4      : 1 ;  // 13    reserved
  Uint16  ECANENCLK  : 1 ;  // 14    Enable system clk to eCAN
} ;

union PCLKCR_REG 
{
  Uint16              all ;
  struct PCLKCR_BITS  bit ;
} ;   

// PLL control register bit definitions:
struct PLLCR_BITS 
{
  Uint16  DIV   :  4 ;  // 3:0   Set clock ratio for the PLL
  Uint16  rsvd1 : 12 ;  // 15:4  reserved
} ;

union PLLCR_REG 
{
  Uint16             all ;
  struct PLLCR_BITS  bit ;
} ;

// Low Power Mode 0 control register bit definitions:
struct LPMCR0_BITS 
{ 
  Uint16  LPM       : 2 ;  // 1:0   Set the low power mode
  Uint16  QUALSTDBY : 6 ;  // 7:2   Qualification   
  Uint16  rsvd1     : 8 ;  // 15:8  reserved
} ;

union LPMCR0_REG 
{
  Uint16              all ;
  struct LPMCR0_BITS  bit ;
} ;

// Low Power Mode 1 control register bit definitions:
struct LPMCR1_BITS 
{
  Uint16  XINT1   : 1 ;  // 0     Enable XINT1 to wake the device from standby
  Uint16  XNMI    : 1 ;  // 1     Enable XMNI to wake the device from standby
  Uint16  WDINT   : 1 ;  // 2     Enable watchdog interrupt to wake the device from standby
  Uint16  T1CTRIP : 1 ;  // 3     Enable T1CTRIP to wake the device from standby
  Uint16  T2CTRIP : 1 ;  // 4     Enable T2CTRIP to wake the device from standby
  Uint16  T3CTRIP : 1 ;  // 5     Enable T3CTRIP to wake the device from standby
  Uint16  T4CTRIP : 1 ;  // 6     Enable T4CTRIP to wake the device from standby
  Uint16  C1TRIP  : 1 ;  // 7     Enable C1TRIP to wake the device from standby
  Uint16  C2TRIP  : 1 ;  // 8     Enable C2TRIP to wake the device from standby
  Uint16  C3TRIP  : 1 ;  // 9     Enable C3TRIP to wake the device from standby
  Uint16  C4TRIP  : 1 ;  // 10    Enable C4TRIP to wake the device from standby
  Uint16  C5TRIP  : 1 ;  // 11    Enable C5TRIP to wake the device from standby
  Uint16  C6TRIP  : 1 ;  // 12    Enable C6TRIP to wake the device from standby
  Uint16  SCIRXA  : 1 ;  // 13    Enable SCIRXA to wake the device from standby
  Uint16  SCIRXB  : 1 ;  // 14    Enable SCIRXB to wake the device from standby
  Uint16  CANRX   : 1 ;  // 15    Enable CANRX to wake the device from standby
} ;

union LPMCR1_REG 
{
  Uint16              all ;
  struct LPMCR1_BITS  bit ;
} ;

//---------------------------------------------------------------------------
// System Control Register File:
struct SYS_CTRL_REGS 
{
  Uint16  rsvd1[10]            ;  // 0-9
  union   HISPCP_REG  HISPCP   ;  // 10: High-speed peripheral clock pre-scaler
  union   LOSPCP_REG  LOSPCP   ;  // 11: Low-speed peripheral clock pre-scaler
  union   PCLKCR_REG  PCLKCR   ;  // 12: Peripheral clock control register
  Uint16              rsvd2    ;  // 13: reserved
  union   LPMCR0_REG  LPMCR0   ;  // 14: Low-power mode control register 0
  union   LPMCR1_REG  LPMCR1   ;  // 15: Low-power mode control register 1
  Uint16              rsvd3    ;  // 16: reserved
  union   PLLCR_REG   PLLCR    ;  // 17: PLL control register
  // No bit definitions are defined for SCSR because
  // a read-modify-write instruction can clear the WDOVERRIDE bit
  Uint16              SCSR     ;  // 18: System control and status register
  Uint16              WDCNTR   ;  // 19: WD counter register
  Uint16              rsvd4    ;  // 20
  Uint16              WDKEY    ;  // 21: WD reset key register
  Uint16              rsvd5[3] ;  // 22-24
  // No bit definitions are defined for WDCR because
  // the proper value must be written to the WDCHK field
  // whenever writing to this register. 
  Uint16              WDCR     ;  // 25: WD timer control register
  Uint16              rsvd6[6] ;  // 26-31
} ;

volatile struct SYS_CTRL_REGS SysCtrRegs ;
#pragma DATA_SECTION(SysCtrRegs,"SysCtrRegsFile") ;

//===========================================================================
// Serial Periphral Interface - A Register Bit Defination : SpiAstRegs
// ADDRESS : 0x00 7040 - 0x00 704F
// Not EALLOW Protected 
//===========================================================================

// SPI FIFO Transmit register bit    definitions:
struct  SPIFFTX_BITS 
{ 
  Uint16  TXFFIL     : 5 ;   // 4:0    Interrupt level
  Uint16  TXFFIENA   : 1 ;   // 5      Interrupt enable
  Uint16  TXFFINTCLR : 1 ;   // 6      Clear INT flag
  Uint16  TXFFINT    : 1 ;   // 7      INT flag
  Uint16  TXFFST     : 5 ;   // 12:8   FIFO status
  Uint16  TXFIFO     : 1 ;   // 13     FIFO reset
  Uint16  SPIFFENA   : 1 ;   // 14     Enhancement enable
  Uint16  SPIRST     : 1 ;   // 15     Reset SPI
} ; 

union SPIFFTX_REG 
{
  Uint16               all ;
  struct SPIFFTX_BITS  bit ;
} ;

// SPI FIFO recieve register bit definitions:
struct  SPIFFRX_BITS 
{
  Uint16  RXFFIL      : 5 ;  // 4:0    Interrupt level
  Uint16  RXFFIENA    : 1 ;  // 5      Interrupt enable
  Uint16  RXFFINTCLR  : 1 ;  // 6      Clear INT flag
  Uint16  RXFFINT     : 1 ;  // 7      INT flag
  Uint16  RXFFST      : 5 ;  // 12:8   FIFO status
  Uint16  RXFIFORESET : 1 ;  // 13     FIFO reset
  Uint16  RXFFOVFCLR  : 1 ;  // 14     Clear overflow
  Uint16  RXFFOVF     : 1 ;  // 15     FIFO overflow
} ; 

union SPIFFRX_REG 
{
  Uint16               all ;
  struct SPIFFRX_BITS  bit ;
} ;

// SPI FIFO control register bit definitions:
struct  SPIFFCT_BITS 
{
  Uint16  TXDLY : 8 ;  // 7:0    FIFO transmit delay
  Uint16  rsvd  : 8 ;  // 15:8   reserved
} ;

union SPIFFCT_REG 
{
  Uint16               all ;
  struct SPIFFCT_BITS  bit ;
} ;
   
// SPI configuration register bit definitions:
struct  SPICCR_BITS 
{ 
  Uint16 SPICHAR     : 4 ;  // 3:0    Character length control
  Uint16 SPILBK      : 1 ;  // 4      Loop-back enable/disable
  Uint16 rsvd1       : 1 ;  // 5      reserved
  Uint16 CLKPOLARITY : 1 ;  // 6      Clock polarity
  Uint16 SPISWRESET  : 1 ;  // 7      SPI SW Reset
  Uint16 rsvd2       : 8 ;  // 15:8   reserved   
} ;

union SPICCR_REG 
{
  Uint16              all ;
  struct SPICCR_BITS  bit ;
} ;

// SPI operation control register bit definitions:
struct  SPICTL_BITS 
{     
  Uint16  SPIINTENA     :  1 ;  // 0      Interrupt enable
  Uint16  TALK          :  1 ;  // 1      Master/Slave transmit enable
  Uint16  MASTER_SLAVE  :  1 ;  // 2      Network control mode
  Uint16  CLK_PHASE     :  1 ;  // 3      Clock phase select
  Uint16  OVERRUNINTENA :  1 ;  // 4      Overrun interrupt enable
  Uint16  rsvd          : 11 ;  // 15:5   reserved      
} ;

union SPICTL_REG 
{
  Uint16              all ;
  struct SPICTL_BITS  bit ;
} ;

// SPI status register bit definitions:
struct  SPISTS_BITS 
{ 
  Uint16  rsvd1        : 5 ;  // 4:0    reserved
  Uint16  BUFFULL_FLAG : 1 ;  // 5      SPI transmit buffer full flag
  Uint16  INT_FLAG     : 1 ;  // 6      SPI interrupt flag
  Uint16  OVERRUN_FLAG : 1 ;  // 7      SPI reciever overrun flag
  Uint16  rsvd2        : 8 ;  // 15:8   reserved   
} ;

union SPISTS_REG 
{
  Uint16              all ;
  struct SPISTS_BITS  bit ;
} ; 

// SPI priority control register bit definitions:
struct  SPIPRI_BITS
{ 
  Uint16  rsvd1    : 4 ;  // 3:0    reserved
  Uint16  FREE     : 1 ;  // 4      Free emulation mode control
  Uint16  SOFT     : 1 ;  // 5      Soft emulation mode control
  Uint16  PRIORITY : 1 ;  // 6      Interrupt priority select
  Uint16  rsvd2    : 9 ;  // 15:7   reserved
} ;

union SPIPRI_REG 
{
  Uint16              all ;
  struct SPIPRI_BITS  bit ;
} ;       

// SPI Register File:
struct  SPI_REGS 
{ 
  union SPICCR_REG   SPICCR   ;  // Configuration register 
  union SPICTL_REG   SPICTL   ;  // Operation control register
  union SPISTS_REG   SPISTS   ;  // Status register
  Uint16             rsvd1    ;  // reserved
  Uint16             SPIBRR   ;  // Baud Rate
  Uint16             rsvd2    ;  // reserved
  Uint16             SPIRXEMU ;  // Emulation buffer
  Uint16             SPIRXBUF ;  // Serial input buffer
  Uint16             SPITXBUF ;  // Serial output buffer
  Uint16             SPIDAT   ;  // Serial data 
  union SPIFFTX_REG  SPIFFTX  ;  // FIFO transmit register
  union SPIFFRX_REG  SPIFFRX  ;  // FIFO recieve register
  union SPIFFCT_REG  SPIFFCT  ;  // FIFO control register
  Uint16             rsvd3[2] ;  // reserved
  union SPIPRI_REG   SPIPRI   ;  // FIFO Priority control
} ;

// SPI External References & Function Declarations:
volatile struct SPI_REGS SpiAstRegs ;
#pragma DATA_SECTION(SpiAstRegs,"SpiAstRegsFile") ;

//===========================================================================
// Serial Communication Interface - A,B Register Bit Defination : SciAstRegs
// ADDRESS : 0x00 7050 - 0x00 705F
// Not EALLOW Protected 
//===========================================================================

// SCICCR communication control register bit definitions:
struct  SCICCR_BITS 
{ 
  Uint16  SCICHAR       : 3 ;   // 2:0    Character length control        
  Uint16  ADDRIDLE_MODE : 1 ;   // 3      ADDR/IDLE Mode control
  Uint16  LOOPBKENA     : 1 ;   // 4      Loop Back enable
  Uint16  PARITYENA     : 1 ;   // 5      Parity enable   
  Uint16  PARITY        : 1 ;   // 6      Even or Odd Parity
  Uint16  STOPBITS      : 1 ;   // 7      Number of Stop Bits
  Uint16  rsvd1         : 8 ;   // 15:8   reserved
} ; 


union SCICCR_REG 
{
  Uint16              all ;
  struct SCICCR_BITS  bit ;
} ;

// SCICTL1 control register 1 bit definitions:
struct  SCICTL1_BITS 
{ 
  Uint16  RXENA       : 1 ;  // 0      SCI receiver enable
  Uint16  TXENA       : 1 ;  // 1      SCI transmitter enable
  Uint16  SLEEP       : 1 ;  // 2      SCI sleep  
  Uint16  TXWAKE      : 1 ;  // 3      Transmitter wakeup method
  Uint16  rsvd        : 1 ;  // 4      reserved
  Uint16  SWRESET     : 1 ;  // 5      Software reset   
  Uint16  RXERRINTENA : 1 ;  // 6      Recieve interrupt enable
  Uint16  rsvd1       : 9 ;  // 15:7   reserved
} ; 

union SCICTL1_REG 
{
  Uint16               all ;
  struct SCICTL1_BITS  bit ;
} ;


// SCICTL2 control register 2 bit definitions:
struct  SCICTL2_BITS 
{ 
  Uint16  TXINTENA   : 1 ;   // 0      Transmit interrupt enable    
  Uint16  RXBKINTENA : 1 ;   // 1      Receiver-buffer break enable
  Uint16  rsvd       : 4 ;   // 5:2    reserved
  Uint16  TXEMPTY    : 1 ;   // 6      Transmitter empty flag
  Uint16  TXRDY      : 1 ;   // 7      Transmitter ready flag  
  Uint16  rsvd1      : 8 ;   // 15:8   reserved
} ; 

union SCICTL2_REG 
{
  Uint16               all ;
  struct SCICTL2_BITS  bit ;
} ;


// SCIRXST Receiver status register bit definitions:
struct  SCIRXST_BITS 
{ 
  Uint16  rsvd    : 1 ;   // 0      reserved
  Uint16  RXWAKE  : 1 ;   // 1      Receiver wakeup detect flag
  Uint16  PE      : 1 ;   // 2      Parity error flag
  Uint16  OE      : 1 ;   // 3      Overrun error flag
  Uint16  FE      : 1 ;   // 4      Framing error flag
  Uint16  BRKDT   : 1 ;   // 5      Break-detect flag   
  Uint16  RXRDY   : 1 ;   // 6      Receiver ready flag
  Uint16  RXERROR : 1 ;   // 7      Receiver error flag
} ; 

union SCIRXST_REG 
{
  Uint16               all ;
  struct SCIRXST_BITS  bit ;
} ;

// SCIRXBUF Receiver Data Buffer with FIFO bit definitions:
struct  SCIRXBUF_BITS 
{ 
  Uint16  RXDT    : 8 ;   // 7:0    Receive word
  Uint16  rsvd    : 6 ;   // 13:8   reserved
  Uint16  SCIFFPE : 1 ;   // 14     SCI PE error in FIFO mode
  Uint16  SCIFFFE : 1 ;   // 15     SCI FE error in FIFO mode
} ;

union SCIRXBUF_REG 
{
  Uint16                all ;
  struct SCIRXBUF_BITS  bit ;
} ;


// SCIPRI Priority control register bit definitions:
struct  SCIPRI_BITS 
{ 
  Uint16  rsvd  : 3 ;  // 2:0    reserved
  Uint16  FREE  : 1 ;  // 3      Free emulation suspend mode
  Uint16  SOFT  : 1 ;  // 4      Soft emulation suspend mode
  Uint16  rsvd1 : 3 ;  // 7:5    reserved
} ; 

union SCIPRI_REG 
{
  Uint16              all ;
  struct SCIPRI_BITS  bit ;
} ;

// SCI FIFO Transmit register bit definitions:
struct  SCIFFTX_BITS 
{
  Uint16  TXFFILIL     : 5 ;  // 4:0    Interrupt level
  Uint16  TXFFIENA     : 1 ;  // 5      Interrupt enable
  Uint16  TXINTCLR     : 1 ;  // 6      Clear INT flag
  Uint16  TXFFINT      : 1 ;  // 7      INT flag
  Uint16  TXFFST       : 5 ;  // 12:8   FIFO status
  Uint16  TXFIFOXRESET : 1 ;  // 13     FIFO reset
  Uint16  SCIFFENA     : 1 ;  // 14     Enhancement enable
  Uint16  SCIRST       : 1 ;  // 15     SCI reset rx/tx channels 
} ; 

union SCIFFTX_REG 
{
  Uint16               all ;
  struct SCIFFTX_BITS  bit ;
} ;

// SCI FIFO recieve register bit definitions:
struct  SCIFFRX_BITS 
{       // bits   description
  Uint16  RXFFIL      : 5 ;   // 4:0    Interrupt level
  Uint16  RXFFIENA    : 1 ;   // 5      Interrupt enable
  Uint16  RXFFINTCLR  : 1 ;   // 6      Clear INT flag
  Uint16  RXFFINT     : 1 ;   // 7      INT flag
  Uint16  RXFIFST     : 5 ;   // 12:8   FIFO status
  Uint16  RXFIFORESET : 1 ;   // 13     FIFO reset
  Uint16  RXFFOVRCLR  : 1 ;   // 14     Clear overflow
  Uint16  RXFFOVF     : 1 ;   // 15     FIFO overflow
} ; 

union SCIFFRX_REG 
{
  Uint16               all ;
  struct SCIFFRX_BITS  bit ;
} ;

// SCI FIFO control register bit definitions:
struct  SCIFFCT_BITS 
{ 
  Uint16  FFTXDLY : 8 ;  // 7:0    FIFO transmit delay
  Uint16  rsvd    : 5 ;  // 12:8   reserved
  Uint16  CDC     : 1 ;  // 13     Auto baud mode enable
  Uint16  ABDCLR  : 1 ;  // 14     Auto baud clear
  Uint16  ABD     : 1 ;  // 15     Auto baud detect
} ;

union SCIFFCT_REG 
{
  Uint16               all ;
  struct SCIFFCT_BITS  bit ;
} ;

// SCI Register File:
struct  SCI_REGS 
{
  union SCICCR_REG     SCICCR   ;  // Communications control register
  union SCICTL1_REG    SCICTL1  ;  // Control register 1
  Uint16               SCIHBAUD ;  // Baud rate (high) register
  Uint16               SCILBAUD ;  // Baud rate (low) register
  union SCICTL2_REG    SCICTL2  ;  // Control register 2
  union SCIRXST_REG    SCIRXST  ;  // Recieve status register
  Uint16               SCIRXEMU ;  // Recieve emulation buffer register
  union SCIRXBUF_REG   SCIRXBUF ;  // Recieve data buffer  
  Uint16               rsvd1    ;  // reserved
  Uint16               SCITXBUF ;  // Transmit data buffer 
  union SCIFFTX_REG    SCIFFTX  ;  // FIFO transmit register
  union SCIFFRX_REG    SCIFFRX  ;  // FIFO recieve register
  union SCIFFCT_REG    SCIFFCT  ;  // FIFO control register
  Uint16               rsvd2    ;  // reserved
  Uint16               rsvd3    ;  // reserved
  union SCIPRI_REG     SCIPRI   ;  // FIFO Priority control   
} ;

// SCI External References & Function Declarations:
volatile struct SCI_REGS SciAstRegs ;
volatile struct SCI_REGS SciBstRegs ;
#pragma DATA_SECTION(SciAstRegs,"SciAstRegsFile") ;
#pragma DATA_SECTION(SciBstRegs,"SciBstRegsFile") ;

//===========================================================================
// External Interrupt Register Bit Defination : SciAstRegs
// ADDRESS : 0x00 7070 - 0x00 707F
// Not EALLOW Protected 
//===========================================================================

struct XINTCR_BITS 
{
  Uint16   ENABLE   :  1 ;  // 0      enable/disable
  Uint16   rsvd1    :  1 ;  // 1      reserved
  Uint16   POLARITY :  1 ;  // 2      pos/neg triggered
  Uint16   rsvd2    : 12 ;  // 15:3   reserved
} ;

union XINTCR_REG 
{
  Uint16               all ;
  struct XINTCR_BITS   bit ;
} ;  

struct XNMICR_BITS 
{
  Uint16  ENABLE   :  1 ;  // 0      enable/disable
  Uint16  SELECT   :  1 ;  // 1      Timer 1 or XNMI connected to INT13
  Uint16  POLARITY :  1 ;  // 2      pos/neg triggered
  Uint16  rsvd2    : 12 ;  // 15:3   reserved
} ;

union XNMICR_REG 
{
  Uint16               all ;
  struct XNMICR_BITS   bit ;
} ;  

//---------------------------------------------------------------------------
// External Interrupt Register File:
struct XINTRUPT_REGS 
{
  union   XINTCR_REG  XINT1CR ;
  union   XINTCR_REG  XINT2CR ;
  Uint16  rsvd1[5]            ;
  union   XNMICR_REG  XNMICR  ;
  Uint16  XINT1CTR            ;
  Uint16  XINT2CTR            ;
  Uint16  rsvd[5]             ;
  Uint16  XNMICTR             ;
} ;

//---------------------------------------------------------------------------
// External Interrupt References & Function Declarations:
volatile struct XINTRUPT_REGS ExtIntRegs ;
#pragma DATA_SECTION(ExtIntRegs,"ExtIntRegsFile") ;

//===========================================================================
// General Purpose Input Output Mux Register Bit Defination : SciAstRegs
// ADDRESS : 0x00 70C0 - 0x00 70DF
// EALLOW Protected 
//===========================================================================

// GPIO A mux control register bit definitions
struct GPAMUX_BITS  
{        
	Uint16  PWM1_GPIOA0     : 1 ;  // 0  
  Uint16  PWM2_GPIOA1     : 1 ;  // 1 
  Uint16  PWM3_GPIOA2     : 1 ;  // 2  
  Uint16  PWM4_GPIOA3     : 1 ;  // 3  
  Uint16  PWM5_GPIOA4     : 1 ;  // 4  
  Uint16  PWM6_GPIOA5     : 1 ;  // 5
  Uint16  T1PWM_GPIOA6    : 1 ;  // 6  
  Uint16  T2PWM_GPIOA7    : 1 ;  // 7        
  Uint16  CAP1Q1_GPIOA8   : 1 ;  // 8 
  Uint16  CAP2Q2_GPIOA9   : 1 ;  // 9 
  Uint16  CAP3QI1_GPIOA10 : 1 ;  // 10
  Uint16  TDIRA_GPIOA11   : 1 ;  // 11
  Uint16  TCLKINA_GPIOA12 : 1 ;  // 12
  Uint16  C1TRIP_GPIOA13  : 1 ;  // 13  
  Uint16  C2TRIP_GPIOA14  : 1 ;  // 14  
  Uint16  C3TRIP_GPIOA15  : 1 ;  // 15   
} ;     
        
union GPAMUX_REG 
{
  Uint16             all ;
  struct GPAMUX_BITS bit ;
} ;      
        
// GPIO A Direction control register bit definitions                                    
    
struct GPADIR_BITS  
{ 
  Uint16  GPIOA0  : 1 ;  // 0  
  Uint16  GPIOA1  : 1 ;  // 1 
  Uint16  GPIOA2  : 1 ;  // 2  
  Uint16  GPIOA3  : 1 ;  // 3  
  Uint16  GPIOA4  : 1 ;  // 4  
  Uint16  GPIOA5  : 1 ;  // 5
  Uint16  GPIOA6  : 1 ;  // 6  
  Uint16  GPIOA7  : 1 ;  // 7        
  Uint16  GPIOA8  : 1 ;  // 8 
  Uint16  GPIOA9  : 1 ;  // 9 
  Uint16  GPIOA10 : 1 ;  // 10
  Uint16  GPIOA11 : 1 ;  // 11
  Uint16  GPIOA12 : 1 ;  // 12
  Uint16  GPIOA13 : 1 ;  // 13  
  Uint16  GPIOA14 : 1 ;  // 14  
  Uint16  GPIOA15 : 1 ;  // 15   
} ;

union GPADIR_REG 
{
  Uint16             all ;
  struct GPADIR_BITS bit ;
} ;


// GPA Qualregister bit definitions
struct GPAQUAL_BITS 
{ 
  Uint16  QUALPRD : 8 ;  // 0:7    Qualification Sampling Period
  Uint16  rsvd1   : 8 ;  // 15:8   reserved
} ; 

union GPAQUAL_REG 
{
  Uint16               all ;
  struct GPAQUAL_BITS  bit ;
} ;          

// GPIO A Data register bit definitions                                    
struct GPADAT_BITS  
{  
   Uint16  GPIOA0  : 1 ;   // 0  
   Uint16  GPIOA1  : 1 ;   // 1 
   Uint16  GPIOA2  : 1 ;   // 2  
   Uint16  GPIOA3  : 1 ;   // 3  
   Uint16  GPIOA4  : 1 ;   // 4  
   Uint16  GPIOA5  : 1 ;   // 5
   Uint16  GPIOA6  : 1 ;   // 6  
   Uint16  GPIOA7  : 1 ;   // 7        
   Uint16  GPIOA8  : 1 ;   // 8 
   Uint16  GPIOA9  : 1 ;   // 9 
   Uint16  GPIOA10 : 1 ;   // 10
   Uint16  GPIOA11 : 1 ;   // 11
   Uint16  GPIOA12 : 1 ;   // 12
   Uint16  GPIOA13 : 1 ;   // 13  
   Uint16  GPIOA14 : 1 ;   // 14  
   Uint16  GPIOA15 : 1 ;   // 15   
} ;

union GPADAT_REG 
{
  Uint16              all ;
  struct GPADAT_BITS  bit ;
} ;

// GPIO A Data set bit definitions                                    
struct GPASET_BITS  
{ 
  Uint16  GPIOA0  : 1 ;  // 0  
  Uint16  GPIOA1  : 1 ;  // 1 
  Uint16  GPIOA2  : 1 ;  // 2  
  Uint16  GPIOA3  : 1 ;  // 3  
  Uint16  GPIOA4  : 1 ;  // 4  
  Uint16  GPIOA5  : 1 ;  // 5
  Uint16  GPIOA6  : 1 ;  // 6  
  Uint16  GPIOA7  : 1 ;  // 7        
  Uint16  GPIOA8  : 1 ;  // 8 
  Uint16  GPIOA9  : 1 ;  // 9 
  Uint16  GPIOA10 : 1 ;  // 10
  Uint16  GPIOA11 : 1 ;  // 11
  Uint16  GPIOA12 : 1 ;  // 12
  Uint16  GPIOA13 : 1 ;  // 13  
  Uint16  GPIOA14 : 1 ;  // 14  
  Uint16  GPIOA15 : 1 ;  // 15   
} ;

union GPASET_REG 
{
  Uint16              all ;
  struct GPASET_BITS  bit ;
} ;

// GPIO A Data clear register bit definitions                                    
struct GPACLEAR_BITS  
{
  Uint16  GPIOA0  : 1 ;   // 0  
  Uint16  GPIOA1  : 1 ;   // 1 
  Uint16  GPIOA2  : 1 ;   // 2  
  Uint16  GPIOA3  : 1 ;   // 3  
  Uint16  GPIOA4  : 1 ;   // 4  
  Uint16  GPIOA5  : 1 ;   // 5
  Uint16  GPIOA6  : 1 ;   // 6  
  Uint16  GPIOA7  : 1 ;   // 7        
  Uint16  GPIOA8  : 1 ;   // 8 
  Uint16  GPIOA9  : 1 ;   // 9 
  Uint16  GPIOA10 : 1 ;   // 10
  Uint16  GPIOA11 : 1 ;   // 11
  Uint16  GPIOA12 : 1 ;   // 12
  Uint16  GPIOA13 : 1 ;   // 13  
  Uint16  GPIOA14 : 1 ;   // 14  
  Uint16  GPIOA15 : 1 ;   // 15   
} ;

union GPACLEAR_REG 
{
  Uint16                all ;
  struct GPACLEAR_BITS  bit ;
} ;

// GPIO A Data toggle register bit definitions                                    
struct GPATOGGLE_BITS  
{ 
   Uint16  GPIOA0  : 1 ;   // 0  
   Uint16  GPIOA1  : 1 ;   // 1 
   Uint16  GPIOA2  : 1 ;   // 2  
   Uint16  GPIOA3  : 1 ;   // 3  
   Uint16  GPIOA4  : 1 ;   // 4  
   Uint16  GPIOA5  : 1 ;   // 5
   Uint16  GPIOA6  : 1 ;   // 6  
   Uint16  GPIOA7  : 1 ;   // 7        
   Uint16  GPIOA8  : 1 ;   // 8 
   Uint16  GPIOA9  : 1 ;   // 9 
   Uint16  GPIOA10 : 1 ;   // 10
   Uint16  GPIOA11 : 1 ;   // 11
   Uint16  GPIOA12 : 1 ;   // 12
   Uint16  GPIOA13 : 1 ;   // 13  
   Uint16  GPIOA14 : 1 ;   // 14  
   Uint16  GPIOA15 : 1 ;   // 15   
} ;

union GPATOGGLE_REG 
{
  Uint16                 all ;
  struct GPATOGGLE_BITS  bit ;
} ;

// GPIO B mux control register bit definitions                                    
struct GPBMUX_BITS  
{ 
  Uint16  PWM7_GPIOB0     : 1 ;  // 0  
  Uint16  PWM8_GPIOB1     : 1 ;  // 1 
  Uint16  PWM9_GPIOB2     : 1 ;  // 2  
  Uint16  PWM10_GPIOB3    : 1 ;  // 3  
  Uint16  PWM11_GPIOB4    : 1 ;  // 4  
  Uint16  PWM12_GPIOB5    : 1 ;  // 5
  Uint16  T3PWM_GPIOB6    : 1 ;  // 6  
  Uint16  T4PWM_GPIOB7    : 1 ;  // 7        
  Uint16  CAP4Q1_GPIOB8   : 1 ;  // 8 
  Uint16  CAP5Q2_GPIOB9   : 1 ;  // 9 
  Uint16  CAP6QI2_GPIOB10 : 1 ;  // 10
  Uint16  TDIRB_GPIOB11   : 1 ;  // 11
  Uint16  TCLKINB_GPIOB12 : 1 ;  // 12
  Uint16  C4TRIP_GPIOB13  : 1 ;  // 13  
  Uint16  C5TRIP_GPIOB14  : 1 ;  // 14  
  Uint16  C6TRIP_GPIOB15  : 1 ;  // 15   
} ;

union GPBMUX_REG 
{
  Uint16              all ;
  struct GPBMUX_BITS  bit ;
} ;

// GPIO B Direction control register bit definitions                                    
struct GPBDIR_BITS  
{ 
   Uint16 GPIOB0:1;          // 0  
   Uint16 GPIOB1:1;          // 1 
   Uint16 GPIOB2:1;          // 2  
   Uint16 GPIOB3:1;          // 3  
   Uint16 GPIOB4:1;          // 4  
   Uint16 GPIOB5:1;          // 5
   Uint16 GPIOB6:1;          // 6  
   Uint16 GPIOB7:1;          // 7        
   Uint16 GPIOB8:1;          // 8 
   Uint16 GPIOB9:1;          // 9 
   Uint16 GPIOB10:1;         // 10
   Uint16 GPIOB11:1;         // 11
   Uint16 GPIOB12:1;         // 12
   Uint16 GPIOB13:1;         // 13  
   Uint16 GPIOB14:1;         // 14  
   Uint16 GPIOB15:1;         // 15   
} ;

union GPBDIR_REG 
{
  Uint16             all;
  struct GPBDIR_BITS bit;
};


// GPB Qualregister bit definitions 
struct GPBQUAL_BITS 
{  
	Uint16 QUALPRD:8;     // 0:7    Qualification Sampling Period
  Uint16 rsvd1:8;       // 15:8   reserved
} ;

union GPBQUAL_REG 
{
  Uint16               all ;
  struct GPBQUAL_BITS  bit ;
} ;           

// GPIO B data register bit definitions                                    
struct GPBDAT_BITS  
{  
   Uint16 GPIOB0:1;          // 0  
   Uint16 GPIOB1:1;          // 1 
   Uint16 GPIOB2:1;          // 2  
   Uint16 GPIOB3:1;          // 3  
   Uint16 GPIOB4:1;          // 4  
   Uint16 GPIOB5:1;          // 5
   Uint16 GPIOB6:1;          // 6  
   Uint16 GPIOB7:1;          // 7        
   Uint16 GPIOB8:1;          // 8 
   Uint16 GPIOB9:1;          // 9 
   Uint16 GPIOB10:1;         // 10
   Uint16 GPIOB11:1;         // 11
   Uint16 GPIOB12:1;         // 12
   Uint16 GPIOB13:1;         // 13  
   Uint16 GPIOB14:1;         // 14  
   Uint16 GPIOB15:1;         // 15   
} ;

union GPBDAT_REG 
{
  Uint16              all ;
  struct GPBDAT_BITS  bit ;
} ;

// GPIO B data set register bit definitions                                    
struct GPBSET_BITS  
{
   Uint16 GPIOB0:1;          // 0  
   Uint16 GPIOB1:1;          // 1 
   Uint16 GPIOB2:1;          // 2  
   Uint16 GPIOB3:1;          // 3  
   Uint16 GPIOB4:1;          // 4  
   Uint16 GPIOB5:1;          // 5
   Uint16 GPIOB6:1;          // 6  
   Uint16 GPIOB7:1;          // 7        
   Uint16 GPIOB8:1;          // 8 
   Uint16 GPIOB9:1;          // 9 
   Uint16 GPIOB10:1;         // 10
   Uint16 GPIOB11:1;         // 11
   Uint16 GPIOB12:1;         // 12
   Uint16 GPIOB13:1;         // 13  
   Uint16 GPIOB14:1;         // 14  
   Uint16 GPIOB15:1;         // 15   
} ;

union GPBSET_REG 
{
  Uint16              all ;
  struct GPBSET_BITS  bit ;
} ;

// GPIO B data clear register bit definitions                                    
struct GPBCLEAR_BITS  
{
   Uint16 GPIOB0:1;          // 0  
   Uint16 GPIOB1:1;          // 1 
   Uint16 GPIOB2:1;          // 2  
   Uint16 GPIOB3:1;          // 3  
   Uint16 GPIOB4:1;          // 4  
   Uint16 GPIOB5:1;          // 5
   Uint16 GPIOB6:1;          // 6  
   Uint16 GPIOB7:1;          // 7        
   Uint16 GPIOB8:1;          // 8 
   Uint16 GPIOB9:1;          // 9 
   Uint16 GPIOB10:1;         // 10
   Uint16 GPIOB11:1;         // 11
   Uint16 GPIOB12:1;         // 12
   Uint16 GPIOB13:1;         // 13  
   Uint16 GPIOB14:1;         // 14  
   Uint16 GPIOB15:1;         // 15   
} ;

union GPBCLEAR_REG 
{
  Uint16                all ;
  struct GPBCLEAR_BITS  bit ;
} ;

// GPIO B data toggle register bit definitions                                    
struct GPBTOGGLE_BITS  
{
   Uint16 GPIOB0:1;          // 0  
   Uint16 GPIOB1:1;          // 1 
   Uint16 GPIOB2:1;          // 2  
   Uint16 GPIOB3:1;          // 3  
   Uint16 GPIOB4:1;          // 4  
   Uint16 GPIOB5:1;          // 5
   Uint16 GPIOB6:1;          // 6  
   Uint16 GPIOB7:1;          // 7        
   Uint16 GPIOB8:1;          // 8 
   Uint16 GPIOB9:1;          // 9 
   Uint16 GPIOB10:1;         // 10
   Uint16 GPIOB11:1;         // 11
   Uint16 GPIOB12:1;         // 12
   Uint16 GPIOB13:1;         // 13  
   Uint16 GPIOB14:1;         // 14  
   Uint16 GPIOB15:1;         // 15   
} ;

union GPBTOGGLE_REG 
{
  Uint16                 all ;
  struct GPBTOGGLE_BITS  bit ;
} ;

// GPIO D mux control register bit definitions                                    
struct GPDMUX_BITS  
{                  // bits  description
  Uint16 T1CTRIP_PDPA_GPIOD0:1;       // 0  
  Uint16 T2CTRIP_SOCA_GPIOD1:1;       // 1   
  Uint16 rsvd1:3;                     // 4:2  
  Uint16 T3CTRIP_PDPB_GPIOD5:1;       // 5  
  Uint16 T4CTRIP_SOCB_GPIOD6:1;       // 6   
  Uint16 rsvd2:9;                     // 15:7  
} ;

union GPDMUX_REG 
{
  Uint16              all ;
  struct GPDMUX_BITS  bit ;
} ;

//----------------------------------------------------
// GPIO D Direction control register bit definitions 
//                                     
//
struct GPDDIR_BITS  
{
  Uint16 GPIOD0:1;          // 0  
  Uint16 GPIOD1:1;          // 1 
  Uint16 rsvd1:3;           // 4:2  
  Uint16 GPIOD5:1;          // 5
  Uint16 GPIOD6:1;          // 6  
  Uint16 rsvd2:9;           // 15:7
} ;

union GPDDIR_REG 
{
  Uint16              all ;
  struct GPDDIR_BITS  bit ;
} ;

// GPIO D data register bit definitions 
struct GPDDAT_BITS  
{ 
   Uint16 GPIOD0:1;          // 0  
   Uint16 GPIOD1:1;          // 1 
   Uint16 rsvd1:3;           // 4:2  
   Uint16 GPIOD5:1;          // 5
   Uint16 GPIOD6:1;          // 6  
   Uint16 rsvd2:9;           // 15:7
} ;           

union GPDDAT_REG 
{
  Uint16              all ;
  struct GPDDAT_BITS  bit ;
} ;

// GPIO D data set register bit definitions 
struct GPDSET_BITS  
{ 
   Uint16 GPIOD0:1;          // 0  
   Uint16 GPIOD1:1;          // 1 
   Uint16 rsvd1:3;           // 4:2  
   Uint16 GPIOD5:1;          // 5
   Uint16 GPIOD6:1;          // 6  
   Uint16 rsvd2:9;           // 15:7
} ;

union GPDSET_REG 
{
  Uint16             all;
  struct GPDSET_BITS bit;
} ;

// GPIO D data clear register bit definitions 
struct GPDCLEAR_BITS  
{
   Uint16 GPIOD0:1;          // 0  
   Uint16 GPIOD1:1;          // 1 
   Uint16 rsvd1:3;           // 4:2  
   Uint16 GPIOD5:1;          // 5
   Uint16 GPIOD6:1;          // 6  
   Uint16 rsvd2:9;           // 15:7
} ;

union GPDCLEAR_REG 
{
  Uint16                all ;
  struct GPDCLEAR_BITS  bit ;
} ;

// GPIO D data toggle register bit definitions 
struct GPDTOGGLE_BITS 
{   
   Uint16 GPIOD0:1;          // 0  
   Uint16 GPIOD1:1;          // 1 
   Uint16 rsvd1:3;           // 4:2  
   Uint16 GPIOD5:1;          // 5
   Uint16 GPIOD6:1;          // 6  
   Uint16 rsvd2:9;           // 15:7
} ;

union GPDTOGGLE_REG 
{
  Uint16                 all ;
  struct GPDTOGGLE_BITS  bit ;
} ;

// GPIOD Qualregister bit definitions
struct GPDQUAL_BITS 
{
  Uint16  QUALPRD : 8 ;  // 0:7    Qualification Sampling Period
  Uint16  rsvd1   : 8 ;  // 15:8   reserved
} ;    

union GPDQUAL_REG 
{
  Uint16               all ;
  struct GPDQUAL_BITS  bit ;
} ;       

// GPIO E mux control register bit definitions
struct GPEMUX_BITS  
{                // bits  description
  Uint16  XINT1_XBIO_GPIOE0   :  1 ;       // 0  
  Uint16  XINT2_ADCSOC_GPIOE1 :  1 ;     // 1  
  Uint16  XNMI_XINT13_GPIOE2  :  1 ;      // 2 
  Uint16  rsvd1               : 12 ;                  // 15:3  
} ;

union GPEMUX_REG 
{
  Uint16              all ;
  struct GPEMUX_BITS  bit ;
} ;

// GPIO E Direction control register bit definitions
struct GPEDIR_BITS  
{ 
   Uint16 GPIOE0:1;          // 0 
   Uint16 GPIOE1:1;          // 1 
   Uint16 GPIOE2:1;          // 2 
   Uint16 rsvd1:12;          // 15:3        
} ;

union GPEDIR_REG 
{
  Uint16              all ;
  struct GPEDIR_BITS  bit ;
} ;

// GPIO E data register bit definitions
struct GPEDAT_BITS  
{
  Uint16  GPIOE0 :  1 ;          // 0 
  Uint16  GPIOE1 :  1 ;          // 1 
  Uint16  GPIOE2 :  1 ;          // 2 
  Uint16  rsvd1  : 12 ;          // 15:3        
} ;

union GPEDAT_REG 
{
  Uint16              all ;
  struct GPEDAT_BITS  bit ;
} ;

// GPIO E data set register bit definitions
struct GPESET_BITS  
{
  Uint16  GPIOE0 :  1 ;          // 0 
  Uint16  GPIOE1 :  1 ;          // 1 
  Uint16  GPIOE2 :  1 ;          // 2 
  Uint16  rsvd1  : 12 ;          // 15:3        
} ;

union GPESET_REG 
{
  Uint16              all ;
  struct GPESET_BITS  bit ;
} ;


// GPIO E data clear register bit definitions
struct GPECLEAR_BITS  
{ 
   Uint16 GPIOE0:1;          // 0 
   Uint16 GPIOE1:1;          // 1 
   Uint16 GPIOE2:1;          // 2 
   Uint16 rsvd1:12;          // 15:3        
} ;

union GPECLEAR_REG 
{
  Uint16                all ;
  struct GPECLEAR_BITS  bit ;
} ;


// GPIO E data toggle register bit definitions
struct GPETOGGLE_BITS  
{ 
  Uint16 GPIOE0:1;          // 0 
  Uint16 GPIOE1:1;          // 1 
  Uint16 GPIOE2:1;          // 2 
  Uint16 rsvd1:12;          // 15:3        
} ;

union GPETOGGLE_REG 
{
  Uint16                 all ;
  struct GPETOGGLE_BITS  bit ;
} ;

// GPIOE Qualregister bit definitions 
struct GPEQUAL_BITS 
{
  Uint16  QUALPRD : 8 ;   // 0:7    Qualification Sampling Period
  Uint16  rsvd1   : 8 ;   // 15:8   reserved
} ;     

union GPEQUAL_REG 
{
  Uint16               all ;
  struct GPEQUAL_BITS  bit ;
} ;      


//  GPIO F mux control register bit definitions
struct GPFMUX_BITS  
{ 
   Uint16 SPISIMOA_GPIOF0:1; // 0 
   Uint16 SPISOMIA_GPIOF1:1; // 1 
   Uint16 SPICLKA_GPIOF2:1;  // 2 
   Uint16 SPISTEA_GPIOF3:1;  // 3 
   Uint16 SCITXDA_GPIOF4:1;  // 4 
   Uint16 SCIRXDA_GPIOF5:1;  // 5 
   Uint16 CANTXA_GPIOF6:1;   // 6 
   Uint16 CANRXA_GPIOF7:1;   // 7 
   Uint16 MCLKXA_GPIOF8:1;   // 8 
   Uint16 MCLKRA_GPIOF9:1;   // 9 
   Uint16 MFSXA_GPIOF10:1;   // 10
   Uint16 MFSRA_GPIOF11:1;   // 11
   Uint16 MDXA_GPIOF12:1;    // 12
   Uint16 MDRA_GPIOF13:1;    // 13
   Uint16 XF_GPIOF14:1;      // 14
   Uint16 spare_GPIOF15:1;   // 15
};

// Allow access to the bit fields or entire register
union GPFMUX_REG 
{
  Uint16              all ;
  struct GPFMUX_BITS  bit ;
} ;

// GPIO F Direction control register bit definitions
struct GPFDIR_BITS  
{
   Uint16 GPIOF0:1;          // 0 
   Uint16 GPIOF1:1;          // 1 
   Uint16 GPIOF2:1;          // 2 
   Uint16 GPIOF3:1;          // 3 
   Uint16 GPIOF4:1;          // 4 
   Uint16 GPIOF5:1;          // 5 
   Uint16 GPIOF6:1;          // 6 
   Uint16 GPIOF7:1;          // 7 
   Uint16 GPIOF8:1;          // 8 
   Uint16 GPIOF9:1;          // 9 
   Uint16 GPIOF10:1;         // 10
   Uint16 GPIOF11:1;         // 11
   Uint16 GPIOF12:1;         // 12
   Uint16 GPIOF13:1;         // 13
   Uint16 GPIOF14:1;         // 14
   Uint16 GPIOF15:1;         // 15
} ;

union GPFDIR_REG 
{
  Uint16              all ;
  struct GPFDIR_BITS  bit ;
} ;

// GPIO F data register bit definitions
struct GPFDAT_BITS  
{ 
   Uint16 GPIOF0:1;          // 0 
   Uint16 GPIOF1:1;          // 1 
   Uint16 GPIOF2:1;          // 2 
   Uint16 GPIOF3:1;          // 3 
   Uint16 GPIOF4:1;          // 4 
   Uint16 GPIOF5:1;          // 5 
   Uint16 GPIOF6:1;          // 6 
   Uint16 GPIOF7:1;          // 7 
   Uint16 GPIOF8:1;          // 8 
   Uint16 GPIOF9:1;          // 9 
   Uint16 GPIOF10:1;         // 10
   Uint16 GPIOF11:1;         // 11
   Uint16 GPIOF12:1;         // 12
   Uint16 GPIOF13:1;         // 13
   Uint16 GPIOF14:1;         // 14
   Uint16 GPIOF15:1;         // 15
} ;

union GPFDAT_REG 
{
  Uint16              all ;
  struct GPFDAT_BITS  bit ;
} ;

// GPIO F data set register bit definitions
struct GPFSET_BITS  
{
   Uint16 GPIOF0:1;          // 0 
   Uint16 GPIOF1:1;          // 1 
   Uint16 GPIOF2:1;          // 2 
   Uint16 GPIOF3:1;          // 3 
   Uint16 GPIOF4:1;          // 4 
   Uint16 GPIOF5:1;          // 5 
   Uint16 GPIOF6:1;          // 6 
   Uint16 GPIOF7:1;          // 7 
   Uint16 GPIOF8:1;          // 8 
   Uint16 GPIOF9:1;          // 9 
   Uint16 GPIOF10:1;         // 10
   Uint16 GPIOF11:1;         // 11
   Uint16 GPIOF12:1;         // 12
   Uint16 GPIOF13:1;         // 13
   Uint16 GPIOF14:1;         // 14
   Uint16 GPIOF15:1;         // 15
} ;

union GPFSET_REG 
{
  Uint16              all ;
  struct GPFSET_BITS  bit ;
} ;

// GPIO F data clear register bit definitions
struct GPFCLEAR_BITS  
{
   Uint16 GPIOF0:1;          // 0 
   Uint16 GPIOF1:1;          // 1 
   Uint16 GPIOF2:1;          // 2 
   Uint16 GPIOF3:1;          // 3 
   Uint16 GPIOF4:1;          // 4 
   Uint16 GPIOF5:1;          // 5 
   Uint16 GPIOF6:1;          // 6 
   Uint16 GPIOF7:1;          // 7 
   Uint16 GPIOF8:1;          // 8 
   Uint16 GPIOF9:1;          // 9 
   Uint16 GPIOF10:1;         // 10
   Uint16 GPIOF11:1;         // 11
   Uint16 GPIOF12:1;         // 12
   Uint16 GPIOF13:1;         // 13
   Uint16 GPIOF14:1;         // 14
   Uint16 GPIOF15:1;         // 15
} ;

union GPFCLEAR_REG 
{
  Uint16                all ;
  struct GPFCLEAR_BITS  bit ;
} ;

// GPIO F data toggle register bit definitions
struct GPFTOGGLE_BITS  
{
   Uint16 GPIOF0:1;          // 0 
   Uint16 GPIOF1:1;          // 1 
   Uint16 GPIOF2:1;          // 2 
   Uint16 GPIOF3:1;          // 3 
   Uint16 GPIOF4:1;          // 4 
   Uint16 GPIOF5:1;          // 5 
   Uint16 GPIOF6:1;          // 6 
   Uint16 GPIOF7:1;          // 7 
   Uint16 GPIOF8:1;          // 8 
   Uint16 GPIOF9:1;          // 9 
   Uint16 GPIOF10:1;         // 10
   Uint16 GPIOF11:1;         // 11
   Uint16 GPIOF12:1;         // 12
   Uint16 GPIOF13:1;         // 13
   Uint16 GPIOF14:1;         // 14
   Uint16 GPIOF15:1;         // 15
} ;

union GPFTOGGLE_REG 
{
  Uint16                 all ;
  struct GPFTOGGLE_BITS  bit ;
} ;

//  GPIO G mux control register bit definitions
struct GPGMUX_BITS  
{
   Uint16 rsvd1:4;           // 3:0
   Uint16 SCITXDB_GPIOG4:1;  // 4 
   Uint16 SCIRXDB_GPIOG5:1;  // 5 
   Uint16 rsvd2:10;          // 15:6
} ;

// Allow access to the bit fields or entire register
union GPGMUX_REG 
{
  Uint16              all ;
  struct GPGMUX_BITS  bit ;
} ;

// GPIO G Direction control register bit definitions
struct GPGDIR_BITS  
{
   Uint16 rsvd1:4;           // 3:0
   Uint16 GPIOG4:1;          // 4 
   Uint16 GPIOG5:1;          // 5 
   Uint16 rsvd2:10;          // 15:6
} ;

union GPGDIR_REG 
{
  Uint16             all;
  struct GPGDIR_BITS bit;
} ;

// GPIO G data register bit definitions
struct GPGDAT_BITS  
{
   Uint16 rsvd1:4;           // 3:0
   Uint16 GPIOG4:1;          // 4 
   Uint16 GPIOG5:1;          // 5 
   Uint16 rsvd2:10;          // 15:6
} ;

union GPGDAT_REG 
{
  Uint16             all;
  struct GPGDAT_BITS bit;
} ;


// GPIO G data set register bit definitions
struct GPGSET_BITS  
{
	 Uint16 rsvd1:4;           // 3:0
   Uint16 GPIOG4:1;          // 4 
   Uint16 GPIOG5:1;          // 5 
   Uint16 rsvd2:10;          // 15:6
} ;

union GPGSET_REG 
{
   Uint16             all;
   struct GPGSET_BITS bit;
} ;

// GPIO G data clear register bit definitions
struct GPGCLEAR_BITS  
{
   Uint16 rsvd1:4;           // 3:0
   Uint16 GPIOG4:1;          // 4 
   Uint16 GPIOG5:1;          // 5 
   Uint16 rsvd2:10;          // 15:6
} ;

union GPGCLEAR_REG 
{
  Uint16               all;
  struct GPGCLEAR_BITS bit;
} ;


// GPIO G data toggle register bit definitions
struct GPGTOGGLE_BITS  
{
   Uint16 rsvd1:4;           // 3:0
   Uint16 GPIOG4:1;          // 4 
   Uint16 GPIOG5:1;          // 5 
   Uint16 rsvd2:10;          // 15:6
} ;

union GPGTOGGLE_REG 
{
  Uint16                all ;
  struct GPGTOGGLE_BITS bit ;
} ;

struct GPIO_MUX_REGS 
{
  union  GPAMUX_REG   GPAMUX;
  union  GPADIR_REG   GPADIR;
  union  GPAQUAL_REG  GPAQUAL;
  Uint16              rsvd1;
  union  GPBMUX_REG   GPBMUX;
  union  GPBDIR_REG   GPBDIR;
  union  GPBQUAL_REG  GPBQUAL;   
  Uint16              rsvd2[5];
  union  GPDMUX_REG   GPDMUX;
  union  GPDDIR_REG   GPDDIR;
  union  GPDQUAL_REG  GPDQUAL;   
  Uint16              rsvd3;
  union  GPEMUX_REG   GPEMUX;
  union  GPEDIR_REG   GPEDIR;
  union  GPEQUAL_REG  GPEQUAL;   
  Uint16              rsvd4;
  union  GPFMUX_REG   GPFMUX;
  union  GPFDIR_REG   GPFDIR;
  Uint16              rsvd5[2];
  union  GPGMUX_REG   GPGMUX;
  union  GPGDIR_REG   GPGDIR;
  Uint16              rsvd6[6];
} ;

struct GPIO_DATA_REGS 
{
  union  GPADAT_REG    GPADAT ;
  union  GPASET_REG    GPASET ;
  union  GPACLEAR_REG  GPACLEAR ;
  union  GPATOGGLE_REG GPATOGGLE;
  union  GPBDAT_REG    GPBDAT;
  union  GPBSET_REG    GPBSET;
  union  GPBCLEAR_REG  GPBCLEAR;
  union  GPBTOGGLE_REG GPBTOGGLE;
  Uint16               rsvd1[4];
  union  GPDDAT_REG    GPDDAT;
  union  GPDSET_REG    GPDSET;
  union  GPDCLEAR_REG  GPDCLEAR;
  union  GPDTOGGLE_REG GPDTOGGLE;
  union  GPEDAT_REG    GPEDAT;
  union  GPESET_REG    GPESET;
  union  GPECLEAR_REG  GPECLEAR;
  union  GPETOGGLE_REG GPETOGGLE;
  union  GPFDAT_REG    GPFDAT;
  union  GPFSET_REG    GPFSET;
  union  GPFCLEAR_REG  GPFCLEAR;
  union  GPFTOGGLE_REG GPFTOGGLE;
  union  GPGDAT_REG    GPGDAT;
  union  GPGSET_REG    GPGSET;
  union  GPGCLEAR_REG  GPGCLEAR;
  union  GPGTOGGLE_REG GPGTOGGLE;
  Uint16               rsvd2[4];      
} ;     
 

//---------------------------------------------------------------------------
// GPI/O External References & Function Declarations:
//
volatile struct GPIO_MUX_REGS  GioMuxRegs ;
volatile struct GPIO_DATA_REGS GioDatRegs ;

#pragma DATA_SECTION(GioMuxRegs,"GioMuxRegsFile") ;
#pragma DATA_SECTION(GioDatRegs,"GioDatRegsFile") ;


//===========================================================================
// Analog to Digital Converter Register Bit Defination : AdcCtrRegs
// ADDRESS : 0x00 7100 - 0x00 711F
// Not EALLOW Protected 
//===========================================================================

// ADC Individual Register Bit Definitions:

struct ADCTRL1_BITS 
{     // bits  description
    Uint16  rsvd1:4;      // 3:0   reserved
    Uint16  SEQ_CASC:1;   // 4     Cascaded sequencer mode
    Uint16  SEQ_OVRD:1;   // 5     Sequencer override 
    Uint16  CONT_RUN:1;   // 6     Continuous run
    Uint16  CPS:1;        // 7     ADC core clock pre-scalar
    Uint16  ACQ_PS:4;     // 11:8  Acquisition window size
    Uint16  SUSMOD:2;     // 13:12 Emulation suspend mode
    Uint16  RESET:1;      // 14    ADC reset
    Uint16  rsvd2:1;      // 15    reserved
};


union ADCTRL1_REG {
   Uint16                all;
   struct ADCTRL1_BITS   bit;
};


struct ADCTRL2_BITS {         // bits  description
    Uint16  EVB_SOC_SEQ2:1;   // 0     Event manager B SOC mask for SEQ2
    Uint16  rsvd1:1;          // 1     reserved
    Uint16  INT_MOD_SEQ2:1;   // 2     SEQ2 Interrupt mode
    Uint16  INT_ENA_SEQ2:1;   // 3     SEQ2 Interrupt enable
    Uint16  rsvd2:1;          // 4     reserved
    Uint16  SOC_SEQ2:1;       // 5     Start of conversion for SEQ2
    Uint16  RST_SEQ2:1;       // 6     Reset SEQ2
    Uint16  EXT_SOC_SEQ1:1;   // 7     External start of conversion for SEQ1
    Uint16  EVA_SOC_SEQ1:1;   // 8     Event manager A SOC mask for SEQ1
    Uint16  rsvd3:1;          // 9     reserved
    Uint16  INT_MOD_SEQ1:1;   // 10    SEQ1 Interrupt mode
    Uint16  INT_ENA_SEQ1:1;   // 11    SEQ1 Interrupt enable
    Uint16  rsvd4:1;          // 12    reserved
    Uint16  SOC_SEQ1:1;       // 13    Start of conversion trigger for SEQ1
    Uint16  RST_SEQ1:1;       // 14    Restart sequencer 1   
    Uint16  EVB_SOC_SEQ:1;    // 15    EVB SOC enable
};


union ADCTRL2_REG {
   Uint16                all;
   struct ADCTRL2_BITS   bit;
};


struct ADCASEQSR_BITS {       // bits   description
    Uint16  SEQ1_STATE:4;     // 3:0    SEQ1 state
    Uint16  SEQ2_STATE:3;     // 6:4    SEQ2 state
    Uint16  rsvd1:1;          // 7      reserved
    Uint16  SEQ_CNTR:4;       // 11:8   Sequencing counter status 
    Uint16  rsvd2:4;          // 15:12  reserved  
};

union ADCASEQSR_REG {
   Uint16                 all;
   struct ADCASEQSR_BITS  bit;
};


struct ADCMAXCONV_BITS {      // bits  description
    Uint16  MAX_CONV1:4;      // 3:0   Max number of conversions
    Uint16  MAX_CONV2:3;      // 6:4   Max number of conversions    
    Uint16  rsvd1:9;          // 15:7  reserved 
};

union ADCMAXCONV_REG {
   Uint16                  all;
   struct ADCMAXCONV_BITS  bit;
};


struct ADCCHSELSEQ1_BITS {    // bits   description
    Uint16  CONV00:4;         // 3:0    Conversion selection 00
    Uint16  CONV01:4;         // 7:4    Conversion selection 01
    Uint16  CONV02:4;         // 11:8   Conversion selection 02
    Uint16  CONV03:4;         // 15:12  Conversion selection 03
};

union  ADCCHSELSEQ1_REG{
   Uint16                    all;
   struct ADCCHSELSEQ1_BITS  bit;
};

struct ADCCHSELSEQ2_BITS {    // bits   description
    Uint16  CONV04:4;         // 3:0    Conversion selection 04
    Uint16  CONV05:4;         // 7:4    Conversion selection 05
    Uint16  CONV06:4;         // 11:8   Conversion selection 06
    Uint16  CONV07:4;         // 15:12  Conversion selection 07
};

union  ADCCHSELSEQ2_REG{
   Uint16                    all;
   struct ADCCHSELSEQ2_BITS  bit;
};

struct ADCCHSELSEQ3_BITS {    // bits   description
    Uint16  CONV08:4;         // 3:0    Conversion selection 08
    Uint16  CONV09:4;         // 7:4    Conversion selection 09
    Uint16  CONV10:4;         // 11:8   Conversion selection 10
    Uint16  CONV11:4;         // 15:12  Conversion selection 11
};

union  ADCCHSELSEQ3_REG{
   Uint16                    all;
   struct ADCCHSELSEQ3_BITS  bit;
};

struct ADCCHSELSEQ4_BITS {    // bits   description
    Uint16  CONV12:4;         // 3:0    Conversion selection 12
    Uint16  CONV13:4;         // 7:4    Conversion selection 13
    Uint16  CONV14:4;         // 11:8   Conversion selection 14
    Uint16  CONV15:4;         // 15:12  Conversion selection 15
};

union  ADCCHSELSEQ4_REG {
   Uint16                    all;
   struct ADCCHSELSEQ4_BITS  bit;
};

struct ADCTRL3_BITS {         // bits   description
    Uint16   SMODE_SEL:1;     // 0      Sampling mode select
    Uint16   ADCCLKPS:4;      // 4:1    ADC core clock divider
    Uint16   ADCPWDN:1;       // 5      ADC powerdown
    Uint16   ADCBGRFDN:2;     // 7:6    ADC bandgap/ref power down
    Uint16   rsvd1:8;         // 15:8   reserved
}; 

union  ADCTRL3_REG {
   Uint16                all;
   struct ADCTRL3_BITS   bit;
};


struct ADCST_BITS {           // bits   description
    Uint16   INT_SEQ1:1;      // 0      SEQ1 Interrupt flag  
    Uint16   INT_SEQ2:1;      // 1      SEQ2 Interrupt flag
    Uint16   SEQ1_BSY:1;      // 2      SEQ1 busy status
    Uint16   SEQ2_BSY:1;      // 3      SEQ2 busy status
    Uint16   INT_SEQ1_CLR:1;  // 4      SEQ1 Interrupt clear
    Uint16   INT_SEQ2_CLR:1;  // 5      SEQ2 Interrupt clear
    Uint16   EOS_BUF1:1;      // 6      End of sequence buffer1
    Uint16   EOS_BUF2:1;      // 7      End of sequence buffer2
    Uint16   rsvd1:8;         // 15:8   reserved
};


union  ADCST_REG {
   Uint16             all;
   struct ADCST_BITS  bit;
};


struct ADC_REGS {
    union ADCTRL1_REG      ADCTRL1;       // ADC Control 1
    union ADCTRL2_REG      ADCTRL2;       // ADC Control 2
    union ADCMAXCONV_REG   ADCMAXCONV;    // Max conversions
    union ADCCHSELSEQ1_REG ADCCHSELSEQ1;  // Channel select sequencing control 1
    union ADCCHSELSEQ2_REG ADCCHSELSEQ2;  // Channel select sequencing control 2
    union ADCCHSELSEQ3_REG ADCCHSELSEQ3;  // Channel select sequencing control 3
    union ADCCHSELSEQ4_REG ADCCHSELSEQ4;  // Channel select sequencing control 4
    union ADCASEQSR_REG    ADCASEQSR;     // Autosequence status register
    Uint16                 ADCRESULT0;    // Conversion Result Buffer 0
    Uint16                 ADCRESULT1;    // Conversion Result Buffer 1
    Uint16                 ADCRESULT2;    // Conversion Result Buffer 2
    Uint16                 ADCRESULT3;    // Conversion Result Buffer 3
    Uint16                 ADCRESULT4;    // Conversion Result Buffer 4
    Uint16                 ADCRESULT5;    // Conversion Result Buffer 5
    Uint16                 ADCRESULT6;    // Conversion Result Buffer 6
    Uint16                 ADCRESULT7;    // Conversion Result Buffer 7
    Uint16                 ADCRESULT8;    // Conversion Result Buffer 8
    Uint16                 ADCRESULT9;    // Conversion Result Buffer 9
    Uint16                 ADCRESULT10;   // Conversion Result Buffer 10
    Uint16                 ADCRESULT11;   // Conversion Result Buffer 11
    Uint16                 ADCRESULT12;   // Conversion Result Buffer 12
    Uint16                 ADCRESULT13;   // Conversion Result Buffer 13
    Uint16                 ADCRESULT14;   // Conversion Result Buffer 14
    Uint16                 ADCRESULT15;   // Conversion Result Buffer 15
    union ADCTRL3_REG      ADCTRL3;       // ADC Control 3  
    union ADCST_REG        ADCST;         // ADC Status Register
};

//---------------------------------------------------------------------------
// ADC External References & Function Declarations:
//
volatile struct ADC_REGS AdcCtrRegs ;

#pragma DATA_SECTION(AdcCtrRegs,"AdcCtrRegsFile") ;


//===========================================================================
// Event Manager Modules(EVA, EVB) Register Bit Defination : 
// ADDRESS : 0x00 7400 - 0x00 743F : 0x00 7500 - 0x00 753F
// EALLOW Protected 
//===========================================================================

/* --------------------------------------------------- */
/* F2810/12 Event Manager (EV) GP Timer Registers      */
/*                                                     */
/* ----------------------------------------------------*/

/* Overall Timer Control Register */

struct GPTCONA_BITS  {
   Uint16 T1PIN:2;         // 1:0   Polarity of GP timer 1 compare
   Uint16 T2PIN:2;         // 3:2   Polarity of GP timer 2 compare
   Uint16 T1CMPOE:1;       // 4     Timer1 compare output
   Uint16 T2CMPOE:1;       // 5     Timer2 compare output 
   Uint16 TCMPOE:1;        // 6     Compare output enable
   Uint16 T1TOADC:2;       // 8:7   Start ADC with timer 1 event
   Uint16 T2TOADC:2;       // 10:9  Start ADC with timer 2 event
   Uint16 T1CTRIPE:1;      // 11    Enable Timer 1 compare trip
   Uint16 T2CTRIPE:1;      // 12    Enable Timer 2 compare trip
   Uint16 T1STAT:1;        // 13    GP Timer 1 status (read only)
   Uint16 T2STAT:1;        // 14    GP Timer 2 status (read only)
   Uint16 rsvd:1;          // 15    reserved
};

/* Allow access to the bit fields or entire register */
union GPTCONA_REG {
   Uint16        all;
   struct  GPTCONA_BITS bit;
};

struct GPTCONB_BITS  {
   Uint16 T3PIN:2;         // 1:0   Polarity of GP timer 3 compare
   Uint16 T4PIN:2;         // 3:2   Polarity of GP timer 4 compare
   Uint16 T3CMPOE:1;       // 4     Timer3 compare output
   Uint16 T4CMPOE:1;       // 5     Timer4 compare output 
   Uint16 TCMPOE:1;        // 6     Compare output enable
   Uint16 T3TOADC:2;       // 8:7   Start ADC with timer 3 event
   Uint16 T4TOADC:2;       // 10:9  Start ADC with timer 4 event
   Uint16 T3CTRIPE:1;      // 11    Timer 3 trip enable
   Uint16 T4CTRIPE:1;      // 12    Timer 4 trip enable
   Uint16 T3STAT:1;        // 13    GP Timer 3 status (read only)
   Uint16 T4STAT:1;        // 14    GP Timer 4 status (read only)
   Uint16 rsvd2:1;         // 15    reserved
};

/* Allow access to the bit fields or entire register */
union GPTCONB_REG {
   Uint16        all;
   struct  GPTCONB_BITS bit;
};

/* Timer 1 Control Register bit defintions */
struct T1CON_BITS  {
   Uint16  rsvd1:1;         // 0     reserved
   Uint16  TECMPR:1;        // 1     Timer compare enable
   Uint16  TCLD10:2;        // 3:2   Timer copare register reload
   Uint16  TCLKS10:2;       // 5:4   Clock source select
   Uint16  TENABLE:1;       // 6     Timer enable
   Uint16  rsvd2:1;         // 7     reserved
   Uint16  TPS:3;           // 10:8  Input clock prescaler
   Uint16  TMODE:2;         // 12:11 Count mode selection
   Uint16  rsvd:1;          // 13    reserved
   Uint16  FREE:1;          // 14    Free emulation control
   Uint16  SOFT:1;          // 15    Soft emulation control
};      

/* Allow access to the bit fields or entire register */
union T1CON_REG {
   Uint16             all;
   struct  T1CON_BITS bit;
};


/* Timer 2 Control Register bit defintions */
struct T2CON_BITS  {
   Uint16  SET1PR:1;        // 0     Period register select
   Uint16  TECMPR:1;        // 1     Timer compare enable
   Uint16  TCLD10:2;        // 3:2   Timer copare register reload
   Uint16  TCLKS10:2;       // 5:4   Clock source select
   Uint16  TENABLE:1;       // 6     Timer enable
   Uint16  T2SWT1:1;        // 7     Start GP timer 2 with GP timer 1's enable
   Uint16  TPS:3;           // 10:8  Input clock prescaler
   Uint16  TMODE:2;         // 12:11 Count mode selection
   Uint16  rsvd:1;          // 13    reserved
   Uint16  FREE:1;          // 14    Free emulation control
   Uint16  SOFT:1;          // 15    Soft emulation control
};      

/* Allow access to the bit fields or entire register */
union T2CON_REG 
{
  Uint16             all ;
  struct  T2CON_BITS bit ;
} ;

/* Timer 3 Control Register bit defintions */
struct T3CON_BITS  
{
  Uint16  rsvd1:1;         // 0     reserved
  Uint16  TECMPR:1;        // 1     Timer compare enable
  Uint16  TCLD10:2;        // 3:2   Timer copare register reload
  Uint16  TCLKS10:2;       // 5:4   Clock source select
  Uint16  TENABLE:1;       // 6     Timer enable
  Uint16  rsvd2:1;         // 7     reserved
  Uint16  TPS:3;           // 10:8  Input clock prescaler
  Uint16  TMODE:2;         // 12:11 Count mode selection
  Uint16  rsvd:1;          // 13    reserved
  Uint16  FREE:1;          // 14    Free emulation control
  Uint16  SOFT:1;          // 15    Soft emulation control
} ;      

/* Allow access to the bit fields or entire register */
union T3CON_REG 
{
  Uint16              all ;
  struct  T3CON_BITS  bit ;
} ;

/* Timer 4 Control Register bit defintions */
struct T4CON_BITS  
{
  Uint16  SET3PR:1;        // 0     Period register select
  Uint16  TECMPR:1;        // 1     Timer compare enable
  Uint16  TCLD10:2;        // 3:2   Timer copare register reload
  Uint16  TCLKS10:2;       // 5:4   Clock source select
  Uint16  TENABLE:1;       // 6     Timer enable
  Uint16  T4SWT3:1;        // 7     Start GP timer 2 with GP timer 1's enable
  Uint16  TPS:3;           // 10:8  Input clock prescaler
  Uint16  TMODE:2;         // 12:11 Count mode selection
  Uint16  rsvd:1;          // 13    reserved
  Uint16  FREE:1;          // 14    Free emulation control
  Uint16  SOFT:1;          // 15    Soft emulation control
} ;      

/* Allow access to the bit fields or entire register */
union T4CON_REG 
{
  Uint16              all ;
  struct  T4CON_BITS  bit ;
} ;


struct EXTCONA_BITS {
   Uint16   INDCOE:1;        // 0      Independant compare output
   Uint16   QEPIQUAL:1;      // 1      QEP/CAP3 Index Qual Mode
   Uint16   QEPIE:1;         // 2      QEP index enable
   Uint16   EVSOCE:1;        // 3      EvA start of conversion output enable
   Uint16   rsvd:12;         // 15:4   reserved
};

/* Allow access to the bit fields or entire register */
union EXTCONA_REG {
   Uint16        all;
   struct  EXTCONA_BITS bit;
};


struct EXTCONB_BITS {
   Uint16   INDCOE:1;        // 0      Independant compare output
   Uint16   QEPIQUAL:1;      // 1      QEP/CAP3 Index Qual Mode
   Uint16   QEPIE:1;         // 2      QEP index enable
   Uint16   EVSOCE:1;        // 3      EvB start of conversion output enable
   Uint16   rsvd:12;         // 15:4   reserved
};

/* Allow access to the bit fields or entire register */
union EXTCONB_REG {
   Uint16               all;
   struct  EXTCONA_BITS bit;
};



/* Compare Control Register */
struct COMCONA_BITS {
   Uint16   C1TRIPE:1;      // 0      C1TRIP enable
   Uint16   C2TRIPE:1;      // 1      C2TRIP enable
   Uint16   C3TRIPE:1;      // 2      C3TRIP eanble
   Uint16   rsvd:2;         // 4:3    reserved
   Uint16   FCMP1OE:1;      // 5      Full compare 1 output enable
   Uint16   FCMP2OE:1;      // 6      Full compare 2 output enable
   Uint16   FCMP3OE:1;      // 7      Full compare 3 output enable
   Uint16   PDPINTASTATUS:1;// 8      Current status of the PDPINTA pin
   Uint16   FCOMPOE:1;      // 9      Compare output enable
   Uint16   ACTRLD:2;       // 11:10  Action control register reload
   Uint16   SVENABLE:1;     // 12     Space vector PWM Mode enable
   Uint16   CLD:2;          // 14:13  Compare register reload condition
   Uint16   CENABLE:1;      // 15     Compare enable
}; 

/* Allow access to the bit fields or entire register */
union COMCONA_REG {
   Uint16               all;
   struct  COMCONA_BITS bit;
};

struct COMCONB_BITS {
   Uint16   C4TRIPE:1;      // 0      C4TRIP enable
   Uint16   C5TRIPE:1;      // 1      C5TRIP enable
   Uint16   C6TRIPE:1;      // 2      C6TRIP eanble
   Uint16   rsvd:2;         // 4:3    reserved
   Uint16   FCMP4OE:1;      // 5      Full compare 4 output enable
   Uint16   FCMP5OE:1;      // 6      Full compare 5 output enable
   Uint16   FCMP6OE:1;      // 7      Full compare 6 output enable
   Uint16   PDPINTBSTATUS:1;// 8      Current status of the PDPINTB pin
   Uint16   FCOMPOE:1;      // 9      Compare output enable
   Uint16   ACTRLD:2;       // 11:10  Action control register reload
   Uint16   SVENABLE:1;     // 12     Space vector PWM Mode enable
   Uint16   CLD:2;          // 14:13  Compare register reload condition
   Uint16   CENABLE:1;      // 15     Compare enable
}; 

/* Allow access to the bit fields or entire register */
union COMCONB_REG {
   Uint16               all;
   struct  COMCONB_BITS bit;
};

/* Compare Action Control Register bit definitions */

struct ACTRA_BITS {
   Uint16   CMP1ACT:2;     // 1:0    Action on compare output pin 1 CMP1
   Uint16   CMP2ACT:2;     // 3:2    Action on compare output pin 2 CMP2
   Uint16   CMP3ACT:2;     // 5:4    Action on compare output pin 3 CMP3
   Uint16   CMP4ACT:2;     // 7:6    Action on compare output pin 4 CMP4
   Uint16   CMP5ACT:2;     // 9:8    Action on compare output pin 5 CMP5
   Uint16   CMP6ACT:2;     // 11:10  Action on compare output pin 6 CMP6
   Uint16   D:3;           // 14:12  Basic vector bits
   Uint16   SVRDIR:1;      // 15     Space vecor PWM rotation dir
};

/* Allow access to the bit fields or entire register */
union ACTRA_REG {
   Uint16             all;
   struct  ACTRA_BITS bit;
};

struct ACTRB_BITS {
   Uint16   CMP7ACT:2;     // 1:0    Action on compare output pin 7 CMP7
   Uint16   CMP8ACT:2;     // 3:2    Action on compare output pin 8 CMP8
   Uint16   CMP9ACT:2;     // 5:4    Action on compare output pin 9 CMP9
   Uint16   CMP10ACT:2;    // 7:6    Action on compare output pin 10 CMP10
   Uint16   CMP11ACT:2;    // 9:8    Action on compare output pin 11 CMP11
   Uint16   CMP12ACT:2;    // 11:10  Action on compare output pin 12 CMP12
   Uint16   D:3;           // 14:12  Basic vector bits
   Uint16   SVRDIR:1;      // 15     Space vecor PWM rotation dir
};

/* Allow access to the bit fields or entire register */
union ACTRB_REG {
   Uint16        all;
   struct  ACTRB_BITS bit;
};

/* Dead-Band Timer Control register bit definitions */
struct DBTCON_BITS {
   Uint16   rsvd1:2;       // 1:0    reserved
   Uint16   DBTPS:3;       // 4:2    Dead-Band timer prescaler
   Uint16   EDBT1:1;       // 5      Dead-Band timer 1 enable
   Uint16   EDBT2:1;       // 6      Dead-Band timer 2 enable
   Uint16   EDBT3:1;       // 7      Dead-Band timer 3 enable
   Uint16   DBT:4;         // 11:8   Dead-Band timer period
   Uint16   rsvd2:4;       // 15:12  reserved   
};

/* Allow access to the bit fields or entire register */
union DBTCON_REG {
   Uint16        all;
   struct  DBTCON_BITS bit;
};


/* Capture Control register bit definitions */
struct CAPCONA_BITS {
   Uint16  rsvd1:2;         // 1:0   reserved
   Uint16  CAP3EDGE:2;      // 3:2   Edge Detection for Unit 3
   Uint16  CAP2EDGE:2;      // 5:4   Edge Detection for Unit 2
   Uint16  CAP1EDGE:2;      // 7:6   Edge Detection for Unit 1
   Uint16  CAP3TOADC:1;     // 8     Unit 3 starts the ADC
   Uint16  CAP12TSEL:1;     // 9     GP Timer selection for Units 1 and 2
   Uint16  CAP3TSEL:1;      // 10    GP Timer selection for Unit 3
   Uint16  rsvd2:1;         // 11    reserved
   Uint16  CAP3EN:1;        // 12    Capture Unit 3 enable
   Uint16  CAP12EN:2;       // 14:13 Capture Unit 1 and 2 enable
   Uint16  CAPRES:1;        // 15    Capture reset (always reads 0)
};

/* Allow access to the bit fields or entire register */
union CAPCONA_REG {
   Uint16        all;
   struct  CAPCONA_BITS bit;
};  


/* Control register bit definitions */
struct CAPCONB_BITS {
   Uint16  rsvd1:2;         // 1:0   reserved
   Uint16  CAP6EDGE:2;      // 3:2   Edge Detection for Unit 6
   Uint16  CAP5EDGE:2;      // 5:4   Edge Detection for Unit 5
   Uint16  CAP4EDGE:2;      // 7:6   Edge Detection for Unit 4
   Uint16  CAP6TOADC:1;     // 8     Unit 6 starts the ADC
   Uint16  CAP45TSEL:1;     // 9     GP Timer selection for Units 4 and 5
   Uint16  CAP6TSEL:1;      // 10    GP Timer selection for Unit 6
   Uint16  rsvd2:1;         // 11    reserved
   Uint16  CAP6EN:1;        // 12    Capture Unit 6 control
   Uint16  CAP45EN:2;       // 14:13 Capture Unit 4 and 5 control
   Uint16  CAPRES:1;        // 15    Capture reset (always reads 0)
};

/* Allow access to the bit fields or entire register */
union CAPCONB_REG {
   Uint16        all;
   struct  CAPCONB_BITS bit;
}; 

/* Capture FIFO Status Register bit definitions */
struct CAPFIFOA_BITS  {
   Uint16 rsvd1:8;           // 7:0   reserved
   Uint16 CAP1FIFO:2;        // 9:8   CAP1 FIFO status
   Uint16 CAP2FIFO:2;        // 11:10 CAP2 FIFO status
   Uint16 CAP3FIFO:2;        // 13:12 CAP2 FIFO status
   Uint16 rsvd2:2;           // 15:14 reserved
}; 

/* Allow access to the bit fields or entire register */
union CAPFIFOA_REG {
   Uint16        all;
   struct  CAPFIFOA_BITS bit;
}; 

/* Capture FIFO Status Register bit definitions */
struct CAPFIFOB_BITS  {
   Uint16 rsvd1:8;           // 7:0   reserved
   Uint16 CAP4FIFO:2;        // 9:8   CAP4 FIFO status
   Uint16 CAP5FIFO:2;        // 11:10 CAP5 FIFO status
   Uint16 CAP6FIFO:2;        // 13:12 CAP6 FIFO status
   Uint16 rsvd2:2;           // 15:14 reserved
}; 

/* Allow access to the bit fields or entire register */
union CAPFIFOB_REG {
   Uint16        all;
   struct  CAPFIFOB_BITS bit;
};

/* Interrupt Mask Register bit definitions */
struct EVAIMRA_BITS {
    Uint16  PDPINTA:1;      // 0       Enable PDPINTA
    Uint16  CMP1INT:1;      // 1       Enable
    Uint16  CMP2INT:1;      // 2       Enable
    Uint16  CMP3INT:1;      // 3       Enable
    Uint16  rsvd1:3;        // 6:4     reserved
    Uint16  T1PINT:1;       // 7       Enable
    Uint16  T1CINT:1;       // 8       Enable
    Uint16  T1UFINT:1;      // 9       Enable
    Uint16  T1OFINT:1;      // 10      Enable
    Uint16  rsvd2:5;        // 15:11   reserved
};
   
/* Allow access to the bit fields or entire register */
union EVAIMRA_REG {
   Uint16         all;
   struct  EVAIMRA_BITS bit;
};

/* Interrupt Mask Register bit definitions */
struct EVBIMRA_BITS {
    Uint16  PDPINTB:1;      // 0       Enable PDPINTB
    Uint16  CMP4INT:1;      // 1       Enable
    Uint16  CMP5INT:1;      // 2       Enable
    Uint16  CMP6INT:1;      // 3       Enable
    Uint16  rsvd1:3;        // 6:4     reserved
    Uint16  T3PINT:1;       // 7       Enable
    Uint16  T3CINT:1;       // 8       Enable
    Uint16  T3UFINT:1;      // 9       Enable
    Uint16  T3OFINT:1;      // 10      Enable
    Uint16  rsvd2:5;        // 15:11   reserved
};
   
/* Allow access to the bit fields or entire register */
union EVBIMRA_REG {
   Uint16         all;
   struct  EVBIMRA_BITS bit;
};

struct EVAIMRB_BITS {
   Uint16   T2PINT:1;       // 0       Enable
   Uint16   T2CINT:1;       // 1       Enable
   Uint16   T2UFINT:1;      // 2       Enable
   Uint16   T2OFINT:1;      // 3       Enable
   Uint16   rsvd1:12;       // 15:4    reserved
};

/* Allow access to the bit fields or entire register */
union EVAIMRB_REG {
   Uint16         all;
   struct  EVAIMRB_BITS bit;
};

struct EVBIMRB_BITS {
   Uint16   T4PINT:1;       // 0       Enable
   Uint16   T4CINT:1;       // 1       Enable
   Uint16   T4UFINT:1;      // 2       Enable
   Uint16   T4OFINT:1;      // 3       Enable
   Uint16   rsvd1:12;       // 15:4    reserved
};

/* Allow access to the bit fields or entire register */
union EVBIMRB_REG {
   Uint16         all;
   struct  EVBIMRB_BITS bit;
};

struct EVAIMRC_BITS {
    Uint16   CAP1INT:1;     // 0        Enable
    Uint16   CAP2INT:1;     // 1        Enable
    Uint16   CAP3INT:1;     // 2        Enable
    Uint16   rsvd1:13;      // 15:3     reserved
};

/* Allow access to the bit fields or entire register */
union EVAIMRC_REG {
   Uint16         all;
   struct  EVAIMRC_BITS bit;
};

struct EVBIMRC_BITS {
    Uint16   CAP4INT:1;     // 0        Enable
    Uint16   CAP5INT:1;     // 1        Enable
    Uint16   CAP6INT:1;     // 2        Enable
    Uint16   rsvd1:13;      // 15:3     reserved
};

/* Allow access to the bit fields or entire register */
union EVBIMRC_REG {
   Uint16         all;
   struct  EVBIMRC_BITS bit;
};

/* Interrupt Flag Register bit definitions */
struct EVAIFRA_BITS {
    Uint16  PDPINTA:1;      // 0       Flag PDPINTA
    Uint16  CMP1INT:1;      // 1       Flag
    Uint16  CMP2INT:1;      // 2       Flag
    Uint16  CMP3INT:1;      // 3       Flag
    Uint16  rsvd1:3;        // 6:4     reserved
    Uint16  T1PINT:1;       // 7       Flag
    Uint16  T1CINT:1;       // 8       Flag
    Uint16  T1UFINT:1;      // 9       Flag
    Uint16  T1OFINT:1;      // 10      Flag
    Uint16  rsvd2:5;        // 15:11   reserved
};
   
/* Allow access to the bit fields or entire register */
union EVAIFRA_REG {
   Uint16         all;
   struct  EVAIMRA_BITS bit;
};

/* Interrupt Mask Register bit definitions */
struct EVBIFRA_BITS {
    Uint16  PDPINTB:1;      // 0       Flag PDPINTB
    Uint16  CMP4INT:1;      // 1       Flag
    Uint16  CMP5INT:1;      // 2       Flag
    Uint16  CMP6INT:1;      // 3       Flag
    Uint16  rsvd1:3;        // 6:4     reserved
    Uint16  T3PINT:1;       // 7       Flag
    Uint16  T3CINT:1;       // 8       Flag
    Uint16  T3UFINT:1;      // 9       Flag
    Uint16  T3OFINT:1;      // 10      Flag
    Uint16  rsvd2:5;        // 15:11   reserved
};
   
/* Allow access to the bit fields or entire register */
union EVBIFRA_REG {
   Uint16         all;
   struct  EVBIFRA_BITS bit;
};

struct EVAIFRB_BITS {
   Uint16   T2PINT:1;       // 0       Flag
   Uint16   T2CINT:1;       // 1       Flag
   Uint16   T2UFINT:1;      // 2       Flag
   Uint16   T2OFINT:1;      // 3       Flag
   Uint16   rsvd1:12;       // 15:4    reserved
};

/* Allow access to the bit fields or entire register */
union EVAIFRB_REG {
   Uint16         all;
   struct  EVAIFRB_BITS bit;
};

struct EVBIFRB_BITS {
   Uint16   T4PINT:1;       // 0       Flag
   Uint16   T4CINT:1;       // 1       Flag
   Uint16   T4UFINT:1;      // 2       Flag
   Uint16   T4OFINT:1;      // 3       Flag
   Uint16   rsvd1:12;       // 15:4    reserved
};

/* Allow access to the bit fields or entire register */
union EVBIFRB_REG {
   Uint16         all;
   struct  EVBIFRB_BITS bit;
};

struct EVAIFRC_BITS {
    Uint16   CAP1INT:1;     // 0        Flag
    Uint16   CAP2INT:1;     // 1        Flag
    Uint16   CAP3INT:1;     // 2        Flag
    Uint16   rsvd1:13;      // 15:3     reserved
};

/* Allow access to the bit fields or entire register */
union EVAIFRC_REG {
   Uint16         all;
   struct  EVAIFRC_BITS bit;
};

struct EVBIFRC_BITS {
    Uint16   CAP4INT:1;     // 0        Flag
    Uint16   CAP5INT:1;     // 1        Flag
    Uint16   CAP6INT:1;     // 2        Flag
    Uint16   rsvd1:13;      // 15:3     reserved
};

/* Allow access to the bit fields or entire register */
union EVBIFRC_REG {
   Uint16         all;
   struct  EVBIFRC_BITS bit;
};

/* EVA Register File */

struct EVA_REGS  {
  union GPTCONA_REG  GPTCONA;   //0x7400
  Uint16             T1CNT;     //0x7401
  Uint16             T1CMPR;    //0x7402
  Uint16             T1PR;      //0x7403
  union T1CON_REG    T1CON;     //0x7404
  Uint16             T2CNT;     //0x7405
  Uint16             T2CMPR;    //0x7406
  Uint16             T2PR;      //0x7407
  union T2CON_REG    T2CON;     //0x7408
  union EXTCONA_REG  EXTCONA;   //0x7409
  Uint16             rsvd1[7];  //0x740A-10
  union COMCONA_REG  COMCONA;	//0x7411
  Uint16             rsvd2;     //0x7412
  union ACTRA_REG    ACTRA;     //0x7413
  Uint16             rsvd3;     //0x7414
  union DBTCON_REG   DBTCONA;   //0x7415
  Uint16             rsvd4;     //0x7416
  Uint16             CMPR1;     //0x7417
  Uint16             CMPR2;     //0x7418
  Uint16             CMPR3;     //0x7419
  Uint16             rsvd5[6];  //0x741A-F
  union CAPCONA_REG  CAPCONA;	//0x7420
  Uint16             rsvd6;     //0x7421
  union CAPFIFOA_REG CAPFIFOA;  //0x7422
  Uint16             CAP1FIFO;  //0x7423
  Uint16             CAP2FIFO;  //0x7424
  Uint16             CAP3FIFO;  //0x7425
  Uint16             rsvd7;     //0x7426
  Uint16             CAP1FBOT;  //0x7427
  Uint16             CAP2FBOT;  //0x7428
  Uint16             CAP3FBOT;  //0x7429
  Uint16             rsvd8[2];  //0x742A-B
  union EVAIMRA_REG  EVAIMRA;	//0x742C
  union EVAIMRB_REG  EVAIMRB;	//0x742D
  union EVAIMRC_REG  EVAIMRC;	//0x742E
  union EVAIFRA_REG  EVAIFRA;	//0x742F
  union EVAIFRB_REG  EVAIFRB;	//0x7430
  union EVAIFRC_REG  EVAIFRC;	//0x7431
};


/* EVB Register File */

struct EVB_REGS  {
  union GPTCONB_REG  GPTCONB;	//0x7500
  Uint16             T3CNT;     //0x7501
  Uint16             T3CMPR;    //0x7502
  Uint16             T3PR;      //0x7503
  union T3CON_REG    T3CON;     //0x7504
  Uint16             T4CNT;     //0x7505
  Uint16             T4CMPR;    //0x7506
  Uint16             T4PR;      //0x7507
  union T4CON_REG    T4CON;     //0x7508
  union EXTCONB_REG  EXTCONB;   //0x7509
  Uint16             rsvd1[7];  //0x750A-10
  union COMCONB_REG  COMCONB;   //0x7511
  Uint16             rsvd2;     //0x7512
  union ACTRB_REG    ACTRB;     //0x7513
  Uint16             rsvd3;     //0x7514
  union DBTCON_REG   DBTCONB;   //0x7515
  Uint16             rsvd4;     //0x7516
  Uint16             CMPR4;     //0x7517
  Uint16             CMPR5;     //0x7518
  Uint16             CMPR6;     //0x7519
  Uint16             rsvd5[6];  //0x751A-F
  union CAPCONB_REG  CAPCONB;   //0x7520
  Uint16             rsvd6;     //0x7521
  union CAPFIFOB_REG CAPFIFOB;  //0x7522
  Uint16             CAP4FIFO;  //0x7523
  Uint16             CAP5FIFO;  //0x7524
  Uint16             CAP6FIFO;  //0x7525
  Uint16             rsvd7;     //0x7526
  Uint16             CAP4FBOT;  //0x7527
  Uint16             CAP5FBOT;  //0x7528
  Uint16             CAP6FBOT;  //0x7529
  Uint16             rsvd8[2];  //0x752A-B
  union EVBIMRA_REG  EVBIMRA;   //0x752C
  union EVBIMRB_REG  EVBIMRB;   //0x752D
  union EVBIMRC_REG  EVBIMRC;   //0x752E
  union EVBIFRA_REG  EVBIFRA;   //0x752F
  union EVBIFRB_REG  EVBIFRB;   //0x7530
  union EVBIFRC_REG  EVBIFRC;   //0x7531
};                              



//---------------------------------------------------------------------------
// Function prototypes and external definitions:

volatile struct EVA_REGS EvaCtrRegs ;
volatile struct EVB_REGS EvbCtrRegs ;

#pragma DATA_SECTION(EvaCtrRegs,"EvaCtrRegsFile") ;
#pragma DATA_SECTION(EvbCtrRegs,"EvbCtrRegsFile") ;

//===========================================================================
// Multichannel Buffered Serial Port Register Bit Defination : McbSpiRegs
// ADDRESS : 0x00 7800 - 0x00 783F
// Not EALLOW Protected 
//===========================================================================

struct  DRR2_BITS {       // bit   description
   Uint16     HWLB:8;     // 16:23 High word low byte
   Uint16     HWHB:8;     // 24:31 High word high byte
};                                                                 

union DRR2_REG {
   Uint16            all;
   struct DRR2_BITS  bit;
};

// McBSP DRR1 register bit definitions:
struct  DRR1_BITS {       // bit   description
   Uint16     LWLB:8;     // 16:23 Low word low byte
   Uint16     LWHB:8;     // 24:31 low word high byte
};

union DRR1_REG {
   Uint16            all;
   struct DRR1_BITS  bit;
};

// McBSP DXR2 register bit definitions:
struct  DXR2_BITS {       // bit   description
   Uint16     HWLB:8;     // 16:23 High word low byte
   Uint16     HWHB:8;     // 24:31 High word high byte
};

union DXR2_REG {
   Uint16            all;
   struct DXR2_BITS  bit;
};

// McBSP DXR1 register bit definitions:
struct  DXR1_BITS {       // bit   description
   Uint16     LWLB:8;     // 16:23 Low word low byte
   Uint16     LWHB:8;     // 24:31 low word high byte
};               

union DXR1_REG {
   Uint16              all;
   struct DXR1_BITS  bit;
};

// SPCR2 control register bit definitions:
struct  SPCR2_BITS {       // bit   description
   Uint16     XRST:1;      // 0     transmit reset
   Uint16     XRDY:1;      // 1     transmit ready
   Uint16     XEMPTY:1;    // 2     Transmit empty    
   Uint16     XSYNCERR:1;  // 3     Transmit syn errorINT flag
   Uint16     XINTM:2;     // 5:4   Transmit interrupt types
   Uint16     GRST:1;      // 6     CLKG reset     
   Uint16     FRST:1;      // 7     Frame sync reset
   Uint16     SOFT:1;      // 8     SOFT bit
   Uint16     FREE:1;      // 9     FREE bit
   Uint16     rsvd:6;      // 15:10 reserved
}; 

union SPCR2_REG {
   Uint16               all;
   struct SPCR2_BITS  bit;
};
         
// SPCR1 control register bit definitions:
struct  SPCR1_BITS {       // bit   description
   Uint16     RRST:1;      // 0     Receive reset
   Uint16     RRDY:1;      // 1     Receive  ready
   Uint16     RFULL:1;     // 2     Receive  full    
   Uint16     RSYNCERR:1;  // 7     Receive  syn error
   Uint16     RINTM:2;     // 5:4   Receive  interrupt types
   Uint16     ABIS:1;      // 6     ABIS mode select     
   Uint16     DXENA:1;     // 7     DX hi-z enable     
   Uint16     rsvd:3;      // 10:8  reserved  
   Uint16     CLKSTP:2;    // 12:11 CLKSTOP mode bit
   Uint16     RJUST:2;     // 13:14 Right justified
   Uint16     DLB:1;       // 15    Digital loop back
}; 

union SPCR1_REG {
   Uint16              all;
   struct SPCR1_BITS bit;
};                                                               

// RCR2 control register bit definitions:
struct  RCR2_BITS {         // bit    description
   Uint16     RDATDLY:2;    // 1:0    Receive data delay
   Uint16     RFIG:1;       // 2      Receive  frame sync ignore
   Uint16     RCOMPAND:2;   // 4:3    Receive  Companding Mode selects
   Uint16     RWDLEN2:3;    // 7:5    Receive  word length   
   Uint16     RFRLEN2:7;    // 14:8   Receive  Frame sync
   Uint16     RPHASE:1;     // 15     Receive Phase
}; 

union RCR2_REG {
   Uint16           all;
   struct RCR2_BITS bit;
};
     
// RCR1 control register bit definitions:
struct  RCR1_BITS {         // bit   description
   Uint16     rsvd1:5;      // 4:0   reserved  
   Uint16     RWDLEN1:3;    // 7:5   Receive word length   
   Uint16     RFRLEN1:7;    // 14:8  Receive frame length    
   Uint16     rsvd2:1;      // 15    reserved  
}; 

union RCR1_REG {
   Uint16           all;
   struct RCR1_BITS bit;
};    

// XCR2 control register bit definitions:

struct  XCR2_BITS {         // bit    description
   Uint16     XDATDLY:2;    // 1:0    Transmit data delay
   Uint16     XFIG:1;       // 2      Transmit frame sync ignore
   Uint16     XCOMPAND:2;   // 4:3    Transmit Companding Mode selects
   Uint16     XWDLEN2:3;    // 7:5    Transmit  word length   
   Uint16     XFRLEN2:7;    // 14:8   Transmit  Frame sync
   Uint16     XPHASE:1;     // 15     Transmit Phase
}; 

union XCR2_REG {
   Uint16           all;
   struct XCR2_BITS bit;
};
     
// XCR1 control register bit definitions:
struct  XCR1_BITS {         // bit   description
   Uint16     rsvd1:5;      // 4:0   reserved      
   Uint16     XWDLEN1:3;    // 7:5   Transmit word length    
   Uint16     XFRLEN1:7;    // 14:8  Transmit frame length    
   Uint16     rsvd2:1;      // 15    reserved  
}; 

union XCR1_REG {
   Uint16             all;
   struct XCR1_BITS bit;
};         

// SRGR2 Sample rate generator control register bit definitions:
struct  SRGR2_BITS {        // bit  description
   Uint16     FPER:12;      // 11:0 Frame period
   Uint16     FSGM:1;       // 12   Frame sync generator mode 
   Uint16     CLKSM:1;      // 13   Sample rate generator mode
   Uint16     rsvd:1;       // 14   reserved 
   Uint16     GSYNC:1;      // 15   CLKG sync   
}; 

union  SRGR2_REG {
   Uint16              all;
   struct  SRGR2_BITS  bit;
};

// SRGR1 control register bit definitions:
struct  SRGR1_BITS {        // bit   description
   Uint16     CLKGDV:8;     // 7:0   CLKG divider 
   Uint16     FWID:8;       // 15:8  Frame width
}; 

union  SRGR1_REG {
   Uint16              all;
   struct  SRGR1_BITS  bit;
};

// MCR2 Multichannel control register bit definitions:
struct  MCR2_BITS {         // bit   description
   Uint16     XMCM:2;       // 1:0   Transmit multichannel mode      
   Uint16     XCBLK:3;      // 2:4   Transmit current block    
   Uint16     XPABLK:2;     // 5:6   Transmit partition A Block 
   Uint16     XPBBLK:2;     // 7:8   Transmit partition B Block 
   Uint16     XMCME:1;      // 9     Transmit multi-channel enhance mode 
   Uint16     rsvd:6;       // 15:10 reserved  
}; 

union  MCR2_REG {
   Uint16             all;
   struct  MCR2_BITS  bit;
};
      
// MCR1 Multichannel control register bit definitions:
struct  MCR1_BITS {         // bit   description
   Uint16     RMCM:1;       // 0     Receive multichannel mode  
   Uint16     rsvd:1;       // 1     reserved     
   Uint16     RCBLK:3;      // 4:2   Receive current block    
   Uint16     RPABLK:2;     // 6:5   Receive partition A Block 
   Uint16     RPBBLK:2;     // 7:8   Receive partition B Block 
   Uint16     RMCME:1;      // 9     Receive multi-channel enhance mode 
   Uint16     rsvd1:6;      // 15:10 reserved   
}; 

union  MCR1_REG {
   Uint16             all;
   struct  MCR1_BITS  bit;
};
 
// RCERA control register bit definitions:
struct  RCERA_BITS {         // bit description
   Uint16     RCEA0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEA1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEA2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEA3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEA4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEA5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEA6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEA7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEA8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEA9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEA10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEA11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEA12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEA13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEA14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEA15:1;      // 15  Receive Channel enable bit 
}; 

union RCERA_REG {
   Uint16              all;
   struct  RCERA_BITS  bit;
};  

// RCERB control register bit definitions:
struct  RCERB_BITS {         // bit description
   Uint16     RCEB0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEB1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEB2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEB3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEB4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEB5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEB6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEB7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEB8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEB9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEB10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEB11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEB12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEB13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEB14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEB15:1;      // 15  Receive Channel enable bit   
}; 

union RCERB_REG {
   Uint16              all;
   struct  RCERB_BITS  bit;
};

// XCERA control register bit definitions:
struct  XCERA_BITS {         // bit description
   Uint16     XCERA0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERA1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERA2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERA3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERA4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERA5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERA6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERA7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERA8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERA9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERA10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERA11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERA12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERA13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERA14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERA15:1;      // 15  Receive Channel enable bit 
}; 

union XCERA_REG {
   Uint16              all;
   struct  XCERA_BITS  bit;
};  

// XCERB control register bit definitions:
struct  XCERB_BITS {         // bit description
   Uint16     XCERB0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERB1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERB2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERB3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERB4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERB5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERB6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERB7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERB8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERB9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERB10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERB11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERB12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERB13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERB14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERB15:1;      // 15  Receive Channel enable bit 
}; 

union XCERB_REG {
   Uint16              all;
   struct  XCERB_BITS  bit;
};
  
// PCR control register bit definitions:
struct  PCR_BITS {          // bit description
   Uint16     CLKRP:1;       // 0   Receive Clock polarity
   Uint16     CLKXP:1;       // 1   Transmit clock polarity  
   Uint16     FSRP:1;        // 2   Receive Frame synchronization polarity  
   Uint16     FSXP:1;        // 3   Transmit Frame synchronization polarity   
   Uint16     DR_STAT:1;     // 4   DR pin status - reserved for this McBSP  
   Uint16     DX_STAT:1;     // 5   DX pin status - reserved for this McBSP  
   Uint16     CLKS_STAT:1;   // 6   CLKS pin status - reserved for 28x -McBSP  
   Uint16     SCLKME:1;      // 7   Enhanced sample clock mode selection bit.
   Uint16     CLKRM:1;       // 8   Receiver Clock Mode 
   Uint16     CLKXM:1;       // 9   Transmitter Clock Mode.  
   Uint16     FSRM:1;        // 10  Receive Frame Synchronization Mode  
   Uint16     FSXM:1;        // 11  Transmit Frame Synchronization Mode
   Uint16     RIOEN:1;       // 12  General Purpose I/O Mode - reserved in this 28x-McBSP    
   Uint16     XIOEN:1;       // 13  General Purpose I/O Mode - reserved in this 28x-McBSP
   Uint16     IDEL_EN:1;     // 14  reserved in this 28x-McBSP
   Uint16     rsvd:1  ;      // 15  reserved
}; 

union PCR_REG {
   Uint16            all;
   struct  PCR_BITS  bit;
};
  
// RCERC control register bit definitions:
struct  RCERC_BITS {         // bit description
   Uint16     RCEC0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEC1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEC2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEC3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEC4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEC5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEC6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEC7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEC8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEC9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEC10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEC11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEC12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEC13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEC14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEC15:1;      // 15  Receive Channel enable bit 
}; 

union RCERC_REG {
   Uint16              all;
   struct  RCERC_BITS  bit;
};  

// RCERD control register bit definitions:
struct  RCERD_BITS {         // bit description
   Uint16     RCED0:1;       // 0   Receive Channel enable bit  
   Uint16     RCED1:1;       // 1   Receive Channel enable bit  
   Uint16     RCED2:1;       // 2   Receive Channel enable bit  
   Uint16     RCED3:1;       // 3   Receive Channel enable bit   
   Uint16     RCED4:1;       // 4   Receive Channel enable bit  
   Uint16     RCED5:1;       // 5   Receive Channel enable bit  
   Uint16     RCED6:1;       // 6   Receive Channel enable bit  
   Uint16     RCED7:1;       // 7   Receive Channel enable bit 
   Uint16     RCED8:1;       // 8   Receive Channel enable bit  
   Uint16     RCED9:1;       // 9   Receive Channel enable bit  
   Uint16     RCED10:1;      // 10  Receive Channel enable bit  
   Uint16     RCED11:1;      // 11  Receive Channel enable bit 
   Uint16     RCED12:1;      // 12  Receive Channel enable bit  
   Uint16     RCED13:1;      // 13  Receive Channel enable bit  
   Uint16     RCED14:1;      // 14  Receive Channel enable bit  
   Uint16     RCED15:1;      // 15  Receive Channel enable bit 
}; 

union RCERD_REG {
   Uint16              all;
   struct  RCERD_BITS  bit;
};

// XCERC control register bit definitions:
struct  XCERC_BITS {         // bit description
   Uint16     XCERC0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERC1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERC2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERC3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERC4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERC5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERC6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERC7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERC8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERC9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERC10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERC11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERC12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERC13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERC14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERC15:1;      // 15  Receive Channel enable bit 
}; 

union XCERC_REG {
   Uint16              all;
   struct  XCERC_BITS  bit;
};  

// XCERD control register bit definitions:
struct  XCERD_BITS {         // bit description
   Uint16     XCERD0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERD1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERD2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERD3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERD4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERD5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERD6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERD7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERD8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERD9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERD10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERD11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERD12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERD13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERD14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERD15:1;      // 15  Receive Channel enable bit 
}; 

union XCERD_REG {
   Uint16              all;
   struct  XCERD_BITS  bit;
};
  
// RCERE control register bit definitions:
struct  RCERE_BITS {         // bit description
   Uint16     RCEE0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEE1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEE2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEE3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEE4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEE5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEE6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEE7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEE8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEE9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEE10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEE11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEE12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEE13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEE14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEE15:1;      // 15  Receive Channel enable bit 
}; 

union RCERE_REG {
   Uint16              all;
   struct  RCERE_BITS  bit;
};  

// RCERF control register bit definitions:
struct  RCERF_BITS {         // bit   description
   Uint16     RCEF0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEF1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEF2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEF3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEF4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEF5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEF6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEF7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEF8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEF9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEF10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEF11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEF12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEF13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEF14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEF15:1;      // 15  Receive Channel enable bit 
}; 

union RCERF_REG {
   Uint16              all;
   struct  RCERF_BITS  bit;
};

// XCERE control register bit definitions:
struct  XCERE_BITS {         // bit description
   Uint16     XCERE0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERE1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERE2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERE3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERE4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERE5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERE6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERE7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERE8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERE9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERE10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERE11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERE12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERE13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERE14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERE15:1;      // 15  Receive Channel enable bit 
}; 

union XCERE_REG {
   Uint16              all;
   struct  XCERE_BITS  bit;
};  

// XCERF control register bit definitions:
struct  XCERF_BITS {         // bit description
   Uint16     XCERF0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERF1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERF2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERF3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERF4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERF5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERF6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERF7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERF8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERF9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERF10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERF11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERF12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERF13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERF14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERF15:1;      // 15  Receive Channel enable bit 
}; 

union XCERF_REG {
   Uint16              all;
   struct  XCERF_BITS  bit;
};                   

// RCERG control register bit definitions:
struct  RCERG_BITS {         // bit description
   Uint16     RCEG0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEG1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEG2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEG3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEG4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEG5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEG6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEG7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEG8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEG9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEG10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEG11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEG12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEG13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEG14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEG15:1;      // 15  Receive Channel enable bit 
}; 

union RCERG_REG {
   Uint16              all;
   struct  RCERG_BITS  bit;
};  

// RCERH control register bit definitions:
struct  RCERH_BITS {         // bit description
   Uint16     RCEH0:1;       // 0   Receive Channel enable bit  
   Uint16     RCEH1:1;       // 1   Receive Channel enable bit  
   Uint16     RCEH2:1;       // 2   Receive Channel enable bit  
   Uint16     RCEH3:1;       // 3   Receive Channel enable bit   
   Uint16     RCEH4:1;       // 4   Receive Channel enable bit  
   Uint16     RCEH5:1;       // 5   Receive Channel enable bit  
   Uint16     RCEH6:1;       // 6   Receive Channel enable bit  
   Uint16     RCEH7:1;       // 7   Receive Channel enable bit 
   Uint16     RCEH8:1;       // 8   Receive Channel enable bit  
   Uint16     RCEH9:1;       // 9   Receive Channel enable bit  
   Uint16     RCEH10:1;      // 10  Receive Channel enable bit  
   Uint16     RCEH11:1;      // 11  Receive Channel enable bit 
   Uint16     RCEH12:1;      // 12  Receive Channel enable bit  
   Uint16     RCEH13:1;      // 13  Receive Channel enable bit  
   Uint16     RCEH14:1;      // 14  Receive Channel enable bit  
   Uint16     RCEH15:1;      // 15  Receive Channel enable bit 
}; 

union RCERH_REG {
   Uint16              all;
   struct  RCERH_BITS  bit;
};

// XCERG control register bit definitions:
struct  XCERG_BITS {         // bit description
   Uint16     XCERG0:1;       // 0   Receive Channel enable bit  
   Uint16     XCERG1:1;       // 1   Receive Channel enable bit  
   Uint16     XCERG2:1;       // 2   Receive Channel enable bit  
   Uint16     XCERG3:1;       // 3   Receive Channel enable bit   
   Uint16     XCERG4:1;       // 4   Receive Channel enable bit  
   Uint16     XCERG5:1;       // 5   Receive Channel enable bit  
   Uint16     XCERG6:1;       // 6   Receive Channel enable bit  
   Uint16     XCERG7:1;       // 7   Receive Channel enable bit 
   Uint16     XCERG8:1;       // 8   Receive Channel enable bit  
   Uint16     XCERG9:1;       // 9   Receive Channel enable bit  
   Uint16     XCERG10:1;      // 10  Receive Channel enable bit  
   Uint16     XCERG11:1;      // 11  Receive Channel enable bit 
   Uint16     XCERG12:1;      // 12  Receive Channel enable bit  
   Uint16     XCERG13:1;      // 13  Receive Channel enable bit  
   Uint16     XCERG14:1;      // 14  Receive Channel enable bit  
   Uint16     XCERG15:1;      // 15  Receive Channel enable bit 
}; 

union XCERG_REG {
   Uint16              all;
   struct  XCERG_BITS  bit;
};  

// XCERH control register bit definitions:
struct  XCERH_BITS {         // bit description
   Uint16     XCEH0:1;       // 0   Receive Channel enable bit  
   Uint16     XCEH1:1;       // 1   Receive Channel enable bit  
   Uint16     XCEH2:1;       // 2   Receive Channel enable bit  
   Uint16     XCEH3:1;       // 3   Receive Channel enable bit   
   Uint16     XCEH4:1;       // 4   Receive Channel enable bit  
   Uint16     XCEH5:1;       // 5   Receive Channel enable bit  
   Uint16     XCEH6:1;       // 6   Receive Channel enable bit  
   Uint16     XCEH7:1;       // 7   Receive Channel enable bit 
   Uint16     XCEH8:1;       // 8   Receive Channel enable bit  
   Uint16     XCEH9:1;       // 9   Receive Channel enable bit  
   Uint16     XCEH10:1;      // 10  Receive Channel enable bit  
   Uint16     XCEH11:1;      // 11  Receive Channel enable bit 
   Uint16     XCEH12:1;      // 12  Receive Channel enable bit  
   Uint16     XCEH13:1;      // 13  Receive Channel enable bit  
   Uint16     XCEH14:1;      // 14  Receive Channel enable bit  
   Uint16     XCEH15:1;      // 15  Receive Channel enable bit 
}; 

union XCERH_REG {
   Uint16              all;
   struct  XCERH_BITS  bit;
};

// McBSP FIFO Transmit register bit definitions:
struct  MFFTX_BITS {            // bit   description
   Uint16     TXFFIL:5;         // 4:0   Interrupt level
   Uint16     TXFFIENA:1;       // 5     Interrupt enable
   Uint16     TXFFINT_CLEAR:1;  // 6     Clear INT flag
   Uint16     TXFFINT_FLAG:1;   // 7     INT flag
   Uint16     TXFFST:5;         // 12:8  FIFO status
   Uint16     TXFIFO_RESET:1;   // 13    FIFO reset
   Uint16     MFFENA:1;         // 14    Enhancement enable
   Uint16     rsvd:1;           // 15    reserved
}; 

union MFFTX_REG {
   Uint16            all;
   struct MFFTX_BITS bit;
};

// McBSP FIFO recieve register bit definitions:
struct  MFFRX_BITS {        // bits  description
   Uint16 RXFFIL:5;         // 4:0   Interrupt level
   Uint16 RXFFIENA:1;       // 5     Interrupt enable
   Uint16 RXFFINT_CLEAR:1;  // 6     Clear INT flag
   Uint16 RXFFINT_FLAG:1;   // 7     INT flag
   Uint16 RXFFST:5;         // 12:8  FIFO status
   Uint16 RXFIFO_RESET:1;   // 13    FIFO reset
   Uint16 RXFFOVF_CLEAR:1;  // 14    Clear overflow
   Uint16 RXFFOVF_FLAG:1;   // 15    FIFO overflow
}; 

union MFFRX_REG {
   Uint16            all;
   struct MFFRX_BITS bit;
};

// McBSP FIFO control register bit definitions:
struct  MFFCT_BITS {        // bits  description
    Uint16 FFTXTXDLY:8;     // 7:0   FIFO transmit delay
    Uint16 rsvd:7;          // 15:7  reserved
    Uint16 IACKM:1;         // 15    is IACK mode enable bit
};

union MFFCT_REG {
   Uint16             all;
   struct MFFCT_BITS  bit;
};
   
// McBSP FIFO INTERRUPT control register bit definitions:
struct  MFFINT_BITS {       // bits description
    Uint16     XINT:1;      // 0    XINT  interrupt enable
    Uint16     XEVTA:1;     // 1    XEVTA interrupt enable
    Uint16     RINT:1;      // 2    RINT  interrupt enable
    Uint16     REVTA:1;     // 3    REVTA interrupt enable
    Uint16     rsvd:12;     // 15:4 reserved
};

union MFFINT_REG {
   Uint16              all;
   struct MFFINT_BITS  bit;
};

// McBSP FIFO INTERRUPT status  register bit definitions:
struct  MFFST_BITS {       // bits description
    Uint16     EOBX:1;     // 0    EOBX flag
    Uint16     FSX:1;      // 1    FSX flag
    Uint16     EOBR:1;     // 2    EOBR flag
    Uint16     FSR:1;      // 3    FSR flag
    Uint16     rsvd:12;    // 15:4 reserved
};

union MFFST_REG {
   Uint16            all;
   struct MFFST_BITS bit;
};


//---------------------------------------------------------------------------
// McBSP Register File:
//
struct  MCBSP_REGS {      
   union DRR2_REG    DRR2;   // 0x7800, MCBSP Data receive register bits 31-16 
   union DRR1_REG    DRR1;   // 0x7801, MCBSP Data receive register bits 15-0 
   union DXR2_REG    DXR2;   // 0x7802, MCBSP Data transmit register bits 31-16 
   union DXR1_REG    DXR1;   // 0x7803, MCBSP Data transmit register bits 15-0 
   union SPCR2_REG   SPCR2;  // 0x7804, MCBSP control register bits 31-16 
   union SPCR1_REG   SPCR1;  // 0x7805, MCBSP control register bits 15-0 
   union RCR2_REG    RCR2;   // 0x7806, MCBSP receive control register bits 31-16 
   union RCR1_REG    RCR1;   // 0x7807, MCBSP receive control register bits 15-0 
   union XCR2_REG    XCR2;   // 0x7808, MCBSP transmit control register bits 31-16 
   union XCR1_REG    XCR1;   // 0x7809, MCBSP transmit control register bits 15-0 
   union SRGR2_REG   SRGR2;  // 0x7810, MCBSP sample rate gen register bits 31-16 
   union SRGR1_REG   SRGR1;  // 0x7811, MCBSP sample rate gen register bits 15-0  
   union MCR2_REG    MCR2;   // 0x7812, MCBSP multichannel register bits 31-16 
   union MCR1_REG    MCR1;   // 0x7813, MCBSP multichannel register bits 15-0    
   union RCERA_REG   RCERA;  // 0x7814, MCBSP Receive channel enable partition A 
   union RCERB_REG   RCERB;  // 0x7815, MCBSP Receive channel enable partition B 
   union XCERA_REG   XCERA;  // 0x7816, MCBSP Transmit channel enable partition A 
   union XCERB_REG   XCERB;  // 0x7817, MCBSP Transmit channel enable partition B            
   union PCR_REG     PCR;    // 0x7818, MCBSP Pin control register bits 15-0  
   union RCERC_REG   RCERC;  // 0x7819, MCBSP Receive channel enable partition C 
   union RCERD_REG   RCERD;  // 0x7820, MCBSP Receive channel enable partition D
   union XCERC_REG   XCERC;  // 0x7821, MCBSP Transmit channel enable partition C 
   union XCERD_REG   XCERD;  // 0x7823, MCBSP Transmit channel enable partition D             
   union RCERE_REG   RCERE;  // 0x7824, MCBSP Receive channel enable partition E 
   union RCERF_REG   RCERF;  // 0x7825, MCBSP Receive channel enable partition F
   union XCERE_REG   XCERE;  // 0x7826, MCBSP Transmit channel enable partition E
   union XCERF_REG   XCERF;  // 0x7827, MCBSP Transmit channel enable partition F            
   union RCERG_REG   RCERG;  // 0x7828, MCBSP Receive channel enable partition G
   union RCERH_REG   RCERH;  // 0x7829, MCBSP Receive channel enable partition H
   union XCERG_REG   XCERG;  // 0x7830, MCBSP Transmit channel enable partition G 
   union XCERH_REG   XCERH;  // 0x7831, MCBSP Transmit channel enable partition H             
   Uint16            rsvd1;  // 0x7832, reserved             
   union MFFTX_REG   MFFTX;  // 0x7833, MCBSP Transmit FIFO register bits  
   union MFFRX_REG   MFFRX;  // 0x7834, MCBSP Receive FIFO register bits
   union MFFCT_REG   MFFCT;  // 0x7835, MCBSP FIFO control register bits    
   union MFFINT_REG  MFFINT; // 0x7836, MCBSP Interrupt register bits  
   union MFFST_REG   MFFST;  // 0x7837, MCBSP Status register bits 
};

//---------------------------------------------------------------------------
// McBSP External References & Function Declarations:
//
volatile struct MCBSP_REGS McbSpiRegs ;

#pragma DATA_SECTION(McbSpiRegs,"McbSpiRegsFile") ;


