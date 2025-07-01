#include <stdint.h>

// Current mapping:
// ┌───────────────┬───────┬───────┬─────────┬───────────────┬───────────┬─────┐
// │ bits ( = LED) │ 1     │ 2     │ 3       │ 4             │ 5         │ 6   │
// ├───────────────┼───────┼───────┼─────────┼───────────────┼───────────┼─────┤
// │ sensor        │ servo │ radio │ sd card │ accelerometer │ barometer │ gps │
// └───────────────┴───────┴───────┴─────────┴───────────────┴───────────┴─────┘

void status_barometer_responds(uint8_t* status);
void status_acc_responds(uint8_t* status);
void status_radio_responds(uint8_t* status);
void status_servo_responds(uint8_t* status);
void status_sd_mounts(uint8_t* status);
void status_gps_responds(uint8_t* status);
