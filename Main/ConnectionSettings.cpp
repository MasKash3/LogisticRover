// 
// 
// 

#include "ConnectionSettings.h"

Credentials credentials;

Rover rover;

Sensors sensors;

WiFiServer server(SERVER_PORT);

void NetworkConnection::init() {

	rover.init();

	credentials.init();

	sensors.init();

	client_connected = false;

	server.begin();
}

void NetworkConnection::initWifi(String ssid, String password) {
	unsigned long time_out_counter;
	DEBUG_PORT.println("");
	DEBUG_PORT.print("Network: ");
	DEBUG_PORT.println(ssid);

	WiFi.begin(ssid, password);
	DEBUG_PORT.println("");
	DEBUG_PORT.println("Attempting connection.");
	DEBUG_PORT.println("Please wait...");

	while (WiFi.status() != WL_CONNECTED) {
		time_out_counter = millis();
		if (WiFi.status() == WL_CONNECT_FAILED || time_out_counter == 10000) {
			DEBUG_PORT.println("Connection failed.");
			DEBUG_PORT.println("Please re-enter credentials.");
			credentials.recheck();
		}
	}
	DEBUG_PORT.println("");
	DEBUG_PORT.println("WiFi connected.");
	DEBUG_PORT.println("IP address: ");
	DEBUG_PORT.println(WiFi.localIP());

}

void NetworkConnection::run() {

	WiFiClient client = server.available();

	if (client) {
		if (connection_counter == 0) {
			DEBUG_PORT.println("Rover connected.");
			connection_counter = 1;
			client_connected = true;
		}

		while (client.connected()) {

			if (client.available()) {

				int bytes_read = client.read((uint8_t*)&app_received_data, sizeof(app_received_data));

				if (bytes_read == sizeof(app_received_data)) {
#ifdef APP_DEBUG_ENABLED
					DEBUG_PORT.print(" ");
					DEBUG_PORT.print(app_received_data[START_BYTE_INDEX], 3);
					DEBUG_PORT.print(", ");
					DEBUG_PORT.print(app_received_data[JOYSTICK_X_INDEX], 3);
					DEBUG_PORT.print(", ");
					DEBUG_PORT.print(app_received_data[JOYSTICK_Y_INDEX], 3);
					DEBUG_PORT.print(", ");
					DEBUG_PORT.print(app_received_data[JOYSTICK2_X_INDEX], 3);
					DEBUG_PORT.print(", ");
					DEBUG_PORT.print(app_received_data[JOYSTICK2_Y_INDEX], 3);
					DEBUG_PORT.print(", ");
					DEBUG_PORT.print(app_received_data[END_BYTE_INDEX], 3);
#endif // APP_DEBUG_ENABLED
				}
				sensors.run();
				rover.motorControl(app_received_data);
				client.write(ack_text);
			}
		}
	}
	else
	{
		client_connected = false;
		if (client_connected == false && connection_counter > 0) {
			app_received_data[DATA_BUFFER_SIZE] = 0;
			connection_counter = 0;
			DEBUG_PORT.println("Rover disconnected.");
		}
	}
}