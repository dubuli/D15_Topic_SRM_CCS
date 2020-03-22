/*=====================================================================================
File name:        SetPeripheral.C  (IQ version)                                     
Originator:	LH
Description: 
This File is for Initializing of peripheral register
=====================================================================================*/

//===================A/D初始化==============================
void Setup_ADCfunc(void)
{
  // ADC init
  AdcCtrRegs.ADCTRL3.bit.ADCBGRFDN = 0x3 ;	//p412  Power up bandgap/reference circuitry
  Delay_msec(7)  ;	                        // Delay before powering up rest of ADC,7ms?2010.8.31
  AdcCtrRegs.ADCTRL3.bit.ADCPWDN = 1     ;	//p412 Power up rest of ADC
  Delay_usec(20) ;                   		  // Delay after powering up ADC

//  AdcCtrRegs.ADCTRL3.bit.SMODE_SEL = 1 ;  //同时采样模式2010.9.1
  
  AdcCtrRegs.ADCTRL1.bit.ACQ_PS = 2   ;  //p409 Acquition window size = 3 clock
  AdcCtrRegs.ADCTRL1.bit.CPS = 1      ;  //p409 Tclk = CLK/2
  AdcCtrRegs.ADCTRL3.bit.ADCCLKPS = 4 ;  //p412 ADC core clock divider, HSPCLK(75MHz)/(2*4) = 9.3728MHz

  AdcCtrRegs.ADCMAXCONV.all = 0x0009  ;	 //p297
  AdcCtrRegs.ADCTRL1.bit.SEQ_CASC = 1 ;  //p293 Cascaded mode,SEQ1 and SEQ2 = single 16-state
  AdcCtrRegs.ADCTRL1.bit.CONT_RUN = 1 ;  //p293 Cont. conv. mode
	
  AdcCtrRegs.ADCCHSELSEQ1.all = 0xFE76 ; //p300
  AdcCtrRegs.ADCCHSELSEQ2.all = 0x9345 ; //p300
  AdcCtrRegs.ADCCHSELSEQ3.all = 0x00AB ; //p300
  AdcCtrRegs.ADCCHSELSEQ4.all = 0x0000 ; //p300
}	

