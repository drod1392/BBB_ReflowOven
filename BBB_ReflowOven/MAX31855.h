#pragma once
#include "GPIO.h"
#include <iostream>

using namespace exploringBB;

#define DATASIZE			32 //Bits
#define MASK_THERMO_BITS	0x3FFF // 14 bits
#define THERMO_SIGN_BIT		0x2000
#define MASK_JUNCTION_BITS	0x0FFF // 12 bits
#define JUNCTION_SIGN_BIT	0x0800

#define FAULT_BIT			0x10000 // D16
#define FAULT_OC_BIT		0x01	// D0
#define FAULT_SCG_BIT		0x02	// D1	
#define FAULT_SCV_BIT		0x04	// D2

namespace reflowOven {
	
	class MAX31855
	{
	private:
		GPIO* DataIn;
		GPIO* SCLK;
		GPIO* CS;

		int RawData;
		double ThermoTempC;
		double JunctionTempC;

		enum errorType {
			NONE,
			OC,
			SCG,
			SCV, 
			SPI
		};

		errorType readError;

		const double TempStepSize_Thermo = 0.25;
		const double TempStepSize_Junction = 0.0625;

		//int RawData;
		virtual void calculateThermoTemp();
		virtual void calculateJunctionTemp();
		virtual int checkFault();

	public:

		MAX31855(GPIO* DataIn, GPIO* SCLK, GPIO* CS);
		virtual int ReadTemp();
		virtual double getThermoTempC();
		virtual double getThermoTempF();
		virtual double getJunctionTempC();
		virtual double getJunctionTempF();
		virtual double convertCtoF(double tempC);
		virtual ~MAX31855();
	};

}
