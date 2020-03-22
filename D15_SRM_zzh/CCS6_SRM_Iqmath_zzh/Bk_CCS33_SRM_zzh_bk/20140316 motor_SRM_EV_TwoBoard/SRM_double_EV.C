/*=====================================================================================
File name:        SRM_MAIN.C  (IQ version)                                     
Originator:	LH
Description: 
Main file for SRM CONTROL.
=====================================================================================*/

#define  XTAL    (30)
#define  SET_SYS_CLOCKS    (150000)
#define  GLOBAL_Q    15
long GlobalQ = GLOBAL_Q;     

#include "F281x_setGMACS.h"
#include "F281x_setGREGS.h" 
#include "F281x_setGINTR.h"
#include "F281x_setGFUNC.h"
#include "F281x_setLCDSCIB.h"
#include "math.h"
#include "IQmathLib.h"
#include "SRM1.h"
#include "SRM1_FUNC.C"
#include "SRM2.h"
#include "SRM2_FUNC.C"
#include "SetPeripheral.C"


#define LEVEL1  1      	           
#define LEVEL2  2                     
#define LEVEL3  3                    
#define   BUILDLEVEL LEVEL2

float32  T=0.001/ISR_FREQUENCY ;     
float32  SpeedRef = 0.3  ;            
Uint16 SpeedLoopCount = 1;           
Uint16 SpeedLoopPrescaler = 20;       

READ_KEY  read_key1= READ_KEY_DEFAULTS;
ADC adc=ADC_DEFAULTS;                        

STC1    stc1 = STC1_DEFAULTS;
APC1    apc1 = APC1_DEFAULTS;          
CCC1    ccc1 = CCC1_DEFAULTS;        
PWMGEN1 pwm1 = PWMGEN1_DEFAULTS ;            
PIDREG1  pid1_spd = PIDREG1_DEFAULTS;
ILEG3CORRECT1         ileg3_crc1 = ILEG3CORRECT1_DEFAULTS ;     
ILEG3DCBUSMEAS1       ileg3_vdc1 = ILEG3DCBUSMEAS1_DEFAULTS;   
SPEED_MEAS1_CAP   spd_meas1 = SPEED_MEAS1_CAP_DEFAULTS ;

STC2    stc2 = STC2_DEFAULTS;
APC2    apc2 = APC2_DEFAULTS;       
CCC2    ccc2 = CCC2_DEFAULTS;         
PWMGEN2 pwm2 = PWMGEN2_DEFAULTS ;            
PIDREG2  pid2_spd = PIDREG2_DEFAULTS;
ILEG3CORRECT2         ileg3_crc2 = ILEG3CORRECT2_DEFAULTS ;     
ILEG3DCBUSMEAS2       ileg3_vdc2 = ILEG3DCBUSMEAS2_DEFAULTS;    
SPEED_MEAS2_CAP   spd_meas2 = SPEED_MEAS2_CAP_DEFAULTS ;


