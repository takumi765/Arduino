/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/unit/joystick
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/joystick
*
* describe: JOYSTICK.
* date：2021/8/30
*******************************************************************************
  Please connect to Port,Read JOYSTICK Unit X, Y axis offset data and button status
  请连接端口,读取操纵杆单位X, Y轴偏移数据和按钮状态
*/
#include <M5Atom.h>
#include<Arduino.h>

#define JOY_ADDR 0x52 //define Joystick I2C address.  定义摇杆的I2C地址

void setup() {
  M5.begin(true, false, true);
  Serial.begin(115200);
  Wire.begin(26,32);
}

char data[100];
void loop() {
  static int x_data,y_data,button_data;
  Wire.requestFrom(JOY_ADDR, 3);  //Request 3 bytes from the slave device.  向从设备请求3个字节
  if (Wire.available()) { //If data is received.  如果接收到数据
    x_data = Wire.read() - 125;//max=249
    y_data = Wire.read() - 120;//max=240
    button_data = Wire.read();
    sprintf(data, "x:%d,y:%d,button:%d\n", x_data, y_data, button_data);
    Serial.print(data);

    //Serial.printf("x:%04d y:%04d button:%d\n", x_data, y_data, button_data);
  }
  delay(200);
}