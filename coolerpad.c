
#include <stdio.h>
#include <unistd.h>

#include "temperature.h"
#include "pwm.h"
#include "motor.h"

int main()
{
    int period = 100;
    int duty = 50;
    int temp = 0;

    pwm_disable();
    pwm_period(period);
    pwm_duty(duty);
    pwm_enable();

    while (1)
    {
        float temperature = read_temperature();

        if (temperature == -1)
        {
            break;
            // return -1;
        }

        if (temperature >= 31)
        {
            temp = 90;
            if (temp != duty)
            {
                speed_transition(duty, temp, 1);
                duty = temp;
            }
        }
        else if (temperature >= 30.5)
        {
            temp = 10;
            if (temp != duty)
            {
                speed_transition(duty, temp, 1);
                duty = temp;
            }
        }

        printf("%.3f\n", temperature);
        usleep(50000);
    }

    return 0;
}
