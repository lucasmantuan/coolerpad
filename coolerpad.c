
#include <stdio.h>
#include <unistd.h>

#include "temperature/temperature.h"
#include "motor/motor.h"
#include "pwm/pwm.h"

int main()
{
    int period = 100;
    int duty = 60;
    int temp = 0;

    turn_off();
    pwm_disable();

    pwm_period(period);
    pwm_duty(duty);
    pwm_enable();

    forward();

    while (1)
    {
        float temperature = read_temperature();
        printf("%.3f\n", temperature);

        if (temperature == -1)
        {
            break;
            // return -1;
        }

        if (temperature >= 30)
        {
            temp = 100;
            if (temp != duty)
            {
                forward();
                speed_transition(duty, temp, 1);
                duty = temp;
            }
        }
        else if (temperature >= 29)
        {
            temp = 40;
            if (temp != duty)
            {
                forward();
                speed_transition(duty, temp, 1);
                duty = temp;
            }
        }
        else if (temperature >= 28)
        {
            temp = 20;
            if (temp != duty)
            {
                forward();
                speed_transition(duty, temp, 1);
                duty = temp;
                turn_off();
            }
        }

        sleep(2);
    }

    return 0;
}
