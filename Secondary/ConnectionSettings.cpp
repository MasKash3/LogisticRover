// 
// 
// 

#include "ConnectionSettings.h"
#include "MotorSettings.h"
#include "Globals.h"
#include "SensorSettings.h"

Motor motor;

Sensors sensors;

SoftwareSerial esp_serial(ESP_RX_PIN, ESP_TX_PIN);


void ConnectionSettings::init() {
	esp_serial.begin(ESP_BAUD_RATE);
	//sensors.init();
	data_received_flag = false;
	motor.init();
}

void ConnectionSettings::run() {

	//sensors.run();

	if (esp_serial.available()) {

		esp_serial.readBytes((char*)data_received, sizeof(data_received));
		if (data_received[MOTOR_STATE_INDEX] >= 0 && data_received[MOTOR_STATE_INDEX] < 3) {

			motor.set(data_received[MOTOR_STATE_INDEX]);

		}

		esp_serial.flush();
		//if (data_received[START_BYTE_INDEX] == START_BYTE && data_received[MOTOR_END_BYTE_INDEX] == END_BYTE) {
		//	if (data_received[MOTOR_STATE_INDEX] >= 0 && data_received[MOTOR_STATE_INDEX] < 3) {
		//		motor.set(data_received[MOTOR_STATE_INDEX]);

		//	}
		//	//esp_serial.write((uint8_t*)data_to_send, sizeof(data_to_send));
		//}
	}
}