#include <Arduino.h>

//Lesson12 Potentiometer（可変抵抗器）
//https://omoroya.com/

int analogPin =3; //アナログ入力ピンを３番に設定
int val = 0; //読み取り値の変数設定
float v_convert = 0.0f; //計算値の変数設定、オーバーフローしないようにflaot設定

void setup() {
Serial.begin(115200); //シリアル通信のデータ転送レートを9600bpsで指定。bpsはビット/秒。
}

void loop(){
val = analogRead( analogPin ); //ピンの値を読み取り
v_convert = (float)val / 1023.0f * 5.0f; //読み取った値を電圧に変換、floatで計算

//Serial.print( "value / volt : " ); //表示をプリント
//Serial.print( val ); //読み取り値を表示
//Serial.print( " / " ); //表示をプリント
Serial.print( v_convert ); //計算した電圧値を表示、改行

delay(100); //2秒ごとに表示させるための遅延
}