Uint16  FLAG_LCDS = 0;
Uint16  DutyCycle1=0, DutyCycle2=0, DutyCycle3=0 ; 
Uint16  Slice = 0 ; 
Uint16 TMP_ALAM=0,FLAG_ALAM = 0;
Uint16 FLAG_HYS=0, FLAG_HYS2=0,FLAG_HYS3=0 ;
Uint32  Cnt_T1PINT_isr=0;
interrupt void T1PINT_isr(void)
{
  Slice++ ;
  Cnt_T1PINT_isr++ ;                        
  spd_meas1.SpeedMeasCount++;             
  spd_meas2.SpeedMeasCount++;             

  read_key1.read(&read_key1);             
  adc.read(&adc);                         

  ileg3_vdc1.read(&ileg3_vdc1);        
  ileg3_vdc2.read(&ileg3_vdc2);        
  ADC_START ; 

  if((GioDatRegs.GPDDAT.bit.GPIOD0 ==0)||(GioDatRegs.GPDDAT.bit.GPIOD5 ==0))
       {TMP_ALAM=1;}  
  else {TMP_ALAM=0;}
    
  if(TMP_ALAM==1){FLAG_ALAM=1;ON_BUZZER;}

  if(FLAG_ALAM==0)
  {
// ***************** LEVEL1 *****************
#if (BUILDLEVEL==LEVEL1)                      

  if(FLAG_HYS==0)   
    {
        if(spd_meas1.SpeedRpm<SPD_BORDER){FLAG_HYS=0;}          
        else{FLAG_HYS=1;}

        stc1.RunState=read_key1.RunState;     
        stc1.calc(&stc1);

		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagStartPhase1=stc1.FlagStartPhase1;
		pwm1.FlagStartPhase2=stc1.FlagStartPhase2;
		pwm1.FlagStartPhase3=stc1.FlagStartPhase3;
	}
  else if(FLAG_HYS==1) 
    {
        if(spd_meas1.SpeedRpm>=(SPD_BORDER-50)){FLAG_HYS=1;}      
        else{FLAG_HYS=0;}

        apc1.RunState=read_key1.RunState; 
           
    	if(apc1.RunState==FWD_STATE)
		{
		 
             apc1.AngOn = _IQ(0.4);                
             apc1.AngOff = _IQ(1.7);              
             apc1.AngStepCmut = _IQ(1.8);         
             apc1.calc(&apc1);

 		  
         }
        else if(apc1.RunState==RVS_STATE) 
        { 
		  if(spd_meas1.SpeedRpm<10)
	    	{
             apc1.AngOn = _IQ(0.7);               
             apc1.AngOff = _IQ(1.8);              
             apc1.AngStepCmut = _IQ(2.0);         
//             apc1.calc(&apc1);
		    }
		  else
		    {
             apc1.AngOn = _IQ(0.7);                
             apc1.AngOff = _IQ(1.8);              
             apc1.AngStepCmut = _IQ(2.0);         
//             apc1.calc(&apc1);
		    }

         }

		apc1.calc(&apc1);

		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagRunPhase1=apc1.FlagRunPhase1;
		pwm1.FlagRunPhase2=apc1.FlagRunPhase2;
		pwm1.FlagRunPhase3=apc1.FlagRunPhase3;
        pwm1.FlagStepCmutPhase1=apc1.FlagStepCmutPhase1;
        pwm1.FlagStepCmutPhase2=apc1.FlagStepCmutPhase2;
        pwm1.FlagStepCmutPhase3=apc1.FlagStepCmutPhase3;
	}

  pwm1.Da=_IQ(0.5);                            
  pwm1.Db=_IQ(0.5);                          
  pwm1.Dc=_IQ(0.5);                          
  pwm1.calc(&pwm1);


 if(FLAG_HYS2==0)  
   {
        if(spd_meas2.SpeedRpm<SPD_BORDER){FLAG_HYS2=0;}          
        else{FLAG_HYS2=1;}

             
        stc2.RunState=read_key1.RunState;     
        stc2.calc(&stc2);

		pwm2.FlagStc=stc2.FlagStc;
		pwm2.FlagApc=apc2.FlagApc;
		pwm2.FlagStartPhase1=stc2.FlagStartPhase1;
		pwm2.FlagStartPhase2=stc2.FlagStartPhase2;
		pwm2.FlagStartPhase3=stc2.FlagStartPhase3;

        
	}
  else if(FLAG_HYS2==1)     
    {
	    if(spd_meas2.SpeedRpm>=(SPD_BORDER-50)){FLAG_HYS2=1;}      
        else{FLAG_HYS2=0;}

        apc2.RunState=read_key1.RunState;    

		if(apc2.RunState==FWD_STATE)
		{
          apc2.AngOn = _IQ(0.0);                
          apc2.AngOff = _IQ(1.0);            
          apc2.AngStepCmut = _IQ(1.8); 
		   
//		  apc2.calc(&apc2);
        } 
        else if(apc2.RunState==RVS_STATE) 
        {
          apc2.AngOn = _IQ(0.6);                
          apc2.AngOff = _IQ(1.8);            
          apc2.AngStepCmut = _IQ(2.0); 

//          apc2.calc(&apc2);
         }     
       
        apc2.calc(&apc2);
	  
		pwm2.FlagStc=stc2.FlagStc;
		pwm2.FlagApc=apc2.FlagApc;
		pwm2.FlagRunPhase1=apc2.FlagRunPhase1;
		pwm2.FlagRunPhase2=apc2.FlagRunPhase2;
		pwm2.FlagRunPhase3=apc2.FlagRunPhase3;
        pwm2.FlagStepCmutPhase1=apc2.FlagStepCmutPhase1;
        pwm2.FlagStepCmutPhase2=apc2.FlagStepCmutPhase2;
        pwm2.FlagStepCmutPhase3=apc2.FlagStepCmutPhase3;
	  }

  pwm2.Du=_IQ(0.1);                         
  pwm2.Dv=_IQ(0.1);                           
  pwm2.Dw=_IQ(0.1);                          
  pwm2.calc(&pwm2);

#endif // (BUILDLEVEL==LEVEL1)   


// ***************** LEVEL2 *****************
#if (BUILDLEVEL==LEVEL2)                      

  if(FLAG_HYS==0)  
    {
        if(spd_meas1.SpeedRpm<SPD_BORDER){FLAG_HYS=0;}         
        else{FLAG_HYS=1;}

        stc1.RunState=read_key1.RunState;    
        stc1.calc(&stc1);

		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagStartPhase1=stc1.FlagStartPhase1;
		pwm1.FlagStartPhase2=stc1.FlagStartPhase2;
		pwm1.FlagStartPhase3=stc1.FlagStartPhase3;
	}
  else if(FLAG_HYS==1) 
    {
        if(spd_meas1.SpeedRpm>=(SPD_BORDER-50)){FLAG_HYS=1;}     
        else{FLAG_HYS=0;}

        apc1.RunState=read_key1.RunState;     


         apc1.AngOn = _IQ(0.2);                
         apc1.AngOff = _IQ(1.5);             
         apc1.AngStepCmut = _IQ(1.5);        
         apc1.calc(&apc1);


		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagRunPhase1=apc1.FlagRunPhase1;
		pwm1.FlagRunPhase2=apc1.FlagRunPhase2;
		pwm1.FlagRunPhase3=apc1.FlagRunPhase3;
        pwm1.FlagStepCmutPhase1=apc1.FlagStepCmutPhase1;
        pwm1.FlagStepCmutPhase2=apc1.FlagStepCmutPhase2;
        pwm1.FlagStepCmutPhase3=apc1.FlagStepCmutPhase3;

	}

//  ccc1.Ref = adc.Ref;                        
  ccc1.Ref = _IQ(1.0);
  ccc1.FdbPhase1= ileg3_vdc1.ImeasA;         
  ccc1.FdbPhase2= ileg3_vdc1.ImeasB;      
  ccc1.FdbPhase3= ileg3_vdc1.ImeasC;          
  ccc1.calc(&ccc1);
 
 

  pwm1.Da=ccc1.Da;                           
  pwm1.Db=ccc1.Db;                          
  pwm1.Dc=ccc1.Dc;                          
  pwm1.calc(&pwm1);


  if(FLAG_HYS2==0)  
    {
     if  (spd_meas2.SpeedRpm<SPD_BORDER) {FLAG_HYS2=0;}
     else{FLAG_HYS2=1;}
         
          stc2.RunState=read_key1.RunState;    
          stc2.calc(&stc2);

	   	  pwm2.FlagStc=stc2.FlagStc;
		  pwm2.FlagApc=apc2.FlagApc;
		  pwm2.FlagStartPhase1=stc2.FlagStartPhase1;
		  pwm2.FlagStartPhase2=stc2.FlagStartPhase2;
		  pwm2.FlagStartPhase3=stc2.FlagStartPhase3;

    }
   else if(FLAG_HYS2==1)     
    {
	    if(spd_meas2.SpeedRpm>=(SPD_BORDER-50)){FLAG_HYS2=1;}      
        else{FLAG_HYS2=0;}

          apc2.RunState=read_key1.RunState;    
          apc2.AngOn = _IQ(0.0);               
          apc2.AngOff = _IQ(1.0);              
          apc2.AngStepCmut = _IQ(1.8);       
          apc2.calc(&apc2);

		  pwm2.FlagStc=stc2.FlagStc;
	  	  pwm2.FlagApc=apc2.FlagApc;
		  pwm2.FlagRunPhase1=apc2.FlagRunPhase1;
		  pwm2.FlagRunPhase2=apc2.FlagRunPhase2;
		  pwm2.FlagRunPhase3=apc2.FlagRunPhase3;
          pwm2.FlagStepCmutPhase1=apc2.FlagStepCmutPhase1;
          pwm2.FlagStepCmutPhase2=apc2.FlagStepCmutPhase2;
          pwm2.FlagStepCmutPhase3=apc2.FlagStepCmutPhase3;
	 }

//     ccc2.Ref = adc.Ref;
     ccc2.Ref = _IQ(1.1);                    
     ccc2.FdbPhase1= ileg3_vdc2.ImeasU;        
     ccc2.FdbPhase2= ileg3_vdc2.ImeasV;         
     ccc2.FdbPhase3= ileg3_vdc2.ImeasW;         
     ccc2.calc(&ccc2);

     pwm2.Du=ccc2.Du;                          
     pwm2.Dv=ccc2.Dv;                           
     pwm2.Dw=ccc2.Dw;                           
     pwm2.calc(&pwm2);


#endif // (BUILDLEVEL==LEVEL2)


// ***************** LEVEL3 *****************
#if (BUILDLEVEL==LEVEL3)                     

  if  (spd_meas1.SpeedRpm<SPD_BORDER)        
      {
        stc1.RunState=read_key1.RunState;    
        stc1.calc(&stc1);

		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagStartPhase1=stc1.FlagStartPhase1;
		pwm1.FlagStartPhase2=stc1.FlagStartPhase2;
		pwm1.FlagStartPhase3=stc1.FlagStartPhase3;

      }
  else if(spd_meas1.SpeedRpm>=SPD_BORDER)     
      {
        apc1.RunState=read_key1.RunState;    
        apc1.AngOn = _IQ(0.0);              
        apc1.AngOff = _IQ(0.5);              
        apc1.AngStepCmut = _IQ(1.0);         
        apc1.calc(&apc1);

		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagRunPhase1=apc1.FlagRunPhase1;
		pwm1.FlagRunPhase2=apc1.FlagRunPhase2;
		pwm1.FlagRunPhase3=apc1.FlagRunPhase3;
        pwm1.FlagStepCmutPhase1=apc1.FlagStepCmutPhase1;
        pwm1.FlagStepCmutPhase2=apc1.FlagStepCmutPhase2;
        pwm1.FlagStepCmutPhase3=apc1.FlagStepCmutPhase3;
	  }

  ccc1.Ref = pid1_spd.Out;                       
  ccc1.FdbPhase1= ileg3_vdc1.ImeasA;         
  ccc1.FdbPhase2= ileg3_vdc1.ImeasB;         
  ccc1.FdbPhase3= ileg3_vdc1.ImeasC;        
  ccc1.calc(&ccc1);

  pwm1.Da=ccc1.Da;                          
  pwm1.Db=ccc1.Db;                           
  pwm1.Dc=ccc1.Dc;                          
  pwm1.calc(&pwm1);

  if((read_key1.RunState==FWD_STATE)||(read_key1.RunState==RVS_STATE))
    {
      SpeedLoopCount++;

      if(SpeedLoopCount >= SpeedLoopPrescaler)
        {
          pid1_spd.Ref=adc.Ref;
          pid1_spd.Fdb=spd_meas1.Speed;
          pid1_spd.calc(&pid1_spd);
          SpeedLoopCount=0;
	    }
    } 
  else
    {
      pid1_spd.Ui=0;
	}


  if  (spd_meas2.SpeedRpm<SPD_BORDER)         
      {
        stc2.RunState=read_key1.RunState;     
        stc2.calc(&stc2);

		pwm2.FlagStc=stc2.FlagStc;
		pwm2.FlagApc=apc2.FlagApc;
		pwm2.FlagStartPhase1=stc2.FlagStartPhase1;
		pwm2.FlagStartPhase2=stc2.FlagStartPhase2;
		pwm2.FlagStartPhase3=stc2.FlagStartPhase3;

      }
  else if(spd_meas2.SpeedRpm>=SPD_BORDER)      
      {
        apc2.RunState=read_key1.RunState;    
        apc2.AngOn = _IQ(0.1);               
        apc2.AngOff = _IQ(0.6);              
        apc2.AngStepCmut = _IQ(1.1);         
        apc2.calc(&apc2);

		pwm2.FlagStc=stc2.FlagStc;
		pwm2.FlagApc=apc2.FlagApc;
		pwm2.FlagRunPhase1=apc2.FlagRunPhase1;
		pwm2.FlagRunPhase2=apc2.FlagRunPhase2;
		pwm2.FlagRunPhase3=apc2.FlagRunPhase3;
        pwm2.FlagStepCmutPhase1=apc2.FlagStepCmutPhase1;
        pwm2.FlagStepCmutPhase2=apc2.FlagStepCmutPhase2;
        pwm2.FlagStepCmutPhase3=apc2.FlagStepCmutPhase3;
	  }

  ccc2.Ref = adc.Ref;                      
  ccc2.FdbPhase1= ileg3_vdc2.ImeasU;         
  ccc2.FdbPhase2= ileg3_vdc2.ImeasV;         
  ccc2.FdbPhase3= ileg3_vdc2.ImeasW;        
  ccc2.calc(&ccc2);

  pwm2.Du=ccc2.Du;                          
  pwm2.Dv=ccc2.Dv;                          
  pwm2.Dw=ccc2.Dw;                           
  pwm2.calc(&pwm2);

  if((read_key1.RunState==FWD_STATE)||(read_key1.RunState==RVS_STATE))
    {
      SpeedLoopCount++;

      if(SpeedLoopCount >= SpeedLoopPrescaler)
        {
          pid2_spd.Ref=adc.Ref;
          pid2_spd.Fdb=spd_meas2.Speed;
          pid2_spd.calc(&pid2_spd);
          SpeedLoopCount=0;
	    }
    } 
  else
    {
      pid2_spd.Ui=0;
	}


#endif // (BUILDLEVEL==LEVEL3)   

    }
  else   
    {
     EvaCtrRegs.CMPR1 = 0xFFFF ;
     EvaCtrRegs.CMPR2 = 0xFFFF ;
     EvaCtrRegs.CMPR3 = 0xFFFF ;
     EvbCtrRegs.CMPR4 = 0xFFFF ;
     EvbCtrRegs.CMPR5 = 0xFFFF ;
     EvbCtrRegs.CMPR6 = 0xFFFF ;
	}
  DutyCycle1=(100*pwm1.Da)>>15  ;     
  DutyCycle2=(100*pwm2.Du)>>15  ;  

  if(Slice == 1)
    {
//      if(ileg3_vdc1.VdcMeas>_IQ(0.5))
//        {ON_RELAY1; }
//	  else
//	    {OFF_RELAY1;}
    }
  else if (Slice == 2){;}
  else if (Slice == 5){Slice = 0;}
 
  if( (Cnt_T1PINT_isr % 5000) == 0) { T_LED; }  
  if( (Cnt_T1PINT_isr % 2000) == 0) { FLAG_LCDS = 1 ; }   

  EvaCtrRegs.EVAIFRA.all = 0x0080      ; 
  PieCtrRegs.PIEACK.all = PIEACK_GROUP2 ;
}


