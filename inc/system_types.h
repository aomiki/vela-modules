//Shouldn't have dependency on HAL

#ifndef __SYSTEM_TYPES_H
#define __SYSTEM_TYPES_H

#include "stdint.h"

typedef enum
{
	SYS_AREA_NONE,
	SYS_AREA_INIT,
	SYS_AREA_MAIN_ALGO,
	SYS_AREA_READ_SENSORS,
	SYS_AREA_PERIPH_SDCARD,
	SYS_AREA_PERIPH_RADIO,
	SYS_AREA_PERIPH_BAROM,
	SYS_AREA_PERIPH_ACC

} SystemArea;

typedef enum {
    PERIPH_BAROM = 1,
    PERIPH_ACC = 1 << 1,
    PERIPH_SD = 1 << 2,
    PERIPH_RADIO = 1 << 3,
	PERIPH_GPS = 1 << 4,
	PERIPH_SERVO = 1 << 5,
	PERIPH_JUMPER = 1 << 6
} Peripheral;

typedef enum
{
	SYS_STATE_NONE = 0,
	SYS_STATE_INIT,
	SYS_STATE_STANDBY,
	SYS_STATE_LIFTOFF,
	SYS_STATE_ASCENT,
	SYS_STATE_APOGY,
	SYS_STATE_DESCENT,
	SYS_STATE_GROUND
} SystemState;

#define status_t uint8_t

#endif
