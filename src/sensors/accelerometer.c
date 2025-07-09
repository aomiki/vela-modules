#include "accelerometer.h"
#include <stdint.h>
#include "i2c.h"
#include "usart.h"
#include "communication.h"
#include "string.h"

static const uint8_t dev_address = 0b11010100; //адрес устройства по линии I2C
static const uint32_t timeout_default = 0xFF; //Таймаут, 255 мс

bool check_acc_identity()
{
	uint8_t acc_id;
	log_register(HAL_I2C_Mem_Read(&hi2c1, dev_address, 0x0F, I2C_MEMADD_SIZE_8BIT, &acc_id, 1, timeout_default), "WHO AM I", SYS_STATE_NONE, SYS_AREA_PERIPH_ACC);
	if (acc_id != 0x69)
	{
		char buffer [50] = "ACCELEROMETER READ ERROR\n\r";
		send_message(buffer, PRIORITY_HIGH);
		return false;
	}

	return true;
}

short acc_power_on()
{
	//acc power mode + gyro power mode
	uint8_t sensor_power_mode[2] = {0b01000100, 0b01000100};
	log_register(HAL_I2C_Mem_Write(&hi2c1, dev_address, 0x10, I2C_MEMADD_SIZE_8BIT, sensor_power_mode, 2, timeout_default), "CTRL1_XL CTRL2_G", SYS_STATE_NONE, SYS_AREA_PERIPH_ACC);

	return 0;
}

void read_acceleration_xyz(float* buffer_xyz)
{
	uint8_t raw_val[6];

	log_register(HAL_I2C_Mem_Read(&hi2c1, dev_address, 0x28, I2C_MEMADD_SIZE_8BIT, raw_val, 6, timeout_default), "OUT?_?_XL", SYS_STATE_NONE, SYS_AREA_PERIPH_ACC);

	int16_t x_val = raw_val[1] << 8 | raw_val[0];
	int16_t y_val = raw_val[3] << 8 | raw_val[2];
	int16_t z_val = raw_val[5] << 8 | raw_val[4];

	buffer_xyz[0] = ((float)x_val * 0.488/1000)*9.81;
	buffer_xyz[1] = ((float)y_val * 0.488/1000)*9.81;
	buffer_xyz[2] = ((float)z_val * 0.488/1000)*9.81;
}

void read_acceleration_angular_xyz(float* buffer_xyz)
{
	uint8_t raw_val[6];

	log_register(HAL_I2C_Mem_Read(&hi2c1, dev_address, 0x22, I2C_MEMADD_SIZE_8BIT, raw_val, 6, timeout_default), "OUT?_?_G", SYS_STATE_NONE, SYS_AREA_PERIPH_ACC);

	int16_t x_val = raw_val[1] << 8 | raw_val[0];
	int16_t y_val = raw_val[3] << 8 | raw_val[2];
	int16_t z_val = raw_val[5] << 8 | raw_val[4];

	buffer_xyz[0] = ((float)x_val * 0.488/1000)*9.81;
	buffer_xyz[1] = ((float)y_val * 0.488/1000)*9.81;
	buffer_xyz[2] = ((float)z_val * 0.488/1000)*9.81;
}
