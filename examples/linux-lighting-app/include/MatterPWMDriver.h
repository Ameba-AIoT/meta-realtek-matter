#pragma once

#include "pwm.h"

class MatterPWMDriver
{
public:
    void Init(uint8_t pwm_chip, uint8_t pwm_channel);
    void Deinit();
    void Enable();
    void Disable();
    void SetDutyCycle(const uint8_t &value);

private:
    pwm_t *mPwm;
};