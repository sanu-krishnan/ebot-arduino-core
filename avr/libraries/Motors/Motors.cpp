
#include "Arduino.h"
#include "Motors.h"

Motors::Motors()
{
}

#if defined(EBOT_8) || defined(EBOT_4)

void Motors::init2()
{
  // setup pwm
  // all pwm pins to out
  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);
  pinMode(PM1, OUTPUT);
  pinMode(PM2, OUTPUT);
  pinMode(ME, OUTPUT);
  digitalWrite(ME, 1);
}

void Motors::setMLSpeed(int speed)
{
  init2();
  analogWrite(PM1, abs(speed));
  if (speed == 0)
  {
    //digitalWrite(M11,HIGH);
    //digitalWrite(M12,HIGH);
  }
  else if (speed > 0)
  {
    digitalWrite(M11, HIGH);
    digitalWrite(M12, LOW);
  }
  else if (speed < 0)
  {
    digitalWrite(M11, LOW);
    digitalWrite(M12, HIGH);
  }
}

void Motors::setMRSpeed(int speed)
{
  init2();
  analogWrite(PM2, abs(speed));
  if (speed == 0)
  {
    //digitalWrite(M21,HIGH);
    //digitalWrite(M22,HIGH);
  }
  else if (speed > 0)
  {
    digitalWrite(M21, HIGH);
    digitalWrite(M22, LOW);
  }
  else if (speed < 0)
  {
    digitalWrite(M21, LOW);
    digitalWrite(M22, HIGH);
  }
}

/* Minimal GPIO implementation with NOT gates */
#ifdef EBOT_8
void Motors::initMotors()
{
  // setup pwm
  // all pwm pins to out
  pinMode(Motor1Dir, OUTPUT);
  pinMode(Motor2Dir, OUTPUT);
  pinMode(PM1, OUTPUT);
  pinMode(PM2, OUTPUT);
  pinMode(ME, OUTPUT);
  digitalWrite(ME, 1);
}

void Motors::setLeftMotorSpeed(int speed)
{
  initMotors();
  analogWrite(PM1, abs(speed));
  if (speed > 0)
  {
    digitalWrite(Motor1Dir, HIGH);
  }
  else if (speed < 0)
  {
    digitalWrite(Motor1Dir, LOW);
  }
}

void Motors::setRightMotorSpeed(int speed)
{
  initMotors();
  analogWrite(PM2, abs(speed));
  if (speed > 0)
  {
    digitalWrite(Motor2Dir, HIGH);
  }
  else if (speed < 0)
  {
    digitalWrite(Motor2Dir, LOW);
  }
}
#endif
/**************************************************/

/*void Motors::setMSpeed(int speed1,int speed2) {
  setMLSpeed(speed1);
  setMRSpeed(speed2);
}*/

void Motors::disable()
{
  //Motors::setMSpeed(0,0);
  setMLSpeed(0);
  setMRSpeed(0);
}

#endif
