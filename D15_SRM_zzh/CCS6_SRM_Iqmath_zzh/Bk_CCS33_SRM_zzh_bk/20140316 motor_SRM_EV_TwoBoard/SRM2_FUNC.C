/* =================================================================================
File name:        SRM2_FUN.C  (IQ version)                  
                    
Originator:	LH

Description: 

=====================================================================================*/

void STC2_calc(STC2 *v)
{
  extern Uint16 FLAG_CAP4,	FLAG_CAP5, FLAG_CAP6;
  extern SPEED_MEAS2_CAP spd_meas2;
  extern APC2 apc2;

  v->FlagStc=1;                              
  apc2.FlagApc=0;                          

  if(v->RunState==FWD_STATE)
    {
      if(spd_meas2.SpeedRpm<SPD_BORDER)
        {
          v->HallData1=GioDatRegs.GPBDAT.bit.GPIOB13; 
          v->HallData2=GioDatRegs.GPBDAT.bit.GPIOB12; 
          v->HallData3=GioDatRegs.GPBDAT.bit.GPIOB11;  
          v->HallData4=GioDatRegs.GPDDAT.bit.GPIOD6;
          v->HallData5=GioDatRegs.GPEDAT.bit.GPIOE0; 
          v->HallData6=GioDatRegs.GPEDAT.bit.GPIOE1;  


	       if(spd_meas2.SpeedRpm<260)              
	         {

//               if(v->HallData5==1){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if(v->HallData6==1){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if(v->HallData4==1){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}               if((v->HallData5==1)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
               if((v->HallData1==0)&&(v->HallData4==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
               if((v->HallData3==0)&&(v->HallData6==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
               if((v->HallData2==0)&&(v->HallData5==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if((v->HallData2==0)&&(v->HallData1==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==0)&&(v->HallData2==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData1==0)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if((v->HallData2==0)&&(v->HallData5==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==0)&&(v->HallData6==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
             }
	       else                                      
	         {
               if     ((v->HallData1==0)&&(v->HallData3==1))     
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;} 
               else if((v->HallData2==1)&&(v->HallData3==0))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData1==1)&&(v->HallData2==0))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=0; v->FlagStartPhase3=1;}
             }
        }
	}
  else if(v->RunState==RVS_STATE)
	{
	 
	 if(spd_meas2.SpeedRpm<SPD_BORDER)
        {
          v->HallData1=GioDatRegs.GPBDAT.bit.GPIOB13; 
          v->HallData2=GioDatRegs.GPBDAT.bit.GPIOB12; 
          v->HallData3=GioDatRegs.GPBDAT.bit.GPIOB11;  
          v->HallData4=GioDatRegs.GPDDAT.bit.GPIOD6;
          v->HallData5=GioDatRegs.GPEDAT.bit.GPIOE0; 
          v->HallData6=GioDatRegs.GPEDAT.bit.GPIOE1;  


	       if(spd_meas2.SpeedRpm<160)              
	         {

//               if(v->HallData5==1){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if(v->HallData6==1){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if(v->HallData4==1){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}               if((v->HallData5==1)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
               if((v->HallData1==1)&&(v->HallData4==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
               if((v->HallData3==1)&&(v->HallData6==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
               if((v->HallData2==1)&&(v->HallData5==1)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if((v->HallData2==0)&&(v->HallData1==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==0)&&(v->HallData2==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData1==0)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if((v->HallData2==0)&&(v->HallData5==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==0)&&(v->HallData6==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
             }
	       else                                      
	         {
               if     ((v->HallData1==1)&&(v->HallData3==0))     
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;} 
               else if((v->HallData2==0)&&(v->HallData3==1))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData1==0)&&(v->HallData2==1))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=0; v->FlagStartPhase3=1;}
             }
        }

	}
  else if(v->RunState==REG_STATE)
    {

	}
  else if(v->RunState==STOP_STATE)
    {
      v->FlagStartPhase1=0;
      v->FlagStartPhase2=0;
      v->FlagStartPhase3=0;

	  v->FlagStc=0;
	}

  FLAG_CAP4=0;    
  FLAG_CAP5=0;    
  FLAG_CAP6=0;	 

}
/*====================================================================================*/ 

void APC2_calc(APC2 *v)
{ extern Uint16 FLAG_CAP4,	FLAG_CAP5, FLAG_CAP6;
  extern SPEED_MEAS2_CAP spd_meas2;
  extern STC2 stc2;
  _iq TempSpd;  

  v->FlagApc=1;                                
  stc2.FlagStc=0;                             
     
  TempSpd=spd_meas2.Speed*BASE_SPD;              
  v->AngStep=TempSpd/(60000*ISR_FREQUENCY);  
  v->AngStep=v->AngStep*360 ;                 
  v->AngStep=_IQdiv(v->AngStep,_IQ(BASE_ANG)); 

  if(v->RunState==FWD_STATE)
    {
      if(FLAG_CAP4)
        { 
          v->AngPhase1 += v->AngStep;

          if     (v->AngPhase1 < v->AngOn)
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOn)&&(v->AngPhase1<v->AngOff)) 
                 {v->FlagRunPhase1=1; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOff)&&(v->AngPhase1<v->AngStepCmut)) 
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
	      else if(v->AngPhase1>=v->AngStepCmut)
	        	 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1; v->AngPhase1=0; FLAG_CAP4=0;}
        }

      if(FLAG_CAP5)
        { 
          v->AngPhase2 += v->AngStep;

          if     (v->AngPhase2 < v->AngOn) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOn)&&(v->AngPhase2<v->AngOff)) 
                 {v->FlagRunPhase2=1; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOff)&&(v->AngPhase2<v->AngStepCmut)) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
	   	  else if(v->AngPhase2>=v->AngStepCmut)
		         {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=1; v->AngPhase2=0; FLAG_CAP5=0;}
        }

      if(FLAG_CAP6)
        {
          v->AngPhase3 += v->AngStep;

          if     (v->AngPhase3 < v->AngOn) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOn)&&(v->AngPhase3<v->AngOff)) 
                 {v->FlagRunPhase3=1; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOff)&&(v->AngPhase3<v->AngStepCmut)) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
	   	  else if(v->AngPhase3>=v->AngStepCmut)
		         {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1; v->AngPhase3=0; FLAG_CAP6=0;}
        }
    }
  else if(v->RunState==RVS_STATE)
	{

	if(FLAG_CAP6)
        { 
          v->AngPhase1 += v->AngStep;

          if     (v->AngPhase1 < v->AngOn)
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOn)&&(v->AngPhase1<v->AngOff)) 
                 {v->FlagRunPhase1=1; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOff)&&(v->AngPhase1<v->AngStepCmut)) 
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
	      else if(v->AngPhase1>=v->AngStepCmut)
	        	 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1; v->AngPhase1=0; FLAG_CAP6=0;}
        }

      if(FLAG_CAP4)
        { 
          v->AngPhase2 += v->AngStep;

          if     (v->AngPhase2 < v->AngOn) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOn)&&(v->AngPhase2<v->AngOff)) 
                 {v->FlagRunPhase2=1; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOff)&&(v->AngPhase2<v->AngStepCmut)) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
	   	  else if(v->AngPhase2>=v->AngStepCmut)
		         {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=1; v->AngPhase2=0; FLAG_CAP4=0;}
        }

      if(FLAG_CAP5)
        {
          v->AngPhase3 += v->AngStep;

          if     (v->AngPhase3 < v->AngOn) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOn)&&(v->AngPhase3<v->AngOff)) 
                 {v->FlagRunPhase3=1; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOff)&&(v->AngPhase3<v->AngStepCmut)) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
	   	  else if(v->AngPhase3>=v->AngStepCmut)
		         {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1; v->AngPhase3=0; FLAG_CAP5=0;}
        }
	}
  else if(v->RunState==REG_STATE)
    {

	}
  else if(v->RunState==STOP_STATE)
    {
	  v->FlagApc=0;
      v->FlagRunPhase1=0;
      v->FlagRunPhase2=0;
      v->FlagRunPhase3=0;
	  v->FlagStepCmutPhase1=0;
	  v->FlagStepCmutPhase2=0;
	  v->FlagStepCmutPhase3=0;

     
	}

}

