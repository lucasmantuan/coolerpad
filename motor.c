#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "motor.h"
#include "pwm.h"

void speed_transition(int initial, int final, int time)
{

    int steps = abs((initial - final) / 10);
    int step_value = 10;

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
}
