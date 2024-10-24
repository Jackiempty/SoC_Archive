#include "mbed.h"

DigitalIn  button(BUTTON1); //the button on your board
DigitalOut led[3] = {LED1,LED2,LED3};

int main()
{   
    printf("Lab2\n");
    int i = 1;
    int state = 0;
    button.mode(PullNone);
    while(1) {
        state = button.read();
        if(state == 0)
        {   
            i = !i;
            while(!state&&i) {
                led[2].write(0);
                led[0].write(1);
                wait_us(100000);
                state = button.read();
                led[0].write(0);
                led[1].write(1);
                wait_us(100000);
                state = button.read();
                led[1].write(0);
                led[2].write(1);
                wait_us(100000);
                state = button.read();
            }
            while(!state&&!i) {
                led[0].write(0);
                led[2].write(1);
                wait_us(100000);
                state = button.read();
                led[2].write(0);
                led[1].write(1);
                wait_us(100000);
                state = button.read();
                led[1].write(0);
                led[0].write(1);
                wait_us(100000);
                state = button.read();
            }
        }
        else
        {       
            ;
        }
    }
}

