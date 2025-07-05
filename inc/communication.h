#include "system_types.h"
#include "communication_types.h"
#include "main.h"

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

void send_status(Peripheral status);
