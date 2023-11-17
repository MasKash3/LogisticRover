// 
// 
// 

#include "MotorSettings.h"

void Motor::init() {
	pinMode(MOTOR_EN_PIN, OUTPUT);
	pinMode(MOTOR_IN1_PIN, OUTPUT);
	pinMode(MOTOR_IN2_PIN, OUTPUT);
	//digitalWrite(MOTOR_EN_PIN, HIGH);

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
		delay(1000);
		stop();
		DEBUG_PORT.println("UP");
		lift_state = UP;
		/*unsigned long current_time;
		static unsigned long previous_time = 0;
		current_time = millis();
		moveUp();
		if (current_time - previous_time > 1000) {
			DEBUG_PORT.println("UP");
			previous_time = current_time;
			stop();
			lift_state = true;
		}*/
	}
	else if (direction == DOWN && lift_state == UP) {
		moveDown();
		run();
		delay(1000);
		stop();
		lift_state = DOWN;
		DEBUG_PORT.println("DOWN");
		/*unsigned long current_time;
		static unsigned long previous_time = 0;
		current_time = millis();
		moveDown();
		if (current_time - previous_time > 1000) {
			DEBUG_PORT.println("DOWN");
			previous_time = current_time;
			stop();
			lift_state = false;
		}*/
	}
	else
	{
		stop();
	}


}
