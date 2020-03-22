/* =================================================================================
File name:        SRM1_FUN.C  (IQ version)                  
                    
Originator:	LH

Description: 

=====================================================================================*/

void READ_KEY_calc(READ_KEY *v)
{
	v->KeyFwd =!GioDatRegs.GPFDAT.bit.GPIOF1; 
	v->KeyRvs =!GioDatRegs.GPFDAT.bit.GPIOF11;
	v->KeyStop=!GioDatRegs.GPFDAT.bit.GPIOF13;

	if(v->KeyFwd==1)    {v->FlagTemp1=1;}else{v->FlagTemp1=0;}
	if(v->FlagTemp1==1) {v->RunState=FWD_STATE;ON_FWD;OFF_RVS;OFF_BLK;}

    if(v->KeyRvs==1)    {v->FlagTemp2=1;}else{v->FlagTemp2=0;}
	if(v->FlagTemp2==1) {v->RunState=RVS_STATE;OFF_FWD;ON_RVS;OFF_BLK;}

    if(v->KeyStop==1)   {v->FlagTemp3=1;}else{v->FlagTemp3=0;}
	if(v->FlagTemp3==1) {v->RunState=STOP_STATE;OFF_FWD;OFF_RVS;ON_BLK;}
}
/*====================================================================================*/

