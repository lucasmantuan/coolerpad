
#include <stdio.h>
#include <unistd.h>

#include "temperature.h"
#include "pwm.h"

int main()
{
    pwm_enable();

    float new_temperature = read_temperature();
    printf("%.3f\n", new_temperature);
}
