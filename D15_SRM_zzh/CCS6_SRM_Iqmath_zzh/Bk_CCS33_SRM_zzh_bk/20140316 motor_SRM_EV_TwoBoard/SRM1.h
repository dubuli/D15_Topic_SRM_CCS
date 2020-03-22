/*=====================================================================================
File name:        SRM1.H  (IQ version)                                     
Originator:	LH
Description: 
Header file containing constants, data type definitions, and 
function prototypes for SRM CONTROL.
=====================================================================================*/
#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES

typedef char             Sint08  ;
typedef int              Sint16  ;
typedef long             Sint32  ;
typedef unsigned char    Uint08  ;
typedef unsigned int     Uint16  ;
typedef unsigned long    Uint32  ;
typedef float            float32 ;
typedef long double      float64 ;
#endif //DSP28_DATA_TYPES
/*=====================================================================================*/

#ifndef __PARAMETER_H__
#define __PARAMETER_H__
#define PI 3.14159265358979
#define ISR_FREQUENCY  10       

#define  SRM_ROTORS        16   
#define  SRM_STATOR        12  
#define  ENC_PULSES       2000  

#define BASE_VOLTAGE    100       
#define BASE_CURRENT    40       
#define BASE_SPD      	1000        
#define BASE_ANG        7.5      

#define SPD_BORDER      400      

#define FWD_STATE       1111         
#define RVS_STATE       2222         
#define STOP_STATE      3333         
#define REG_STATE       4444         

#define SET_EV1   GioDatRegs.GPASET.bit.GPIOA6=1         
#define	RST_EV1	  GioDatRegs.GPACLEAR.bit.GPIOA6=1       
#define SET_EV2   GioDatRegs.GPBSET.bit.GPIOB7=1          
#define	RST_EV2	  GioDatRegs.GPBCLEAR.bit.GPIOB7=1       
#define ACTIVE    0                                       
#define INACTIVE  1                                      

#define ADC_START		  AdcCtrRegs.ADCTRL2.bit.SOC_SEQ1 = 1
#define ADC_BUSYS		  AdcCtrRegs.ADCST.bit.SEQ1_BSY

#define	ON_LED	GioDatRegs.GPFCLEAR.bit.GPIOF14=1
#define	OFF_LED	GioDatRegs.GPFSET.bit.GPIOF14=1
#define	T_LED	GioDatRegs.GPFTOGGLE.bit.GPIOF14=1

#define	ON_FWD	GioDatRegs.GPFCLEAR.bit.GPIOF8=1
#define	OFF_FWD	GioDatRegs.GPFSET.bit.GPIOF8=1
#define	T_FWD	GioDatRegs.GPFTOGGLE.bit.GPIOF8=1

#define	ON_RVS	GioDatRegs.GPFCLEAR.bit.GPIOF9=1
#define	OFF_RVS	GioDatRegs.GPFSET.bit.GPIOF9=1
#define	T_RVS	GioDatRegs.GPFTOGGLE.bit.GPIOF9=1

#define	ON_BLK	GioDatRegs.GPFCLEAR.bit.GPIOF10=1
#define	OFF_BLK	GioDatRegs.GPFSET.bit.GPIOF10=1
#define	T_BLK	GioDatRegs.GPFTOGGLE.bit.GPIOF10=1

#define	ON_BUZZER	GioDatRegs.GPFSET.bit.GPIOF0=1
#define	OFF_BUZZER	GioDatRegs.GPFCLEAR.bit.GPIOF0=1

#define ON_RELAY1   GioDatRegs.GPFCLEAR.bit.GPIOF5=1
#define	OFF_RELAY1	GioDatRegs.GPFSET.bit.GPIOF5=1
#define ON_RELAY2   GioDatRegs.GPBCLEAR.bit.GPIOB15=1
#define	OFF_RELAY2	GioDatRegs.GPBSET.bit.GPIOB15=1

#endif  //__PARAMETER_H__

/*=====================================================================================*/

#ifndef __READ_KEY_H__              
#define __READ_KEY_H__
typedef struct {  
          Uint16  RunState;         

          Uint16  KeyFwd;            
          Uint16  KeyRvs;            
          Uint16  KeyStop;           

		  Uint16  FlagTemp1;		
		  Uint16  FlagTemp2;	     
		  Uint16  FlagTemp3;		 

		  void  (*read)();	  	// Pointer to calculation function
	       } READ_KEY;	            
typedef READ_KEY *READ_KEY_handle;                  
#define READ_KEY_DEFAULTS {0,0,0,0,0,0,0, \
              		      (void (*)(Uint32))READ_KEY_calc }