void STC1_calc(STC1 *v)
{
  extern Uint16 FLAG_CAP1,	FLAG_CAP2, FLAG_CAP3;
  extern SPEED_MEAS1_CAP spd_meas1;
  extern APC1 apc1;

  v->FlagStc=1;                           
  apc1.FlagApc=0;                           

  if(v->RunState==FWD_STATE)
    {
      if(spd_meas1.SpeedRpm<SPD_BORDER)
        {
          v->HallData1=GioDatRegs.GPADAT.bit.GPIOA13;  
          v->HallData2=GioDatRegs.GPADAT.bit.GPIOA12; 
          v->HallData3=GioDatRegs.GPADAT.bit.GPIOA11; 
          v->HallData4=GioDatRegs.GPADAT.bit.GPIOA14; 
          v->HallData5=GioDatRegs.GPADAT.bit.GPIOA15;  
          v->HallData6=GioDatRegs.GPBDAT.bit.GPIOB14; 


	       if(spd_meas1.SpeedRpm<800)             
	         {
//               if((v->HallData5==0)&&(v->HallData4==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData6==0)&&(v->HallData5==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData4==0)&&(v->HallData6==1)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
               if((v->HallData1==0)&&(v->HallData2==1)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
               if((v->HallData2==0)&&(v->HallData3==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
               if((v->HallData3==0)&&(v->HallData1==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if(v->HallData1==1){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if(v->HallData2==1){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if(v->HallData3==1){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}  
//               if((v->HallData1==1)&&(v->HallData5==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData2==1)&&(v->HallData6==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==1)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if     ((v->HallData1==0)&&(v->HallData2==1))     
//                      {v->FlagStartPhase2=0; v->FlagStartPhase1=0; v->FlagStartPhase3=1;} 
//               else if((v->HallData2==0)&&(v->HallData3==1))
//                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
//               else if((v->HallData1==1)&&(v->HallData3==0))
//                      {v->FlagStartPhase3=0; v->FlagStartPhase2=1; v->FlagStartPhase1=0;}


             }
	       else if(spd_meas1.SpeedRpm<1250)                                       
	         {
               if     ((v->HallData1==0)&&(v->HallData2==1))     
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;} 
               else if((v->HallData2==0)&&(v->HallData3==1))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData1==1)&&(v->HallData3==0))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=0; v->FlagStartPhase3=1;}
             }
/*		   else   	//开通角为-1.875°
		     {
               if     ((v->HallData1==0)&&(v->HallData6==1))     
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=0; v->FlagStartPhase3=1;} 
               else if((v->HallData5==1)&&(v->HallData1==0))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData4==1)&&(v->HallData3==0))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;}
			 }*/
        }
	}
  else if(v->RunState==RVS_STATE)
	{
	if(spd_meas1.SpeedRpm<SPD_BORDER)
        {
          v->HallData1=GioDatRegs.GPADAT.bit.GPIOA13;  
          v->HallData2=GioDatRegs.GPADAT.bit.GPIOA12; 
          v->HallData3=GioDatRegs.GPADAT.bit.GPIOA11; 
          v->HallData4=GioDatRegs.GPADAT.bit.GPIOA14; 
          v->HallData5=GioDatRegs.GPADAT.bit.GPIOA15;  
          v->HallData6=GioDatRegs.GPBDAT.bit.GPIOB14; 


	       if(spd_meas1.SpeedRpm<160)             
	         {
//               if((v->HallData5==0)&&(v->HallData4==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData6==0)&&(v->HallData5==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData4==0)&&(v->HallData6==1)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if((v->HallData1==1)&&(v->HallData4==1)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData2==1)&&(v->HallData5==1)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==1)&&(v->HallData6==1)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
               if(v->HallData1==1){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
               if(v->HallData2==1){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
               if(v->HallData3==1){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}  
//               if((v->HallData1==1)&&(v->HallData5==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//               if((v->HallData2==1)&&(v->HallData6==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData3==1)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if     ((v->HallData1==0)&&(v->HallData2==1))     
//                      {v->FlagStartPhase2=0; v->FlagStartPhase1=0; v->FlagStartPhase3=1;} 
//               else if((v->HallData2==0)&&(v->HallData3==1))
//                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
//               else if((v->HallData1==1)&&(v->HallData3==0))
//                      {v->FlagStartPhase3=0; v->FlagStartPhase2=1; v->FlagStartPhase1=0;}


             }
	       else if(spd_meas1.SpeedRpm<1250)                                       
	         {
               if     ((v->HallData1==1)&&(v->HallData2==0))     
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;} 
               else if((v->HallData2==1)&&(v->HallData3==0))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData1==0)&&(v->HallData3==1))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=0; v->FlagStartPhase3=1;}
             }
/*		   else   	//开通角为-1.875°
		     {
               if     ((v->HallData1==0)&&(v->HallData6==1))     
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=0; v->FlagStartPhase3=1;} 
               else if((v->HallData5==1)&&(v->HallData1==0))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData4==1)&&(v->HallData3==0))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;}
			 }*/
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

  FLAG_CAP1=0;   
  FLAG_CAP2=0;    
  FLAG_CAP3=0;	 

}
/*====================================================================================*/ 

void APC1_calc(APC1 *v)
{ extern Uint16 FLAG_CAP1,	FLAG_CAP2, FLAG_CAP3;
  extern SPEED_MEAS1_CAP spd_meas1;
  extern STC1 stc1;
  _iq TempSpd;  

  v->FlagApc=1;                              
  stc1.FlagStc=0;                            
     
  TempSpd=spd_meas1.Speed*BASE_SPD;               
  v->AngStep=TempSpd/(60000*ISR_FREQUENCY);   
  v->AngStep=v->AngStep*360 ;                  
  v->AngStep=_IQdiv(v->AngStep,_IQ(BASE_ANG)); 

  if(v->RunState==FWD_STATE)
    {
      if(FLAG_CAP1)
        { 
          v->AngPhase1 += v->AngStep;

          if     (v->AngPhase1 < v->AngOn)
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1;}
          else if((v->AngPhase1>=v->AngOn)&&(v->AngPhase1<v->AngOff)) 
                 {v->FlagRunPhase1=1; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOff)&&(v->AngPhase1<v->AngStepCmut)) 
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
	      else if(v->AngPhase1>=v->AngStepCmut)
	        	 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1; v->AngPhase1=0; FLAG_CAP1=0;}
        }

      if(FLAG_CAP3)
        { 
          v->AngPhase2 += v->AngStep;

          if     (v->AngPhase2 < v->AngOn) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=1;}
          else if((v->AngPhase2>=v->AngOn)&&(v->AngPhase2<v->AngOff)) 
                 {v->FlagRunPhase2=1; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOff)&&(v->AngPhase2<v->AngStepCmut)) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
	   	  else if(v->AngPhase2>=v->AngStepCmut)
		         {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=1; v->AngPhase2=0; FLAG_CAP3=0;}
        }

      if(FLAG_CAP2)
        {
          v->AngPhase3 += v->AngStep;

          if     (v->AngPhase3 < v->AngOn) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1;}
          else if((v->AngPhase3>=v->AngOn)&&(v->AngPhase3<v->AngOff)) 
                 {v->FlagRunPhase3=1; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOff)&&(v->AngPhase3<v->AngStepCmut)) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
	   	  else if(v->AngPhase3>=v->AngStepCmut)
		         {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1; v->AngPhase3=0; FLAG_CAP2=0;}
        }
    }
  else if(v->RunState==RVS_STATE)
	{

	 if(FLAG_CAP2)
        { 
          v->AngPhase1 += v->AngStep;

          if     (v->AngPhase1 < v->AngOn)
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOn)&&(v->AngPhase1<v->AngOff)) 
                 {v->FlagRunPhase1=1; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOff)&&(v->AngPhase1<v->AngStepCmut)) 
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
	      else if(v->AngPhase1>=v->AngStepCmut)
	        	 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1; v->AngPhase1=0; FLAG_CAP2=0;}
        }

      if(FLAG_CAP1)
        { 
          v->AngPhase2 += v->AngStep;

          if     (v->AngPhase2 < v->AngOn) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOn)&&(v->AngPhase2<v->AngOff)) 
                 {v->FlagRunPhase2=1; v->FlagStepCmutPhase2=0;}
          else if((v->AngPhase2>=v->AngOff)&&(v->AngPhase2<v->AngStepCmut)) 
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=0;}
	   	  else if(v->AngPhase2>=v->AngStepCmut)
		         {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=1; v->AngPhase2=0; FLAG_CAP1=0;}
        }

      if(FLAG_CAP3)
        {
          v->AngPhase3 += v->AngStep;

          if     (v->AngPhase3 < v->AngOn) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOn)&&(v->AngPhase3<v->AngOff)) 
                 {v->FlagRunPhase3=1; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOff)&&(v->AngPhase3<v->AngStepCmut)) 
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
	   	  else if(v->AngPhase3>=v->AngStepCmut)
		         {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1; v->AngPhase3=0; FLAG_CAP3=0;}
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