/*=====================================================================================*/

void CCC2_calc(CCC2 *v)
{ 

    if     (v->FdbPhase1 > v->Imax){v->Du=_IQ(0.0);}
    else if(v->FdbPhase1 > v->Ref ){v->Du=_IQ(0.0);}
    else   {v->Du=_IQ(0.2);}                         

    if     (v->FdbPhase2 > v->Imax){v->Dv=_IQ(0.0);}
    else if(v->FdbPhase2 > v->Ref ){v->Dv=_IQ(0.0);}
    else   {v->Dv=_IQ(0.2);}                        

    if     (v->FdbPhase3 > v->Imax){v->Dw=_IQ(0.0);}
    else if(v->FdbPhase3 > v->Ref ){v->Dw=_IQ(0.0);}
    else   {v->Dw=_IQ(0.2);}                        
}
/*=====================================================================================*/

void PWMGEN2_calc(PWMGEN2 *v)              
{
  if((v->FlagStc==1)&&(v->FlagApc==0))         
    {
        if(v->FlagStartPhase1==1)    
            {
             EvbCtrRegs.CMPR4 = (Uint16)(((_IQ(1)- v->Du)*PERD_TMR3)>>15) ;  
             GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ; 
            }
	      else
		    {
		     EvbCtrRegs.CMPR4 = 0xFFFF ;
             GioDatRegs.GPBDAT.bit.GPIOB1 = INACTIVE ;   
            }
        if(v->FlagStartPhase2==1)    
            {
             EvbCtrRegs.CMPR5 = (Uint16)(((_IQ(1)-v->Dv)*PERD_TMR3)>>15) ;    //Q15 to Q0
             GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ; 
            }
	      else
		    {
		     EvbCtrRegs.CMPR5 = 0xFFFF ;
             GioDatRegs.GPBDAT.bit.GPIOB3 = INACTIVE ;     
            }
        if(v->FlagStartPhase3==1)    
            {
             EvbCtrRegs.CMPR6 = (Uint16)(((_IQ(1)-v->Dw)*PERD_TMR3)>>15) ;   //Q15 to Q0 ;
             GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ; 
            }
	      else
		    {
		     EvbCtrRegs.CMPR6 = 0xFFFF ;
             GioDatRegs.GPBDAT.bit.GPIOB5 = INACTIVE ;    
            }
    }

  else if((v->FlagStc==0)&&(v->FlagApc==1))	    
	{
        if(v->FlagRunPhase1==1)    
            {
             EvbCtrRegs.CMPR4 = (Uint16)(((_IQ(1)-v->Du)*PERD_TMR3)>>15) ;  
             GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ; 
            }
	      else
		    {
		     EvbCtrRegs.CMPR4 = 0xFFFF ;
			 if(v->FlagStepCmutPhase1==0){GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ;}  
		      else{GioDatRegs.GPBDAT.bit.GPIOB1 = INACTIVE ;}
            }

        if(v->FlagRunPhase2==1)
            {	 
             EvbCtrRegs.CMPR5 = (Uint16)(((_IQ(1)-v->Dv)*PERD_TMR3)>>15) ;  
	         GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ; 
            }
	      else
		    {
		     EvbCtrRegs.CMPR5 = 0xFFFF ; 
			 if(v->FlagStepCmutPhase2==0){GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ;}
		      else{GioDatRegs.GPBDAT.bit.GPIOB3 = INACTIVE ;}
            }

        if(v->FlagRunPhase3==1)
            {	 
             EvbCtrRegs.CMPR6 = (Uint16)(((_IQ(1)-v->Dw)*PERD_TMR3)>>15) ; 
             GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ; 
	        }
	      else
		    {
		     EvbCtrRegs.CMPR6 = 0xFFFF ; 
			 if(v->FlagStepCmutPhase3==0){GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ;}  
		      else{GioDatRegs.GPBDAT.bit.GPIOB5 = INACTIVE ;}
            }

    }
}
/*====================================================================================*/ 


