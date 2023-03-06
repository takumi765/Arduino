#include <Arduino.h>
#include "M5Atom.h"

const int motor_pin  = G26; // M5StickC
const int ledChannel = 0;
const int maxBit     = 8;

void setup() {
  // 本体初期化（UART有効, I2C無効, LED有効）
  M5.begin(true, false, true);

  Serial.begin(115200);
  // PWMで速度を制御
  ledcSetup(ledChannel, 12000, maxBit);
  ledcAttachPin(motor_pin, ledChannel);
}

void loop() {
  if (Serial.available()) {
    char key = Serial.read();
    // 第二引数/maxBitの大きさで出力する
    ledcWrite(ledChannel, 256 * 0.5); // 最大出力（256/256）
    delay(150);
    // 停止
    ledcWrite(ledChannel, 0);
    delay(200);
  } 

  // 確認用：ボタンが押されたとき
  M5.update(); //本体のボタン状態更新
  if (M5.Btn.wasPressed()){
    // 始動は20%以上で15ミリ秒以上必要
    ledcWrite(ledChannel, 256 * 0.5);
    delay(150); // 150秒振動させる
    // 停止
    ledcWrite(ledChannel, 0);
    delay(200); // 200ms入力を受け付けない
  }
}