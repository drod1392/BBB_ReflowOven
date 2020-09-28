#pragma once

#include "GPIO.h"
#include "SPIDevice.h"
#include "I2CDevice.h"
#include "MAX31855.h"
#include "MatrixOrbital_LCD2041.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace exploringBB;
using namespace reflowOven;

#define HEAT1_GPIO	3	// GPIO_3	/ P9.21
#define HEAT2_GPIO	2	// GPIO_2	/ P9.22
#define THERMO1_CS	115	// GPIO_113	/ P9.27
#define THERMO2_CS	117	// GPIO_117	/ P9.25
#define THERMO_DATA	111	// GPIO_111 (MOSI) / P9.29
#define THERMO_CLK	110	// GPIO_110 (SPI_CLK) / P9.31
