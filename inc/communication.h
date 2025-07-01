#include "main.h"
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

/// @brief Конвертирует статус регистра в читабельное сообщение и отправляет его
/// @param status Статус регистра
/// @param reg Название регистра
void log_register(HAL_StatusTypeDef status, char *reg, SystemState sys_state, SystemArea sys_area);

/// @brief Отправляет данные в сконфигурированные хранилища информации (память/радио/юарт/т.п.)
/// @param msg Текстовое сообщение
/// @param priority Приоритет сообщения
void send_message(char *msg, Msg_Priority priority);

/// @brief Отправляет данные в сконфигурированные хранилища информации (память/радио/юарт/т.п.)
void log_message(Message* msg);

/// @brief Формирует и отправляет данные фиксированной длины
/// @param status Статус регистра
/// @param reg Название регистра
void log_telemetry(Telemetry* msg);

void send_status(uint8_t status);
