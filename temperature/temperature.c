#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "temperature.h"
#define SENSOR "/sys/bus/w1/devices/28-000000656035/w1_slave"

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

    file = fopen(SENSOR, "r");

    if (file == NULL)
    {
        return -1;
    }

    if (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (find_string(buffer, "crc") && find_string(buffer, "YES"))
        {
            crc = 1;
            sscanf(buffer, "%[^:]", device);
        }
    }

    if (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (crc && find_string(buffer, "t="))
        {
            sscanf(buffer, "%*[^=]=%s", temp);
            return atof(temp) / 1000.0;
        }
    }

    fclose(file);
    
    return 0;
}
