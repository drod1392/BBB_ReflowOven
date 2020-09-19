#include "MAX31855.h"

using namespace exploringBB;
using namespace std;

namespace reflowOven {

	MAX31855::MAX31855(GPIO* dataIn, GPIO* sclk, GPIO* cs) {
		DataIn = dataIn;
		SCLK = sclk;
		CS = cs;

		DataIn->setDirection(INPUT);

		SCLK->setDirection(OUTPUT);
		SCLK->setValue(LOW);

		CS->setDirection(OUTPUT);
		CS->setValue(HIGH);
	}

	int MAX31855::ReadTemp() {
		RawData = 0;
		
		CS->setValue(LOW);
		for (int i = 0; i < DATASIZE; i++) {
			RawData <<= 1;
			SCLK->toggleOutput();
			RawData |= DataIn->getValue();
		}
		CS->setValue(HIGH);

		if (checkFault() < 0) {
			/*cout << "Read Error: ";
			if(readError == errorType::OC)
				cout << "OPEN CIRCUIT Fault" << endl;
			if (readError == errorType::SCG)
				cout << "SHORT TO GND Fault" << endl;
			if (readError == errorType::SCV)
				cout << "SHORT TO VCC Fault" << endl;*/
			calculateJunctionTemp();
			return -1;

		}

		calculateThermoTemp();
		calculateJunctionTemp();
		return 0;
	}

	void MAX31855::calculateJunctionTemp() {
		/****************
		input: (int) value = 12 bits (D15-D4)
		Ouput: (float) tempValue = Converted temp in Celcius
		
			**** Test Values from Datasheet ****
			value = 0b011111110000 (0x07F0)   #  127.0000C
			value = 0b011001001001 (0x0649)   #  100.5625C 
			value = 0b000110010000 (0x0190)   #   25.0000C
			value = 0b000000000000 (0x0000)   #    0.0000C
			value = 0b111111111111 (0x0FFF)   #   -0.0625C
			value = 0b111111110000 (0x0FF0)   #   -1.0000C
			value = 0b111011000000 (0x0EC0)   #  -20.0000C
			value = 0b110010010000 (0x0C90)   #  -55.0000C
		*/

		signed int value = RawData >> 4;

		value &= MASK_JUNCTION_BITS;

		if (value & JUNCTION_SIGN_BIT) {
			value = (~value + 1);
			value &= 0x0FFF;
			value *= -1;
		}
		JunctionTempC = value * TempStepSize_Junction;
	}

	void MAX31855::calculateThermoTemp() {
		/****************** 
		input: (int)value = 14 bits(D31 - D18)
		Ouput : (float)tempValue = Converted temp in Celcius

			**** Test Values from Datasheet ****
			value = 0b01100100000000 (0x1900)	#  1600.00C
			value = 0b00111110100000 (0x0FA0)	#  1000.00C
			value = 0b00000110010011 (0x0193)	#   100.75C
			value = 0b00000001100100 (0x0064)	#    25.00C
			value = 0b00000000000000 (0x0000)	#     0.00C
			value = 0b11111111111111 (0x3FFF)	#     - 0.25C
			value = 0b11111111111100 (0x3FFC)	#     - 1.00C
			value = 0b11110000011000 (0x3C18)	#   - 250.00C
		*/

		signed int value = RawData >> 18;

		value &= MASK_THERMO_BITS;

		if (value & THERMO_SIGN_BIT) {
			value = (~value + 1);
			value &= 0x2FFF;
			value *= -1;
		}

		ThermoTempC = value * TempStepSize_Thermo;
	}

	double MAX31855::getJunctionTempC() {
		return JunctionTempC;
	}

	double MAX31855::getJunctionTempF() {
		return convertCtoF(JunctionTempC);
	}

	double MAX31855::getThermoTempC() {
		return ThermoTempC;
	}

	double MAX31855::getThermoTempF() {
		return convertCtoF(ThermoTempC);
	}

	double MAX31855::convertCtoF(double tempC) {
		return ((tempC * 1.8) + 32);
	}

	int MAX31855::checkFault() {
		if (!(RawData & FAULT_BIT)) {
			readError = errorType::NONE;
			return 0;
		}

		if (RawData = 0xFFFFFFFF) {
			readError = errorType::SPI;
			return -1;
		}

		if (RawData & FAULT_OC_BIT)
			readError = errorType::OC;

		if (RawData & FAULT_SCG_BIT)
			readError = errorType::SCG;

		if (RawData & FAULT_SCV_BIT)
			readError = errorType::SCV;

		return -1;
	}

	MAX31855::~MAX31855() {

	}





}
