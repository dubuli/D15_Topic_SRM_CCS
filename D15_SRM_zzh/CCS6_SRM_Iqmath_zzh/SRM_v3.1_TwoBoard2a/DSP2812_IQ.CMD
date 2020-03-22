/*************************************************************************/
/**  The Command File of TMS320F2812 Ver 1.0                            **/
/**  KEMPEL and SRTEK of KysungSung University                          **/
/**  2005. 07. 26                                                       **/
/*************************************************************************/

-c
-stack 0x400

-x


 
-m SRM_double_EV.map
-o SRM_double_EV.out

/*
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes: 
         Memory blocks on F2812 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.  
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program 
         and/or data. 
*/

MEMORY
{
PAGE 0:    /* Program Memory */
   PRAMH0      : origin = 0x3F8000, length = 0x002000	  /* Program RAM Area */
   PRAML0      : origin = 0x008000, length = 0x001000     /* on-chip RAM block L0 */
   ZONE0       : origin = 0x002000, length = 0x002000     /* XINTF zone 0 */
   ZONE1       : origin = 0x004000, length = 0x002000     /* XINTF zone 1 */
   ZONE2       : origin = 0x080000, length = 0x080000     /* XINTF zone 2 */
   ZONE6       : origin = 0x100000, length = 0x080000     /* XINTF zone 6 */
   OTP         : origin = 0x3D7800, length = 0x000800     /* on-chip OTP */
   FLASHJ      : origin = 0x3D8000, length = 0x002000     /* on-chip FLASH */
   FLASHI      : origin = 0x3DA000, length = 0x002000     /* on-chip FLASH */
   FLASHH      : origin = 0x3DC000, length = 0x004000     /* on-chip FLASH */
   FLASHG      : origin = 0x3E0000, length = 0x004000     /* on-chip FLASH */
   FLASHF      : origin = 0x3E4000, length = 0x004000     /* on-chip FLASH */
   FLASHE      : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
   FLASHD      : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
   FLASHC      : origin = 0x3F0000, length = 0x004000     /* on-chip FLASH */
   FLASHB      : origin = 0x3F4000, length = 0x002000     /* on-chip FLASH */
   FLASHA      : origin = 0x3F6000, length = 0x001F80     /* on-chip FLASH */
   CSM_RSVD	   : origin = 0x3F7F80, length = 0x000076     /* CSM Reserved locations in FLASHA */
   CSM_PWL     : origin = 0x3F7FF8, length = 0x000008     /* CSM password locations in FLASHA */
   BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
/* ZONE7       : origin = 0x3FC000, length = 0x003FC0     /* XINTF zone 7 available if MP/MCn=1 */ 
   IQTABLES    : origin = 0x3FF000, length = 0x000FC0     /* IQmathTables,Boot ROM available if MP/MCn=0 */
/*   ROM         : origin = 0x3FF000, length = 0x000FC0   /* Boot ROM available if MP/MCn=0 */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM (MP/MCn=0) or XINTF zone 7 (MP/MCn=1) */

PAGE 1 :   /* Data Memory */
           /* Registers remain on PAGE1 */
   DRAMM       : origin = 0x000000, length = 0x000800     /* on-chip RAM block M0+M1 */
   DRAML0      : origin = 0x008000, length = 0x001000     /* IQmathTablesRam */
   DRAML1      : origin = 0x009000, length = 0x001000	  /* on-chip RAM block L1 */
   DEV_EMU     : origin = 0x000880, length = 0x000180     /* Device emulation registers */
   FLASH_REGS  : origin = 0x000A80, length = 0x000060     /* FLASH registers */
   CSM         : origin = 0x000AE0, length = 0x000010     /* Code security module registers */
   XINTF       : origin = 0x000B20, length = 0x000020     /* External interface registers */
   CPU_TIMER0  : origin = 0x000C00, length = 0x000008     /* CPU Timer0 registers (CPU Timer1 and Timer2 are reserved for BIOS)*/
   PIE_CTRL    : origin = 0x000CE0, length = 0x000020     /* PIE control registers */
   PIE_VECT    : origin = 0x000D00, length = 0x000100     /* PIE vector table */
   ECANA       : origin = 0x006000, length = 0x000040     /* eCAN registers */
   ECANA_LAM   : origin = 0x006040, length = 0x000040     /* eCAN mailbox LAM */
   ECANA_MOTS  : origin = 0x006080, length = 0x000040     /* eCAN MOTS  */
   ECANA_MOTO  : origin = 0x0060C0, length = 0x000040     /* eCAN MOTO  */
   ECANA_MBOX  : origin = 0x006100, length = 0x000100     /* eCAN mailboxes */
   SYSTEM      : origin = 0x007010, length = 0x000020     /* System control registers */
   SPIA        : origin = 0x007040, length = 0x000010     /* SPI registers */
   SCIA        : origin = 0x007050, length = 0x000010     /* SCI-A registers */
   XINTRUPT    : origin = 0x007070, length = 0x000010     /* External interrupt registers */
   GPIOMUX     : origin = 0x0070C0, length = 0x000020     /* GPIO mux registers */
   GPIODAT     : origin = 0x0070E0, length = 0x000020     /* GPIO data registers */
   ADC         : origin = 0x007100, length = 0x000020     /* ADC registers */
   EVA         : origin = 0x007400, length = 0x000040     /* Event Manager A registers */
   EVB         : origin = 0x007500, length = 0x000040     /* Event Manager B registers */
   SCIB        : origin = 0x007750, length = 0x000010     /* SCI-B registers */
   MCBSPA      : origin = 0x007800, length = 0x000040     /* McBSP registers */

}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code 
                   execution when booting to flash
