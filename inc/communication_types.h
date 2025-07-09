//Separate from communication.h to avoid dependency on HAL

#ifndef __COMMUNICATION_TYPES_H
#define __COMMUNICATION_TYPES_H

#include "system_types.h"

#define TELEMETRY_BYTES_SIZE 58
static uint16_t TELEMETRY_ID = 0b0011011001010010; //R6 team code

#define TELEMETRY_ID_UPPER (TELEMETRY_ID & 0xFF)
#define TELEMETRY_ID_LOWER ((TELEMETRY_ID >> 8) & 0xFF)

typedef enum
{
	PRIORITY_DEBUG,
	PRIORITY_LOW,
	PRIORITY_MEDIUM,
	PRIORITY_HIGH
} Msg_Priority;

typedef struct {
	SystemState sys_state;
	SystemArea sys_area;
	Msg_Priority priority;
	char *text;
} Message;

typedef struct {
	SystemState sys_state;
	SystemArea sys_area;
	Peripheral sys_status;
	float temp;
	float altitude;
	float pressure;
	float acc_x;
	float acc_y;
	float acc_z;
	float acc_angular_x;
	float acc_angular_y;
	float acc_angular_z;
	GPS_Data gps;
} Telemetry;

void set_default_telemetry(Telemetry* tel);

void telemetry_to_bytes(uint8_t* byte_arr, uint32_t time_ms, Telemetry* tel);
void bytes_to_telemetry(Telemetry* tel, uint32_t* time_ms, uint16_t* received_id, uint8_t* byte_arr);

#endif
