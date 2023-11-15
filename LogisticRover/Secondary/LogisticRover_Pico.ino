/*
 Name:		LogisticRover_Pico.ino
 Created:	11/13/2023 7:45:37 PM
 Author:	maska
*/

// the setup function runs once when you press reset or power the board
#include "SensorSettings.h"
#include "Globals.h"
#include "ConnectionSettings.h"

ConnectionSettings connection;

void setup() {

	DEBUG_PORT.begin(DEBUG_BAUD_RATE);

	connection.init();
}

// the loop function runs over and over again until power down or reset
void loop() {

	connection.run();

}