Uint16  FLAG_CAP1 = 0, FLAG_CAP2 = 0,FLAG_CAP3 = 0 ;
Uint16  FLAG_CAP4 = 0, FLAG_CAP5 = 0,FLAG_CAP6 = 0 ;
interrupt void cap1_isr(void) 
{
  spd_meas1.calc(&spd_meas1);               
  if(read_key1.RunState!=STOP_STATE){FLAG_CAP1 = 1  ;} 
   
  EvaCtrRegs.EVAIFRC.all = 0x0001      ;
  PieCtrRegs.PIEACK.all = PIEACK_GROUP3 ;  	
}

interrupt void cap2_isr(void) 
{
  spd_meas1.calc(&spd_meas1);              
  if(read_key1.RunState!=STOP_STATE){FLAG_CAP2 = 1  ;} 

  EvaCtrRegs.EVAIFRC.all = 0x0002       ;  
  PieCtrRegs.PIEACK.all = PIEACK_GROUP3 ; 	
}

interrupt void cap3_isr(void)  
{
  spd_meas1.calc(&spd_meas1);                
  if(read_key1.RunState!=STOP_STATE){FLAG_CAP3 = 1  ;} 
  
  EvaCtrRegs.EVAIFRC.all = 0x0004       ;  
  PieCtrRegs.PIEACK.all = PIEACK_GROUP3 ;  	
}

