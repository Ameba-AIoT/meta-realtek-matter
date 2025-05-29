#include "MatterPWMDriver.h"
#include <lib/support/logging/CHIPLogging.h>

void MatterPWMDriver::Init(uint8_t pwm_chip, uint8_t pwm_channel)
{
    mPwm = pwm_new();

    /* Open PWM chip, and channel */
    if (pwm_open(mPwm, pwm_chip, pwm_channel) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_open(): %s\n", pwm_errmsg(mPwm));
    }

    /* Set frequency to 1 kHz */
    if (pwm_set_frequency(mPwm, 1e3) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_set_frequency(): %s\n", pwm_errmsg(mPwm));
    }

    /* Set duty cycle to 0% */
    if (pwm_set_duty_cycle(mPwm, 0.0l) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_set_duty_cycle(): %s\n", pwm_errmsg(mPwm));
    }

    /* Set polarity to normal */
    if (pwm_set_polarity(mPwm, PWM_POLARITY_NORMAL) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_set_polarity(): %s\n", pwm_errmsg(mPwm));
    }
}

void MatterPWMDriver::Deinit()
{
    /* Close PWM */
    if (pwm_close(mPwm) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_close(): %s\n", pwm_errmsg(mPwm));
    }

    /* Free PWM */
    pwm_free(mPwm);
}

void MatterPWMDriver::Enable()
{
    /* Enable PWM */
    if (pwm_enable(mPwm) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_enable(): %s\n", pwm_errmsg(mPwm));
    }
}

void MatterPWMDriver::Disable()
{
    /* Disable PWM */
    if (pwm_disable(mPwm) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_disable(): %s\n", pwm_errmsg(mPwm));
    }
}

void MatterPWMDriver::SetDutyCycle(const uint8_t &value)
{
    uint8_t max_level = UINT8_MAX;

    // Percentage duty cycle range from 0.0 to 1.0
    double percent_duty_cycle = (double)value / (double)max_level;

    /* Change duty cycle */
    if (pwm_set_duty_cycle(mPwm, percent_duty_cycle) < 0)
    {
        ChipLogError(DeviceLayer, "pwm_set_duty_cycle(): %s\n", pwm_errmsg(mPwm));
    }
}