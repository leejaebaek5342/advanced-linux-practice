#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

#define PCF8591_ADDR 0x48

int cds_read(int arg)
{
    int a2dChannel = 0;
    wiringPiI2CWrite(arg,0x00 | a2dChannel);
    delay(10);
    wiringPiI2CRead(arg);
    return wiringPiI2CRead(arg);
}

int main()
{
    int val,fd;
    wiringPiSetup();
    fd = wiringPiI2CSetup(PCF8591_ADRR);

    if(fd == -1)
    {
        perror("error");
        exit(1);
    }
    while(1)
    {
        val = cds_read(fd);
        printf("PCF8591 조도센서 측정값: %d\n",val);
        delay(1000);
    }

    return 0;
}