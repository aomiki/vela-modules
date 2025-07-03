#include"communication_types.h"

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
}
