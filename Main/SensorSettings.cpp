// 
// 
// 

#include "SensorSettings.h"

Rover rover_;

SoftwareSerial sensor_serial(SENSOR_RX_PIN, SENSOR_TX_PIN);

void Sensors::init() {

	sensor_serial.begin(SENSOR_BAUD_RATE);

}

void Sensors::run() {

	if (sensor_serial.availableForWrite() > 0) {

		sensor_serial.write((uint8_t*)&data_to_send, sizeof(data_to_send));
		delay(50);

		if (sensor_received_data[START_BYTE_INDEX] == START_BYTE &&
			sensor_received_data[END_BYTE_INDEX] == END_BYTE) {

			// Sensors to stop motors
#ifdef SENSOR_DEBUG_ENABLED
			DEBUG_PORT.print(" ");
			DEBUG_PORT.print(sensor_received_data[START_BYTE_INDEX], 3);
			DEBUG_PORT.print(", ");
			DEBUG_PORT.print(sensor_received_data[FRONT_INDEX], 3);
			DEBUG_PORT.print(", ");
			DEBUG_PORT.print(sensor_received_data[RIGHT_INDEX], 3);
			DEBUG_PORT.print(", ");
			DEBUG_PORT.print(sensor_received_data[BACK_INDEX], 3);
			DEBUG_PORT.print(", ");
			DEBUG_PORT.print(sensor_received_data[LEFT_INDEX], 3);
			DEBUG_PORT.print(", ");
			DEBUG_PORT.print(sensor_received_data[END_BYTE_INDEX], 3);
#endif // SENSOR_DEBUG_ENABLED			

#ifdef SENSOR_ENABLED
			rover_.monitor(sensor_received_data);
#endif // SENSOR_ENABLED

		}

		sensor_serial.flush();

	}
}
