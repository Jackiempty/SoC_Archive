
const int INT7 = 2;
const int INT2 = 4;
const int INT3 = 5;
const int INT4 = 6;
const int ENA  = 3;
const int ENB  = 9;  
int PWM1 = 50;
int PWM2 = 50;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
void setup() {
  pinMode(INT7, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(INT3, OUTPUT);
  pinMode(INT4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

}

void loop() {
  Front();
  delay(1000);
  BACK();
  delay(1000);
  

}

void BACK(){
  M1Front();
  M2Front();
  }

void Front(){
  M1BACK();
  M2BACK();
  }
void right(){
  M1BACK();
  M2STOP();
  }

void left(){
  M1STOP();
  M2BACK();
  }

void STOP(){
  M1STOP();
  M2STOP();
  }
void BackLeft(){
  M1Front();
  M2STOP();
  }

void BackRight(){
  M1STOP();
  M2Front();
  }

void M1Front(){
  digitalWrite(INT7, HIGH);
  digitalWrite(INT2, LOW);
  analogWrite(ENA, PWM1);
  }

void M1BACK(){
  digitalWrite(INT7, LOW);
  digitalWrite(INT2, HIGH);
  analogWrite(ENA, PWM1);
  }

void M1STOP(){
  digitalWrite(INT7, LOW);
  digitalWrite(INT2, LOW);
  analogWrite(ENA, PWM1);
  }

void M2Front(){
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);
  analogWrite(ENB, PWM2);
  }

  
void M2BACK(){
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);
  analogWrite(ENB, PWM2);
  }

void M2STOP(){
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, LOW);
  analogWrite(ENB, PWM2);
  }
