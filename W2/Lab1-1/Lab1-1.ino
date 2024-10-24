void setup() {
  // put your setup code here, to run once:
  for (int i = 3; i <= 7; i++)  // 整數變數i由3變化到7，每次加1
  {
    pinMode(i, OUTPUT);  // 設定i變數所指定的腳位為輸出功能
    digitalWrite(i, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 3; i<=7; i++)
  {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
  for (int i = 6; i>=3; i--)
  {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
}