//===============通用I/0口初始化====================
void Setup_GpioSet(void)
{
  EALLOW  ;
  
  // Setup for PWM Mode
  // GioMuxRegs.GPAMUX.all = 0x077F ;
  
  // Setup for Switch Mode
  //GioMuxRegs.GPAMUX.all = 0x0015 ; //p33,pwm1 3 5使能，2 4 6数字IO口控制,CAP1 2 3数字IO
  GioMuxRegs.GPAMUX.all = 0x0795 ;//p33,pwm1 3 5使能，2 4 6数字IO口控制,CAP1 2 3捕获功能,T2PWM使能，其他数字IO口
  GioDatRegs.GPADAT.all = 0x00FF ; //p33   
  GioMuxRegs.GPADIR.all = 0x00FF   ;	//p33 PA DIR : 1=output,0=input pwm1-6, T1PWM，T2PWM输出， 其它输入
  GioMuxRegs.GPAQUAL.all = 0x0000  ;	//p33 PA Input Qualification:
  /* 0x00=No, 0x01=SET_SYS_CLOCKS/2, 0x02=SET_SYS_CLOCKS/4, 0x04=SET_SYS_CLOCKS/510 */
  
  // Setup for PWM mode  
  // GioMuxRegs.GPBMUX.all = 0x0003  ;   
  
  // Setup for Relay Mode
  GioMuxRegs.GPBMUX.all = 0x0755 ;//pwm7 9 11使能，8 10 12数字IO口控制,CAP4 5 6捕获功能,T3PWM使能，其他数字IO口
  GioDatRegs.GPBDAT.all = 0x80FF  ;  //p33
  GioMuxRegs.GPBDIR.all = 0x80FF   ; //1=output,0=input pwm7-12, T3PWM，T4PWM，C6TRIP输出， 其它输入
  GioMuxRegs.GPBQUAL.all = 0x0000  ;	//p33 PB Input Qualification:
  /* 0x00=No, 0x01=SET_SYS_CLOCKS/2, 0x02=SET_SYS_CLOCKS/4, 0x04=SET_SYS_CLOCKS/510 */
  
  GioMuxRegs.GPDMUX.all = 0x0000 ; //p33  
  GioMuxRegs.GPDDIR.all = 0x0000  ;	// DIR: 1=output,0=input
  GioMuxRegs.GPDQUAL.all = 0x0000  ;	// PD Input Qualification:
  /* 0x00=No, 0x01=SET_SYS_CLOCKS/2, 0x02=SET_SYS_CLOCKS/4, 0x04=SET_SYS_CLOCKS/510 */
	
  GioMuxRegs.GPEMUX.all = 0x0000  ; 	
  GioMuxRegs.GPEDIR.all = 0x04  ;	// DIR: 1=output,0=input，load输出，XINT1，XINT2输入
  GioMuxRegs.GPEQUAL.all = 0x02 ;	// PE Input Qualification:
  /* 0x00=No, 0x01=SET_SYS_CLOCKS/2, 0x02=SET_SYS_CLOCKS/4, 0x04=SET_SYS_CLOCKS/510 */

  GioMuxRegs.GPFMUX.all = 0x0080 ;   // F6、7使能，其它数字IO		 
  GioMuxRegs.GPFDIR.all = 0x4731 ;	// DIR: 1=output,0=input,F0、5、8、9、10、14输出，其他输入

  GioMuxRegs.GPGMUX.all = 0x0030 ; 
  GioMuxRegs.GPGDIR.all = 0x10 ;	// DIR: 1=output,0=input
  //	5(RXDB),4(TXDB),3,2,1,0
  //     0       1    0 0 0 0	= 0x10
  EDIS  ; 
}

//================捕获单元1初始化====================

void Setup_CAPfunc1(void)  
{
	  
  EvaCtrRegs.CAPCONA.all = 0x32A8  ; // P348, （0x3254上升沿,0x32A8下降沿）
  EvaCtrRegs.CAPFIFOA.all = 0x0000 ; 
  EvaCtrRegs.EVAIFRC.all = 0xFFFF  ; //p356
  EvaCtrRegs.EVAIMRC.all = 0x0007  ; //p358 捕获单元中断屏蔽使能

}

//================捕获单元2初始化====================

void Setup_CAPfunc2(void)  
{
	  
  EvbCtrRegs.CAPCONB.all = 0x32A8  ; // P350 （0x3254上升沿,0x32A8下降沿）
  EvbCtrRegs.CAPFIFOB.all = 0x0000 ; 
  EvbCtrRegs.EVBIFRC.all = 0xFFFF  ; //p360
  EvbCtrRegs.EVBIMRC.all = 0x0007  ; //p362 捕获单元中断屏蔽使能

}

//=================EV1初始化设置===============

