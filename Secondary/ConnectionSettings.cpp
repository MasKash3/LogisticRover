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
	motor.init();
#ifdef SENSOR_ENABLED
	sensors.init();
#endif // SENSOR_ENABLED
	data_received_flag = false;

}

void ConnectionSettings::run() {

#ifdef SENSOR_ENABLED
	sensors.run();
	esp_serial.write((uint8_t*)data_to_send, sizeof(data_to_send));
	delay(50);
#endif // SENSOR_ENABLED


	if (esp_serial.available()) {

		esp_serial.readBytes((char*)data_received, sizeof(data_received));

		if (data_received[START_BYTE_INDEX] == START_BYTE && data_received[MOTOR_END_BYTE_INDEX] == END_BYTE) {

			if (data_received[MOTOR_STATE_INDEX] >= STOP_DIRECTION && data_received[MOTOR_STATE_INDEX] <= DOWN) {

				motor.set(data_received[MOTOR_STATE_INDEX]);

			}
		}

		esp_serial.flush();

	}
}