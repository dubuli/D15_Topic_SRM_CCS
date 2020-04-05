#include "DSP28_Device.h"


//---------------------------------------------------------------------------
// InitXIntrupt: 
//---------------------------------------------------------------------------
// This function initializes external interrupts to a known state.
//

void InitXIntrupt(void)
{

}	

//===========================================================================
// No more.
//===========================================================================





//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSpi(void)
{
	// Initialize SPI-A:

	//tbd...
	
}	
	
//===========================================================================
// No more.
//===========================================================================




//---------------------------------------------------------------------------
// InitSPI: 
//---------------------------------------------------------------------------
// This function initializes the SPI(s) to a known state.
//
void InitSci(void)
{
	// Initialize SCI-A:

	//tbd...
 	

	// Initialize SCI-B:

	//tbd...
}	
	
//===========================================================================
// No more.
//===========================================================================


//---------------------------------------------------------------------------
// InitMcbsp: 
//---------------------------------------------------------------------------
// This function initializes the McBSP to a known state.
//
void InitMcbsp(void)
{
 
	//tbd...
 
}	
	
//===========================================================================
// No more.
//===========================================================================





//---------------------------------------------------------------------------
// InitECan: 
//---------------------------------------------------------------------------
// This function initializes to a known state.
//
void InitECan(void)
{

}	

//===========================================================================
// No more.
//===========================================================================



//---------------------------------------------------------------------------
// InitPeripherals:
//---------------------------------------------------------------------------
// The following function initializes the peripherals to a default state.
// It calls each of the peripherals default initialization functions.
// This function should be executed at boot time or on a soft reset.
//
void InitPeripherals(void)
{

  
    // Initialize External Interface To default State:
	InitXintf();

	// Initialize CPU Timers To default State:
	InitCpuTimers();

	// Initialize McBSP Peripheral To default State:
	InitMcbsp();

	// Initialize Event Manager Peripheral To default State:
	InitEv();
	
    // Initialize ADC Peripheral To default State:
	InitAdc();
	
	// Initialize eCAN Peripheral To default State:
    InitECan();

	// Initialize SPI Peripherals To default State:
	InitSpi();

	// Initialize SCI Peripherals To default State:
	InitSci();
}

//===========================================================================
// No more.
//===========================================================================



