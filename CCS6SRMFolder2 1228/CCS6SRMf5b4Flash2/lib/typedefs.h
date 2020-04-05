/***********************************************************
* File: TYPEDEFS.H *
* TMS320x240 Test Bed Code *
* Texas Instruments, Inc. *
* Copyright (c) 1996 Texas Instruments Inc. *
* 11/05/96 Version 1.0 *
* Jeff Crankshaw *
***********************************************************/
#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#define FALSE 0
#define TRUE 1
typedef unsigned int WORD; /* 16-bit data */
typedef unsigned long DWORD; /* 32-bit data */
typedef volatile WORD * PORT;
#define STR(x) #x
#define OUTMAC(address,data) \
	asm(" LDPK _"STR(data)); \
	asm(" OUT _"STR(data) ", " STR(address))
#define INMAC(address,data) \
	asm(" LDPK _"STR(data)); \
	asm(" IN _"STR(data) ", " STR(address))
#define Int_Read(addr) * (int *) (addr)
#define Int_Write(addr,data) * (int *) (addr) = (data)
#endif /* _TYPEDEFS */
