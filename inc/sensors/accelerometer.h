#include <stdbool.h>

/// @brief Делает тестовый запрос к устройству
/// @returns Возвращает 1 если ответило правильное устройство, 0 иначе
bool check_acc_identity();

/// @brief Устанавливает режим работы в устройство
short acc_power_on();

/// @brief Возвращает ускорение по трем осям
/// @param xyz массив из трех значений, в котором будет хранится ускорение по осям x,y,z соответственно
void read_acceleration_xyz(float* buffer_xyz);

void read_acceleration_angular_xyz(float* buffer_xyz);
