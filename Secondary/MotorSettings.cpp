// 
// 
// 

#include "MotorSettings.h"

void Motor::init() {
	pinMode(MOTOR_EN_PIN, OUTPUT);
	pinMode(MOTOR_IN1_PIN, OUTPUT);
	pinMode(MOTOR_IN2_PIN, OUTPUT);

	direction = UP;
}

void Motor::stop() {
	digitalWrite(MOTOR_IN1_PIN, LOW);
	digitalWrite(MOTOR_IN2_PIN, LOW);
}

void Motor::moveUp() {
	digitalWrite(MOTOR_IN1_PIN, LOW);
	digitalWrite(MOTOR_IN2_PIN, HIGH);

}

void Motor::moveDown() {
	digitalWrite(MOTOR_IN1_PIN, HIGH);
	digitalWrite(MOTOR_IN2_PIN, LOW);
}

void Motor::run() {
	digitalWrite(MOTOR_EN_PIN, HIGH);
}

void Motor::set(int direction) {
	
	if (direction == UP) {
		DEBUG_PORT.println("UP");
		moveUp();
		run();
		
	}
	else if (direction == DOWN) {
		DEBUG_PORT.println("DOWN");
		moveDown();
		run();
	}
	else if(direction == STOP_DIRECTION) {
		stop();
	}
}