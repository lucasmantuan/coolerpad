
#include <stdio.h>
#include <unistd.h>

#include "temperature/temperature.h"
#include "pwm/pwm.h"
#include "motor/motor.h"

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
        printf("%.3f\n", temperature);

        if (temperature == -1)
        {
            break;
            // return -1;
        }

        if (temperature >= 33)
        {
            temp = 90;
            if (temp != duty)
            {
                speed_transition(duty, temp, 1);
                duty = temp;
            }
        }
        else if (temperature >= 32.6)
        {
            temp = 10;
            if (temp != duty)
            {
                speed_transition(duty, temp, 1);
                duty = temp;
            }
        }

        usleep(50000);
    }

    return 0;
}
