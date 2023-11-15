// 
// 
// 

#include "CredentialsSettings.h"

NetworkConnection connectivity;

void Credentials::init() {

	EEPROM.begin(EEPROM_SIZE);

	delay(STARTUP_DELAY);

	checkCredentials();
}

void Credentials::checkCredentials() {
	stored_credentials = readCredentials(CREDENTIAL_INDEX);
	int comma_index = stored_credentials.indexOf(',');
	ssid = stored_credentials.substring(0, comma_index);
	password = stored_credentials.substring(comma_index + 1);

	if (stored_credentials.length() > 0) {
		DEBUG_PORT.println("Credentials found.");
		int comma_index = stored_credentials.indexOf(',');
		if (comma_index != -1) {
			ssid = stored_credentials.substring(0, comma_index);
			password = stored_credentials.substring(comma_index + 1);
		}
		connectivity.initWifi(ssid, password);
	}
	else {
		DEBUG_PORT.println("No credentials found.");

		DEBUG_PORT.print("Enter SSID: ");
		char* ssid_temp = readFromSerial();
		DEBUG_PORT.println(ssid_temp);

		DEBUG_PORT.print("Enter password: ");
		char* password_temp = readFromSerial();
		DEBUG_PORT.println(password_temp);

		writeCredentials(CREDENTIAL_INDEX, ssid_temp, password_temp);

		DEBUG_PORT.println("Credentials stored.");

		connectivity.initWifi(ssid_temp, password_temp);
	}
}

void Credentials::recheck() {

	DEBUG_PORT.print("Enter SSID: ");
	char* ssid_temp = readFromSerial();
	DEBUG_PORT.println(ssid_temp);

	DEBUG_PORT.print("Enter password: ");
	char* password_temp = readFromSerial();
	DEBUG_PORT.println(password_temp);

	writeCredentials(CREDENTIAL_INDEX, ssid_temp, password_temp);

	DEBUG_PORT.println("Credentials stored.");

	connectivity.initWifi(ssid_temp, password_temp);
}

char* Credentials::readFromSerial() {
	char* input = (char*)malloc(100); // Allocate memory dynamically
	int index = 0;
	while (true) {
		while (DEBUG_PORT.available() > 0) {
			char c = DEBUG_PORT.read();
			if (c == '\n' || c == '\r') {
				input[index] = '\0'; // Null terminate the string
				return input;
			}
			else {
				input[index] = c;
				index++;
			}
		}
		delay(100);
	}
}

void Credentials::writeCredentials(char address, String ssid, String password) {

	String credentials = ssid + "," + password;

	int _size = credentials.length();

	for (int i = 0; i < _size; i++)
	{
		EEPROM.write(address + i, credentials[i]);
	}
	EEPROM.write(address + _size, '\0');   //Add termination null character for String Data
	EEPROM.commit();
}

String Credentials::readCredentials(char address) {
	int i;
	char data[100]; //Max 100 Bytes
	int len = 0;
	unsigned char k;
	k = EEPROM.read(address);
	while (k != '\0' && len < 500)   //Read until null character
	{
		k = EEPROM.read(address + len);
		data[len] = k;
		len++;
	}
	data[len] = '\0';
	return String(data);
}
