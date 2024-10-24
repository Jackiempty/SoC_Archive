const int button = 2;
const int led = 13;  //UNO內建LED
bool led_state = HIGH;
bool last_state = HIGH;
int buttonState;  
unsigned long debounceDelay = 5;
unsigned long lastDebounceTime = 0;
int current_state;
void setup() {
  pinMode(button, INPUT_PULLUP);  //上拉
  pinMode(led, OUTPUT);
  digitalWrite(led, led_state);
  Serial.begin(115200);
}

void loop() 
{
  current_state = digitalRead(button);
  if(current_state == HIGH)
  {
    last_state = current_state;
  }
  else if(current_state == LOW){
    
    if(current_state != last_state)
    {
      lastDebounceTime = millis();
      led_state != led_state;
      while(millis() - lastDebounceTime < debounceDelay)
      {
        digitalWrite(led, led_state);
      }
      if(millis() - lastDebounceTime > debounceDelay)
      {
        if(digitalRead(button) == current_state)
        {
          Serial.println(current_state);
          led_state != led_state;
          last_state = current_state;
          if(led_state == HIGH)
          {
            led_state = LOW;
          }
          else
          {
            led_state = HIGH;
          }
          digitalWrite(led, led_state);
        }
      }
    }
  }
}