void CCC1_calc(CCC1 *v)
{ 

    if     (v->FdbPhase1 > v->Imax){v->Da=_IQ(0.0);}
    else if(v->FdbPhase1 > v->Ref ){v->Da=_IQ(0.0);}
    else   {v->Da=_IQ(1);}                        

    if     (v->FdbPhase2 > v->Imax){v->Db=_IQ(0.0);}
    else if(v->FdbPhase2 > v->Ref ){v->Db=_IQ(0.0);}
    else   {v->Db=_IQ(1);}                        

    if     (v->FdbPhase3 > v->Imax){v->Dc=_IQ(0.0);}
    else if(v->FdbPhase3 > v->Ref ){v->Dc=_IQ(0.0);}
    else   {v->Dc=_IQ(1);}                        
}
/*=====================================================================================*/

void PWMGEN1_calc(PWMGEN1 *v)          
{
  if((v->FlagStc==1)&&(v->FlagApc==0))         
    {
        if(v->FlagStartPhase1==1)    
            {
             EvaCtrRegs.CMPR1 = (Uint16)(((_IQ(1)- v->Da)*PERD_TMR1)>>15) ;   
             GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ; 
            }
	      else
		    {
		     EvaCtrRegs.CMPR1 = 0xFFFF ;
             GioDatRegs.GPADAT.bit.GPIOA1 = INACTIVE ;    
            }
        if(v->FlagStartPhase2==1)    
            {
             EvaCtrRegs.CMPR2 = (Uint16)(((_IQ(1)-v->Db)*PERD_TMR1)>>15) ;   
             GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ; 
            }
	      else
		    {
		     EvaCtrRegs.CMPR2 = 0xFFFF ;
             GioDatRegs.GPADAT.bit.GPIOA3 = INACTIVE ;    

            }
        if(v->FlagStartPhase3==1)    
            {
             EvaCtrRegs.CMPR3 = (Uint16)(((_IQ(1)-v->Dc)*PERD_TMR1)>>15) ;   
             GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ; 
            }
	      else
		    {
		     EvaCtrRegs.CMPR3 = 0xFFFF ;
             GioDatRegs.GPADAT.bit.GPIOA5 = INACTIVE ;     
            }
    }

  else if((v->FlagStc==0)&&(v->FlagApc==1))	   
	{
        if(v->FlagRunPhase1==1)    
            {
             EvaCtrRegs.CMPR1 = (Uint16)(((_IQ(1)-v->Da)*PERD_TMR1)>>15) ; 
             GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ; 
            }
	      else
		    {
		     EvaCtrRegs.CMPR1 = 0xFFFF ;
			 if(v->FlagStepCmutPhase1==0){GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ;}  
		      else{GioDatRegs.GPADAT.bit.GPIOA1 = INACTIVE ;}
            }

        if(v->FlagRunPhase2==1)
            {	 
             EvaCtrRegs.CMPR2 = (Uint16)(((_IQ(1)-v->Db)*PERD_TMR1)>>15) ; 
	         GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ; 
            }
	      else
		    {
		     EvaCtrRegs.CMPR2 = 0xFFFF ; 
			 if(v->FlagStepCmutPhase2==0){GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ;} 
		      else{GioDatRegs.GPADAT.bit.GPIOA3 = INACTIVE ;}
            }

        if(v->FlagRunPhase3==1)
            {	 
             EvaCtrRegs.CMPR3 = (Uint16)(((_IQ(1)-v->Dc)*PERD_TMR1)>>15) ;  //Q15 to Q0 ;;
             GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ; 
	        }
	      else
		    {
		     EvaCtrRegs.CMPR3 = 0xFFFF ; 
			 if(v->FlagStepCmutPhase3==0){GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ;}  
		      else{GioDatRegs.GPADAT.bit.GPIOA5 = INACTIVE ;}
            }

    }
}
/*====================================================================================*/ 

