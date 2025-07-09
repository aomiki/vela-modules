#include"communication_types.h"
#include <string.h>

void set_default_telemetry(Telemetry *tel)
{
	tel->sys_state = SYS_STATE_NONE;
	tel->sys_area = SYS_AREA_NONE;
	tel->sys_status = 0;

	tel->acc_x = 0;
	tel->acc_y = 0;
	tel->acc_z = 0;

	tel->acc_angular_x = 0;
	tel->acc_angular_y = 0;
	tel->acc_angular_z = 0;

	tel->pressure = 0;
	tel->temp = 0;
	tel->altitude = 0;

	tel->gps.altitude = 0;
	tel->gps.latitude = 0;
	tel->gps.longitude = 0;
	tel->gps.fix_status = 0;
	tel->gps.satellites = 0;
}

// У телеметрии такое байтовое представление:
// ┌───────┬─────┬───────────┬───────┬──────┬─────────────┬──────────┬────────┬────────┬────────┬─────────┬─────────┬─────────┬───────────────┬──────────┬────────────────┬─────────────────┬────────────────┬──────────────────┬──────────────────┐
// │ BYTES │ 0-1 │ 2-4       │ 5     │ 6    │ 7-10        │ 11-14    │ 15-18  │ 19-22  │ 23-26  │ 27-30   │ 31-34   │ 35-38   │ 39            │ 40-43    │ 44-47          │ 48-51           │ 52-55          │ 56               │ 57               │
// ├───────┼─────┼───────────┼───────┼──────┼─────────────┼──────────┼────────┼────────┼────────┼─────────┼─────────┼─────────┼───────────────┼──────────┼────────────────┼─────────────────┼────────────────┼──────────────────┼──────────────────┤
// │ VALUE │ id  │ time (ms) │ state │ area │ temperature │ pressure │ acc: x │ acc: y │ acc: z │ gyro: x │ gyro: y │ gyro: z │ system status │ altitude │ (gps) altitude │ (gps) longitude │ (gps) latitude │ (gps) fix status │ (gps) satellites │
// └───────┴─────┴───────────┴───────┴──────┴─────────────┴──────────┴────────┴────────┴────────┴─────────┴─────────┴─────────┴───────────────┴──────────┴────────────────┴─────────────────┴────────────────┴──────────────────┴──────────────────┘
/**
 * @brief Конвертирует телеметрию \p tel и время \p time_ms в массив байтов \p byte_arr 
 * @param[out] byte_arr Результирующий массив байтов
 * @param[in] time_ms Время для конвертации
 * @param[in] tel Телеметрия для конвертации
 */
void telemetry_to_bytes(uint8_t* byte_arr, uint32_t time_ms, Telemetry* tel)
{
	memcpy(byte_arr, 		&TELEMETRY_ID, 		2);
	memcpy(byte_arr + 2,	&time_ms,			4); //4 bytes
	memcpy(byte_arr + 5, 	&tel->sys_state, 	1);
	memcpy(byte_arr + 6, 	&tel->sys_area, 	1);
	memcpy(byte_arr + 7, 	&tel->temp, 		4);
	memcpy(byte_arr + 11, 	&tel->pressure, 	4);
	memcpy(byte_arr + 15, 	&tel->acc_x, 		4);
	memcpy(byte_arr + 19, 	&tel->acc_y, 		4);
	memcpy(byte_arr + 23, 	&tel->acc_z, 		4);
	memcpy(byte_arr + 27, 	&tel->acc_angular_x,4);
	memcpy(byte_arr + 31, 	&tel->acc_angular_y,4);
	memcpy(byte_arr + 35, 	&tel->acc_angular_z,4);
	memcpy(byte_arr + 39, 	&tel->sys_status, 	1);
	memcpy(byte_arr + 40, 	&tel->altitude, 	4);

	memcpy(byte_arr + 44, 	&tel->gps.altitude,  4);
	memcpy(byte_arr + 48, 	&tel->gps.longitude, 4);
	memcpy(byte_arr + 52, 	&tel->gps.latitude,  4);
	memcpy(byte_arr + 56, 	&tel->gps.fix_status,  1);
	memcpy(byte_arr + 57, 	&tel->gps.satellites,  1);
}

/**
 * @brief Конвертирует массив байтов \p byte_arr в телеметрию \p tel и время \p time_ms
 * @param[out] byte_arr Массив байтов для конвертации
 * @param[in] time_ms Результирующее время
 * @param[in] tel Результирующая телеметрия
 */
void bytes_to_telemetry(Telemetry* tel, uint32_t* time_ms, uint16_t* received_id, uint8_t* byte_arr)
{
    memcpy(received_id,			byte_arr,		2);
    memcpy(time_ms,				byte_arr + 2,	4);
    memcpy(&tel->sys_state,		byte_arr + 5,	1);
    memcpy(&tel->sys_area,		byte_arr + 6,	1);
    memcpy(&tel->temp,			byte_arr + 7,	4);
    memcpy(&tel->pressure,		byte_arr + 11,	4);
    memcpy(&tel->acc_x,			byte_arr + 15,	4);
    memcpy(&tel->acc_y,			byte_arr + 19,	4);
    memcpy(&tel->acc_z,			byte_arr + 23,	4);
    memcpy(&tel->acc_angular_x,	byte_arr + 27,	4);
    memcpy(&tel->acc_angular_y,	byte_arr + 31,	4);
    memcpy(&tel->acc_angular_z,	byte_arr + 35,	4);
    memcpy(&tel->sys_status,	byte_arr + 39,	1);
    memcpy(&tel->altitude,		byte_arr + 40,	4);

	memcpy(&tel->gps.altitude, 	byte_arr + 44,	4);
	memcpy(&tel->gps.longitude, byte_arr + 48,	4);
	memcpy(&tel->gps.latitude, 	byte_arr + 52,	4);
	memcpy(&tel->gps.fix_status, byte_arr + 56,	1);
	memcpy(&tel->gps.satellites, byte_arr + 57,	1);
}
