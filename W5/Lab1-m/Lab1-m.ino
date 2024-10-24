#include <SPI.h>
String textSend="", textReceive="";


void setup (void) {
   Serial.begin(115200); 
   digitalWrite(SS, HIGH); // 確保SS初始狀態為HIGH
   SPI.begin ();
   SPI.setClockDivider(SPI_CLOCK_DIV8);//設定時脈為16/8 = 2 Mhz
}

void loop (void) {
   char c;
   digitalWrite(SS, LOW); //開始與從機通訊 //SS pin為10
   textSend="hello"; textReceive="";
   // textSend = Serial.readString();
   if(textSend != ""){
    for(int i = 0; i < textSend.length(); i++){
      delayMicroseconds (20);
      SPI.transfer(textSend[i]);
      Serial.print(textSend[i]);
      Serial.print("\n");
    }

    Serial.print ("Master: ");
    Serial.println (textSend);
    }
    else{
      int i = 0;
      char c;
      do{
        delayMicroseconds (20);
        c = SPI.transfer(1);
        textReceive += c;
        i++;
      }while(textReceive[i] != 0);
      if(textReceive[i] == 0){
        Serial.print ("Slave: ");
        Serial.println (textReceive);
        textReceive = "";
      }
    }
   digitalWrite(SS, HIGH); // 關閉與從機的通訊
   delay(2000);
}