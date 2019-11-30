*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
* *
* File: VECTORS.ASM *
* Target Processor: TMS320F240 *
* Assembler Version: 6.6 *
* Created: 10/31/97 *
* *
*----------------------------------------------------------*
* This file contains the interrupt vectors *
************************************************************
.length 58
.option T
.option X
*********************************************************** *
* ILLEGAL INTERRUPT ROUTINE *
*********************************************************** *;
.text
.def _int_0
_int_0: B _int_0 ; ILLEGAL INTERRUPT SPIN

*********************************************************** *
* INTERRUPT VECTORS *
*********************************************************** *
.sect "VECTOR"
.ref _c_int0
.ref _c_int3
.ref _c_int4
B _c_int0 ; RESET
B _int_0 ; INT1
B _int_0 ; INT2
B _c_int3 ; INT3
B _c_int4 ; INT4
B _int_0 ; INT5
B _int_0 ; INT6
B _int_0 ; Reserved
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ;
B _int_0 ; TRAP
B _int_0 ; NMI
B _int_0 ;
B _int_0 ;
B _int_0 ;
.end
/* Linker command file for TMS320F240 EVM */
vectors.obj
evmgr.obj
srm.obj
-c /* use ROM autoinitialization model */
-m main.map
-o main.out
-l c:\2xxtools\rts2xx.lib
MEMORY
{
PAGE 0: VECTORS: origin = 0x0000 length = 0x0040 /* EMIF */
PAGE 0: CODE: origin = 0x0040 length = 0x1FC0 /* EMIF */
PAGE 1: MMRS: origin = 0x0000 length = 0x0060 /* MMRS */
B2: origin = 0x0060 length = 0x0020 /* DARAM */
B0: origin = 0x0100 length = 0x0100 /* DARAM */
B1: origin = 0x0300 length = 0x0100 /* DARAM */
DATA: origin = 0xa000 length = 0x2000 /* EMIF */
}
SECTIONS
{
.VECTOR > VECTORS PAGE 0
.text > CODE PAGE 0
.cinit > CODE PAGE 0
.switch > CODE PAGE 0
.mmrs > MMRS PAGE 1 /* Memory Mapped Registers */
.data > DATA PAGE 1
.bss > DATA PAGE 1
.const > DATA PAGE 1
.stack > DATA PAGE 1
.sysmem > DATA PAGE 1