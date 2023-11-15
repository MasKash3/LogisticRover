
#include <WiFi.h>
#include <WiFiUdp.h>

#include <Arduino.h>
#include <SoftwareSerial.h>

const char* ack = "AutonoSkyi";
SoftwareSerial dataSerial(9, 8); // RX TX

// Motor A connections left front
int enA = 18;
int in1 = 19;
int in2 = 20;

int dataToSend[4] = { 1, 2, 0, 1 };
String lift_state = "down";
//string message = "thtnknmnxnkvkxvlkmvi";
void setup() {
	//serial with esp32
	dataSerial.begin(115200);

	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);


	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);

	Serial.begin(115200);
	//udp.begin(WiFi.localIP(), udpPort);
	delay(1500);
	Serial.println("started");

}

void loop() {
	//motorControl(scaleFunction(x));
	if (dataSerial.available() > 0) {
		
		int receivedData[4];
		dataSerial.readBytes((char*)&receivedData, sizeof(receivedData));

		if (receivedData[0] == 1 && receivedData[3] == 1) {
			Serial.print("Received data: ");
			//Serial.print(sizeof(receivedData));
			Serial.println(receivedData[1]);
			if (receivedData[1]==1 && lift_state=="up") {
				// Turn on motors
				digitalWrite(in1, LOW);
				digitalWrite(in2, HIGH);
				motorControl(scaleFunction(0.8));
				delay(3000);
				motorControl(scaleFunction(0));
				lift_state = "down";
			}
			else if (receivedData[1] == 2 && lift_state == "down") {
				// Turn on motors
				digitalWrite(in1, HIGH);
				digitalWrite(in2, LOW);
				motorControl(scaleFunction(0.8));
				delay(3000);
				motorControl(scaleFunction(0));
				lift_state = "up";
			}
			else {
				motorControl(scaleFunction(0.0));
			}
			//Serial.print(sizeof(receivedData));

		}


		dataSerial.write((uint8_t*)&dataToSend, sizeof(dataToSend));

	}
}

float scaleFunction(float value) {
	//input range
	float a = 0;
	float b = 1;
	//output range
	float c = 20;
	float d = 255;
	float y = (value - a) / (b - a) * (d - c) + c;
	Serial.println(y);
	return y;

}
void motorControl(float val) {
	analogWrite(enA, val);

	delay(20);

}