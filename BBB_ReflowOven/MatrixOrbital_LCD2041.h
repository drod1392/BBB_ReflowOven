#pragma once
#include <string>
#include <string.h>
#include "I2CDevice.h"

using namespace std;
using namespace exploringBB;


namespace reflowOven {

	class MatrixOrbital_LCD2041
	{
		I2CDevice* device;
	public:
		MatrixOrbital_LCD2041(I2CDevice* i2cDevice);
		virtual void clearDisplay();
		virtual void drawHorizontalBarGraph(char col, char row, char dir, char length);
		virtual void drawVerticalBarGraph(char col, char height, bool narrow);
		virtual void placeLargeDigit(char col, char digit);
		virtual void autolineWrap(bool state);
		virtual void autoScroll(bool state);
		virtual void setCursorPosition(char col, char row);
		virtual void cursorHome();
		virtual void underlineCursor(bool state);
		virtual void blinkingCursor(bool state);
		virtual void cursorLeft();
		virtual void cursorRight();
		virtual void writeString(char* str);
		virtual ~MatrixOrbital_LCD2041();
	private:
		virtual void sendCommand(char cmd1);
		virtual void sendCommand(char cmd1, char param1);
		virtual void sendCommand(char cmd1, char param1, char param2);
		virtual void sendCommand(char cmd1, char param1, char param2, char param3);
		virtual void sendCommand(char cmd1, char param1, char param2, char param3, char param4);
		virtual void initializeHorizontalBarGraph();
		virtual void initializeWideVerticalBarGraph();
		virtual void initializeNarrowVerticalBarGraph();
		virtual void initializeLargeDigits();
	};

}

