#include "mbed.h"

AnalogOut  breathled(PA_4);
volatile float i = 0;
volatile float ctrl = 1;
Ticker breath_ticker;

void breath(){
        i = i + (0.1 * ctrl);
        ctrl = (i <= 0) * (1) + (i >= 1) * (-1) + ctrl*(i>0)*(i<1);
        }

int main(void)
{
 
    breath_ticker.attach(&breath,0.1);

    while(1) {
        breathled = i;
    }
}