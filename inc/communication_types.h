//Separate from communication.h to avoid dependency on HAL

#ifndef __COMMUNICATION_TYPES_H
#define __COMMUNICATION_TYPES_H

#include "system_types.h"

#define TELEMETRY_BYTES_SIZE 54
static uint16_t TELEMETRY_ID = 69;

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
	double acc_x;
	double acc_y;
	double acc_z;
	GPS_Data gps;
} Telemetry;

void set_default_telemetry(Telemetry* tel);

void telemetry_to_bytes(uint8_t* byte_arr, uint32_t time_ms, Telemetry* tel);
void bytes_to_telemetry(Telemetry* tel, uint32_t* time_ms, uint16_t* received_id, uint8_t* byte_arr);

#endif
