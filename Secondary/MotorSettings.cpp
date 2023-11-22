// 
// 
// 

#include "MotorSettings.h"

void Motor::init() {

	pinMode(MOTOR_EN_PIN, OUTPUT);
	pinMode(MOTOR_IN1_PIN, OUTPUT);
	pinMode(MOTOR_IN2_PIN, OUTPUT);

	lift_state = DOWN;

}

void Motor::stop() {

	digitalWrite(MOTOR_IN1_PIN, LOW);
	digitalWrite(MOTOR_IN2_PIN, LOW);

}

void Motor::moveUp() {

	digitalWrite(MOTOR_IN1_PIN, HIGH);
	digitalWrite(MOTOR_IN2_PIN, LOW);

}

void Motor::moveDown() {

	digitalWrite(MOTOR_IN1_PIN, LOW);
	digitalWrite(MOTOR_IN2_PIN, HIGH);

}

void Motor::run() {

	digitalWrite(MOTOR_EN_PIN, HIGH);

}

void Motor::set(int direction) {

	if (direction == UP && lift_state == DOWN) {

		moveUp();
		run();
		delay(LIFT_DURATION);
		stop();
		DEBUG_PORT.println("UP");
		lift_state = UP;

	}
	else if (direction == DOWN && lift_state == UP) {

		moveDown();
		run();
		delay(LIFT_DURATION);
		stop();
		lift_state = DOWN;
		DEBUG_PORT.println("DOWN");

	}
	else
	{
		stop();
	}

}
