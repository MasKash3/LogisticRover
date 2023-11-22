// SensorSettings.h

#pragma once

#include <SoftwareSerial.h>

#include "Globals.h"

#include "MotorSettings.h"

#define SENSOR_RX_PIN 21
#define SENSOR_TX_PIN 22

#define SENSOR_BAUD_RATE 9600

#define START_BYTE 33
#define END_BYTE 66

class Sensors {
private:

public:
	float sensor_received_data[DATA_BUFFER_SIZE];

	void init();

	void run();
};