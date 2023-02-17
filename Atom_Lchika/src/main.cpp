#include <Arduino.h>
#include <M5Atom.h> //Atomのヘッダファイルを準備
//FastLED（CRGB構造体）設定
CRGB dispColor(uint8_t r, uint8_t g, uint8_t b) {
  return (CRGB)((r << 16) | (g << 8) | b);
}
// 初期設定 -----------------------------------------------
void setup() {
  // 本体初期化（UART有効, I2C無効, LED有効
  M5.begin(true, false, true);
  // LED全消灯（赤, 緑, 青)
  M5.dis.drawpix(0, dispColor(0, 0, 0));
}
// メイン -------------------------------------------------
void loop() {
  M5.update(); //本体のボタン状態更新
  if (M5.Btn.isPressed()) {  //ボタンが押されていれば
    M5.dis.drawpix(0, dispColor(0, 0, 255)); //LED（指定色）
  } else { //ボタンが押されてなければ
    M5.dis.drawpix(0, dispColor(20, 20, 20)); //LED（白）
  }
  delay(100); //100ms待機
}