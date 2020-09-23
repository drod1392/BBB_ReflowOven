#include "main.h"

#include <unistd.h>
#include <stdio.h>
#include <cstring>




int main() {
	GPIO* thermo1_cs = new GPIO(THERMO1_CS);
	GPIO* thermo2_cs = new GPIO(THERMO2_CS);
	GPIO* spi_data = new GPIO(THERMO_DATA);
	GPIO* spi_clk = new GPIO(THERMO_CLK);

	MAX31855 Temp1(spi_data, spi_clk, thermo1_cs);
	MAX31855 Temp2(spi_data, spi_clk, thermo2_cs);

	I2CDevice *device = new I2CDevice(1, 0x2E);

	MatrixOrbital_LCD2041 display(device);
	display.blinkingCursor(false);


	//char *test = "Hello World";



	cout << "Begin" << endl;
	while(true) {
		//display.writeArray(test, 11);
		//display.drawHorizontalBarGraph(0x02, 0x00, 50, 0x00);

		if (Temp1.ReadTemp() < 0) {
			cout << "TEMP1 - Read Error" << endl;
		} else {
			cout << "TEMP1 - Thermo Temp : " << Temp1.getThermoTempF() << " F" << endl;
			cout << "TEMP1 - Junction Temp : " << Temp1.getJunctionTempF() << " F" << endl << endl;
		}

		if (Temp2.ReadTemp() < 0) {
			cout << "TEMP2 - Read Error" << endl;
		}
		else {
			cout << "TEMP2 - Thermo Temp : " << Temp2.getThermoTempF() << " F" << endl;
			cout << "TEMP2 - Junction Temp : " << Temp2.getJunctionTempF() << " F" << endl << endl;
		}

		char line1buffer[20];
		char line2buffer[20];
		snprintf(line1buffer, sizeof(line1buffer), "Temp1: %.1fF", Temp1.getThermoTempF());
		snprintf(line2buffer, sizeof(line2buffer), "Junction1: %.1fF", Temp1.getJunctionTempF());
		display.clearDisplay();
		display.writeString(line1buffer);
		display.setCursorPosition(0, 2);
		display.writeString(line2buffer);
		usleep(250000);
	}

	return 0;
}