*/ 
 
SECTIONS
{
   codestart         : > BEGIN,	PAGE = 0
   .text             : > FLASHA|FLASHB,	PAGE = 0
   .cinit            : > FLASHA,	PAGE = 0
   .pinit            : > FLASHA,	PAGE = 0
   .switch           : > FLASHA,	PAGE = 0
   .econst           : > FLASHA,	PAGE = 0      
   RamFncRegsFile          : LOAD = FLASHD,  /*RamFncRegsFile下载到FLASH空间FLASHD中*/
                         RUN = PRAML0,       /*RamFncRegsFile复制到RAM空间PRAML0中执行*/
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   DLOG              : > DRAML0,	PAGE = 1   /*用于DLOG4CHC.asm, 作为数据采集的缓冲区*/

   .stack            : > DRAMM,	PAGE = 1
   .ebss             : > DRAML1,	PAGE = 1
   .esysmem          : > DRAML1,	PAGE = 1

   csm_rsvd	         : > CSM_RSVD, PAGE = 0
  /* csmpasswds        : > CSM_PWL,  PAGE = 0 */
   CsmPwlRegsFile        : > CSM_PWL,  PAGE = 0 
   /* .reset indicates the start of _c_int00 for C Code.  
   /* When using the boot ROM this section and the CPU vector
   /* table is not needed.  Thus the default type is set to 
   /* DSECT */ 
   /* .reset is a standard section used by the compiler.  It contains the */ 
   /* the address of the start of _c_int00 for C Code.   /*
   /* When booting from XINTF this is a pointer to the c_init routine */
   /* For this example we will go through codestart first, in order to*/
   /* disable the watchdog before the init.  Thus this is DSECT       */

   .reset            : > RESET,	PAGE = 0, TYPE = DSECT
    vectors           : > VECTORS,	PAGE = 0, TYPE = DSECT

/* ------------------------------------------------------------- */
/* The following allocations are required for the DSP28 Header file
   examples.  Each allocation maps a structure defined in the DSP28 
   header files to the memory location of those registers.  
*/
   PieVecRegsFile   : > PIE_VECT,   PAGE = 1
      
   /* Allocate Peripheral Frame 0 Register Structures:   */
   DevEmuRegsFile   : > DEV_EMU     PAGE = 1
   Flash_RegsFile   : > FLASH_REGS  PAGE = 1
   CodSecRegsFile   : > CSM         PAGE = 1
   Xintf_RegsFile   : > XINTF       PAGE = 1
   CpuTm0RegsFile   : > CPU_TIMER0  PAGE = 1      
   PieCtrRegsFile   : > PIE_CTRL    PAGE = 1      
   PieVecRegs       : > PIE_VECT    PAGE = 1

   /* Allocate Peripheral Frame 2 Register Structures:   */
   CanCtrRegsFile   : > ECANA       PAGE = 1   
   CanLamRegsFile   : > ECANA_LAM   PAGE = 1   
   CanMboRegsFile   : > ECANA_MBOX  PAGE = 1
   CanMtoRegsFile   : > ECANA_MOTS  PAGE = 1
   CanMtsRegsFile   : > ECANA_MOTO  PAGE = 1
   
   /* Allocate Peripheral Frame 1 Register Structures:   */
   SysCtrRegsFile   : > SYSTEM      PAGE = 1
   SpiAstRegsFile   : > SPIA        PAGE = 1
   SciAstRegsFile   : > SCIA        PAGE = 1
   ExtIntRegsFile   : > XINTRUPT    PAGE = 1
   GioMuxRegsFile   : > GPIOMUX     PAGE = 1
   GioDatRegsFile   : > GPIODAT     PAGE = 1
   AdcCtrRegsFile   : > ADC         PAGE = 1
   EvaCtrRegsFile   : > EVA         PAGE = 1
   EvbCtrRegsFile   : > EVB         PAGE = 1
   SciBstRegsFile   : > SCIB        PAGE = 1
   McbSpiRegsFile   : > MCBSPA      PAGE = 1
   IQmath           : > FLASHC,       PAGE = 0                  /* Math Code */
   IQmathTables     : > IQTABLES,    PAGE = 0, type = NOLOAD    /* Math Tables In ROM */
/*   IQmathTablesRam  : > DRAML0,     PAGE = 1*/

/*IQmath段是IQmath库中汇编程序的映射，
IQmathTables段是IQsin, IQcos, IQatan, IQatan2等使用的查找表的映射，
对于F2812来讲，这个查找表被固化在了Boot rom中，
使用Boot rom中的查找表可以节约Ram空间，
但是Rom的访问需要额外的1个等待周期，
所以用户可以自己权衡时间(1 wait)和空间(Ram)哪个对自己是最重要的。
另外，如果选择直接调用Boot rom中的查找表，重映射时，必须使用NOLOAD关键字。
IQmathTablesRam段是IQasin, IQacos, and IQexp等使用的查找表的映射，
如果不使用这些功能，可以直接删除该段，节约Ram或Flash资源。 
还有一点需要注意，IQmath中编译代码的大小是动态的，
它是根据用户代码中调用的IQmath库函数来条件编译的，
所以初始时，可以将IQmath段的大小定义的稍微大一些，
最后根据map文件适当增减段的大小，节约宝贵的Ram资源。
*/
}
