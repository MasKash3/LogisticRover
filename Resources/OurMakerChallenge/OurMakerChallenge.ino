
#include <WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>


SoftwareSerial picoSerial(21, 22); // RX TX
const char* ssid = "Autonosky";
const char* password = "Nach0WiFi!";
//const char* ssid = "In";
//const char* password = "12345678";
const char* ack = "AutonoSky";

float received_data[6];
//char received_data2[5];
float START_BYTE_INDEX = 60.0;
int JOYSTICK_X_INDEX = 1;
int JOYSTICK_Y_INDEX = 2;
int JOYSTICK2_X_INDEX = 3;
int JOYSTICK2_Y_INDEX = 4;
float END_BYTE_INDEX = 60.0;

int dataToSend[4] = { 1, 0, 0, 1 };
float motorModifier[4] = { 0, 0, 0, 0 };
WiFiServer server(4444);
// Motor A connections left back
int enA = 23;
int in1 = 33;
int in2 = 4;
// Motor B connections left front
int enB = 32;
int in3 = 27;
int in4 = 26;
// Motor C connections right front
int enC = 25; //16
int in5 = 12;
int in6 = 14;
// Motor D connections right back
int enD = 13; //17
int in7 = 19;
int in8 = 18;


void setup() {
	picoSerial.begin(115200);
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(enC, OUTPUT);
	pinMode(enD, OUTPUT);

	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(in5, OUTPUT);
	pinMode(in6, OUTPUT);
	pinMode(in7, OUTPUT);
	pinMode(in8, OUTPUT);


	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
	digitalWrite(in5, LOW);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, LOW);

	Serial.begin(115200);
	//wifi connection 
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	//udp.begin(WiFi.localIP(), udpPort);
	delay(1500);
	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	server.begin();
}

void loop() {
	WiFiClient client = server.available();   // listen for incoming clients
	if (client) {                             // if you get a client,
		Serial.println("New Client.");          // print a message out the serial port
		String currentLine = "";
		while (client.connected()) {            // loop while the client's connected

			if (client.available()) {             // if there's bytes to read from the client,

				int bytes_read = client.read((uint8_t*)&received_data, sizeof(received_data));

				if (bytes_read == sizeof(received_data)) {
					//Serial.println("Received Start Byte: ");
					//Serial.println(received_data[START_BYTE_INDEX], 5);
					//Serial.print("Joystick 1 x: ");


					//Serial.println(" ");
					//Serial.print(received_data[JOYSTICK_X_INDEX], 5);
					//Serial.print(", ");
					////Serial.print("Joystick 1 y: ");
					//Serial.print(received_data[JOYSTICK_Y_INDEX], 5);
					//Serial.print(", ");
					////Serial.print("Joystick 2 x: ");
					//Serial.print(received_data[JOYSTICK2_X_INDEX], 5);
					//Serial.print(", ");
					////Serial.print("Joystick 2 y: ");
					//Serial.print(received_data[JOYSTICK2_Y_INDEX], 5);
					//Serial.print(", ");


					//Serial.print("Received End Byte: ");
					//Serial.println(received_data[END_BYTE_INDEX], 5);

					if (received_data[JOYSTICK_Y_INDEX] > 0.3) {
						//flag for lift up
						dataToSend[1] = 1;
						Serial.println("lift up");
					}
					else if (received_data[JOYSTICK_Y_INDEX] < -0.3) {
						//flag for lift down
						dataToSend[1] = 2;
						Serial.println("lift down");

					}
					else {
						dataToSend[1] = 0;
					}
				}


				//Serial.print(received_data[JOYSTICK2_Y_INDEX], 5);
				calculateMove();
				//motorControl(scaleFunction(received_data[JOYSTICK2_Y_INDEX]));
				client.write(ack);
				//motorControl(scaleFunction(x))

			}
			if (picoSerial.available() > 0) {

				int receivedData[4];
				picoSerial.readBytes((char*)&receivedData, sizeof(receivedData));
				//Serial.println(receivedData[1]);

				if (receivedData[0] == 1 && receivedData[3] == 1) {
					//Serial.print("Received data: ");
					//Serial.println(receivedData[1]);


				}

			}
			picoSerial.write((uint8_t*)&dataToSend, sizeof(dataToSend));

		}
	}

}

