#include "ConnectionSettings.h"

NetworkConnection rover_system;

void setup() {

	DEBUG_PORT.begin(DEBUG_BAUD_RATE);

	rover_system.init();

}

void loop() {

	rover_system.run();

}

