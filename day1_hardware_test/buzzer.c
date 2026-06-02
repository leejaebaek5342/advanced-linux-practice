#include <wiringPi.h>
#include <softTone.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SPKR    3
#define TOTAL   32

int notes[] = {
    391, 391, 440, 440, 391, 391, 329, 329,
    391, 391, 329, 329, 293, 293, 293, 0,
    391, 391, 440, 440, 391, 391, 329, 329,
    391, 329, 293, 329, 261, 261, 261, 0
};

void buzzer_on()
{
    softToneCreate(SPKR);
    for(int i = 0; i < TOTAL; i++)
    {
        softToneWrite(SPKR, notes[i]);
        delay(280);
    }
}

void buzzer_off()
{
    softToneWrite(SPKR, 0);
}

int main(int argc, char** argv)
{
    wiringPiSetup();

    if(argc != 2)
    {
        printf("USAGE: ./buzzer [ON/OFF]\n");
        exit(1);
    }

    if(strcmp(argv[1], "ON") == 0)
        buzzer_on();
    else if(strcmp(argv[1], "OFF") == 0)
        buzzer_off();
    else
    {
        printf("잘못된 입력입니다: %s\n", argv[1]);
        exit(1);
    }

    return 0;
}