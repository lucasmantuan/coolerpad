#include "pwm.h"

#include <stdio.h>
#include <stdlib.h>

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

// int pwm_period(int *value) 
// {
//     FILE *period = fopen(PWM "period", "w");

//     if (period == NULL)
//     {
//         return EXIT_FAILURE;
//     }

//     int new_value = value * 1000000;
    
//     fprintf(period, "%d", new_value);
//     fclose(period);

//     return EXIT_SUCCESS;
// }

// int pwm_duty(int *value) 
// {
//     FILE *duty_cycle = fopen(PWM "duty_cycle", "w");

//     if (duty_cycle == NULL)
//     {
//         return EXIT_FAILURE;
//     }

//     int new_value = value * 1000000;
    
//     fprintf(duty_cycle, "%d", new_value);
//     fclose(duty_cycle);

//     return EXIT_SUCCESS;
// }

