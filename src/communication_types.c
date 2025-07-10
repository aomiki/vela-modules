#include"communication_types.h"
#include <string.h>

void set_default_telemetry(Telemetry *tel)
{
	tel->status = 0;
	tel->crc1 = 0;
	tel->num_pkg = 0;

	tel->mag_x = 0;
	tel->mag_y = 0;
	tel->mag_z = 0;

	tel->acc_x = 0;
	tel->acc_y = 0;
	tel->acc_z = 0;

	tel->gyro_x = 0;
	tel->gyro_y = 0;
	tel->gyro_z = 0;

	tel->adc_c = 0;
	tel->adc_c2 = 0;

	tel->pressure = 0;
	tel->temp = 0;
	tel->humidity = 0;
	tel->altitude = 0;
	tel->gps_latitude = 0;
	tel->gps_longitude = 0;
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
    memcpy(byte_arr,			&TELEMETRY_ID,		2);
    memcpy(byte_arr + 2, 		&tel->status,		1);
    memcpy(byte_arr + 3,		&tel->crc1,			1);
    memcpy(byte_arr + 4,		&time_ms,			4);
    memcpy(byte_arr + 8,		&tel->num_pkg,		2);
    memcpy(byte_arr + 10,		&tel->mag_z,		4);

    memcpy(byte_arr + 14,		&tel->mag_x,		4);
    memcpy(byte_arr + 18,		&tel->mag_y,		4);
    memcpy(byte_arr + 22,		&tel->mag_z,		4);

    memcpy(byte_arr + 28,		&tel->acc_x,		4);
    memcpy(byte_arr + 32,		&tel->acc_y,		4);
    memcpy(byte_arr + 36,		&tel->acc_z,		4);

    memcpy(byte_arr + 40,		&tel->gyro_x,		4);
    memcpy(byte_arr + 44,		&tel->gyro_y,		4);
    memcpy(byte_arr + 48,		&tel->gyro_z,		4);

    memcpy(byte_arr + 52,		&tel->adc_c,		4);
    memcpy(byte_arr + 56,		&tel->adc_c2,		4);

    memcpy(byte_arr + 60,		&tel->pressure,		4);
    memcpy(byte_arr + 64,       &tel->temp,			4);
	memcpy(byte_arr + 68,       &tel->humidity, 	4);
	memcpy(byte_arr + 72,       &tel->altitude,	    4);
	memcpy(byte_arr + 76,       &tel->gps_latitude, 4);
	memcpy(byte_arr + 80,       &tel->gps_longitude,4);
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
    memcpy(&tel->num_pkg,		byte_arr + 2,	2);
    memcpy(time_ms,			byte_arr + 4,	4);
    memcpy(&tel->status,		byte_arr + 8,	1);

    memcpy(&tel->mag_x,			byte_arr + 9,	4);
    memcpy(&tel->mag_y,			byte_arr + 13,	4);
    memcpy(&tel->mag_z,			byte_arr + 17,	4);

    memcpy(&tel->acc_x,			byte_arr + 21,	4);
    memcpy(&tel->acc_y,			byte_arr + 25,	4);
    memcpy(&tel->acc_z,			byte_arr + 29,	4);

    memcpy(&tel->gyro_x,	byte_arr + 33,	4);
    memcpy(&tel->gyro_y,	byte_arr + 37,	4);
    memcpy(&tel->gyro_z,	byte_arr + 41,	4);

    memcpy(&tel->adc_c,	byte_arr + 45,	4);
    memcpy(&tel->adc_c2,	byte_arr + 49,	4);

    memcpy(&tel->pressure,	byte_arr + 53,	4);
    memcpy(&tel->temp,		byte_arr + 57,	4);
	memcpy(&tel->humidity, 	byte_arr + 61,	4);
	memcpy(&tel->altitude, byte_arr + 65,	4);
	memcpy(&tel->gps_latitude, 	byte_arr + 69,	4);
	memcpy(&tel->gps_longitude, byte_arr + 73,	4);
}
