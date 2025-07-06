#include "tim.h"
#include "buzzer.h"

void buzzer_set_freq(uint32_t freq_hz) {
    uint32_t clock = HAL_RCC_GetPCLK1Freq();
    uint32_t prescaler = BUZZER_TIM_HANDLE.Instance->PSC;
    uint32_t period = (clock / ((prescaler + 1) * freq_hz)) - 1;

    __HAL_TIM_SET_PRESCALER(&BUZZER_TIM_HANDLE, prescaler);
    __HAL_TIM_SET_AUTORELOAD(&BUZZER_TIM_HANDLE, period);
    __HAL_TIM_SET_COMPARE(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL, period / 2);
}

void buzzer_start() {
    HAL_TIM_PWM_Start(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL);
}

void buzzer_stop() {
    HAL_TIM_PWM_Stop(&BUZZER_TIM_HANDLE, BUZZER_TIM_CHANNEL);
}