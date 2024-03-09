
#include <stdio.h>
#include <unistd.h>

#include "temperature/temperature.h"
#include "motor/motor.h"
#include "pwm/pwm.h"

int main()
{
    FILE *log = fopen("/var/www/html/log.txt", "w");

    float temperature = 0.0;

    float period = 5;
    int duty = 20;
    int temp = 0;

    // turn_off();
    // pwm_disable();
    // pwm_period(period);
    // pwm_duty(duty);
    // pwm_enable();
    // forward();

    while (1)
    {
        temperature = read_temperature();

        fprintf(log, "%.3f\n", temperature);
        printf("%.3f\n", temperature);

        if (temperature == -1)
        {
            break;
            // return -1;
        }

        // acima de 30 graus
        if (temperature >= 30)
        {
            temp = 100;
            if (temp != duty)
            {
                forward();
                speed_transition(duty, temp, 5);
                duty = temp;
            }
        }
        // entre 29 e 29.9 graus
        else if (temperature >= 29)
        {
            temp = 40;
            if (temp != duty)
            {
                forward();
                speed_transition(duty, temp, 5);
                duty = temp;
            }
        }
        // até 28.9 graus
        else if (temperature >= 0)
        {
            temp = 20;
            if (temp != duty)
            {
                forward();
                speed_transition(duty, temp, 5);
                turn_off();
                duty = temp;
            }
        }

        fflush(log);
        sleep(2);
    }

    fclose(log);
    return 0;
}
