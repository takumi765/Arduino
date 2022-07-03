#include <Wire.h>
#include "HX711.h"
const int AIRPRESS_DAT = 9;
const int AIRPRESS_CLK = 8;


HX711 scale;
char data[100];

int sign(double x) {
  int value = 0;
  if (x > 0)
    value = 1;
  else if (x < 0)
    value = -1;

  return value;
}

void setup() {
  Serial.begin(115200);

  // Air press
  scale.begin(AIRPRESS_DAT, AIRPRESS_CLK);
  scale.set_scale(1000);
  scale.tare();
}

void loop()
{
  // Air press
  if (scale.is_ready()) {
    long data = scale.get_units();
    //sprintf(data, "%d", reading1);
    if(data<2000){
      Serial.println(0);    //0で割り算できないのを防ぐ
    }
    else{
      Serial.println(1);
    }
  } 
  //Serial.println("");
  
  delay(100);
}