
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
    int duty = 30;
    int temp = 0;
    
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

        // acima de 35 graus
        if (temperature >= 35)
        {
            temp = 100;
            if (temp != duty)
            {
                speed_control(period, duty);
                speed_transition(duty, temp, 2);
                duty = temp;
            }
        }
        // entre 33 e 34.9 graus
        else if (temperature >= 33)
        {
            temp = 80;
            if (temp != duty)
            {
                speed_control(period, duty);
                speed_transition(duty, temp, 2);
                duty = temp;
            }
        }
        // entre 31 e 32.9 graus
        else if (temperature >= 31)
        {
            temp = 60;
            if (temp != duty)
            {
                speed_control(period, duty);
                speed_transition(duty, temp, 2);
                duty = temp;
            }
        }
        // até 30.9 graus
        else if (temperature >= 0)
        {
            temp = 0;
            if (temp != duty)
            {
                speed_control(period, temp);
                duty = temp;
            }
        }

        fflush(log);
        sleep(2);
    }

    fclose(log);
    return 0;
}