float scaleFunction(float value) {
	//input range
	float a = 0;
	float b = 1;
	//output range
	float c = 20;
	float d = 245;
	float y = (value - a) / (b - a) * (d - c) + c;
	if (y > 255) {
		y = 255;
	}
	//Serial.println(y);
	return y;

}
void rotate() {
	if (received_data[JOYSTICK_X_INDEX] < 0) {
		//clockwise
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
		digitalWrite(in3, LOW);
		digitalWrite(in4, HIGH);
		digitalWrite(in5, LOW);
		digitalWrite(in6, HIGH);
		digitalWrite(in7, LOW);
		digitalWrite(in8, HIGH);
		//motorControl()
		float val = abs(scaleFunction(received_data[JOYSTICK_X_INDEX]));
		motorControl(val, val, val, val);

	}
	else {
		//counter clockwise
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
		digitalWrite(in3, HIGH);
		digitalWrite(in4, LOW);
		digitalWrite(in5, HIGH);
		digitalWrite(in6, LOW);
		digitalWrite(in7, HIGH);
		digitalWrite(in8, LOW);
		//motorControl()
		float val = abs(scaleFunction(received_data[JOYSTICK_X_INDEX]));
		motorControl(val, val, val, val);
	}
}
void motorControl(float A, float B, float C, float D) {
	// Turn on motors
	//digitalWrite(in1, LOW);
	//digitalWrite(in2, HIGH);
	//digitalWrite(in3, LOW);
	//digitalWrite(in4, HIGH);
	//digitalWrite(in5, LOW);
	//digitalWrite(in6, HIGH);
	//digitalWrite(in7, LOW);
	//digitalWrite(in8, HIGH);


	analogWrite(enA, A);
	analogWrite(enB, B);
	analogWrite(enC, C);
	analogWrite(enD, D);

	delay(20);

}

void modifier(String axis) {
	if (axis == "x") {
		//x is dominant modify using y axis
		if (received_data[JOYSTICK2_Y_INDEX] >= 0) {
			//positive y, add move up
			if (received_data[JOYSTICK2_X_INDEX] >= 0) {
				//mix up and right
				motorModifier[0] = -received_data[JOYSTICK2_Y_INDEX];
				motorModifier[1] = received_data[JOYSTICK2_Y_INDEX];
				motorModifier[2] = -received_data[JOYSTICK2_Y_INDEX];
				motorModifier[3] = received_data[JOYSTICK2_Y_INDEX];

			}
			else {
				//mix up and left
				motorModifier[0] = received_data[JOYSTICK2_Y_INDEX];
				motorModifier[1] = -received_data[JOYSTICK2_Y_INDEX];
				motorModifier[2] = received_data[JOYSTICK2_Y_INDEX];
				motorModifier[3] = -received_data[JOYSTICK2_Y_INDEX];
			}

		}
		else {
			//negative y, add move down
			if (received_data[JOYSTICK2_Y_INDEX] >= 0) {
				//mix down and right
				motorModifier[0] = received_data[JOYSTICK2_Y_INDEX];
				motorModifier[1] = -received_data[JOYSTICK2_Y_INDEX];
				motorModifier[2] = received_data[JOYSTICK2_Y_INDEX];
				motorModifier[3] = -received_data[JOYSTICK2_Y_INDEX];
			}
			else {
				//mix down and left
				motorModifier[0] = -received_data[JOYSTICK2_Y_INDEX];
				motorModifier[1] = received_data[JOYSTICK2_Y_INDEX];
				motorModifier[2] = -received_data[JOYSTICK2_Y_INDEX];
				motorModifier[3] = received_data[JOYSTICK2_Y_INDEX];
			}
		}

	}
	else {
		//y is dominant modify using x axis
		if (received_data[JOYSTICK2_X_INDEX] >= 0) {
			//positive x, add move right
			if (received_data[JOYSTICK2_Y_INDEX] >= 0) {
				//mix right and up
				motorModifier[0] = -received_data[JOYSTICK2_X_INDEX];
				motorModifier[1] = received_data[JOYSTICK2_X_INDEX];
				motorModifier[2] = -received_data[JOYSTICK2_X_INDEX];
				motorModifier[3] = received_data[JOYSTICK2_X_INDEX];
			}
			else {
				//mix right and down
				motorModifier[0] = received_data[JOYSTICK2_X_INDEX];
				motorModifier[1] = -received_data[JOYSTICK2_X_INDEX];
				motorModifier[2] = received_data[JOYSTICK2_X_INDEX];
				motorModifier[3] = -received_data[JOYSTICK2_X_INDEX];
			}
		}
		else {
			//negative x, add move left
			if ((received_data[JOYSTICK2_Y_INDEX] >= 0)) {
				//mix left and up
				motorModifier[0] = received_data[JOYSTICK2_X_INDEX];
				motorModifier[1] = -received_data[JOYSTICK2_X_INDEX];
				motorModifier[2] = received_data[JOYSTICK2_X_INDEX];
				motorModifier[3] = -received_data[JOYSTICK2_X_INDEX];
			}
			else {
				//mix left and down
				motorModifier[0] = -received_data[JOYSTICK2_X_INDEX];
				motorModifier[1] = received_data[JOYSTICK2_X_INDEX];
				motorModifier[2] = -received_data[JOYSTICK2_X_INDEX];
				motorModifier[3] = received_data[JOYSTICK2_X_INDEX];
			}
		}
	}

}

