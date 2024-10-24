#include "mbed.h"
#include <iostream>
using namespace std;

DigitalOut com[4] = {D8,D9,D10,D11};
DigitalOut seg[8] = {D0,D1,D2,D3,D4,D5,D6,D7};
int disp[4] = {0,0,0,0};

Timer timer;
Timer watch;
float t1 = 0;
float t2 = 0;

InterruptIn button(BUTTON1);

int table[11][8]=
{
    {1, 1, 1, 1, 1, 1, 0, 0},  //"0"  //資料線
    {0, 1, 1, 0, 0, 0, 0, 0},  //"1"
    {1, 1, 0, 1, 1, 0, 1, 0},  //"2"
    {1, 1, 1, 1, 0, 0, 1, 0},  //"3"
    {0, 1, 1, 0, 0, 1, 1, 0},  //"4"
    {1, 0, 1, 1, 0, 1, 1, 0},  //"5"
    {1, 0, 1, 1, 1, 1, 1, 0},  //"6"
    {1, 1, 1, 0, 0, 0, 0, 0},  //"7"
    {1, 1, 1, 1, 1, 1, 1, 0},  //"8"
    {1, 1, 1, 0, 0, 1, 1, 0},  //"9"
    /*external */
    {0,0,0,0,0,0,0,0}  // void
};   

void packing(float num) // 1234 -> [1][2][3][4]
{   
    int temp = int(num*100);  //  52.3256(s) -> 52.32(s)
    int cut[5] = { 1, 10, 100, 1000, 10000 };
    
    for(int i = 0; i < 4; i++)
        disp[i] = int( ( temp % cut[i+1] ) / cut[i] );
    /* 假如 (1234%10)/1=4,disp[0]=4
            (1234%100)/10=3,disp[1]=3以此類推*/
    if(disp[3] == 0)
        disp[3] = 10 ; //10的定義是 void (不顯示)         
}

void mapping(int disp)
{
    for(int i = 0; i < 8; i++)
        seg[i] = table[disp][i];  
            
}


void t1def()
{
    t1 = timer.read();
}

void t2def()
{
    t2 = timer.read();
}


int main()
{
    timer.start();
    button.rise( &t1def );
    button.fall( &t2def );
    int mode = 0;
    float dt = 0;
    float t3,t4;
              
    while(1)
    {
 
        dt = t2 - t1;      //記錄按按鈕 上緣-下緣時間  
        if( dt > 1 )
        {
            t3 = watch.read(); //為了歸零記錄時間       
        }
            
        else if( dt > 0.01 ){ //0.01是debouncing
            mode = !mode;
            t1 = t2;    //dt=t2-t1=0，為了不要進入if判斷
        }
    
        mode ? watch.start() : watch.stop();//初始停止，按完開始跑
        
        t4 = watch.read();               
        packing(t4 - t3);  /*第一次還沒歸零時t3=0，t4計時，
        當按按鈕超過?秒t4=t3[看上面if裡t3 = watch.read()]就可以歸零 */    
        for(int i = 0; i < 4; i++){
            com[i] = 0;       
            mapping(disp[i]);
            // cout << disp[i] << endl;
            if(i==2){  //if else 顯示小數點在第三位顯示
                seg[7] = 1;
            }
            else{
                seg[7] = 0;
            }
            wait_us(5000);           
            com[i] = 1;
        }               
    }   
     
}