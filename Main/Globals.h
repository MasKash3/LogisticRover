// Globals.h

#pragma once

#include <WiFi.h>

#define TIMEOUT_INCREMENT 2
#define MAX_TIMEOUT 25

#define DEBUG_PORT Serial
#define DEBUG_BAUD_RATE 9600

//#define SENSORS_ENABLED
#define DEBUG_ENABLED

//#define APP_DEBUG_ENABLED
//#define LIFT_DEBUG_ENABLED
//#define SENSOR_DEBUG_ENABLED
//#define DIRECTION_DEBUG_ENABLED

#define DATA_BUFFER_SIZE 6

#define SEND_DATA_BUFFER_SIZE 3

#define START_BYTE_INDEX 0
#define JOYSTICK_X_INDEX 1
#define JOYSTICK_Y_INDEX 2
#define JOYSTICK2_X_INDEX 3
#define JOYSTICK2_Y_INDEX 4
#define END_BYTE_INDEX 5

#define FRONT_INDEX 0
#define RIGHT_INDEX 1
#define BACK_INDEX 2
#define LEFT_INDEX 3

#define LIFT_MOTOR_INDEX 1

#define START_BYTE 60.0

extern int data_to_send[SEND_DATA_BUFFER_SIZE];

extern bool connected;

extern int connection_counter;

extern bool credentials_checked;

extern bool ack;