void Ileg3_dcbus_read2(ILEG3DCBUSMEAS2 *p)
{
    _iq DigitValue=0, AnalogValue=0;                          


     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT4;                          
	 DigitValue=DigitValue<<11;                                      
     AnalogValue=DigitValue * 3 / 4095;                                
     AnalogValue=_IQmpy((AnalogValue - p->ImeasUOffset), p->ImeasUGain);   
     p->RealImeasU=(Sint16)(AnalogValue>>15);                      
	 p->ImeasU=(p->OldImeasU + AnalogValue/BASE_CURRENT)/2;       
     p->OldImeasU = p->ImeasU;

     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT5;                          
	 DigitValue=DigitValue<<11;                                         
     AnalogValue=DigitValue * 3 / 4095;                                 
     AnalogValue=_IQmpy((AnalogValue - p->ImeasVOffset), p->ImeasVGain);   
     p->RealImeasV=(Sint16)(AnalogValue>>15);                        
	 p->ImeasV=(p->OldImeasV + AnalogValue/BASE_CURRENT)/2;         
     p->OldImeasV = p->ImeasV;

     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT6;                            
	 DigitValue=DigitValue<<11;                                          
     AnalogValue=DigitValue * 3 / 4095;                                 
     AnalogValue=_IQmpy((AnalogValue - p->ImeasWOffset), p->ImeasWGain);   
     p->RealImeasW=(Sint16)(AnalogValue>>15);                          
	 p->ImeasW=(p->OldImeasW + AnalogValue/BASE_CURRENT)/2;         
     p->OldImeasW = p->ImeasW;
	 
}      

