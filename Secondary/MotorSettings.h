// MotorSettings.h

#pragma once

#include <Arduino.h>
#include "Globals.h"

#define MOTOR_EN_PIN 12
#define MOTOR_IN1_PIN 13
#define MOTOR_IN2_PIN 23

enum directions {
	STOP_DIRECTION,
	UP,
	DOWN
};

class Motor {
private:
	int direction;
	int lift_state;
public:

	void init();

	void moveUp();

	void moveDown();

	void run();

	void set(int direction);

	void stop();
};