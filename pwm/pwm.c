#include <stdio.h>

#include "pwm.h"

#define PWM "/sys/class/pwm/pwmchip0/pwm0/"

int pwm_enable()
{
    FILE *enable = fopen(PWM "enable", "w");

    if (enable == NULL)
    {
        return -1;
    }

    fprintf(enable, "%d", 1);
    fclose(enable);

    return 0;
}

int pwm_disable()
{
    FILE *enable = fopen(PWM "enable", "w");

    if (enable == NULL)
    {
        return -1;
    }

    fprintf(enable, "%d", 0);
    fclose(enable);

    return 0;
}

long new_period = 0;
long new_duty = 0;

int pwm_period(int value)
{
    FILE *period = fopen(PWM "period", "w");

    if (period == NULL)
    {
        return -1;
    }

    // converte de milissegundos para nanossegundos
    new_period = value * 100000;

    fprintf(period, "%ld", new_period);
    fclose(period);

    return 0;
}

int pwm_duty(int value)
{
    FILE *duty = fopen(PWM "duty_cycle", "w");

    if (duty == NULL)
    {
        return -1;
    }

    // converte de percentual para nanossegundos
    new_duty = (new_period * value) / 100;

    fprintf(duty, "%ld", new_duty);
    fclose(duty);

    return 0;
}