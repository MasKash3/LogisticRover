// ConnectionSettings.h

#pragma once

//#define TIMEOUT_RESTART 

#include "Globals.h"
#include "MotorSettings.h"
#include "CredentialsSettings.h"
#include "SensorSettings.h"

#define SERVER_PORT 4444

#define TIMEOUT 10000

class RoverSystem {

private:

	float app_received_data[DATA_BUFFER_SIZE];

	char ack_text[10] = "AutonoSky";

	bool client_connected;

public:
	void init();

	void initWifi(String ssid, String password);

	void run();

};