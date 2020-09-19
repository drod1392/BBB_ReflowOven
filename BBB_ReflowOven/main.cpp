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

	cout << "Begin" << endl;
	while(true) {

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
		usleep(100000);
	}

	return 0;
}