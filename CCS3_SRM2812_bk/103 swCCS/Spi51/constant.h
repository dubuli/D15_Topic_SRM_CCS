/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* */
/*File: CONSTANT.H */
/*Target Processor: TMS320F240 */
/*Compiler Version: */
/*Assembler Version: */
/*Created: 10/1/97 */
/* */
/*-----------------------------------------------------------------*/
/* Constants for the SRM control algorithms */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*----------------------------------------------*/
/* clock frequencies and time related constants */
/*----------------------------------------------*/
#define PWM_FREQ 20000 /* PWM frequency (Hz) */
#define SYSCLK_FREQ 20000000 /* DSP clock frequency (Hz) */
#define CPU_INT_FREQ 5000 /* timer ISR frequency (Hz) */
#define ONE_HALF_SECOND (CPU_INT_FREQ/2)
/*----------------------------------- */
/* current loop algorithm constants */
/*----------------------------------- */
#define ILOOP_GAIN 22 /* current loop gain: */
/* (Q3: gain = 2.75) */
#define ILIMIT 1023 /* current limit: (1023 bits = */
/* 5 V x 0.855 A/V = 4.273 A) */
#define MAXIMUM_DUTYRATIO 999 /* limit on the PWM duty cycle: */
/* 100 % = */
/* (SYSCLK_FREQ/PWM_FREQ - 1) */
/*-------------------------------------------*/
/* velocity loop algorithm constants */
/*-------------------------------------------*/
#define CMPRSTEPLIMIT 27//sdfsdfdjfskjsldkjfl;sajdflksdjflksjdlfkjsdlkfjlsjdfljsdlkfjslkdjf????????
#define ANGLESTEPLIMIT 27//sdfsdfdjfskjsldkjfl;sajdflksdjflksjdlfkjsdlkfjlsjdfljsdlkfjslkdjf????????

#define INTEGRAL_LIMIT 2793472 /* integrator limit */
#define KI 3 /* (Q13*1000): Ki = 0.366 */
#define KP 1 /* Q1: Kp = 0.5 */
#define KI2 3 /* (Q13*1000): Ki = 0.366 *///////////////////////waiting for calculate!!!!!!!!!!!!!!!!
#define KP2 1 /* Q1: Kp = 0.5 */
#define KI3 3 /* (Q13*1000): Ki = 0.366 *///////////////////////waiting for calculate!!!!!!!!!!!!!!!!
#define KP3 1 /* Q1: Kp = 0.5 */
/*----------------------------------------------------------*/
/* position & velocity estimation algorithm constants */
/*----------------------------------------------------------*/
#define K_POSITION_EST 1432
#define K1_VELOCITY_EST 281250000
#define K2_VELOCITY_EST 62500
#define ALPHA 7 /* Q3: alpha = 0.875 */
#define ONE_MINUS_ALPHA 1 /* Q3: 1-alpha = 0.125 */
/*-------------------------------------------*/
/* motor geometry related */
/*-------------------------------------------*/
#define NR 8 /* number of rotor poles */
#define NUMBER_OF_PHASES 3
/*--------------------------------------------------*/
/* Electrical Angles: 2*pi (rad) = 65535 */
/*--------------------------------------------------*/
#define PIBYSIX_16 5461
#define PIBYFOUR_16 8192
#define PIBYTHREE_16 10923
#define TWOPIBYTHREE_16 21845
#define THREEPIBYFOUR_16 24576
#define FIVEPIBYSIX_16 27307
#define PI_16 32768
#define FOURPIBYTHREE_16 43690
#define FIVEPIBYTHREE_16 54613
#define TWOPI_16 65535


#define wCHANGE 4000 //设置高速低速CCC APC 转换值
#define iRANGE 5 // The Current Range for ReferenceCurrent

#define CMPRBASE 1500


#define S1 GpioDataRegs.GPADAT.bit.GPIOA7
#define S2 GpioDataRegs.GPADAT.bit.GPIOA8
#define S3 GpioDataRegs.GPADAT.bit.GPIOA9
#define S4 GpioDataRegs.GPADAT.bit.GPIOA10

#define SCLK GpioDataRegs.GPFDAT.bit.GPIOF2
#define CS	GpioDataRegs.GPFDAT.bit.GPIOF3
#define SI GpioDataRegs.GPFDAT.bit.GPIOF0
