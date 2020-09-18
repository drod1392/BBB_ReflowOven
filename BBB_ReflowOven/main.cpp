#include "main.h"

#include <unistd.h>
#include <stdio.h>
#include <cstring>




int main() {
	GPIO thermo1_cs(THERMO1_CS);
	GPIO thermo2_cs(THERMO2_CS);
	GPIO spi_data(THERMO_DATA);
	GPIO spi_clk(THERMO_CLK);

	MAX31855 Temp1(&spi_data, &spi_clk, &thermo2_cs);

	cout << "Begin" << endl;
	while(true) {

		if (Temp1.ReadTemp() < 0) {
			cout << "Read Error" << endl;
		} else {
			cout << "Thermo Temp : " << Temp1.getThermoTempF() << " F" << endl;
			cout << "Junction Temp : " << Temp1.getJunctionTempF() << " F" << endl << endl;
		}
		usleep(100000);
	}

	return 0;
}