/*=====================================================================================*/

void Ileg3_correct2(ILEG3CORRECT2 *p)
{
   _iq Temp_UOffset=0, Temp_VOffset=0,Temp_WOffset=0;           
   Uint16 i;

   for(i=0;i<=9;i++)
      {
        ADC_START;
	    Delay_msec(1);

        Temp_UOffset=(Uint32)AdcCtrRegs.ADCRESULT4;                          
	    Temp_UOffset=Temp_UOffset<<11;                                         
		p->ImeasUOffset += Temp_UOffset;                                    

        Temp_VOffset=(Uint32)AdcCtrRegs.ADCRESULT5;                           
	    Temp_VOffset=Temp_VOffset<<11;                                         
		p->ImeasVOffset += Temp_VOffset;                                   

        Temp_WOffset=(Uint32)AdcCtrRegs.ADCRESULT6;                           
	    Temp_WOffset=Temp_WOffset<<11;                                          
		p->ImeasWOffset += Temp_WOffset;                                    

	  }

     p->ImeasUOffset = (p->ImeasUOffset)/10;                                   
     p->ImeasUOffset=p->ImeasUOffset * 3 / 4095;             
     p->ImeasVOffset = (p->ImeasVOffset)/10;                                   
     p->ImeasVOffset=p->ImeasVOffset * 3 / 4095;             
     p->ImeasWOffset = (p->ImeasWOffset)/10;                                   
     p->ImeasWOffset=p->ImeasWOffset * 3 / 4095;              
}      

/*=====================================================================================*/

void speed_meas2_cap_calc(SPEED_MEAS2_CAP *v)
{
  Uint32 DeltCount;

  v->OldCount = v->NewCount;
  v->NewCount = v->SpeedMeasCount;
  DeltCount =  v->NewCount - v->OldCount;
  v->SpeedRpm= ((Uint32)20000*ISR_FREQUENCY) / (DeltCount*SRM_ROTORS);  
  v->Speed = _IQ(v->SpeedRpm) / BASE_SPD  ; 
}
/*=====================================================================================*/

void pid_reg2_calc(PIDREG2 *v)
{	
    v->Err = v->Ref - v->Fdb;
    v->ILoopCount++;
    if(v->ILoopCount >= v->IPrescale)
     {
         v->Ui = v->Ui + _IQmpy(v->Ki , v->Err) ;
         if(v->Ui < v->UiMin ){v->Ui = v->UiMin;}    
         if(v->Ui > v->UiMax ){v->Ui = v->UiMax;}

         v->ILoopCount=0;
     }
    v->Up = _IQmpy(v->Kp,v->Err);
    v->Out = v->Up + v->Ui; 
    if      (v->Out > v->OutMax){ v->Out =  v->OutMax;}     
    else if (v->Out < v->OutMin){ v->Out =  v->OutMin;}

}
/*=====================================================================================*/

