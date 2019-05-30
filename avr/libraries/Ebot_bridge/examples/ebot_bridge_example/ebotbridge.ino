/*
Project       :   Ebot Simplifies App Bridge Firmware
VersionNumber :   2.00
Organization  :   Creative Bits
website       :   www.cbits.cc
Target        :   Ebot8pro	and ebot8 (no ebot4)
*/

#include "Ebot_bridge.h"

void setup()
{
  bridge_setup();

#if defined(EBOT_8_PRO)
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(0, LOW); //scl
  digitalWrite(1, LOW); //sda
  SerialPort.print("AT");
  delay(100);
  SerialPort.print("AT+RENEW");
  delay(1000);
  // SerialPort.print("AT+TYPE3");  delay(200);
  // SerialPort.print("AT+MODE2");  delay(200);
  SerialPort.print("AT+NAMEEBotBlockly");
  delay(200);
  SerialPort.print("AT+RESET");
  delay(1000);
#elif defined(EBOT_8)
  SerialPort.print("AT");
  delay(100);
  SerialPort.print("AT+TYPE2");
  delay(200);
  //SerialPort.print("AT+MODE0");  delay(200);
  SerialPort.print("AT+NAMEEBotBlockly");
  delay(200);
  SerialPort.print("AT+PASS123456");
  delay(200);
  SerialPort.print("AT+TYPE0");
  delay(200);
  SerialPort.print("AT+RESET");
  delay(1000);
  //digitalWrite(BLE_KEY,HIGH);
#endif
}

void loop()
{
  bridge_loop();
}