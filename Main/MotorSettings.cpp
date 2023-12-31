// 
// 
// 

#include "MotorSettings.h"

void Rover::init() {

	// Pins assignments
	pinMode(LF_MOTOR_EN_PIN, OUTPUT);
	pinMode(LF_MOTOR_IN1_PIN, OUTPUT);
	pinMode(LF_MOTOR_IN2_PIN, OUTPUT);

	pinMode(LB_MOTOR_EN_PIN, OUTPUT);
	pinMode(LB_MOTOR_IN1_PIN, OUTPUT);
	pinMode(LB_MOTOR_IN2_PIN, OUTPUT);

	pinMode(RF_MOTOR_EN_PIN, OUTPUT);
	pinMode(RF_MOTOR_IN1_PIN, OUTPUT);
	pinMode(RF_MOTOR_IN2_PIN, OUTPUT);

	pinMode(RB_MOTOR_EN_PIN, OUTPUT);
	pinMode(RB_MOTOR_IN1_PIN, OUTPUT);
	pinMode(RB_MOTOR_IN2_PIN, OUTPUT);

	stopAllMotors();

	data_to_send[START_BYTE_INDEX] = START_BYTE;
	data_to_send[END_BYTE_INDEX] = END_BYTE;

}

/* Move / Stop motors */

// Set direction
void Rover::moveUp() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move up");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(LF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, HIGH);

}

void Rover::moveUpRight() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move up right");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(LF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, HIGH);

}

void Rover::moveUpLeft() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move up left");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::moveDown() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move down");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::moveDownLeft() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move down left");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::moveDownRight() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move down right");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::moveLeft() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move left");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::moveRight() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("move right");
#endif // DIRECTION_DEBUG_ENABLED
	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, HIGH);

}

void Rover::rotateClockwise() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("rotate clockwise");
#endif // DIRECTION_DEBUG_ENABLED

	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, HIGH);

}

