#include "mbed.h"
DigitalOut led[3] = {LED1,LED2,LED3};

Timer timer;
int main()
{   
    printf("LAB 1\r\n"); 
    

    while(1) {
        led[2].write(0);
        led[0].write(1);
        wait_us(100000);
        led[0].write(0);
        led[1].write(1);
        wait_us(100000);
        led[1].write(0);
        led[2].write(1);
        wait_us(100000);
        
    }
}