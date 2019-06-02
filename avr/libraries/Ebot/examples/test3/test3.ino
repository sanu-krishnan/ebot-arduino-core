#define ultrasound(x) ((analogRead(x) * 0.833) / 4)
#define Potentiometer(x) (analogRead(x))
#define temp(x) (analogRead(x) / 2.048)
#define soundLevel(x) ((analogRead(x) - 600) / 4.24)
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define ir(x) analogRead(x)
#define Potentiometer(x) (analogRead(x))
#define cds(x) analogRead(x)
#define colour(x) (senseColor(x))
#include <SoftwareSerial.h>
#define CustomInput(x) analogRead(x)
#define CustomOutput(p, x) digitalWrite(p, x)
#define CustomOutput(p, x) analogWrite(p, x)
#include <SoftwareSerial.h>

#include "Ebot.h"
int item = 0;

int array_item[0] = {};

SoftwareSerial myserialRxA2(A2, 255);
SoftwareSerial mybluetoothRxA1(A1, 255);
SoftwareSerial mybluetoothRxA0(A0, 255);
SoftwareSerial mybluetoothTx0(255, 0);
SoftwareSerial lcd1(255, 1);
String d1;
SoftwareSerial myserialtx2(255, 2);
Servo myservo_3;
Servo myservo_4;
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800);

int a = 0;
int b = 0;

int RemoteA3Count = 0;
IR rc3(A3);
int ButtonA3Count = 0;
int EdgeA3Count = 0;
int IRA3Count = 0;

int PotentiometerA3Count = 0;
int LightA3Count = 0;
IR rc5(A5);
SoftwareSerial lcd2(255, 2);
String d2;
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(10,6,NEO_GRB + NEO_KHZ800);
Servo myservo_7;

void setup()
{
  //Initialisations
  ebot_setup();

  //Pin Modes
  pinMode(16, INPUT_PULLUP); //Slide Switches
  pinMode(17, INPUT_PULLUP); //Slide Switches
  pinMode(18, INPUT_PULLUP); //Slide Switches
  pinMode(A5, INPUT);        //Ultra Sonic
  pinMode(A7, INPUT);        //Potentiometer
  pinMode(A4, INPUT);        //Temperature
  pinMode(A3, INPUT);        //Sound Sensor
  myserialRxA2.begin(9600);
  mybluetoothRxA1.begin(9600);
  mybluetoothRxA0.begin(9600);
  mybluetoothTx0.begin(9600); //Serial Tx
  lcd1.begin(2400);           //LCD
  myserialtx2.begin(9600);    //Serial Tx
  pinMode(3, OUTPUT);         //Servo
  myservo_3.attach(3, -90, 90);
  pinMode(4, OUTPUT); //Servo Continuous
  myservo_4.attach(4, -270, 270);
  pinMode(5, OUTPUT); //Relay
  pinMode(6, OUTPUT); //RGB LED
  strip6.begin();
  strip6.show();
  pinMode(A6, INPUT);
  pinMode(7, OUTPUT);
  Serial.begin(115200); //Multimedia, Mouse and Keyboard
  connectBluetoothTo("Ebot_S", EBOT8);
  setBluetoothName("Ebot_M", EBOT8);
  Serial.begin(9600); //Serial Tx
  ebotSingInit(0);    //Buzzer
  pinMode(A3, INPUT); //Remote
  pinMode(A2, INPUT); //Color Sensor
  mybluetoothRxA0.begin(9600);
  pinMode(A1, INPUT); //Button
  pinMode(A4, INPUT); //CustomInput
  rc5.enable(HW_CH);  //Remote
  pinMode(1, OUTPUT); //Custom Output
  pinMode(2, OUTPUT); //Custom Output
  pinMode(8, OUTPUT); //LED
  pinMode(3, OUTPUT); //LED
  pinMode(4, OUTPUT); //Relay
  strip5.begin();
  strip5.show();
  pinMode(5, OUTPUT); //RGB LED
  pinMode(6, OUTPUT); //RGB LED
  strip6.begin();
  strip6.show();
  pinMode(7, OUTPUT); //Servo
  myservo_7.attach(7, -90, 90);
  Serial.begin(115200); //Multimedia, Mouse and Keyboard
  pinMode(A6, INPUT);   //IR
}

