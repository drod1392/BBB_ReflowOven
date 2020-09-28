#include "MatrixOrbital_LCD2041.h"

namespace reflowOven {
	MatrixOrbital_LCD2041::MatrixOrbital_LCD2041(I2CDevice* i2cDevice) {
		device = i2cDevice;
	}

	void MatrixOrbital_LCD2041::placeLargeDigit(char col, char digit)
	{
		sendCommand(35, col, digit);
	}

	void MatrixOrbital_LCD2041::autolineWrap(bool state)
	{
		if (state)
			sendCommand(67);
		else
			sendCommand(68);
	}

	void MatrixOrbital_LCD2041::autoScroll(bool state)
	{
		if (state)
			sendCommand(81);
		else
			sendCommand(82);
	}

	void MatrixOrbital_LCD2041::setCursorPosition(char col, char row)
	{
		sendCommand(71, col, row);
	}

	void MatrixOrbital_LCD2041::cursorHome()
	{
		sendCommand(72);
	}

	void MatrixOrbital_LCD2041::underlineCursor(bool state)
	{
		if (state)
			sendCommand(74);
		else
			sendCommand(75);
	}

	void MatrixOrbital_LCD2041::blinkingCursor(bool state)
	{
		if (state)
			sendCommand(83);
		else 
			sendCommand(84);
	}

	void MatrixOrbital_LCD2041::cursorLeft()
	{
		sendCommand(76);
	}

	void MatrixOrbital_LCD2041::cursorRight()
	{
		sendCommand(77);
	}

	void MatrixOrbital_LCD2041::writeString(char* value) {
		int len = strlen(value);
		device->writeArray(value, len);
	}

	void MatrixOrbital_LCD2041::sendCommand(char cmd) {
		char buf[2];
		char* ptr = buf;
		buf[0] = 254;
		buf[1] = cmd;
		device->writeArray(ptr, 2);
	}
	void MatrixOrbital_LCD2041::sendCommand(char cmd, char param1) {
		char buf[3];
		char* ptr = buf;
		buf[0] = 254;
		buf[1] = cmd;
		buf[2] = param1;
		device->writeArray(ptr, 3);
	}
	void MatrixOrbital_LCD2041::sendCommand(char cmd, char param1, char param2) {
		char buf[4];
		char* ptr = buf;
		buf[0] = 254;
		buf[1] = cmd;
		buf[2] = param1;
		buf[3] = param2;
		device->writeArray(ptr, 4);
	}
	void MatrixOrbital_LCD2041::sendCommand(char cmd, char param1, char param2, char param3) {
		char buf[5];
		char* ptr = buf;
		buf[0] = 254;
		buf[1] = cmd;
		buf[2] = param1;
		buf[3] = param2;
		buf[4] = param3;
		device->writeArray(ptr, 5);
	}
	void MatrixOrbital_LCD2041::sendCommand(char cmd, char param1, char param2, char param3, char param4) {
		char buf[6];
		char* ptr = buf;
		buf[0] = 254;
		buf[1] = cmd;
		buf[2] = param1;
		buf[3] = param2;
		buf[4] = param3;
		buf[5] = param3;
		device->writeArray(ptr, 6);
	}

	void MatrixOrbital_LCD2041::clearDisplay() {
		sendCommand(88);
	}

	void MatrixOrbital_LCD2041::drawHorizontalBarGraph(char col, char row, char dir, char length) {
		initializeHorizontalBarGraph();
		sendCommand(124, col, row, dir, length);
	}

	void MatrixOrbital_LCD2041::drawVerticalBarGraph(char col, char height, bool narrow)
	{
		if (narrow)
			initializeNarrowVerticalBarGraph();
		else
			initializeWideVerticalBarGraph();
		sendCommand(61, col, height);
	}

	void MatrixOrbital_LCD2041::initializeHorizontalBarGraph() {
		sendCommand(68);
	}

	void MatrixOrbital_LCD2041::initializeWideVerticalBarGraph()
	{
		sendCommand(118);
	}

	void MatrixOrbital_LCD2041::initializeNarrowVerticalBarGraph()
	{
	}

	void MatrixOrbital_LCD2041::initializeLargeDigits()
	{
	}

	MatrixOrbital_LCD2041::~MatrixOrbital_LCD2041() {

	}
}
