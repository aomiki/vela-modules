//Separate from communication.h to avoid dependency on HAL

#ifndef __COMMUNICATION_TYPES_H
#define __COMMUNICATION_TYPES_H

#include "system_types.h"

#define TELEMETRY_BYTES_SIZE 78
static uint16_t TELEMETRY_ID = 0b0011100001011010; //Z8 team code

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
	uint8_t status;
	uint8_t crc1;
	uint16_t num_pkg;
	float mag_x;
	float mag_y;
	float mag_z;

	float acc_x;
	float acc_y;
	float acc_z;

	float gyro_x;
	float gyro_y;
	float gyro_z;

	float adc_c;
	float adc_c2;

	float pressure;
	float temp;
	float humidity;
	float altitude;
	float gps_latitude;
	float gps_longitude;
} Telemetry;

void set_default_telemetry(Telemetry* tel);

void telemetry_to_bytes(uint8_t* byte_arr, uint32_t time_ms, Telemetry* tel);
void bytes_to_telemetry(Telemetry* tel, uint32_t* time_ms, uint16_t* received_id, uint8_t* byte_arr);

#endif