void Ileg3_dcbus_read1(ILEG3DCBUSMEAS1 *p)
{
    _iq DigitValue=0, AnalogValue=0;                         
//     while (AdcCtrRegs.ADCST.bit.SEQ1_BSY == 1){};    


     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT0;                          
	 DigitValue=DigitValue<<11;                                        
     AnalogValue=DigitValue * 3 / 4095;                               
     AnalogValue=_IQmpy((AnalogValue - p->ImeasAOffset), p->ImeasAGain);  
     p->RealImeasA=(Sint16)(AnalogValue>>15);                       
	 p->ImeasA=(p->OldImeasA + AnalogValue/BASE_CURRENT)/2;       
     p->OldImeasA = p->ImeasA;

     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT1;                             
	 DigitValue=DigitValue<<11;                                        
     AnalogValue=DigitValue * 3 / 4095;                                 
     AnalogValue=_IQmpy((AnalogValue - p->ImeasBOffset), p->ImeasBGain);   
     p->RealImeasB=(Sint16)(AnalogValue>>15);                          
	 p->ImeasB=(p->OldImeasB + AnalogValue/BASE_CURRENT)/2;           
     p->OldImeasB = p->ImeasB;

     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT2;                           
	 DigitValue=DigitValue<<11;                                         
     AnalogValue=DigitValue * 3 / 4095;                                
     AnalogValue=_IQmpy((AnalogValue - p->ImeasCOffset), p->ImeasCGain);  
     p->RealImeasC=(Sint16)(AnalogValue>>15);                          
	 p->ImeasC=(p->OldImeasC + AnalogValue/BASE_CURRENT)/2;         
     p->OldImeasC = p->ImeasC;
	 
     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT3;                             
	 DigitValue=DigitValue<<11;                                         
     AnalogValue=DigitValue * 3 / 4095;                                 
     AnalogValue=_IQmpy(AnalogValue , p->VdcMeasGain)+p->VdcMeasOffset ;   
     p->RealVdcMeas=(Uint16)(AnalogValue>>15);                         
	 p->VdcMeas=(p->OldVdcMeas + AnalogValue/BASE_VOLTAGE)/2;            
     p->OldVdcMeas = p->VdcMeas;

}      

