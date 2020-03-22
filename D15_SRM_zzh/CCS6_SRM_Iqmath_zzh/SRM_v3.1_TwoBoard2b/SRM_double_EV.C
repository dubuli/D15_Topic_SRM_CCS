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
//#include "SRM1_FUNC.C"
/* =================================================================================
File name:        SRM1_FUN.C  (IQ version)

Originator:	LH

Description:

=====================================================================================*/

void READ_KEY_calc(READ_KEY *v)
{
	v->KeyFwd =!GioDatRegs.GPFDAT.bit.GPIOF1;
	v->KeyRvs =!GioDatRegs.GPFDAT.bit.GPIOF2;
	v->KeyStop=!GioDatRegs.GPFDAT.bit.GPIOF3;

	if(v->KeyFwd==1)    {v->FlagTemp1=1;}else{v->FlagTemp1=0;}
	if(v->FlagTemp1==1) {v->RunState=FWD_STATE;ON_FWD;OFF_RVS;OFF_BLK;}

    if(v->KeyRvs==1)    {v->FlagTemp2=1;}else{v->FlagTemp2=0;}
	if(v->FlagTemp2==1) {v->RunState=RVS_STATE;OFF_FWD;ON_RVS;OFF_BLK;}

//    if(v->KeyStop==1)   {v->FlagTemp3=1;}else{v->FlagTemp3=0;}
//	if(v->FlagTemp3==1) {v->RunState=STOP_STATE;OFF_FWD;OFF_RVS;ON_BLK;}
}
/*====================================================================================*/

