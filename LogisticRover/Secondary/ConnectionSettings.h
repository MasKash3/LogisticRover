// ConnectionSettings.h

#pragma once

#include <SoftwareSerial.h>

#define ESP_RX_PIN 18
#define ESP_TX_PIN 19

#define ESP_BAUD_RATE 9600

class ConnectionSettings {
private:
	bool data_received_flag;

public:
	void init();

	void run();
};