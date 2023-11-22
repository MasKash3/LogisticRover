// Globals.h

#pragma once

//#define SENSOR_ENABLED
//#define DETECTION_ENABLED


#define DEBUG_PORT Serial
#define DEBUG_BAUD_RATE 9600

#define BUFFER_SIZE 6
#define RECEIVE_BUFFER_SIZE 3

#define START_BYTE_INDEX 0
#define END_BYTE_INDEX 5

#define MOTOR_STATE_INDEX 1
#define MOTOR_END_BYTE_INDEX 2

#define START_BYTE 33
#define END_BYTE 66

#define SENSOR_COUNT 8

extern bool esp_flag;

extern int data_to_send[BUFFER_SIZE];

extern int data_received[RECEIVE_BUFFER_SIZE];