// MotionSettings.h

#pragma once

#include "ConnectionSettings.h"
#include "Globals.h"

// Left front motor
#define LF_MOTOR_EN_PIN 32
#define LF_MOTOR_IN1_PIN 27
#define LF_MOTOR_IN2_PIN 26

// Right front motor
#define LB_MOTOR_EN_PIN 25
#define LB_MOTOR_IN1_PIN 12
#define LB_MOTOR_IN2_PIN 14

// Left back motor
#define RF_MOTOR_EN_PIN 23
#define RF_MOTOR_IN1_PIN 33
#define RF_MOTOR_IN2_PIN 4

// Right back motor
#define RB_MOTOR_EN_PIN 13
#define RB_MOTOR_IN1_PIN 19
#define RB_MOTOR_IN2_PIN 18

// ----------- Channels -------------
#define FREQUENCY 400
#define LF_MOTOR_EN_CHANNEL 0
#define LB_MOTOR_EN_CHANNEL 1
#define RF_MOTOR_EN_CHANNEL 2
#define RB_MOTOR_EN_CHANNEL 3

#define RESOLUTION 8

#define NO_PWM 0
#define MIN_PWM 100
#define MAX_PWM 130
//#define MAX_PWM 200

#define INITIAL_MOTOR_SPEED 0

#define RF_INDEX 0
#define LF_INDEX 1
#define LB_INDEX 2
#define RB_INDEX 3

#define LIFT_MOTOR_LOW_DEADZONE 0.2
#define LIFT_MOTOR_DEADZONE 0.7

#define LB_MOTOR_INDEX 0
#define LF_MOTOR_INDEX 1
#define RF_MOTOR_INDEX 2
#define RB_MOTOR_INDEX 3

#define JOYSTICK_LOWER_BOUND 0
#define JOYSTICK_UPPER_BOUND 1

#define SPEED_LOWER_BOUND 20
#define SPEED_UPPER_BOUND 245

#define DISTANCE_THRESHOLD 30

enum rover_clearance {
	STOP,
	GO
};

enum modifier_axes {
	X_AXIS,
	Y_AXIS,
	BOTH_AXES
};

enum lifting_directions {
	STOP_LIFT,
	LIFT_UP,
	LIFT_DOWN
};

enum MovementState {
	STOPPED,
	MOVING_UP,
	MOVING_DOWN,
	MOVING_LEFT,
	MOVING_RIGHT,
	ROTATING_CLOCKWISE,
	ROTATING_COUNTERCLOCKWISE
};


class Rover {
private:
	int current_movement_state;

	bool sensors[4];

	float motor_speed_modifier[4];

	float LB_speed, LF_speed, RF_speed, RB_speed, motor_speed;

	float scaleSpeed(float speed);

	void stopAllMotors();

	void rotate(float joystick1_x);

	void moveUp();

	void moveDown();

	void moveLeft();

	void moveRight();

	void rotateClockwise();

	void rotateCounterClockwise();

	void mixUpRight(float joystick);

	void mixUpLeft(float joystick);

	void mixDownRight(float joystick);

	void mixDownLeft(float joystick);

	void moveMotors(float LB_speed, float LF_speed, float RF_speed, float RB_speed);

	void speedModifier(int axis, float joystick2_x, float joystick2_y);

	void liftMotorControl(float joystick1_y);

	void calculateMotorSpeeds(float joystick1_x, float joystick2_x, float joystick2_y);


public:

	void init();

	void motorControl(float received_data[6]);

	void monitor(float sensors_instructions[DATA_BUFFER_SIZE]);
};
