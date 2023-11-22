// 
// Settings.h

#pragma once

#include <EEPROM.h>
#include "Globals.h"
#include "ConnectionSettings.h"

#define EEPROM_SIZE 512
#define PROFILE_SIZE 100 // (32 for SSID + 64 for Password + 4 for safety buffer)
#define MAX_PROFILES (EEPROM_SIZE / PROFILE_SIZE)

#define STARTUP_DELAY 3000

#define CREDENTIAL_INDEX 7

class Credentials {

private:

	bool serial_flag;

	char user_input;

	String ssid;

	String password;

	String stored_credentials;

public:

	void init();

	void checkCredentials();

	void recheck();

	char* readFromSerial();

	void writeCredentials(char address, String ssid, String password);

	String readCredentials(char address);

};
