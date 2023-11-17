// SensorSettings.h

#pragma once

#include <Arduino.h>
#include "Globals.h"

#define F1_SENSOR_PIN 14
#define F2_SENSOR_PIN 27
#define R1_SENSOR_PIN 26
#define R2_SENSOR_PIN 25
#define B1_SENSOR_PIN 33
#define B2_SENSOR_PIN 32
#define L1_SENSOR_PIN 35
#define L2_SENSOR_PIN 34

#define F1_INDEX 0
#define F2_INDEX 1
#define R1_INDEX 2
#define R2_INDEX 3
#define B1_INDEX 4
#define B2_INDEX 5
#define L1_INDEX 6
#define L2_INDEX 7

#define FRONT_INDEX 0
#define RIGHT_INDEX 1
#define BACK_INDEX 2
#define LEFT_INDEX 3

#define DISTANCE_THRESHOLD_LOWER 3200
#define DISTANCE_THRESHOLD_UPPER 4000

#define RESET_PIN 22

#define SENSOR_COUNT 8

#define DIRECTION_COUNT 4

#define VARIANCE 1.12184278324081E-05
#define PROCESS_VARIANCE 1E-8

enum rover_clearance {
	STOP,
	GO
};

class Sensors {
private:

	int instructions[DIRECTION_COUNT];

	int raw_values[SENSOR_COUNT];

	float filtered_value[SENSOR_COUNT];

	float Pc;
	float kalman_gain;
	float covar_error;
	float Xp; // Next state predictor
	float Zp; // Next state predictor
	float initial_reading;
	float new_reading;
	float Xe;

public:
	void init();

	void initKalmanFilter();

	void filterValues(int values[8]);

	void getRawValues();

	void checkDistance();

	void run();
};