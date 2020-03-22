/*=====================================================================================
File name:        SRM2.H  (IQ version)                                     
Originator:	LH
Description: 
Header file containing constants, data type definitions, and 
function prototypes for SRM CONTROL.
=====================================================================================*/

#ifndef __STC2_H__         
#define __STC2_H__
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
		  void  (*calc)();	  
	       } STC2;	            
typedef STC2 *STC2_handle;                  
#define STC2_DEFAULTS {0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
              		  (void (*)(Uint32))STC2_calc }
void STC2_calc(STC2_handle);
#endif // __STC2_H__
/*=====================================================================================*/

#ifndef __APC2_H__          
#define __APC2_H__
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
		  void  (*calc)();	  	
	       } APC2;	            
typedef APC2 *APC2_handle;                  
#define APC2_DEFAULTS {     0, _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), \
                           0, 0, 0, 0, 0, 0, 0, \
              		   (void (*)(Uint32))APC2_calc }
void APC2_calc(APC2_handle);
#endif // __APC2_H__
/*=====================================================================================*/

#ifndef __CCC2_H__          
#define __CCC2_H__
typedef struct {  
          _iq  Ref;   		         
		  _iq  Imax;   		        

		  _iq  FdbPhase1;			
		  _iq  FdbPhase2;			
		  _iq  FdbPhase3;			

          _iq  Du;                      
		  _iq  Dv;                      
		  _iq  Dw;                      
		  void  (*calc)();	  
	       } CCC2;	            
typedef CCC2 *CCC2_handle;                  
#define CCC2_DEFAULTS { _IQ(0), _IQ(6.5), _IQ(0), _IQ(0), _IQ(0), 0, 0, 0, \
              		   (void (*)(Uint32))CCC2_calc }
void CCC2_calc(CCC2_handle);
#endif // __CCC2_H__
/*=====================================================================================*/

#ifndef __PWMGEN2_H__        
#define __PWMGEN2_H__
typedef struct {  
          _iq  Du;                     
		  _iq  Dv;                     
		  _iq  Dw;                      

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

		  void  (*calc)();	                  
	       } PWMGEN2;	            
typedef PWMGEN2 *PWMGEN2_handle;                  
#define PWMGEN2_DEFAULTS {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
              		  (void (*)(Uint32))PWMGEN2_calc }
void PWMGEN2_calc(PWMGEN2_handle);
#endif // __PWMGEN2_H__
/*=====================================================================================*/


#ifndef __ILEG_VDC2_H__
#define __ILEG_VDC2_H__
typedef struct { _iq ImeasUGain;    
                 _iq ImeasUOffset;    
                 _iq ImeasU;        
				 _iq OldImeasU;      
                 Sint16 RealImeasU;    

                 _iq ImeasVGain;   
                 _iq ImeasVOffset;  
                 _iq ImeasV;       
				 _iq OldImeasV;     
                 Sint16 RealImeasV;   

                 _iq ImeasWGain;    
                 _iq ImeasWOffset;   
                 _iq ImeasW;         
				 _iq OldImeasW;     
                 Sint16 RealImeasW;  
                 
                 _iq VdcMeasGain;   
                 _iq VdcMeasOffset;  
                 _iq VdcMeas;        
				 _iq OldVdcMeas;      
                 Uint16 RealVdcMeas;    

                 void (*read)();     
               } ILEG3DCBUSMEAS2;


typedef ILEG3DCBUSMEAS2 *ILEG3DCBUSMEAS2_handle;
#define ILEG3DCBUSMEAS2_DEFAULTS { _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,             \
                                  _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,            \
                                  _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,             \
								   _IQ(0.0),_IQ(0.0),_IQ(0.0),_IQ(0.0),0,          \
                                 (void (*)(Uint32))Ileg3_dcbus_read2                \
                                }
void Ileg3_dcbus_read2(ILEG3DCBUSMEAS2_handle);

#endif // __ILEG_VDC_H__

/*=====================================================================================*/

#ifndef __ILEG_CRC2_H__
#define __ILEG_CRC2_H__
typedef struct { 
                 _iq ImeasUOffset;  
                 _iq ImeasVOffset;   
                 _iq ImeasWOffset;   

                 void (*read)();       
               } ILEG3CORRECT2;

typedef ILEG3CORRECT2 *ILEG3CORRECT2_handle;
#define ILEG3CORRECT2_DEFAULTS { _IQ(0),_IQ(0),_IQ(0),           \
                                 (void (*)(Uint32))Ileg3_correct2      \
                              }
void Ileg3_correct2(ILEG3CORRECT2_handle);

#endif // __ILEG_CRC2_H__
/*=====================================================================================*/

#ifndef __SPEED_MEAS2_CAP_H__
#define __SPEED_MEAS2_CAP_H__

typedef struct {
       Uint32 OldCount;              	
       Uint32 NewCount;               
       Uint32 SpeedMeasCount;       

       _iq    Speed;     	     	
       Uint32 SpeedRpm;             
       void (*calc)();  	     	
       } SPEED_MEAS2_CAP;           	
typedef SPEED_MEAS2_CAP *SPEED_MEAS2_CAP_handle;
                  
#define SPEED_MEAS2_CAP_DEFAULTS   { 0,  0,  0, _IQ(0),  0, \
                                         (void (*)(Uint32))speed_meas2_cap_calc }

void speed_meas2_cap_calc(SPEED_MEAS2_CAP_handle); 
#endif  // __SPEED_MEAS2_H__
/*=====================================================================================*/

#ifndef __PIDREG2_H__        
#define __PIDREG2_H__
typedef struct {  
          _iq  Ref;   		
		  _iq  Fdb;   			
		  _iq  Err;			

		  _iq  Kp;				
		  _iq  Ki;			    
		  _iq  Up;				
		  _iq  Ui;				
		  _iq  Out;   		
		  _iq  OutMax;		  
		  _iq  OutMin;	    
          _iq  UiMax;                 
          _iq  UiMin;                   
          _iq  Err_Border ;              

          Uint16  ILoopCount;            
          Uint16  IPrescale;             
		  void  (*calc)();	  
	       } PIDREG2;	            
typedef PIDREG2 *PIDREG2_handle;                  
#define PIDREG2_DEFAULTS { 0, 0, 0,  _IQ(0), _IQ(0), 0, 0, 0, \
                           _IQ(0), _IQ(0), _IQ(0), _IQ(0), _IQ(0), 0, 0, \
              		       (void (*)(Uint32))pid_reg2_calc }
void pid_reg2_calc(PIDREG2_handle);
#endif // __PIDREG2_H__
/*=====================================================================================*/ 

