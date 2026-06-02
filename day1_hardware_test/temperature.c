#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

#define PCF8591_ADDR    0x48


int temp_read(int arg)
{
    int a2dChannel = 1;
    wiringPiI2CWrite(arg, 0x00 | a2dChannel);
    wiringPiI2CRead(arg);
    return wiringPiI2CRead(arg);
}

float convert_temp(int val)
{
    return (val / 10.17); 
}

int main()
{
    int fd;
    wiringPiSetup();

    fd = wiringPiI2CSetup(PCF8591_ADDR);
    if(fd == -1)
    {
        perror("error");
        exit(1);
    }

    while(1)
    {
        int val = temp_read(fd);
        float temp = convert_temp(val);
        printf("온도 센서 값: %d / 온도: %.1f°C\n", val, temp);
        delay(1000);
    }

    return 0;
}