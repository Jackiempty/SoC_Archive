#include "mbed.h"

Timer timer;
DigitalIn button(BUTTON1,PullDown);
int s0,t0,t1;
int sudo = 0;



int main()
{
    timer.start();
    s0 = button.read();
    int cnt = 0;
    while(1)
    {
        s0 = button.read();
        //printf("%d,%d,%d\n",s0,t0,t1);
        if(s0 ==1 && t0==0){
            t0 = timer.read();
            //printf("%d\n",t0);
            }
        if(s0==1 && t0>0){
             t1 = timer.read();
        }
        if(s0==0 && t0>0){
            if(t1-t0 > 1){
            sudo = sudo+1;
            printf("%d\n",sudo);
            t0 = 0;
            t1 = 0;}
        }
    }
}