void calculateMove() {
	// find dominant value, x or y
	if (abs(received_data[JOYSTICK2_X_INDEX]) > abs(received_data[JOYSTICK2_Y_INDEX])) {
		//horizontal(x) is dominant
		if (received_data[JOYSTICK2_X_INDEX] >= 0) {
			//move right
			Serial.println("move right");
			digitalWrite(in1, LOW);
			digitalWrite(in2, HIGH);
			digitalWrite(in3, HIGH);
			digitalWrite(in4, LOW);
			digitalWrite(in5, HIGH);
			digitalWrite(in6, LOW);
			digitalWrite(in7, LOW);
			digitalWrite(in8, HIGH);
			modifier("x");
			float m0 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[0] * received_data[JOYSTICK2_X_INDEX]));
			float m1 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[1] * received_data[JOYSTICK2_X_INDEX]));
			float m2 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[2] * received_data[JOYSTICK2_X_INDEX]));
			float m3 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[3] * received_data[JOYSTICK2_X_INDEX]));

			if (abs(received_data[JOYSTICK_X_INDEX]) >= 0.2) {
				rotate();
			}

			else {
				
				motorControl(m0, m1, m2, m3);
			}


			//motorControl(scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])));
		}
		else {
			//move left
			Serial.println("move left");
			digitalWrite(in1, HIGH);
			digitalWrite(in2, LOW);
			digitalWrite(in3, LOW);
			digitalWrite(in4, HIGH);
			digitalWrite(in5, LOW);
			digitalWrite(in6, HIGH);
			digitalWrite(in7, HIGH);
			digitalWrite(in8, LOW);
			float m0 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[0] * received_data[JOYSTICK2_X_INDEX]));
			float m1 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[1] * received_data[JOYSTICK2_X_INDEX]));
			float m2 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[2] * received_data[JOYSTICK2_X_INDEX]));
			float m3 = scaleFunction(abs(received_data[JOYSTICK2_X_INDEX]) + (motorModifier[3] * received_data[JOYSTICK2_X_INDEX]));
			if (abs(received_data[JOYSTICK_X_INDEX]) >= 0.2) {
				rotate();
			}
			else {
				motorControl(m0, m1, m2, m3);
			}
			//motorControl(scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_X_INDEX])));
		}
	}
	else {
		//vertical(y) is dominant
		if (received_data[JOYSTICK2_Y_INDEX] >= 0) {
			//move up
			Serial.println("move up");
			digitalWrite(in1, HIGH);
			digitalWrite(in2, LOW);
			digitalWrite(in3, HIGH);
			digitalWrite(in4, LOW);
			digitalWrite(in5, LOW);
			digitalWrite(in6, HIGH);
			digitalWrite(in7, LOW);
			digitalWrite(in8, HIGH);
			modifier("y");
			float m0 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[0] * received_data[JOYSTICK2_Y_INDEX]));
			float m1 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[1] * received_data[JOYSTICK2_Y_INDEX]));
			float m2 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[2] * received_data[JOYSTICK2_Y_INDEX]));
			float m3 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[3] * received_data[JOYSTICK2_Y_INDEX]));
			if (abs(received_data[JOYSTICK_X_INDEX]) >= 0.2) {
				rotate();
			}
			else {
				motorControl(m0, m1, m2, m3);
			}
			//motorControl(scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])));
		}
		else {
			//move down
			Serial.println("move down");
			digitalWrite(in1, LOW);
			digitalWrite(in2, HIGH);
			digitalWrite(in3, LOW);
			digitalWrite(in4, HIGH);
			digitalWrite(in5, HIGH);
			digitalWrite(in6, LOW);
			digitalWrite(in7, HIGH);
			digitalWrite(in8, LOW);
			modifier("y");
			float m0 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[0] * received_data[JOYSTICK2_Y_INDEX]));
			float m1 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[1] * received_data[JOYSTICK2_Y_INDEX]));
			float m2 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[2] * received_data[JOYSTICK2_Y_INDEX]));
			float m3 = scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX]) + (motorModifier[3] * received_data[JOYSTICK2_Y_INDEX]));
			if (abs(received_data[JOYSTICK_X_INDEX]) >= 0.2) {
				rotate();
			}
			else {
				motorControl(m0, m1, m2, m3);
			}
			//motorControl(scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])), scaleFunction(abs(received_data[JOYSTICK2_Y_INDEX])));
		}
	}
}