void Setup_EV1(float freq)
{
// EVA Configure T1PWM, T2PWM, PWM1-PWM6 
// Step 1  Initalize the timers
  PERD_TMR1 = (Uint16)(SET_SYS_CLOCKS/(long)(4*freq))  ; //freq=
  EvaCtrRegs.T1PR = PERD_TMR1     ;    //p195  Timer1 period
  EvaCtrRegs.T1CMPR = PERD_TMR1/2 ;    //p195 Timer1 compare
  EvaCtrRegs.T1CNT = 0x0000   ;        //p195 Timer1 counter
  // TMODE = continuous up/down
  // Timer enable
  // Timer compare enable
  EvaCtrRegs.T1CON.all = 0x8842 ;  //p337 仿真挂起不受影响，连续增减计数,电机运转时不能仿真挂起！
  EvaCtrRegs.EVAIFRA.all = 0xFFFF  ; //p354
  EvaCtrRegs.EVAIMRA.all = 0x0280  ; //p357 T1周期中断，下溢中断屏蔽使能

  EvaCtrRegs.T2PR = PERD_TMR1     ;    //p195  Timer1 period
  EvaCtrRegs.T2CMPR = PERD_TMR1/2 ;    //p195 Timer1 compare
  EvaCtrRegs.T2CNT = 0x0000   ;        //p195 Timer1 counter
  EvaCtrRegs.T2CON.all = 0x8842 ;  //p337 仿真挂起不受影响，连续增减计数,电机运转时不能仿真挂起！

// Step 2  Setup T1PWM and T2PWM
  // Drive T1/T2 PWM by compare logic
  EvaCtrRegs.GPTCONA.bit.TCMPOE = 1 ; //p197
  // Polarity of GP Timer 1 Compare = Active low
  EvaCtrRegs.GPTCONA.bit.T2PIN = 1 ; //p197

// Step 3 Enable compare for PWM1-PWM6
  EvaCtrRegs.CMPR1 = 0xFFFF ;
  EvaCtrRegs.CMPR2 = 0xFFFF ;
  EvaCtrRegs.CMPR3 = 0xFFFF ;
    
   // Compare action control.  Action that takes place on a cmpare event
   // 10 - active high
   // 01 - active low
  EvaCtrRegs.ACTRA.all = 0x0555   ;	//p346  change 0x0666 => 0x0999,PWM1 2 3 4 5 6低有效
  EvaCtrRegs.DBTCONA.all = 0x0000 ; //p353 Deadband: disable
  EvaCtrRegs.COMCONA.all = 0xA600 ; //p342 0xA600
//  EvaCtrRegs.EXTCONA.bit.INDCOE = 0  ; //p364
}

//=================EV2初始化设置===============
void Setup_EV2(float freq)
{
// EVB Configure T3PWM, T4PWM, PWM7-PWM12 
// Step 1  Initalize the timers

  PERD_TMR3 = (Uint16)(SET_SYS_CLOCKS/(long)(4*freq))  ; //freq=
  EvbCtrRegs.T3PR = PERD_TMR3     ;    //p195  Timer3 period
  EvbCtrRegs.T3CMPR = PERD_TMR3/2 ;    //p195 Timer3 compare
  EvbCtrRegs.T3CNT = 0x0000   ;        //p195 Timer3 counter
  // TMODE = continuous up/down
  // Timer enable
  // Timer compare enable
  EvbCtrRegs.T3CON.all = 0x8842 ;  //p337 仿真挂起不受影响，连续增减计数,电机运转时不能仿真挂起！
  EvbCtrRegs.EVBIFRA.all = 0xFFFF  ; //p354
  EvbCtrRegs.EVBIMRA.all = 0x0280  ; //p357 T3周期中断，下溢中断屏蔽使能

// Step 2  Setup T3PWM and T4PWM
  // Drive T3/T4 PWM by compare logic
  EvbCtrRegs.GPTCONB.bit.TCMPOE = 1 ; //p197
  // Polarity of GP Timer 1 Compare = Active low
  EvbCtrRegs.GPTCONB.bit.T3PIN = 1 ; //p197

// Step 3 Enable compare for PWM1-PWM6
  EvbCtrRegs.CMPR4 = 0xFFFF ;
  EvbCtrRegs.CMPR5 = 0xFFFF ;
  EvbCtrRegs.CMPR6 = 0xFFFF ;
    
   // Compare action control.  Action that takes place on a cmpare event
   // 10 - active high
   // 01 - active low
  EvbCtrRegs.ACTRB.all = 0x0555   ;	//p346  change 0x0666 => 0x0999,PWM1 2 3 4 5 6低有效
  EvbCtrRegs.DBTCONB.all = 0x0000 ; //p353 Deadband: disable
  EvbCtrRegs.COMCONB.all = 0xA600 ; //p342 0xA600
//  EvaCtrRegs.EXTCONA.bit.INDCOE = 0  ; //p364
}