interrupt void cap4_isr(void) 
{
  spd_meas2.calc(&spd_meas2);               
  if(read_key1.RunState!=STOP_STATE){FLAG_CAP4 = 1  ;} 

  EvbCtrRegs.EVBIFRC.all = 0x0001      ; 
  PieCtrRegs.PIEACK.all = PIEACK_GROUP5 ;  	
}

interrupt void cap5_isr(void) 
{
  spd_meas2.calc(&spd_meas2);               
  if(read_key1.RunState!=STOP_STATE){FLAG_CAP5 = 1  ;} 

  EvbCtrRegs.EVBIFRC.all = 0x0002       ; 
  PieCtrRegs.PIEACK.all = PIEACK_GROUP5 ; 	
}

interrupt void cap6_isr(void)  
{
  spd_meas2.calc(&spd_meas2);               
  if(read_key1.RunState!=STOP_STATE){FLAG_CAP6 = 1  ;} 

  EvbCtrRegs.EVBIFRC.all = 0x0004       ;  
  PieCtrRegs.PIEACK.all = PIEACK_GROUP5 ;  	
}



void main(void)
{
  // STEP 1. Initialize System Control registers, PLL, WatchDog, Clocks to default state:
  Setup_CpuCtrl() ;  // F281x_setGFUNC.h

  Setup_GpioSet() ; //¥À∫Ø ˝≈‘⁄ø™Õ∑£¨“ÚŒ™MUXµƒ∏ƒ±‰ª·∏¥Œªƒ≥–©ºƒ¥Ê∆˜

  // Disable and clear all CPU interrupts:
  DINT   ;
  IER = 0x0000  ;
  IFR = 0x0000  ;

  // Initialize Pie Control Registers To Default State:
  Setup_PIEctrl() ;

// Initialize the PIE Vector Table To a Known State:
// This function populates the PIE vector table with pointers
  Setup_PIEvect() ;	
	
  EALLOW  ;	// This is needed to write to EALLOW protected registers

  PieVecRegs.T1PINT = &T1PINT_isr;  
  PieVecRegs.CAPINT1 = &cap1_isr ; 
  PieVecRegs.CAPINT2 = &cap2_isr ;  
  PieVecRegs.CAPINT3 = &cap3_isr ; 
  PieVecRegs.CAPINT4 = &cap4_isr ;
  PieVecRegs.CAPINT5 = &cap5_isr ;
  PieVecRegs.CAPINT6 = &cap6_isr ; 
 
  EDIS    ; // This is needed to disable write to EALLOW protected registers

// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the F2812.cmd file. 
  Opera_MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart) ;

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
  Setup_FlashRM() ;

