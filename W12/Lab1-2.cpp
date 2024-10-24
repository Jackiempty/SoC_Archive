#include "mbed.h"

class LEDcontrol {
public:
    LEDcontrol(PinName pin, PinName pin1){
        _pin = new DigitalOut(LED1);
        /* Do something */
        *_pin = 0;
        _pin1 = new DigitalOut(LED2);
        /* Do something */
        *_pin1 = 0;
    }
    DigitalOut *temp;
    void change() {
        temp = _pin;
        /* Do something */
        _pin = _pin1;
        _pin1 = temp ;
        
    }
    void flip(){
        *_pin = !*_pin;
        *_pin1 = 0;
    }
private:
    DigitalOut *_pin,*_pin1;
};

LEDcontrol led(LED1,LED2);
Timeout t,t1;

int main() {
    
    t.attach(callback(&led, &LEDcontrol::change), 3.0);
    t1.attach(callback(&led, &LEDcontrol::change), 6.0);
    /* Do something */
    while(1) {
        led.flip();
        wait_us(200000);
    }
}