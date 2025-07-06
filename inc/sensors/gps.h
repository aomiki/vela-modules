#ifndef _GPS
#define _GPS

#include "system_types.h"
#include <stdint.h>
#include <stdbool.h>

#define GPS_BUFFER_SIZE 128

bool GPS_Init();
void GPS_UART_Callback();
GPS_Data* GPS_GetData();

#endif
