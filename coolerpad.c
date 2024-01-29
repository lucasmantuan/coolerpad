#include "temperature.h"
#include "pwm.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    float old_temperature, new_temperature;

    pwm_enable();

    while (1)
    {
        new_temperature = read_temperature();

        if (old_temperature != new_temperature)
        {
            old_temperature = new_temperature;
            printf("%.3f\n", new_temperature);
        }

        sleep(1);
    }
}