void Rover::rotateCounterClockwise() {

#ifdef DIRECTION_DEBUG_ENABLED
	DEBUG_PORT.println("rotate counterclockwise");
#endif // DIRECTION_DEBUG_ENABLED

	digitalWrite(LB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(LF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, HIGH);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::stopAllMotors() {

	digitalWrite(LF_MOTOR_IN1_PIN, LOW);
	digitalWrite(LF_MOTOR_IN2_PIN, LOW);
	digitalWrite(LB_MOTOR_IN1_PIN, LOW);
	digitalWrite(LB_MOTOR_IN2_PIN, LOW);
	digitalWrite(RF_MOTOR_IN1_PIN, LOW);
	digitalWrite(RF_MOTOR_IN2_PIN, LOW);
	digitalWrite(RB_MOTOR_IN1_PIN, LOW);
	digitalWrite(RB_MOTOR_IN2_PIN, LOW);

}

void Rover::liftMotorControl(float joystick1_y) {

	if (joystick1_y > LIFT_MOTOR_DEADZONE) {

		data_to_send[LIFT_MOTOR_INDEX] = LIFT_UP;
#ifdef LIFT_DEBUG_ENABLED
		DEBUG_PORT.println("Lift up");
#endif // LIFT_DEBUG_ENABLED

	}
	else if (joystick1_y < -LIFT_MOTOR_DEADZONE) {

		data_to_send[LIFT_MOTOR_INDEX] = LIFT_DOWN;
#ifdef LIFT_DEBUG_ENABLED
		DEBUG_PORT.println("Lift down");
#endif // LIFT_DEBUG_ENABLED

	}
	else {

		data_to_send[LIFT_MOTOR_INDEX] = STOP_LIFT;

	}
}


// Move motors
void Rover::moveMotors(float LB_speed, float LF_speed, float RF_speed, float RB_speed) {

	analogWrite(LB_MOTOR_EN_PIN, LB_speed);
	analogWrite(LF_MOTOR_EN_PIN, LF_speed);
	analogWrite(RF_MOTOR_EN_PIN, RF_speed);
	analogWrite(RB_MOTOR_EN_PIN, RB_speed);

	delay(20);

}

void Rover::rotate(float joystick1_x) {

	motor_speed = scaleSpeed(abs(joystick1_x));

	if (joystick1_x < 0) {

		rotateClockwise();

	}
	else {

		rotateCounterClockwise();

	}

	moveMotors(motor_speed, motor_speed, motor_speed, motor_speed);

}



/* Speed calculations */

// Scaling
float Rover::scaleSpeed(float speed) {

	float scaled_speed = (speed - JOYSTICK_LOWER_BOUND) / (JOYSTICK_UPPER_BOUND - JOYSTICK_LOWER_BOUND)
		* (SPEED_UPPER_BOUND - SPEED_LOWER_BOUND) + SPEED_LOWER_BOUND;

	if (scaled_speed > SPEED_UPPER_BOUND) {

		scaled_speed = SPEED_UPPER_BOUND;

	}
	else if (scaled_speed < SPEED_LOWER_BOUND) {

		scaled_speed = SPEED_LOWER_BOUND;

	}

	return scaled_speed;

}

// Calculating motor speeds
void Rover::calculateMotorSpeeds(float joystick1_x, float joystick2_x, float joystick2_y) {

	if (abs(joystick2_x) >= abs(joystick2_y)) {

		if (joystick2_x < 0
#ifdef SENSORS_ENABLED
			&& sensors[LEFT_INDEX] == GO
#endif // SENSORS_ENABLED
			) {

			moveLeft();

			if (joystick2_x < -0.5 && joystick2_y > 0.8) {

				moveUpLeft();

			}
			else if (joystick2_x < -0.5 && joystick2_y < -0.8) {

				moveDownLeft();

			}

			LB_speed = scaleSpeed(abs(joystick2_x));
			LF_speed = scaleSpeed(abs(joystick2_x));
			RF_speed = scaleSpeed(abs(joystick2_x));
			RB_speed = scaleSpeed(abs(joystick2_x));

		}

		else if (joystick2_x > 0
#ifdef SENSORS_ENABLED
			&& sensors[RIGHT_INDEX] == GO
#endif // SENSORS_ENABLED
			) {

			moveRight();

			if (joystick2_x > 0.5 && joystick2_y > 0.8) {

				moveUpRight();

			}
			else if (joystick2_x > 0.5 && joystick2_y < -0.8) {

				moveDownRight();

			}

			LB_speed = scaleSpeed(abs(joystick2_x));
			LF_speed = scaleSpeed(abs(joystick2_x));
			RF_speed = scaleSpeed(abs(joystick2_x));
			RB_speed = scaleSpeed(abs(joystick2_x));

		}
	}
	else if (abs(joystick2_x) < abs(joystick2_y)) {

		if (joystick2_y > 0
#ifdef SENSORS_ENABLED
			&& sensors[FRONT_INDEX] == GO
#endif // SENSORS_ENABLED
			) {

			moveUp();

			if (joystick2_x > 0.8 && joystick2_y > 0.5) {

				moveUpRight();

			}
			else if (joystick2_x < -0.8 && joystick2_y > 0.5) {

				moveUpLeft();

			}

			LB_speed = scaleSpeed(joystick2_y);
			LF_speed = scaleSpeed(joystick2_y);
			RF_speed = scaleSpeed(joystick2_y);
			RB_speed = scaleSpeed(joystick2_y);

		}
		else if (joystick2_y < 0
#ifdef SENSORS_ENABLED
			&& sensors[BACK_INDEX] == GO
#endif // SENSORS_ENABLED
			) {

			moveDown();

			if (joystick2_x > 0.8 && joystick2_y < -0.5) {

				moveDownRight();

			}
			else if (joystick2_x < -0.8 && joystick2_y < -0.5) {

				moveDownLeft();

			}

			LB_speed = scaleSpeed(abs(joystick2_y));
			LF_speed = scaleSpeed(abs(joystick2_y));
			RF_speed = scaleSpeed(abs(joystick2_y));
			RB_speed = scaleSpeed(abs(joystick2_y));

		}
	}

	if (abs(joystick1_x) >= MOTOR_LOW_DEADZONE) {

		rotate(joystick1_x);

	}
	else {

		moveMotors(LB_speed, LF_speed, RF_speed, RB_speed);

	}
}

void Rover::motorControl(float received_data[6]) {

	liftMotorControl(received_data[JOYSTICK_Y_INDEX]);

	calculateMotorSpeeds(received_data[JOYSTICK_X_INDEX], received_data[JOYSTICK2_X_INDEX], received_data[JOYSTICK2_Y_INDEX]);

}

void Rover::monitor(float sensors_instructions[DATA_BUFFER_SIZE]) {

	for (int i = 1; i <= 4; i++) {

		sensors[i - 1] = sensors_instructions[i];

	}
}