/*=====================================================================================*/

void Ileg3_correct1(ILEG3CORRECT1 *p)
{
   _iq Temp_AOffset=0, Temp_BOffset=0,Temp_COffset=0;          
   Uint16 i;

   for(i=0;i<=9;i++)
      {
        ADC_START;
	    Delay_msec(1);

        Temp_AOffset=(Uint32)AdcCtrRegs.ADCRESULT0;                           
	    Temp_AOffset=Temp_AOffset<<11;                                         
		p->ImeasAOffset += Temp_AOffset;                                   

        Temp_BOffset=(Uint32)AdcCtrRegs.ADCRESULT1;                           
	    Temp_BOffset=Temp_BOffset<<11;                                        
		p->ImeasBOffset += Temp_BOffset;                                    

        Temp_COffset=(Uint32)AdcCtrRegs.ADCRESULT2;                            
	    Temp_COffset=Temp_COffset<<11;                                         
		p->ImeasCOffset += Temp_COffset;                                     

	  }

     p->ImeasAOffset = (p->ImeasAOffset)/10;                                   
     p->ImeasAOffset=p->ImeasAOffset * 3 / 4095;              
     p->ImeasBOffset = (p->ImeasBOffset)/10;                                  
     p->ImeasBOffset=p->ImeasBOffset * 3 / 4095;             
     p->ImeasCOffset = (p->ImeasCOffset)/10;                                  
     p->ImeasCOffset=p->ImeasCOffset * 3 / 4095;             
}    
/*=====================================================================================*/

void speed_meas1_cap_calc(SPEED_MEAS1_CAP *v)
{
  Uint32 DeltCount=0,Speed_tmp=0;

  v->OldCount = v->NewCount;
  v->NewCount = v->SpeedMeasCount;
  DeltCount =  v->NewCount - v->OldCount;
  Speed_tmp = ((Uint32)20000*ISR_FREQUENCY) / (DeltCount*SRM_ROTORS);   
  
  if(abs(Speed_tmp - v->SpeedRpm)<200)            
    {v->SpeedRpm = (v->SpeedRpm + Speed_tmp)/2;}    

  v->Speed = _IQ(v->SpeedRpm) / BASE_SPD  ; 
}
/*=====================================================================================*/

void pid_reg1_calc(PIDREG1 *v)
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

void ADC_read(ADC *p)
{
    p->Ref=(Uint32)AdcCtrRegs.ADCRESULT7;           
	p->Ref=p->Ref<<11;                               
    p->Ref=p->Ref/4095;                             

	p->AngOn=(Uint32)AdcCtrRegs.ADCRESULT8;        
	p->AngOn=p->AngOn<<11;                           
    p->AngOn=p->AngOn/4095;                        

    p->AngOff=(Uint32)AdcCtrRegs.ADCRESULT9;       
	p->AngOff=p->AngOff<<11;                         
    p->AngOff=p->AngOff/4095;                        


}

/*=====================================================================================*/

