
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "temperature/temperature.h"
#include "motor/motor.h"
#include "pwm/pwm.h"

void handle_signal(int signal)
{
    speed_control(5.0, 0);
    turn_off();

    exit(0);
}

int main()
{
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGKILL, handle_signal);

    // FILE *log = fopen("/var/www/html/log.txt", "w");
    float temperature = 0.0;
    float period = 5.0;
    int old_duty = 0;
    int new_duty = 0;

    turn_on();

    while (1)
    {
        temperature = read_temperature();

        // fprintf(log, "%.3f\n", temperature);
        printf("%.3f\n", temperature);

        if (temperature == -1)
        {
            break;
            // return -1;
        }

        // acima de 37
        if (temperature >= 37)
        {
            new_duty = 100;
            if (new_duty != old_duty)
            {
                speed_control(period, old_duty);
                speed_transition(old_duty, new_duty, 3);
                old_duty = new_duty;
            }
        }
        // de 35 até 36.9
        else if (temperature >= 35)
        {
            new_duty = 80;
            if (new_duty != old_duty)
            {
                speed_control(period, old_duty);
                speed_transition(old_duty, new_duty, 3);
                old_duty = new_duty;
            }
        }
        // de 33 até 34.9
        else if (temperature >= 33)
        {
            new_duty = 60;
            if (new_duty != old_duty)
            {
                speed_control(period, old_duty);
                speed_transition(old_duty, new_duty, 3);
                old_duty = new_duty;
            }
        }
        // de 31 até 32.9
        else if (temperature >= 31)
        {
            new_duty = 40;
            if (new_duty != old_duty)
            {
                speed_control(period, old_duty);
                speed_transition(old_duty, new_duty, 3);
                old_duty = new_duty;
            }
        }
        // até 30.9
        else if (temperature >= 0)
        {
            new_duty = 0;
            if (new_duty != old_duty)
            {
                speed_control(period, new_duty);
                old_duty = new_duty;
            }
        }

        // fflush(log);
        sleep(10);
    }

    return 0;
}
