#ifndef BUZZER
#define BUZZER

#include "main.h"

void buzzer_set_freq(uint32_t freq_hz); // 2000
void buzzer_start();
void buzzer_stop();

#endif