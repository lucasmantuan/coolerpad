#include <stdio.h>
#include <stdlib.h>

#include "pwm.h"

#define PWM "/sys/class/pwm/pwmchip0/pwm0/"

int pwm_enable()
{
    FILE *enable = fopen(PWM "enable", "w");

    if (enable == NULL)
    {
        return EXIT_FAILURE;
    }

    fprintf(enable, "%d", 1);
    fclose(enable);

    return EXIT_SUCCESS;
}

int pwm_disable()
{
    FILE *enable = fopen(PWM "enable", "w");

    if (enable == NULL)
    {
        return EXIT_FAILURE;
    }

    fprintf(enable, "%d", 0);
    fclose(enable);

    return EXIT_SUCCESS;
}

int new_period = 0;
int new_duty = 0;

int pwm_period(int *value)
{
    FILE *period = fopen(PWM "period", "w");

    if (period == NULL)
    {
        return EXIT_FAILURE;
    }

    // converte de milissegundos  para nanossegundos
    new_period = (*value) * 1000000;

    fprintf(period, "%d", new_period);
    fclose(period);

    return EXIT_SUCCESS;
}

int pwm_duty(int *value)
{
    FILE *duty = fopen(PWM "duty_cycle", "w");

    if (duty == NULL)
    {
        return EXIT_FAILURE;
    }

    // converte de percentual para nanossegundos
    new_duty = ((new_period * (*value)) / 100) * 1000000;

    fprintf(duty, "%d", new_duty);
    fclose(duty);

    return EXIT_SUCCESS;
}