//  Setup_CpuTmr0() ;
//  Setup_TimeISR(&CpuTmr0, 150, (1000/ISR_FREQUENCY)) ;	// 150MHz CPU Freq, 50 usec Period (in uSeconds)
//  START_CpuTmr0() ;  //”√µΩ∂® ±∆˜T0µƒ∆‰À˚ºƒ¥Ê∆˜≥ı ºªØ∫Û£¨‘Ÿ∆Ù∂ØT0

// Interrupt Enable Register  , P90
//  IER |= M_INT1  ;	// for TINT0
  IER |= M_INT2  ;  // for T1PINT  T1UFINT
  IER |= M_INT3  ;  // for CAPINT3
  IER |= M_INT5  ;  // for CAPINT6
	
//	PIE : Peripheral Interrupts setting  , P90
  PieCtrRegs.PIEIER02.bit.INTx4 = 1  ;   
  PieCtrRegs.PIEIER03.bit.INTx5 = 1  ;    
  PieCtrRegs.PIEIER03.bit.INTx6 = 1  ;    
  PieCtrRegs.PIEIER03.bit.INTx7 = 1  ;   
  PieCtrRegs.PIEIER05.bit.INTx5 = 1  ;  
  PieCtrRegs.PIEIER05.bit.INTx6 = 1  ;    
  PieCtrRegs.PIEIER05.bit.INTx7 = 1  ;   

