#include <Arduino.h>

const int led_pin = 9;
// const int led_pin = 9;

void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    char val = Serial.read();

    if(val == 'a'){
      Serial.println("Fan OFF");
      digitalWrite(led_pin, HIGH);
    }else if(val == 's'){
      Serial.println("Fan ON");
      digitalWrite(led_pin, LOW);
    }
  }
}
	