void loop()
{
  if (isSerCharEqls(&mybluetoothRxA0, 'U'))
  {
    if (isSerCharEqls(&mybluetoothRxA0, 'U'))
    {
      if (isSerCharEqls(&mybluetoothRxA1, 'A'))
      {
        if (isSerStrEqls(&mybluetoothRxA1, "Some text here"))
        {
          if (isSerCharEqls(&myserialRxA2, 'A'))
          {
            if (isSerStrEqls(&myserialRxA2, "Some text here"))
            {
              if (!digitalRead(16) && digitalRead(17) && !digitalRead(18))
              {
                if (soundLevel(A3) >= 60 && soundLevel(A3) <= 100)
                {
                  if (soundLevel(A3) <= 60 || soundLevel(A3) >= 100)
                  {
                    if (temp(A4) >= 0 && temp(A4) <= 100)
                    {
                      if (temp(A4) <= 0 || temp(A4) >= 100)
                      {
                        if (ultrasound(A5) >= 0 && ultrasound(A5) <= 250)
                        {
                          if (ultrasound(A5) <= 0 || ultrasound(A5) >= 250)
                          {
                            delay(500); //Delay for 0 hours 0 mins 0 sec 500 ms
                            delayMicroseconds(5);
                          }
                          if (Potentiometer(A7) >= 0 && Potentiometer(A7) <= 1023)
                          {
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  for (int count = 0; count < item; count++)
  {
    mybluetoothTx0.print("Some text here");
    mybluetoothTx0.println();
    delay(100);
    mybluetoothTx0.print("Some tet here");
    mybluetoothTx0.println();
    delay(100);
    d1 = "$000CN";
    d1 += "";
    d1 += "#";
    lcd1.println(d1);
    delay(200);
    myserialtx2.print(" ");
    myserialtx2.println();
    delay(100);
    myserialtx2.print(item);
    myserialtx2.println();
    delay(100);

    myservo_3.write(90);

    myservo_3.write(item);
    if (item == 0)
    {

      myservo_4.write(10 * 9 + 10);

      myservo_4.write(item * 9 + 10);
      digitalWrite(5, HIGH);
      digitalWrite(5, LOW);
      colorWipe(&strip6, 255, 255, 255, 100);
      rainbow(&strip6, 25);

      strip6.setPixelColor(0, strip6.Color(255, 255, 255));
      strip6.setPixelColor(1, strip6.Color(131, 64, 255));
      strip6.setPixelColor(2, strip6.Color(0, 255, 34));
      strip6.setPixelColor(3, strip6.Color(255, 0, 4));
      strip6.setPixelColor(4, strip6.Color(0, 255, 212));
      strip6.setPixelColor(5, strip6.Color(0, 81, 255));
      strip6.setPixelColor(6, strip6.Color(255, 0, 157));
      strip6.setPixelColor(7, strip6.Color(255, 0, 102));
      strip6.setPixelColor(8, strip6.Color(41, 8, 255));
      strip6.setPixelColor(9, strip6.Color(182, 255, 133));
      strip6.show();
      delay(20);
    }
    else if (Potentiometer(A7))
    {
      if (analogRead(A6) >= 0 && analogRead(A6) <= 1023)
      {
        analogWrite(7, 0);
        analogWrite(7, item);
        if (analogRead(A6) >= 0 && analogRead(A6) <= 1023)
        {
          if (isSerStrEqls(&Serial, "KI||Press||a"))
          {
            Serial.print("MMO||To||0||To||0"); //Command to Mouse Move Output
            Serial.println();
            delay(100);
            Serial.print("MMO||By||0||To||0"); //Command to Mouse Move Output
            Serial.println();
            delay(100);
            Serial.print("MMO||By||0||By||0"); //Command to Mouse Move Output
            Serial.println();
            delay(100);
            //Serial.print("MMO||To||"+item+"||To||"+item);//Command to Mouse Move Output
            Serial.println();
            delay(100);
            //Serial.print("MMO||To||"+item+"||To||0");//Command to Mouse Move Output
            Serial.println();
            delay(100);

            Serial.print("KO||Press||A"); //Command to Keyboard Out
            Serial.println();
            delay(100);
            Serial.print("KO||Type||Some text here"); //Command to Keyboard Out
            Serial.println();
            delay(100);
          }
          array_item[0] = 0;
          array_item[item] = item;
          array_item[item] = 50;
        }
      }
    }
  }

  if (isSerCharEqls(&mybluetoothRxA0, '3'))
  {
    if (button(A1, PRESSED))
    {
      if (isSerCharEqls(&mybluetoothRxA0, 'U'))
      {
        if (colour(A2) >= 0 && colour(A2) <= 45)
        {
          if (cds(A3) >= 0 && cds(A3) <= 1023)
          {
            delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
            LightA3Count++;
          }
          if (LightA3Count == 0)
          {
            LightA3Count = 0;
            if (Potentiometer(A3) >= 0 && Potentiometer(A3) <= 1023)
            {
              delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
              PotentiometerA3Count++;
            }
            if (PotentiometerA3Count == 0)
            {
              PotentiometerA3Count = 0;
              if (ir(A3) >= 0 && ir(A3) <= 1023)
              {
                delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                IRA3Count++;
              }
              if (IRA3Count == 0)
              {
                IRA3Count = 0;
                if (edge(A3, RISING))
                {
                  delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                  EdgeA3Count++;
                }
                if (EdgeA3Count == 0)
                {
                  EdgeA3Count = 0;
                  if (edge(A3, FALLING))
                  {
                    delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                    EdgeA3Count++;
                  }
                  if (EdgeA3Count == 0)
                  {
                    EdgeA3Count = 0;
                    if (button(A3, PRESSED))
                    {
                      delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                      ButtonA3Count++;
                    }
                    if (ButtonA3Count == 0)
                    {
                      ButtonA3Count = 0;
                      if (button(A3, RELEASED))
                      {
                        delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                        ButtonA3Count++;
                      }
                      if (ButtonA3Count == 0)
                      {
                        ButtonA3Count = 0;
                        if (ir_rc(&rc3, FW))
                        {
                          delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                          RemoteA3Count++;
                        }
                        if (RemoteA3Count == 0)
                        {
                          RemoteA3Count = 0;
                          Serial.print("eertewrt");
                          Serial.println();
                          delay(100);
                          Serial.print(a);
                          Serial.println();
                          delay(100);
                          ebotSing(0);
                          ebotSing(0);
                          tone(0, 2093, 1000);
                          tone(0, 1000, 1000);
                          tone(0, a, 1000);
                          tone(0, a, a);
                          tone(0, 1000, a);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (button(A1, RELEASED))
  {
    if (colour(A2) <= 0 || colour(A2) >= 45)
    {
      if (cds(A3) <= 0 || cds(A3) >= 1023)
      {
        delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
        LightA3Count++;
      }
      if (LightA3Count == 0)
      {
        LightA3Count = 0;
        if (Potentiometer(A3) <= 0 || Potentiometer(A3) >= 1023)
        {
          delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
          PotentiometerA3Count++;
        }
        if (PotentiometerA3Count == 0)
        {
          PotentiometerA3Count = 0;
          if (ir(A3) <= 0 || ir(A3) >= 1023)
          {
            delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
            IRA3Count++;
          }
          if (IRA3Count == 0)
          {
            IRA3Count = 0;
            if (CustomInput(A4) >= 0 && CustomInput(A4) <= 1023)
            {
              if (CustomInput(A4) <= 0 || CustomInput(A4) >= 1023)
              {
                if (edge(A4, RISING))
                {
                  if (edge(A4, FALLING))
                  {
                    if (ir_rc(&rc5, FW))
                    {
                      if (ir(A6) >= 0 && ir(A6) <= 1023)
                      {
                        if (ir(A6) <= 0 || ir(A6) >= 1023)
                        {
                          CustomOutput(1, HIGH);
                          CustomOutput(1, LOW);
                          CustomOutput(2, 0);
                          CustomOutput(2, a);
                          CustomOutput(1, a);
                          d2 = "$000CN";
                          d2 += "";
                          d2 += "#";
                          lcd2.println(d2);
                          delay(200);
                          d2 = "$000CY";
                          d2 += a;
                          d2 += "#";
                          lcd2.println(d2);
                          delay(200);
                          digitalWrite(8, HIGH);
                          digitalWrite(8, LOW);
                          digitalWrite(3, HIGH);
                          digitalWrite(3, LOW);
                          LMotor_1(10);
                          RMotor_1(a);
                          RMotor_1(0);
                          digitalWrite(4, HIGH);
                          digitalWrite(4, LOW);
                          strip5.setPixelColor(0, strip5.Color(255, 255, 255));
                          strip5.show();
                          delay(10);
                          strip5.setPixelColor(0, strip5.Color(a, a, a));
                          strip5.show();
                          delay(10);
                          colorWipe(&strip6, 255, 255, 255, 100);

                          myservo_7.write(90);

                          myservo_7.write(a);
                          Serial.print("MMAP|D:*Multimedia*Sounds*الشيخ مشاري راشد العفاسي*103.Al-Asr.mp3|>"); //Command to play Audio
                          Serial.println();
                          delay(100);
                          Serial.print("MMFO|D:*Multimedia*Sounds*الشيخ مشاري راشد العفاسي*093.Ad-Duha.mp3|>"); //Command to open File
                          Serial.println();
                          delay(100);
                          Serial.print("MMIO|D:*Multimedia*20130107_200903.jpg|>"); //Command to open Image
                          Serial.println();
                          delay(100);
                          Serial.print("MMVP|D:*Multimedia*خواطر 11*---#خواطر11 - الحلقة 16 - عليك بالماء - YouTube.mp4|>"); //Command to play Video
                          Serial.println();
                          delay(100);
                          if (isSerStrEqls(&Serial, "MCI||Click||Left"))
                          {
                            if (isSerStrEqls(&Serial, "KI||Press||a"))
                            {

                              Serial.print("KO||Press||A"); //Command to Keyboard Out
                              Serial.println();
                              delay(100);
                            }
                          }
                          if (isSerStrEqls(&Serial, "MMI||H||I||0||0"))
                          {
                            array_item[0] = 0;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}