// for SCI debug
  sci_debug_init() ;

  Setup_EV1(ISR_FREQUENCY)  ;  
  Setup_EV2(ISR_FREQUENCY)  ;   
  RST_EV1 ;                    
  RST_EV2 ;                     

  Setup_CAPfunc1();
  Setup_CAPfunc2();

  Setup_ADCfunc()     ;	
// Enable global Interrupts and higher priority real-time debug events:
  
 //“∫æß≥ı ºªØ
  LCDPO_Init();	
  //LCDPO_SetColor(BLACK,RED); 
   //«Â∆¡
  LCDPO_Clears();

  Delay_msec(500);                                      
  
  ADC_START ;
  Delay_msec(10);


//================º◊µÁª˙øÿ÷∆≤Œ ˝≥ı ºªØ====================

  ileg3_crc1.read(&ileg3_crc1);                         
  if(_IQabs(ileg3_crc1.ImeasAOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc1.ImeasAOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc1.ImeasBOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc1.ImeasBOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc1.ImeasCOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc1.ImeasCOffset=_IQ(0.594);}

// Initialize the ILEG3DCBUSMEAS module ADC
  ileg3_vdc1.ImeasAGain = _IQ(16.667);                    
  ileg3_vdc1.ImeasAOffset = ileg3_crc1.ImeasAOffset;     
  ileg3_vdc1.ImeasBGain = _IQ(16.667);                   
  ileg3_vdc1.ImeasBOffset = ileg3_crc1.ImeasBOffset;     
  ileg3_vdc1.ImeasCGain = _IQ(16.667);                     
  ileg3_vdc1.ImeasCOffset = ileg3_crc1.ImeasCOffset;    
  ileg3_vdc1.VdcMeasGain = _IQ(77.5757);                  
  ileg3_vdc1.VdcMeasOffset = _IQ(0);                     

// Initialize the PID_REG3 module for speed
  pid1_spd.Kp = _IQ(2);                  
  pid1_spd.Ki = _IQ(0.001);							
//  pid1_spd.Ki = _IQ(T*SpeedLoopPrescaler);							
  pid1_spd.OutMax = _IQ(0.5);
  pid1_spd.OutMin = _IQ(0);
  pid1_spd.UiMax = _IQ(0.2); 
  pid1_spd.UiMin = _IQ(-0.2);  
  pid1_spd.Err_Border = _IQ(0.1); 
  pid1_spd.ILoopCount = 0; 
  pid1_spd.IPrescale = 1; 

  ccc1.Imax=_IQ(1);                                    


  ileg3_crc2.read(&ileg3_crc2);                          
  if(_IQabs(ileg3_crc2.ImeasUOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc2.ImeasUOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc2.ImeasVOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc2.ImeasVOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc2.ImeasWOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc2.ImeasWOffset=_IQ(0.594);}

  ileg3_vdc2.ImeasUGain = _IQ(16.667);                   
  ileg3_vdc2.ImeasUOffset = ileg3_crc2.ImeasUOffset;    
  ileg3_vdc2.ImeasVGain = _IQ(16.667);                      
  ileg3_vdc2.ImeasVOffset = ileg3_crc2.ImeasVOffset;    
  ileg3_vdc2.ImeasWGain = _IQ(16.667);                    
  ileg3_vdc2.ImeasWOffset = ileg3_crc2.ImeasWOffset;   

  pid2_spd.Kp = _IQ(2);                  
  pid2_spd.Ki = _IQ(0.001);							
  pid2_spd.OutMax = _IQ(0.5);
  pid2_spd.OutMin = _IQ(0);
  pid2_spd.UiMax = _IQ(0.2); 
  pid2_spd.UiMin = _IQ(-0.2);  
  pid2_spd.Err_Border = _IQ(0.1); 
  pid2_spd.ILoopCount = 0; 
  pid2_spd.IPrescale = 1; 

  ccc2.Imax=_IQ(1);                                    


  EINT ;	// Enable Global interrupt INTM
  ERTM ;	// Enable Global realtime interrupt DBGM

  OFF_BUZZER;
  ON_RELAY1;

 // Delay_msec(800);
  
  ON_RELAY2;

  SET_EV1;          
  SET_EV2;       

  ADC_START ;
//  ileg3_vdc1.read(&ileg3_vdc1);  //Ω¯»ÎTO÷–∂œ÷Æ«∞¨œ»Ω¯––“ª¥Á—πµÁ¡˜≤…—˘£¨∑¿÷πŒÛ∂Ø◊˜

  //Setxy_LcdPort(0,0)    ;
  //LCDPO_PutStr("Speed=")  ;
  //Setxy_LcdPort(0,0)    ;
  //LCDPO_PutStr("on =    off=")  ;

       LCDPO_SetColor(RED,BLUE);                 //∫Ï…´◊÷ÃÂ£¨¿∂…´±≥æ∞
       LCD_PutStr(0x55,180,40,"À´¬÷∂¿¡¢«˝∂ØµÁ∂Ø∆˚≥µ ‘—È∆ΩÃ®") ;
       LCDPO_DispClock(300,550);                 //œ‘ æ ±÷”
       LCD_PutStr(0x54,10,100,"º◊µÁª˙≤Œ ˝œ‘ æ") ;   
       LCD_PutStr(0x54,400,100,"““µÁª˙≤Œ ˝œ‘ æ") ;
       LCDPO_SetColor(WHITE,BLUE);               //∞◊…´◊÷ÃÂ£¨¿∂…´±≥æ∞
  
  while(1)
  {    

    if(FLAG_LCDS)
    {
//*************************************
// cmd:0x53 œ‘ æ8*8µ„’ÛASCII◊÷∑˚¥Æ
//     0x54 œ‘ æ16*16µ„’Û∫∫◊÷¥Æ£®GBK£© 
//	   0x55 œ‘ æ32*32µ„’Û∫∫◊÷¥Æ£®GB2312£©
//	   0x6E œ‘ æ12*12µ„’Û∫∫◊÷¥Æ£®GBK£© 
//     0x6F œ‘ æ24*24µ„’Û∫∫◊÷¥Æ£®GB2312£©
// y:∫·◊¯±Í
// x:◊›◊¯±Í
//str:“™œ‘ æµƒ◊÷∑˚¥Æ
//*************************************

//================º◊µÁª˙≤Œ ˝œ‘ æ====================


       LCD_PutStr(0x54,10,160,"µÁª˙◊™ÀŸ(r/min)£∫") ;
  	   LCDPO_PutDc2(spd_meas1.SpeedRpm,200,160);

       LCD_PutStr(0x54,10,200,"◊™ÀŸ∏¯∂®(r/min)") ;
  	   LCDPO_PutDc2((pid1_spd.Ref*BASE_SPD)>>15,200,200);
 
       LCD_PutStr(0x54,10,240,"µÁ¡˜∏¯∂®(A)£∫") ;
  	   LCDPO_PutDc2((ccc1.Ref*BASE_CURRENT)>>15,200,240);
  
       LCD_PutStr(0x54,10,280,"ª˝∑÷ ‰≥ˆ(%)") ;
  	   LCDPO_PutDc2((pid1_spd.Ui*100)>>15,200,280);

	   LCD_PutStr(0x54,10,320,"Aœ‡’ºø’±»(%)£∫") ;
  	   LCDPO_PutDc2(DutyCycle1,200,320);
	
	   LCD_PutStr(0x54,10,360,"Aœ‡µÁ¡˜(A)£∫") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc1.RealImeasA),200,360);

	   LCD_PutStr(0x54,10,400,"Bœ‡µÁ¡˜(A)") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc1.RealImeasB),200,400);
	
	   LCD_PutStr(0x54,10,440,"Cœ‡µÁ¡˜(A)£∫") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc1.RealImeasC),200,440);

	   LCD_PutStr(0x54,10,480,"ƒ∏œﬂµÁ—π(V)£∫") ;
  	   LCDPO_PutDc2(ileg3_vdc1.RealVdcMeas,200,480);

