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

	tel->pressure = 0;
	tel->temp = 0;
	tel->altitude = 0;
}

// У телеметрии такое байтовое представление:
// ┌───────┬───────────┬───────┬──────┬─────────────┬──────────┬────────┬────────┬────────┬───────────────┐
// │ BYTES │ 0-3       │ 4     │ 5    │ 6-9         │ 10-13    │ 14-21  │ 22-29  │ 30-37  │ 38            │39-42
// ├───────┼───────────┼───────┼──────┼─────────────┼──────────┼────────┼────────┼────────┼───────────────┤
// │ VALUE │ time (ms) │ state │ area │ temperature │ pressure │ acc: x │ acc: y │ acc: z │ system status │altitude
// └───────┴───────────┴───────┴──────┴─────────────┴──────────┴────────┴────────┴────────┴───────────────┘

/** 
 * @brief Конвертирует телеметрию \p tel и время \p time_ms в массив байтов \p byte_arr 
 * @param[out] byte_arr Результирующий массив байтов
 * @param[in] time_ms Время для конвертации
 * @param[in] tel Телеметрия для конвертации
 */
void telemetry_to_bytes(uint8_t* byte_arr, uint32_t time_ms, Telemetry* tel)
{
	memcpy(byte_arr, &time_ms, 4); //4 bytes
	memcpy(byte_arr + 3, 	&tel->sys_state, 	1);
	memcpy(byte_arr + 4, 	&tel->sys_area, 	1);
	memcpy(byte_arr + 5, 	&tel->temp, 		4);
	memcpy(byte_arr + 9, 	&tel->pressure, 	4);
	memcpy(byte_arr + 13, 	&tel->acc_x, 		8);
	memcpy(byte_arr + 21, 	&tel->acc_y, 		8);
	memcpy(byte_arr + 29, 	&tel->acc_z, 		8);
	memcpy(byte_arr + 37, 	&tel->sys_status, 	1);
	memcpy(byte_arr + 38, 	&tel->altitude, 	4);
}

/**
 * @brief Конвертирует массив байтов \p byte_arr в телеметрию \p tel и время \p time_ms
 * @param[out] byte_arr Массив байтов для конвертации
 * @param[in] time_ms Результирующее время
 * @param[in] tel Результирующая телеметрия
 */
void bytes_to_telemetry(Telemetry* tel, uint32_t* time_ms, uint8_t* byte_arr)
{
    memcpy(time_ms,                byte_arr,        4);
    memcpy(&tel->sys_state,      byte_arr + 3,    1);
    memcpy(&tel->sys_area,       byte_arr + 4,    1);
    memcpy(&tel->temp,           byte_arr + 5,    4);
    memcpy(&tel->pressure,       byte_arr + 9,    4);
    memcpy(&tel->acc_x,          byte_arr + 13,   8);
    memcpy(&tel->acc_y,          byte_arr + 21,   8);
    memcpy(&tel->acc_z,          byte_arr + 29,   8);
    memcpy(&tel->sys_status,     byte_arr + 37,   1);
    memcpy(&tel->altitude,       byte_arr + 38,   4);
}
