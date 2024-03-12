#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "motor.h"
#include "../pwm/pwm.h"
#define PIN97 "/sys/class/gpio/gpio97/"

int turn_on()
{
    FILE *pin = fopen(PIN97 "value", "w");

    fprintf(pin, "%d", 1);
    fclose(pin);

    return 0;
}

int turn_off()
{
    FILE *pin = fopen(PIN97 "value", "w");

    fprintf(pin, "%d", 0);
    fclose(pin);

    return 0;
}

int speed_control(int period, int duty)
{
    pwm_disable();
    pwm_period(period);
    pwm_duty(duty);
    pwm_enable();

    return 0;
}

int speed_transition(int initial, int final, int time)
{
    int step_value = 1;
    int steps = abs((initial - final) / step_value);

    if (initial <= final)
    {
        for (int i = initial; i <= final; i += step_value)
        {
            pwm_duty(i);
            usleep(time * 1000000 / steps);
        }
    }
    else
    {
        for (int i = initial; i >= final; i -= step_value)
        {
            pwm_duty(i);
            usleep(time * 1000000 / steps);
        }
    }

    return 0;
}