void STC1_calc(STC1 *v)
{
  extern Uint16 FLAG_CAP1,	FLAG_CAP2, FLAG_CAP3;
  extern SPEED_MEAS1_CAP spd_meas1;
  extern APC1 apc1;

  v->FlagStc=1;
  apc1.FlagApc=0;

//  if(v->RunState==FWD_STATE)
   if(1)
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

//               if((v->HallData2==1)&&(v->HallData3==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData2==0)&&(v->HallData1==1)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
//               if((v->HallData3==1)&&(v->HallData1==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}

//&			   if((v->HallData4==1)&&(v->HallData5==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
// &              if((v->HallData6==1)&&(v->HallData4==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
// &              if((v->HallData5==1)&&(v->HallData6==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}


               if(v->HallData4==1){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
              if(v->HallData5==1){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
               if(v->HallData6==1){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
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
               if     ((v->HallData1==0)&&(v->HallData3==1))
                      {v->FlagStartPhase1=0; v->FlagStartPhase2=1; v->FlagStartPhase3=0;}
               else if((v->HallData2==1)&&(v->HallData3==0))
                      {v->FlagStartPhase1=1; v->FlagStartPhase2=0; v->FlagStartPhase3=0;}
               else if((v->HallData1==1)&&(v->HallData2==0))
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

//if(v->RunState==FWD_STATE)
  if(1)
    {
      if(FLAG_CAP2)

        {
          v->AngPhase1 += v->AngStep;

          if     (v->AngPhase1 < v->AngOn)
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1;}
          else if((v->AngPhase1>=v->AngOn)&&(v->AngPhase1<v->AngOff))
                 {v->FlagRunPhase1=1; v->FlagStepCmutPhase1=0;}
          else if((v->AngPhase1>=v->AngOff)&&(v->AngPhase1<v->AngStepCmut))
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=0;}
	      else if(v->AngPhase1>=v->AngStepCmut)
	        	 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1; v->AngPhase1=0; FLAG_CAP2=0;}
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

      if(FLAG_CAP1)

        {
          v->AngPhase3 += v->AngStep;

          if     (v->AngPhase3 < v->AngOn)
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1;}
          else if((v->AngPhase3>=v->AngOn)&&(v->AngPhase3<v->AngOff))
                 {v->FlagRunPhase3=1; v->FlagStepCmutPhase3=0;}
          else if((v->AngPhase3>=v->AngOff)&&(v->AngPhase3<v->AngStepCmut))
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=0;}
	   	  else if(v->AngPhase3>=v->AngStepCmut)
		         {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1; v->AngPhase3=0; FLAG_CAP1=0;}
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
/*  else if(v->RunState==STOP_STATE)
    {
      v->FlagApc=0;
      v->FlagRunPhase1=0;
      v->FlagRunPhase2=0;
      v->FlagRunPhase3=0;
	  v->FlagStepCmutPhase1=0;
	  v->FlagStepCmutPhase2=0;
	  v->FlagStepCmutPhase3=0;

	}
*/
}


/*=====================================================================================*/

void CCC1_calc(CCC1 *v)
{

    if     (v->FdbPhase1 > v->Imax)
           {
//           v->Da=_IQ(0.0);
 			 Systemstate=1;
           }
    else if(v->FdbPhase1 > v->Ref ){v->Da=_IQ(0.0);}
    else   {v->Da=_IQ(1);}

    if     (v->FdbPhase2 > v->Imax)
           {
//             v->Db=_IQ(0.0);
			  Systemstate=1;
           }
    else if(v->FdbPhase2 > v->Ref ){v->Db=_IQ(0.0);}
    else   {v->Db=_IQ(1);}

    if     (v->FdbPhase3 > v->Imax)
           {
//           v->Dc=_IQ(0.0);
			 Systemstate=1;
           }
    else if(v->FdbPhase3 > v->Ref ){v->Dc=_IQ(0.0);}
    else   {v->Dc=_IQ(1);}
}
/*=====================================================================================*/

void PWMGEN1_calc(PWMGEN1 *v)
{
  extern SPEED_MEAS1_CAP spd_meas1;
  extern Uint32 Prechargecount;
//  int ugg2;
/*   if(spd_meas1.Speed==0)
		    {
		     GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ;
			 GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ;
             GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ;
		    }
*/
// if(Prechargecount<20)
//  {
//      if(spd_meas1.Speed<20)
//		 {
//		   GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ;
//		   GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ;
//           GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ;
//		 }
//   }
//   else if(Prechargecount>30)
//   {

//	 Prechargecount=0;

//   }

if((v->FlagStc==1)&&(v->FlagApc==0))
    {

        if(v->FlagStartPhase1==1)
            {
             GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ;
//			if(spd_meas1.Speed<20)
//			for(ugg2=0;ugg2<50;ugg2++);
             EvaCtrRegs.CMPR1 = (Uint16)(((v->Da)*PERD_TMR1)>>15) ;

            }
	      else
		    {
		     EvaCtrRegs.CMPR1 = 0x0000 ;
			  if(spd_meas1.Speed<20)
			 {

			  GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE;
			 }
              else
			 {
              GioDatRegs.GPADAT.bit.GPIOA1 = INACTIVE ;
             }

           }
        if(v->FlagStartPhase2==1)
            {
             GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ;
//            if(spd_meas1.Speed<20)
//			for(ugg2=0;ugg2<50;ugg2++);
             EvaCtrRegs.CMPR2 = (Uint16)(((v->Db)*PERD_TMR1)>>15) ;

            }
	      else
		    {
		     EvaCtrRegs.CMPR2 = 0x0000 ;

			  if(spd_meas1.Speed<20)
			 {
			  GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE;
			 }
              else
			 {
              GioDatRegs.GPADAT.bit.GPIOA3 = INACTIVE ;
             }

            }
        if(v->FlagStartPhase3==1)
            {
             GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ;
//            if(spd_meas1.Speed<20)
//			for(ugg2=0;ugg2<50;ugg2++);
             EvaCtrRegs.CMPR3 = (Uint16)(((v->Dc)*PERD_TMR1)>>15) ;

            }
	      else
		    {
		     EvaCtrRegs.CMPR3 = 0x0000 ;
             if(spd_meas1.Speed<20)
			 {
			  GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE;
			 }
              else
			 {
              GioDatRegs.GPADAT.bit.GPIOA5 = INACTIVE ;
             }


	       }
  }

  if((v->FlagStc==0)&&(v->FlagApc==1))
	{
        if(v->FlagRunPhase1==1)
            {
             EvaCtrRegs.CMPR1 = (Uint16)(((v->Da)*PERD_TMR1)>>15) ;
             GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ;
            }
	      else
		    {
		     EvaCtrRegs.CMPR1 = 0x0000 ;
			 if(v->FlagStepCmutPhase1==0){GioDatRegs.GPADAT.bit.GPIOA1 = ACTIVE ;}
		      else{GioDatRegs.GPADAT.bit.GPIOA1 = INACTIVE ;}
            }

        if(v->FlagRunPhase2==1)
            {
             EvaCtrRegs.CMPR2 = (Uint16)(((v->Db)*PERD_TMR1)>>15) ;
	         GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ;
            }
	      else
		    {
		     EvaCtrRegs.CMPR2 = 0x0000 ;
			 if(v->FlagStepCmutPhase2==0){GioDatRegs.GPADAT.bit.GPIOA3 = ACTIVE ;}
		      else{GioDatRegs.GPADAT.bit.GPIOA3 = INACTIVE ;}
            }

        if(v->FlagRunPhase3==1)
            {
             EvaCtrRegs.CMPR3 = (Uint16)(((v->Dc)*PERD_TMR1)>>15) ;  //Q15 to Q0 ;;
             GioDatRegs.GPADAT.bit.GPIOA5 = ACTIVE ;
	        }
	      else
		    {
		     EvaCtrRegs.CMPR3 = 0x0000 ;
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
     AnalogValue=DigitValue * 3/ 4095;
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
     AnalogValue=DigitValue * 3 /4095;
     AnalogValue=_IQmpy((AnalogValue - p->ImeasCOffset), p->ImeasCGain);
     p->RealImeasC=(Sint16)(AnalogValue>>15);
	 p->ImeasC=(p->OldImeasC + AnalogValue/BASE_CURRENT)/2;
     p->OldImeasC = p->ImeasC;

     DigitValue=(Uint32)AdcCtrRegs.ADCRESULT3;
	 DigitValue=DigitValue<<11;
     AnalogValue=DigitValue * 3 /4095;
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
     p->ImeasBOffset=p->ImeasBOffset* 3 / 4095;
     p->ImeasCOffset = (p->ImeasCOffset)/10;
     p->ImeasCOffset=p->ImeasCOffset* 3 / 4095;
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
	p->Ref=p->Ref/3;
//    p->ACCref=(Uint32)(p->Ref>>15);


	p->AngOn=(Uint32)AdcCtrRegs.ADCRESULT8;
	p->AngOn=p->AngOn<<11;
    p->AngOn=p->AngOn/4095;

    p->AngOff=(Uint32)AdcCtrRegs.ADCRESULT9;
	p->AngOff=p->AngOff<<11;
    p->AngOff=p->AngOff/4095;


}

/*=====================================================================================*/

/*
void differ_cal(DIFFER *p)
{
  p->Accref=ADC.Ref/(4095*3);

  //p->angle_sign_iq=iq(angle_sign);
 // p->angle_sign_iq=p->angle_sign_iq/720;

  p->angle_real_iq=iq(angle_real);
  p->angle_real_iq=p->angle_real_iq/720;

  if(angle_sign==1)
  {
  p->duty=p->Accref+p->angle_real_iq;
  if(p->duty>_iq(1)) p->duty=_iq(1);

  }
  else
  {
  p->duty=p->Accref-p->angle_real_iq;
  if(p->duty<_iq(0)) p->duty=_iq(0);
  }


}
*/

/*=====================================================================================*/

#include "SRM2.h"
//#include "SRM2_FUNC.C"


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

//  if(v->RunState==FWD_STATE)
if(1)
    {
      if(spd_meas2.SpeedRpm<SPD_BORDER)
        {
          v->HallData1=GioDatRegs.GPBDAT.bit.GPIOB8;
          v->HallData2=GioDatRegs.GPBDAT.bit.GPIOB9;
          v->HallData3=GioDatRegs.GPBDAT.bit.GPIOB10;
          v->HallData4=GioDatRegs.GPDDAT.bit.GPIOD6;
          v->HallData5=GioDatRegs.GPEDAT.bit.GPIOE0;
          v->HallData6=GioDatRegs.GPEDAT.bit.GPIOE1;


	       if(spd_meas2.SpeedRpm<160)
	         {

               if(v->HallData4==1){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
               if(v->HallData5==1){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}
              if(v->HallData6==1){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//               if((v->HallData5==1)&&(v->HallData4==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}

//&               if((v->HallData4==1)&&(v->HallData5==0)){v->FlagStartPhase2=1;} else{v->FlagStartPhase2=0;}
//&               if((v->HallData6==1)&&(v->HallData4==0)){v->FlagStartPhase1=1;} else{v->FlagStartPhase1=0;}
//&               if((v->HallData5==1)&&(v->HallData6==0)){v->FlagStartPhase3=1;} else{v->FlagStartPhase3=0;}


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
//  else if(v->RunState==REG_STATE)
//    {

//	}
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

//  if(v->RunState==FWD_STATE)
    if(1)
    {
      if(FLAG_CAP4)
        {
          v->AngPhase1 += v->AngStep;

          if     (v->AngPhase1 < v->AngOn)
                 {v->FlagRunPhase1=0; v->FlagStepCmutPhase1=1;}
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
                 {v->FlagRunPhase2=0; v->FlagStepCmutPhase2=1;}
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
                 {v->FlagRunPhase3=0; v->FlagStepCmutPhase3=1;}
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

    if     (v->FdbPhase1 > v->Imax)
       {
        v->Du=_IQ(0.0);
	       Systemstate=1;
       }
    else if(v->FdbPhase1 > v->Ref ){v->Du=_IQ(0.0);}
    else   {v->Du=_IQ(1.0);}

    if     (v->FdbPhase2 > v->Imax)
       {
         v->Dv=_IQ(0.0);
	       Systemstate=1;
       }
    else if(v->FdbPhase2 > v->Ref ){v->Dv=_IQ(0.0);}
    else   {v->Dv=_IQ(1.0);}

    if     (v->FdbPhase3 > v->Imax)
       {
         v->Dw=_IQ(0.0);
	       Systemstate=1;
       }
    else if(v->FdbPhase3 > v->Ref ){v->Dw=_IQ(0.0);}
    else   {v->Dw=_IQ(1.0);}
}
/*=====================================================================================*/

void PWMGEN2_calc(PWMGEN2 *v)
{
  extern SPEED_MEAS2_CAP spd_meas2;
  extern Uint32 Prechargecount;
 int ugg1;
 /* if(Prechargecount<20)
  {
      if(spd_meas2.Speed==0)
		 {
		   GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ;
		   GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ;
           GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ;
		 }
	}

   else if(Prechargecount>30)
   {

		   Prechargecount=0;

   }

  if((v->FlagStc==1)&&(v->FlagApc==0))
    {

        if(v->FlagStartPhase1==1)
            {
             EvbCtrRegs.CMPR4 = (Uint16)(((v->Du)*PERD_TMR3)>>15) ;
             GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ;
            }
	      else
		    {
		     EvbCtrRegs.CMPR4 = 0x0000 ;
             GioDatRegs.GPBDAT.bit.GPIOB1 = INACTIVE ;
            }
        if(v->FlagStartPhase2==1)
            {
             EvbCtrRegs.CMPR5 = (Uint16)(((v->Dv)*PERD_TMR3)>>15) ;    //Q15 to Q0
             GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ;
            }
	      else
		    {
		     EvbCtrRegs.CMPR5 = 0x0000 ;
             GioDatRegs.GPBDAT.bit.GPIOB3 = INACTIVE ;
            }
        if(v->FlagStartPhase3==1)
            {
             EvbCtrRegs.CMPR6 = (Uint16)(((v->Dw)*PERD_TMR3)>>15) ;   //Q15 to Q0 ;
             GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ;
            }
	      else
		    {
		     EvbCtrRegs.CMPR6 = 0x0000 ;
             GioDatRegs.GPBDAT.bit.GPIOB5 = INACTIVE ;
            }
    }
	*/
	if((v->FlagStc==1)&&(v->FlagApc==0))

    {



        if(v->FlagStartPhase1==1)
            {

			 GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ;
			 	if(spd_meas2.Speed<20)
			{for(ugg1=0;ugg1<200;ugg1++);};
             EvbCtrRegs.CMPR4 = (Uint16)(((v->Du)*PERD_TMR3)>>15) ;

            }
	      else
		    {
		     EvbCtrRegs.CMPR4 = 0x0000 ;
			 if(spd_meas2.Speed<20)
			 {
			  GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE;
			 }
              else
			 {
              GioDatRegs.GPBDAT.bit.GPIOB1 = INACTIVE ;
             }
			}
        if(v->FlagStartPhase2==1)
            {
			 GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ;
          	if(spd_meas2.Speed<20)
			{for(ugg1=0;ugg1<200;ugg1++);};
             EvbCtrRegs.CMPR5 = (Uint16)(((v->Dv)*PERD_TMR3)>>15) ;

            }
	      else
		    {
		     EvbCtrRegs.CMPR5 = 0x0000 ;
             if(spd_meas2.Speed<20)
			 {
			  GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE;
			 }
              else
			 {
              GioDatRegs.GPBDAT.bit.GPIOB3 = INACTIVE ;
             }

            }
        if(v->FlagStartPhase3==1)
            {
			 GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ;
            	if(spd_meas2.Speed<20)
			{for(ugg1=0;ugg1<200;ugg1++);};
             EvbCtrRegs.CMPR6 = (Uint16)(((v->Dw)*PERD_TMR3)>>15) ;

            }
	      else
		    {
		     EvbCtrRegs.CMPR6 = 0x0000 ;
             if(spd_meas2.Speed<20)
			 {
			  GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE;
			 }
              else
			 {
              GioDatRegs.GPBDAT.bit.GPIOB5 = INACTIVE ;
             }
            }
   }

  else if((v->FlagStc==0)&&(v->FlagApc==1))
	{
        if(v->FlagRunPhase1==1)
            {
             EvbCtrRegs.CMPR4 = (Uint16)(((v->Du)*PERD_TMR3)>>15) ;
             GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ;
            }
	      else
		    {
		     EvbCtrRegs.CMPR4 = 0x0000 ;
			 if(v->FlagStepCmutPhase1==0){GioDatRegs.GPBDAT.bit.GPIOB1 = ACTIVE ;}
		      else{GioDatRegs.GPBDAT.bit.GPIOB1 = INACTIVE ;}
            }

        if(v->FlagRunPhase2==1)
            {
             EvbCtrRegs.CMPR5 = (Uint16)(((v->Dv)*PERD_TMR3)>>15) ;
	         GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ;
            }
	      else
		    {
		     EvbCtrRegs.CMPR5 = 0x0000 ;
			 if(v->FlagStepCmutPhase2==0){GioDatRegs.GPBDAT.bit.GPIOB3 = ACTIVE ;}
		      else{GioDatRegs.GPBDAT.bit.GPIOB3 = INACTIVE ;}
            }

        if(v->FlagRunPhase3==1)
            {
             EvbCtrRegs.CMPR6 = (Uint16)(((v->Dw)*PERD_TMR3)>>15) ;
             GioDatRegs.GPBDAT.bit.GPIOB5 = ACTIVE ;
	        }
	      else
		    {
		     EvbCtrRegs.CMPR6 = 0x0000 ;
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

	 DigitValue=(Uint32)AdcCtrRegs.ADCRESULT10;
	 DigitValue=DigitValue<<11;
     AnalogValue=DigitValue * 3 /4095;
     AnalogValue=_IQmpy(AnalogValue , p->VdcMeasGain)+p->VdcMeasOffset ;
     p->RealVdcMeas=(Uint16)(AnalogValue>>15);
	 p->VdcMeas=(p->OldVdcMeas + AnalogValue/BASE_VOLTAGE)/2;
     p->OldVdcMeas = p->VdcMeas;


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




//#include "SetPeripheral.C"
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

  AdcCtrRegs.ADCMAXCONV.all = 0x000A  ;	 //p297
  AdcCtrRegs.ADCTRL1.bit.SEQ_CASC = 1 ;  //p293 Cascaded mode,SEQ1 and SEQ2 = single 16-state
  AdcCtrRegs.ADCTRL1.bit.CONT_RUN = 1 ;  //p293 Cont. conv. mode

  AdcCtrRegs.ADCCHSELSEQ1.all = 0xFE76 ; //p300
  AdcCtrRegs.ADCCHSELSEQ2.all = 0x9345 ; //p300
  AdcCtrRegs.ADCCHSELSEQ3.all = 0xDDAB ; //p300
  AdcCtrRegs.ADCCHSELSEQ4.all = 0x00DD ; //p300
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
  GioMuxRegs.GPBDIR.all = 0x807F   ; //1=output,0=input pwm7-12, T3PWM，T4PWM，C6TRIP输出， 其它输入
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

  GioMuxRegs.GPFMUX.all = 0x00F0 ;   // F4、5、6、7使能  即SCIA,CAN使能，其它数字IO
  GioMuxRegs.GPFDIR.all = 0x7E51;	// DIR: 1=output,0=input,F0、5、8、9、10、14输出，其他输入

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

//  EvbCtrRegs.CAPCONB.all = 0x32A8  ; // P350 （0x3254上升沿,0x32A8下降沿）
  EvbCtrRegs.CAPCONB.all = 0x32A8  ;  // cap4,cap5下降沿，cap6上升沿
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





#define LEVEL1  1      	           
#define LEVEL2  2                     
#define LEVEL3  3                    
#define   BUILDLEVEL LEVEL2

int TT=-1;
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

_iq Left_du=0,Right_du=0,angle_du=0;
Uint32 fation1,fation2;     //方向盘速度调节


//Uint16 Angle_real,m,n;  //For SCI

Uint16 FLAG_HYS=0, FLAG_HYS2=0,FLAG_HYS3=0 ;
Uint32  Cnt_T1PINT_isr=0,Prechargecount=0;
interrupt void T1PINT_isr(void)
{
  Slice++ ;
  Cnt_T1PINT_isr++ ;                        
  spd_meas1.SpeedMeasCount++;             
  spd_meas2.SpeedMeasCount++; 
  Prechargecount++;  
 
  read_key1.read(&read_key1);             
  adc.read(&adc);                         

  ileg3_vdc1.read(&ileg3_vdc1);        
  ileg3_vdc2.read(&ileg3_vdc2);        
  ADC_START ; 

//  if((GioDatRegs.GPDDAT.bit.GPIOD0 ==0)||(GioDatRegs.GPDDAT.bit.GPIOD5 ==0))
//  if(0)
//       {TMP_ALAM=1;}  
//  else {TMP_ALAM=0;}
    
//  if(TMP_ALAM==1){FLAG_ALAM=1;ON_BUZZER;}

// if(FLAG_ALAM==0)

/*
if(Systemstate==1)
   {
     ON_BUZZER;
     GioDatRegs.GPADAT.bit.GPIOA1 = INACTIVE ;
     GioDatRegs.GPADAT.bit.GPIOA3 = INACTIVE ;
	 GioDatRegs.GPADAT.bit.GPIOA5 = INACTIVE ;
   }
*/
if(Systemstate==0)

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
        if(spd_meas1.SpeedRpm>=(SPD_BORDER-60)){FLAG_HYS=1;}      
        else{FLAG_HYS=0;}

        apc1.RunState=read_key1.RunState; 
           
    //	if(apc1.RunState==FWD_STATE)
      if(1)
		{
		  
		  if(spd_meas1.SpeedRpm<10)
	    	{
             apc1.AngOn = _IQ(0.4);               
             apc1.AngOff = _IQ(1.5);              
             apc1.AngStepCmut = _IQ(1.6);         
//             apc1.calc(&apc1);
		    }
		  else
		    {
             apc1.AngOn = _IQ(0.4);                
             apc1.AngOff = _IQ(1.5);              
             apc1.AngStepCmut = _IQ(1.6);         
//             apc1.calc(&apc1);

 		    }
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
	    if(spd_meas2.SpeedRpm>=(SPD_BORDER-30)){FLAG_HYS2=1;}      
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
        if(spd_meas1.SpeedRpm>=(SPD_BORDER-40)){FLAG_HYS=1;}     
        else{FLAG_HYS=0;}

        apc1.RunState=read_key1.RunState;     

/*		if(spd_meas1.SpeedRpm<10)
		{
         apc1.AngOn = _IQ(0.4);             
         apc1.AngOff = _IQ(1.3);              
         apc1.AngStepCmut = _IQ(1.4);         
         apc1.calc(&apc1);
		}
		else
*/
//		{

//if (angle_sign==0)
         apc1.AngOn = _IQ(0.0);                
         apc1.AngOff = _IQ(1.2);             
         apc1.AngStepCmut = _IQ(1.3);        
         apc1.calc(&apc1);
//		}

		pwm1.FlagStc=stc1.FlagStc;
		pwm1.FlagApc=apc1.FlagApc;
		pwm1.FlagRunPhase1=apc1.FlagRunPhase1;
		pwm1.FlagRunPhase2=apc1.FlagRunPhase2;
		pwm1.FlagRunPhase3=apc1.FlagRunPhase3;
        pwm1.FlagStepCmutPhase1=apc1.FlagStepCmutPhase1;
        pwm1.FlagStepCmutPhase2=apc1.FlagStepCmutPhase2;
        pwm1.FlagStepCmutPhase3=apc1.FlagStepCmutPhase3;

	}

  ccc1.Ref = _IQ(0.9);     
//  ccc1.Ref = _IQ(1.1);
  ccc1.FdbPhase1= ileg3_vdc1.ImeasA;         
  ccc1.FdbPhase2= ileg3_vdc1.ImeasB;      
  ccc1.FdbPhase3= ileg3_vdc1.ImeasC;          
  ccc1.calc(&ccc1);
 
  angle_du=_IQ(angle_real);
  if(angle_sign==1)
  {
    Left_du=adc.Ref-(angle_du/720);
    Right_du=adc.Ref+(angle_du/720);

    if(Left_du<0) {Left_du=_IQ(0.0);} 
    if(Right_du>_IQ(1.0)) {Right_du=_IQ(1.0);}
  }
  else
  {
    Left_du=adc.Ref+(angle_du/720);
    Right_du=adc.Ref-(angle_du/720);
 
    if(Right_du<0) {Right_du=_IQ(0.0);} 
    if(Left_du>_IQ(1.0)) {Left_du=_IQ(1.0);}
  }
 

//  pwm1.Da=Right_du;                           
//  pwm1.Db=Right_du;                          
//  pwm1.Dc=Right_du; 
if(spd_meas1.SpeedRpm<160)
  {
    pwm1.Da=ccc1.Da;                           
    pwm1.Db=ccc1.Db;                          
    pwm1.Dc=ccc1.Dc;                          
  
  }

else
{
    pwm1.Da=Right_du;                           
    pwm1.Db=Right_du;                          
    pwm1.Dc=Right_du; 
}
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
	    if(spd_meas2.SpeedRpm>=(SPD_BORDER-40)){FLAG_HYS2=1;}      
        else{FLAG_HYS2=0;}

          apc2.RunState=read_key1.RunState;    
          apc2.AngOn = _IQ(0.0);               
          apc2.AngOff = _IQ(1.0);             
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

 //    ccc2.Ref = adc.ACCref;
    
    
    
     ccc2.Ref = _IQ(1.0);                    
     ccc2.FdbPhase1= ileg3_vdc2.ImeasU;        
     ccc2.FdbPhase2= ileg3_vdc2.ImeasV;         
     ccc2.FdbPhase3= ileg3_vdc2.ImeasW;         
     ccc2.calc(&ccc2);

     
     if(spd_meas2.SpeedRpm<160)
    {
      pwm2.Du=ccc2.Du;                          
      pwm2.Dv=ccc2.Dv;                           
      pwm2.Dw=ccc2.Dw;
     }  
     else
     {
      pwm2.Du=Left_du;                          
      pwm2.Dv=Left_du;                           
      pwm2.Dw=Left_du; 
     }                        
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
     EvaCtrRegs.CMPR1 = 0x0000 ;
     EvaCtrRegs.CMPR2 = 0x0000 ;
     EvaCtrRegs.CMPR3 = 0x0000 ;
     EvbCtrRegs.CMPR4 = 0x0000 ;
     EvbCtrRegs.CMPR5 = 0x0000 ;
     EvbCtrRegs.CMPR6 = 0x0000 ;
	}
  DutyCycle1=(100*Left_du)>>15  ;     
  DutyCycle2=(100*Right_du)>>15  ;  

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

  Setup_GpioSet() ; //此函数旁诳罚蛭狹UX的改变会复位某些寄存器

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
//  START_CpuTmr0() ;  //用到定时器T0的其他寄存器初始化后，再启动T0

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
  
 //液晶初始化
  LCDPO_Init();	
  //LCDPO_SetColor(BLACK,RED); 
   //清屏
  LCDPO_Clears();

  Delay_msec(500);                                      
  
  ADC_START ;
  Delay_msec(10);


//================甲电机控制参数初始化====================

  ileg3_crc1.read(&ileg3_crc1);                         
  if(_IQabs(ileg3_crc1.ImeasAOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc1.ImeasAOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc1.ImeasBOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc1.ImeasBOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc1.ImeasCOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc1.ImeasCOffset=_IQ(0.594);}

// Initialize the ILEG3DCBUSMEAS module ADC
  ileg3_vdc1.ImeasAGain = _IQ(25.067);                    
  ileg3_vdc1.ImeasAOffset = ileg3_crc1.ImeasAOffset;     
  ileg3_vdc1.ImeasBGain = _IQ(25.067);                   
  ileg3_vdc1.ImeasBOffset = ileg3_crc1.ImeasBOffset;     
  ileg3_vdc1.ImeasCGain = _IQ(25.067);                     
  ileg3_vdc1.ImeasCOffset = ileg3_crc1.ImeasCOffset;    
 
  ileg3_vdc1.VdcMeasGain = _IQ(77.5757);                  
  ileg3_vdc1.VdcMeasOffset = _IQ(0);      
  
  ileg3_vdc2.VdcMeasGain = _IQ(77.5757);                  
  ileg3_vdc2.VdcMeasOffset = _IQ(0);                     

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

  ccc1.Imax=_IQ(1.5);                                    


  ileg3_crc2.read(&ileg3_crc2);                          
  if(_IQabs(ileg3_crc2.ImeasUOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc2.ImeasUOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc2.ImeasVOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc2.ImeasVOffset=_IQ(0.594);}
  if(_IQabs(ileg3_crc2.ImeasWOffset-_IQ(0.594))>_IQ(1))
    {ileg3_crc2.ImeasWOffset=_IQ(0.594);}

  ileg3_vdc2.ImeasUGain = _IQ(25.667);                   
  ileg3_vdc2.ImeasUOffset = ileg3_crc2.ImeasUOffset;    
  ileg3_vdc2.ImeasVGain = _IQ(25.667);                      
  ileg3_vdc2.ImeasVOffset = ileg3_crc2.ImeasVOffset;    
  ileg3_vdc2.ImeasWGain = _IQ(25.667);                    
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

  ccc2.Imax=_IQ(1.5);                                    


  EINT ;	// Enable Global interrupt INTM
  ERTM ;	// Enable Global realtime interrupt DBGM

  OFF_BUZZER;
  ON_RELAY1;

 // Delay_msec(800);
  
  ON_RELAY2;

  SET_EV1;          
  SET_EV2;       

  ADC_START ;
//  ileg3_vdc1.read(&ileg3_vdc1);  //进入TO中断之前冉幸淮缪沟缌鞑裳乐刮蠖�

  //Setxy_LcdPort(0,0)    ;
  //LCDPO_PutStr("Speed=")  ;
  //Setxy_LcdPort(0,0)    ;
  //LCDPO_PutStr("on =    off=")  ;

       LCDPO_SetColor(RED,BLUE);                 //红色字体，蓝色背景
       LCD_PutStr(0x55,180,40,"双轮独立驱动电动汽车试验平台") ;
       LCDPO_DispClock(300,550);                 //显示时钟
       LCD_PutStr(0x54,10,100,"甲电机参数显示") ;
       LCD_PutStr(0x54,400,100,"乙电机参数显示") ;
       LCDPO_SetColor(WHITE,BLUE);               //白色字体，蓝色背景
  
  while(1)
  {    

    if(FLAG_LCDS)
    {
//*************************************
// cmd:0x53 显示8*8点阵ASCII字符串
//     0x54 显示16*16点阵汉字串（GBK）
//	   0x55 显示32*32点阵汉字串（GB2312）
//	   0x6E 显示12*12点阵汉字串（GBK）
//     0x6F 显示24*24点阵汉字串（GB2312）
// y:横坐标
// x:纵坐标
//str:要显示的字符串
//*************************************

//================甲电机参数显示====================


       LCD_PutStr(0x54,10,150,"电机转速(r/min)：") ;
  	   LCDPO_PutDc2(spd_meas1.SpeedRpm,200,150);

       LCD_PutStr(0x54,10,180,"转速给定(r/min)") ;
  	   LCDPO_PutDc2((pid1_spd.Ref*BASE_SPD)>>15,200,180);
 
       LCD_PutStr(0x54,10,210,"电流给定(A)：") ;
  	   LCDPO_PutDc2((ccc1.Ref*BASE_CURRENT)>>15,200,210);
  
       LCD_PutStr(0x54,10,240,"积分输出(%)") ;
  	   LCDPO_PutDc2((pid1_spd.Ui*100)>>15,200,240);

	   LCD_PutStr(0x54,10,270,"A相占空比(%)：") ;
  	   LCDPO_PutDc2(DutyCycle1,200,270);
	
	   LCD_PutStr(0x54,10,300,"A相电流(A)：") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc1.RealImeasA),200,300);

	   LCD_PutStr(0x54,10,330,"B相电流(A)") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc1.RealImeasB),200,330);
	
	   LCD_PutStr(0x54,10,360,"C相电流(A)：") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc1.RealImeasC),200,360);
//       LCD_PutStr(0x54,10,420,"方向盘(A)：") ;
//	   LCDPO_PutDc2(angle_du,200,420);

	   LCD_PutStr(0x54,10,390,"占空比：") ;
 	   LCDPO_PutDc2(DutyCycle1,200,390);

	   LCD_PutStr(0x54,10,420,"母线电压(V)：") ;
  	   LCDPO_PutDc2(ileg3_vdc1.RealVdcMeas,200,420);
	 
//	   LCD_PutStr(0x54,10,480,"母线电压(V)：") ;
// 	   LCDPO_PutDc2(ileg3_vdc1.RealVdcMeas,200,480);

//	   LCD_PutStr(0x54,10,480,"左占空比：") ;
//  	   LCDPO_PutDc2(Left_du,200,480);


	   LCD_PutStr(0x54,10,450,"控制角度(0/1)：") ;
  	   LCDPO_PutDc2(angle_real,200,450);

	   LCD_PutStr(0x54,10,480,"运动方向(0/1)：") ;
  	   LCDPO_PutDc2(angle_sign,200,480);
//	   LCD_PutStr(0x54,10,520,"系统状态(0/1)：") ;
//  	   LCDPO_PutDc2(Systemstate,200,520);


//================乙电机参数显示====================
          
       LCD_PutStr(0x54,400,450,"ccc1.Ref(%)：") ;
  	   LCDPO_PutDc2((adc.AngOff*100)>>15,600,450);

//       LCD_PutStr(0x54,400,140,"adc.AngOn(%):") ;
//  	   LCDPO_PutDc2((adc.AngOn*100)>>15,600,140);
       LCD_PutStr(0x54,400,150,"电机转速(r/min)：") ;
  	   LCDPO_PutDc2(spd_meas2.SpeedRpm,600,150);

       LCD_PutStr(0x54,400,180,"转速给定(r/min)") ;
  	   LCDPO_PutDc2((pid2_spd.Ref*BASE_SPD)>>15,600,180);
 
       LCD_PutStr(0x54,400,210,"电流给定(U)：") ;
  	   LCDPO_PutDc2((ccc2.Ref*BASE_CURRENT)>>15,600,210);
  
       LCD_PutStr(0x54,400,240,"积分输出(%)") ;
  	   LCDPO_PutDc2((pid2_spd.Ui*100)>>15,600,240);

	   LCD_PutStr(0x54,400,270,"U相占空比(%)：") ;
  	   LCDPO_PutDc2(DutyCycle2,600,270);
	
	   LCD_PutStr(0x54,400,300,"U相电流(A)：") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc2.RealImeasU),600,300);

	   LCD_PutStr(0x54,400,330,"V相电流(A)") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc2.RealImeasV),600,330);
	
	   LCD_PutStr(0x54,400,360,"W相电流(A)：") ;
  	   LCDPO_PutDc2(abs(ileg3_vdc2.RealImeasW),600,360);

	   LCD_PutStr(0x54,400,390,"占空比%：") ;
  	   LCDPO_PutDc2(DutyCycle2,600,390);

	   LCD_PutStr(0x54,400,420,"母线电压(V)：") ;
  	   LCDPO_PutDc2(ileg3_vdc2.RealVdcMeas,600,420);

       FLAG_LCDS = 0            ;
    }
  }

} 	