void READ_KEY_calc(READ_KEY_handle);
#endif // __KEY_READ_H__
/*=====================================================================================*/

#ifndef __STC1_H__         
#define __STC1_H__
typedef struct {  
          Uint16  RunState;             

          Uint16  HallData1;           
          Uint16  HallData2;           
          Uint16  HallData3;           
          Uint16  HallData4;          
          Uint16  HallData5;          
          Uint16  HallData6;           

		  Uint16  FlagStartPhase1;			   
		  Uint16  FlagStartPhase2;			
		  Uint16  FlagStartPhase3;				

		  Uint16  FlagStc;                     
		  void  (*calc)();	  	// Pointer to calculation function
	       } STC1;	            
typedef STC1 *STC1_handle;                  
#define STC1_DEFAULTS {0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
              		  (void (*)(Uint32))STC1_calc }
void STC1_calc(STC1_handle);
#endif // __STC1_H__
/*=====================================================================================*/

#ifndef __APC1_H__          
#define __APC1_H__
typedef struct {  
          Uint16  RunState;            

          _iq  AngOn;   		
		  _iq  AngOff;   		
		  _iq  AngStepCmut;			

		  _iq  AngPhase1;			
		  _iq  AngPhase2;				
		  _iq  AngPhase3;			

          _iq  AngStep;                

		  Uint16  FlagRunPhase1;			   
		  Uint16  FlagRunPhase2;			 
		  Uint16  FlagRunPhase3;				 

		  Uint16  FlagStepCmutPhase1;   			 
		  Uint16  FlagStepCmutPhase2;   		
		  Uint16  FlagStepCmutPhase3;   		
		  Uint16  FlagApc;                         
		  void  (*calc)();	  	// Pointer to calculation function
	       } APC1;	            
typedef APC1 *APC1_handle;                  
#define APC1_DEFAULTS {     0, _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), \
                           0, 0, 0, 0, 0, 0, 0, \
              		   (void (*)(Uint32))APC1_calc }
void APC1_calc(APC1_handle);
#endif // __APC1_H__
/*=====================================================================================*/

#ifndef __CCC1_H__       
#define __CCC1_H__
typedef struct {  
          _iq  Ref;   		         
		  _iq  Imax;   		        	

		  _iq  FdbPhase1;			
		  _iq  FdbPhase2;			
		  _iq  FdbPhase3;			

          _iq  Da;                     
		  _iq  Db;                     
		  _iq  Dc;                     
		  void  (*calc)();	  	// Pointer to calculation function
	       } CCC1;	            
typedef CCC1 *CCC1_handle;                  
#define CCC1_DEFAULTS { _IQ(0), _IQ(0.5), _IQ(0), _IQ(0), _IQ(0), 0, 0, 0, \
              		   (void (*)(Uint32))CCC1_calc }
void CCC1_calc(CCC1_handle);
#endif // __CCC1_H__
/*=====================================================================================*/

#ifndef __PWMGEN1_H__         
#define __PWMGEN1_H__
typedef struct {  
          _iq  Da;                   
		  _iq  Db;                      
		  _iq  Dc;                     

		  Uint16  FlagStartPhase1;			   
		  Uint16  FlagStartPhase2;			
		  Uint16  FlagStartPhase3;			

		  Uint16  FlagRunPhase1;               
		  Uint16  FlagRunPhase2;			
		  Uint16  FlagRunPhase3;			

		  Uint16  FlagStepCmutPhase1;       
		  Uint16  FlagStepCmutPhase2;       
		  Uint16  FlagStepCmutPhase3;   	     

		  Uint16  FlagStc;                     
		  Uint16  FlagApc;                    

		  void  (*calc)();	                   	// Pointer to calculation function
	       } PWMGEN1;	            
typedef PWMGEN1 *PWMGEN1_handle;                  
#define PWMGEN1_DEFAULTS {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
              		  (void (*)(Uint32))PWMGEN1_calc }
void PWMGEN1_calc(PWMGEN1_handle);
#endif // __PWMGEN1_H__
/*=====================================================================================*/


#ifndef __ILEG_VDC1_H__
#define __ILEG_VDC1_H__
typedef struct { _iq ImeasAGain;     
                 _iq ImeasAOffset;  
                 _iq ImeasA;         
				 _iq OldImeasA;      
                 Sint16 RealImeasA;     

                 _iq ImeasBGain;     
                 _iq ImeasBOffset;   
                 _iq ImeasB;        
				 _iq OldImeasB;     
                 Sint16 RealImeasB;    

                 _iq ImeasCGain;    
                 _iq ImeasCOffset;   
                 _iq ImeasC;         
				 _iq OldImeasC;     
                 Sint16 RealImeasC;     

                 _iq VdcMeasGain;   
                 _iq VdcMeasOffset;  
                 _iq VdcMeas;        
				 _iq OldVdcMeas;      
                 Uint16 RealVdcMeas;    

                 void (*read)();      
               } ILEG3DCBUSMEAS1;


