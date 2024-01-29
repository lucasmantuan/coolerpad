#include "temperature.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SENSOR "/sys/bus/w1/devices/28-3c01e076c2a0/w1_slave"

int find_string(const char *str, const char *substr)
{
    return (strstr(str, substr) != NULL);
}

float read_temperature() 
{
    FILE *file;
    char buffer[256];
    char device[20];
    char temp[10];
    int crc = 0;
    int attempts = 0;

    while(1) 
    {
        file = fopen(SENSOR, "r");

        if (file != NULL)
        {
            break;
        }

        if (++attempts >= 6) 
        {
            return EXIT_FAILURE;
        }

        sleep(3);
    }


    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (find_string(buffer, "crc") && find_string(buffer, "YES"))
        {
            crc = 1;
            sscanf(buffer, "%[^:]", device);
        }

        if (crc && find_string(buffer, "t="))
        {
            sscanf(buffer, "%*[^=]=%s", temp);
            return atof(temp) / 1000.0;
        }
    }

    fclose(file);

    return EXIT_SUCCESS;
}
