// 
// 
// 

#include "SensorSettings.h"

void Sensors::init() {

	pinMode(F1_SENSOR_PIN, INPUT);
	pinMode(F2_SENSOR_PIN, INPUT);
	pinMode(R1_SENSOR_PIN, INPUT);
	pinMode(R2_SENSOR_PIN, INPUT);
	pinMode(B1_SENSOR_PIN, INPUT);
	pinMode(B2_SENSOR_PIN, INPUT);
	pinMode(L1_SENSOR_PIN, INPUT);
	pinMode(L2_SENSOR_PIN, INPUT);
	pinMode(RESET_PIN, OUTPUT);

	initKalmanFilter();

}

void Sensors::getRawValues() {

	raw_values[F1_INDEX] = analogRead(F1_SENSOR_PIN);
	raw_values[F2_INDEX] = analogRead(F2_SENSOR_PIN);
	raw_values[R1_INDEX] = analogRead(R1_SENSOR_PIN);
	raw_values[R2_INDEX] = analogRead(R2_SENSOR_PIN);
	raw_values[B1_INDEX] = analogRead(B1_SENSOR_PIN);
	raw_values[B2_INDEX] = analogRead(B2_SENSOR_PIN);
	raw_values[L1_INDEX] = analogRead(L1_SENSOR_PIN);
	raw_values[L2_INDEX] = analogRead(L2_SENSOR_PIN);

}


void Sensors::checkDistance() {
	data_to_send[START_BYTE_INDEX] = START_BYTE;
	data_to_send[END_BYTE_INDEX] = END_BYTE;

	if ((filtered_value[F1_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[F1_INDEX] < DISTANCE_THRESHOLD_UPPER)
		|| (filtered_value[F2_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[F2_INDEX] < DISTANCE_THRESHOLD_UPPER)) {
		//DEBUG_PORT.println("Front obstacle detected");
		instructions[FRONT_INDEX] = STOP;
	}
	else
	{
		instructions[FRONT_INDEX] = GO;
	}

	if ((filtered_value[R1_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[R1_INDEX] < DISTANCE_THRESHOLD_UPPER)
		|| (filtered_value[R2_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[R2_INDEX] < DISTANCE_THRESHOLD_UPPER)) {
		//DEBUG_PORT.println("Right obstacle detected");
		instructions[RIGHT_INDEX] = STOP;
	}
	else
	{
		instructions[RIGHT_INDEX] = GO;
	}

	if ((filtered_value[B1_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[B1_INDEX] < DISTANCE_THRESHOLD_UPPER)
		|| (filtered_value[B2_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[B2_INDEX] < DISTANCE_THRESHOLD_UPPER)) {
		//DEBUG_PORT.println("Back obstacle detected");
		instructions[BACK_INDEX] = STOP;
	}
	else
	{
		instructions[BACK_INDEX] = GO;
	}

	if ((filtered_value[L1_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[L1_INDEX] < DISTANCE_THRESHOLD_UPPER)
		|| (filtered_value[L2_INDEX] > DISTANCE_THRESHOLD_LOWER && filtered_value[L2_INDEX] < DISTANCE_THRESHOLD_UPPER)) {
		DEBUG_PORT.println(raw_values[L1_INDEX]);
		DEBUG_PORT.println(", ");
		DEBUG_PORT.println(raw_values[L2_INDEX]);
		//DEBUG_PORT.println("Left obstacle detected");
		instructions[LEFT_INDEX] = STOP;
	}
	else
	{
		instructions[LEFT_INDEX] = GO;
	}

	for (int i = 0; i < 4; i++) {
		data_to_send[i + 1] = instructions[i];
		esp_flag = true;
		//DEBUG_PORT.println(data_to_send[i + 1]);
	}
}

void Sensors::initKalmanFilter() {
	Pc = 0.0;
	kalman_gain = 0.0;
	covar_error = 1.0;
	Xp = 0.0;
	Zp = 0.0;
}

void Sensors::filterValues(int values[8]) {
	for (int i; i <= 8; i++)
	{
		new_reading = values[i];
		Xe = new_reading;
		Pc = covar_error + PROCESS_VARIANCE;
		kalman_gain = Pc / (Pc + VARIANCE);    
		covar_error = (1 - kalman_gain) * Pc;
		Xp = Xe;
		Zp = Xp;
		Xe = kalman_gain * (new_reading - Zp) + Xp;
		if (Xe > 2000 && Xe < 4000) {
			filtered_value[i] = Xe;
		}
		else {
			filtered_value[i] = 0;
		}
	}
}

void Sensors::run() {

	getRawValues();

	filterValues(raw_values);

	checkDistance();

}
