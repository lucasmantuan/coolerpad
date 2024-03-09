#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "motor.h"
#include "../pwm/pwm.h"

#define PIN_IN1 "/sys/class/gpio/gpio99/"
#define PIN_IN2 "/sys/class/gpio/gpio101/"

/*
Motor A             IN1     IN2
Sentido Direto      High    Low
Sentido Reverso     Low     High
Freio               Low     Low
Freio               High    High
*/

int backward()
{
    FILE *in1 = fopen(PIN_IN1 "value", "w");
    FILE *in2 = fopen(PIN_IN2 "value", "w");

    if (in1 == NULL && in2 == NULL)
    {
        return -1;
    }

    fprintf(in1, "%d", 0);
    fprintf(in2, "%d", 1);

    fclose(in1);
    fclose(in2);

    return 0;
}

int forward()
{
    FILE *in1 = fopen(PIN_IN1 "value", "w");
    FILE *in2 = fopen(PIN_IN2 "value", "w");

    if (in1 == NULL && in2 == NULL)
    {
        return -1;
    }

    fprintf(in1, "%d", 1);
    fprintf(in2, "%d", 0);

    fclose(in1);
    fclose(in2);

    return 0;
}

int turn_off()
{
    FILE *in1 = fopen(PIN_IN1 "value", "w");
    FILE *in2 = fopen(PIN_IN2 "value", "w");

    if (in1 == NULL && in2 == NULL)
    {
        return -1;
    }

    fprintf(in1, "%d", 0);
    fprintf(in2, "%d", 0);

    fclose(in1);
    fclose(in2);

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