//================““µÁª˙≤Œ ˝œ‘ æ====================
          
       LCD_PutStr(0x54,400,520,"ccc1.Ref(%)£∫") ;
  	   LCDPO_PutDc2((adc.AngOff*100)>>15,600,520);

//       LCD_PutStr(0x54,400,140,"adc.AngOn(%):") ;
//  	   LCDPO_PutDc2((adc.AngOn*100)>>15,600,140);
       LCD_PutStr(0x54,400,160,"µÁª˙◊™ÀŸ(r/min)£∫") ;
  	   LCDPO_PutDc2(spd_meas2.SpeedRpm,600,160);

       LCD_PutStr(0x54,400,200,"◊™ÀŸ∏¯∂®(r/min)") ;
  	   LCDPO_PutDc2((pid2_spd.Ref*BASE_SPD)>>15,600,200);
 
       LCD_PutStr(0x54,400,240,"µÁ¡˜∏¯∂®(U)£∫") ;
  	   LCDPO_PutDc2((ccc2.Ref*BASE_CURRENT)>>15,600,240);
  
       LCD_PutStr(0x54,400,280,"ª˝∑÷ ‰≥ˆ(%)") ;
  	   LCDPO_PutDc2((pid2_spd.Ui*100)>>15,600,280);

	   LCD_PutStr(0x54,400,320,"Uœ‡’ºø’±»(%)£∫") ;
  	   LCDPO_PutDc2(DutyCycle2,600,320);
	
	   LCD_PutStr(0x54,400,360,"Vœ‡µÁ¡˜(A)£∫") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc2.RealImeasU),600,360);

	   LCD_PutStr(0x54,400,400,"Wœ‡µÁ¡˜(A)") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc2.RealImeasV),600,400);
	
	   LCD_PutStr(0x54,400,440,"Wœ‡µÁ¡˜(A)£∫") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc2.RealImeasW),600,440);

	   LCD_PutStr(0x54,400,480,"ƒ∏œﬂµÁ—π(V)£∫") ;
  	   LCDPO_PutDc2(ileg3_vdc1.RealVdcMeas,600,480);

       FLAG_LCDS = 0            ;
    }
  }

} 	
