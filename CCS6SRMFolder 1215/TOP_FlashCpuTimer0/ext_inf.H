#define	  SetData	GpioDataRegs.GPFDAT.bit.GPIOF0 = 1
#define	  ClrData   GpioDataRegs.GPFDAT.bit.GPIOF0 = 0
#define	  SetClk	GpioDataRegs.GPFDAT.bit.GPIOF2 = 1
#define	  ClrClk	GpioDataRegs.GPFDAT.bit.GPIOF2 = 0

unsigned int * LedReg  = (unsigned int *) 0x5f00;
///unsigned int * Led8Lock= (unsigned int *) 0x25FF;