typedef ILEG3DCBUSMEAS1 *ILEG3DCBUSMEAS1_handle;
#define ILEG3DCBUSMEAS1_DEFAULTS { _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,             \
                                  _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,            \
                                  _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,             \
                                  _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,            \
                                 (void (*)(Uint32))Ileg3_dcbus_read1                \
                                }
void Ileg3_dcbus_read1(ILEG3DCBUSMEAS1_handle);

#endif // __ILEG_VDC1_H__

/*=====================================================================================*/

#ifndef __ILEG_CRC1_H__
#define __ILEG_CRC1_H__
typedef struct { 
                 _iq ImeasAOffset;   // Parameter: offset for Ia (Q15) 
                 _iq ImeasBOffset;   // Parameter: offset for Ib (Q15) 
                 _iq ImeasCOffset;   // Parameter: offset for Ic (Q15) 

                 void (*read)();       // Pointer to the read function 
               } ILEG3CORRECT1;

typedef ILEG3CORRECT1 *ILEG3CORRECT1_handle;
#define ILEG3CORRECT1_DEFAULTS { _IQ(0),_IQ(0),_IQ(0),           \
                                 (void (*)(Uint32))Ileg3_correct1      \
                              }
void Ileg3_correct1(ILEG3CORRECT1_handle);

#endif // __ILEG_CRC1_H__
/*=====================================================================================*/

#ifndef __SPEED_MEAS1_CAP_H__
#define __SPEED_MEAS1_CAP_H__

typedef struct {
       Uint32 OldCount;              
       Uint32 NewCount;                
       Uint32 SpeedMeasCount;      

       _iq    Speed;     	     
       Uint32 SpeedRpm;           
       void (*calc)();  	     
       } SPEED_MEAS1_CAP;           
typedef SPEED_MEAS1_CAP *SPEED_MEAS1_CAP_handle;
                  
#define SPEED_MEAS1_CAP_DEFAULTS   { 0,  0,  0, _IQ(0),  0, \
                                         (void (*)(Uint32))speed_meas1_cap_calc }

void speed_meas1_cap_calc(SPEED_MEAS1_CAP_handle); 
//extern SPEED_MEAS1_CAP spd_mesa1;
#endif  // __SPEED_MEAS1_H__
/*=====================================================================================*/

#ifndef __PIDREG1_H__         
#define __PIDREG1_H__
typedef struct {  
          _iq  Ref;   			// Input: Reference input 
		  _iq  Fdb;   			// Input: Feedback input 
		  _iq  Err;				// Variable: Error

		  _iq  Kp;				// Parameter: Proportional gain
		  _iq  Ki;			    // Parameter: Integral gain
		  _iq  Up;				// Variable: Proportional output 
		  _iq  Ui;				// Variable: Integral output 
		  _iq  Out;   			// Output: PID output 
		  _iq  OutMax;		    // Parameter: Maximum output 
		  _iq  OutMin;	    	// Parameter: Minimum output
          _iq  UiMax;                   // Parameter: Maximum Ui output
          _iq  UiMin;                   //Parameter: Minimum Ui output
          _iq  Err_Border ;             

          Uint16  ILoopCount;             
          Uint16  IPrescale;             
		  void  (*calc)();	  	// Pointer to calculation function
	       } PIDREG1;	            
typedef PIDREG1 *PIDREG1_handle;                  
#define PIDREG1_DEFAULTS { 0, 0, 0,  _IQ(0), _IQ(0), 0, 0, 0, \
                           _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), 0, 0, \
              		       (void (*)(Uint32))pid_reg1_calc }
void pid_reg1_calc(PIDREG1_handle);
#endif // __PIDREG3_H__
/*=====================================================================================*/ 

#ifndef __ADC_H__                 
#define __ADC_H__
typedef struct { _iq Ref;         

                 _iq AngOn;        
                 _iq AngOff;      
                 _iq AngStepCmut;   
                
                 void (*read)();       // Pointer to the read function 
               } ADC;

typedef ADC *ADC_handle;
#define ADC_DEFAULTS { _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),    \
                      (void (*)(Uint32))ADC_read                \
                     }
void ADC_read(ADC_handle);

#endif // __ADC_H__

/*=====================================================================================*/

