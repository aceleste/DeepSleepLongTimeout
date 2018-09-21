#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);

time_t target_fire_time;

bool timeout;

LowPowerTicker halfminute;

void checkRTCTimeout()
{
    timeout = false;
    time_t now = time(NULL);
    led2 = !led2;
    if ( now >= target_fire_time ) timeout = true;
}

int main()
{
    led1 = 1; // LED is ON
    led2 = 0; // LED is ON
    target_fire_time = time(NULL) + 180;
    halfminute.attach(&checkRTCTimeout, 30); /* will tick every 30 seconds */ 
    while(1) {
        while(!timeout) {
            sleep();
        }
        led1 = !led1; /* toggle led */
        target_fire_time = time(NULL) + 180; /* set timeout to 3 minutes */
        timeout = false;
    }
}
