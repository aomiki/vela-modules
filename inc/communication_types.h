//Separate from communication.h to avoid dependency on HAL

#ifndef __COMMUNICATION_TYPES_H
#define __COMMUNICATION_TYPES_H

#include "system_types.h"

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
	status_t sys_status;
	float temp;
	float pressure;
	double acc_x;
	double acc_y;
	double acc_z;
} Telemetry;

void set_default_telemetry(Telemetry* tel);

#endif
