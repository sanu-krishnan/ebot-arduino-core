#define CustomInput(x) analogRead(x)
#define ultrasound(x) ((analogRead(x) * 0.833) / 4)
#define temp(x) (analogRead(x) / 2.048)
#define soundLevel(x) ((analogRead(x) - 600) / 4.24)
#include "Adafruit_NeoPixel.h"
#include "Adafruit_NeoPixel.h"
#include <SoftwareSerial.h>
#include <Servo.h>

#define CustomInput(x) analogRead(x)
#define cds(x) analogRead(x)
#define ir(x) analogRead(x)
#define colour(x) (senseColor(x))
#define CustomOutput(p, x) digitalWrite(p, x)
#include <SoftwareSerial.h>
#include "Adafruit_NeoPixel.h"
#include "Adafruit_NeoPixel.h"
#include <SoftwareSerial.h>
#include "Servo.h"
#include <SoftwareSerial.h>

#include "Ebot.h"
int array_item[0] = {};

Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(1, ebot_pro_pin(0), NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip11 = Adafruit_NeoPixel(10, ebot_pro_pin(11), NEO_GRB + NEO_KHZ800);
SoftwareSerial myserialtx3(255, ebot_pro_pin(3));
Servo myservo_1;
Servo myservo_2;
SoftwareSerial myserialRxA2(A2, 255);
SoftwareSerial mybluetoothRxA0(A0, 255);
SoftwareSerial mybluetoothRxA5(A5, 255);

int xOff = 0;
int yOff = 0;
int zOff = 0;
IR rc5(A5);
int LightA3Count = 0;
SoftwareSerial lcd1(255, ebot_pro_pin(1));
String d1;
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(1, ebot_pro_pin(3), NEO_GRB + NEO_KHZ800);
SoftwareSerial myserialtx4(255, ebot_pro_pin(4));
Servo myservo_5;
Servo myservo_6;

void setup()
{
  //Initialisations
  ebot_setup();

  //Pin Modes
  pinMode(A1, INPUT);        //CustomInput
  pinMode(16, INPUT_PULLUP); //Slide Switches
  pinMode(17, INPUT_PULLUP); //Slide Switches
  pinMode(18, INPUT_PULLUP); //Slide Switches
  pinMode(A4, INPUT);        //Ultra Sonic
  pinMode(16, INPUT);        //Temperature
  pinMode(A3, INPUT);        //Sound Sensor
  Serial.begin(115200);      //Multimedia, Mouse and Keyboard
  strip0.begin();
  strip0.show();
  pinMode(ebot_pro_pin(0), OUTPUT);  //RGB LED
  pinMode(ebot_pro_pin(11), OUTPUT); //RGB LED
  strip11.begin();
  strip11.show();
  myserialtx3.begin(115200);        //Serial Tx
  pinMode(ebot_pro_pin(1), OUTPUT); //Servo
  myservo_1.attach(ebot_pro_pin(1), -90, 90);
  pinMode(ebot_pro_pin(2), OUTPUT); //Servo Continuous
  myservo_2.attach(ebot_pro_pin(2), -270, 270);
  myserialRxA2.begin(9600);
  pinMode(8, OUTPUT); //LED
  mybluetoothRxA0.begin(9600);
  mybluetoothRxA5.begin(9600);
  mpu6050_init();
  pinMode(A4, INPUT); //CustomInput
  rc5.enable(HW_CH);  //Remote
  pinMode(A7, INPUT); //Light Sensor
  pinMode(A6, INPUT); //IR
  pinMode(A3, INPUT); //Light Sensor
  pinMode(A2, INPUT); //Color Sensor
  pinMode(7, OUTPUT);
  Serial.begin(115200);             //Multimedia, Mouse and Keyboard
  Serial1.begin(9600);              //Serial Tx
  ebotSingInit(12);                 //Buzzer
  pinMode(ebot_pro_pin(0), OUTPUT); //Custom Output
  lcd1.begin(2400);                 //LCD
  pinMode(8, OUTPUT);               //LED
  pinMode(ebot_pro_pin(2), OUTPUT); //Relay
  strip3.begin();
  strip3.show();
  pinMode(ebot_pro_pin(3), OUTPUT);  //RGB LED
  pinMode(ebot_pro_pin(11), OUTPUT); //RGB LED
  strip11.begin();
  strip11.show();
  myserialtx4.begin(115200);        //Serial Tx
  pinMode(ebot_pro_pin(5), OUTPUT); //Servo
  myservo_5.attach(ebot_pro_pin(5), -90, 90);
  pinMode(ebot_pro_pin(6), OUTPUT); //Servo Continuous
  myservo_6.attach(ebot_pro_pin(6), -270, 270);
  pinMode(A1, INPUT); //Button
  mybluetoothRxA0.begin(9600);
  Serial1.begin(9600); //Serial Rx
  connectBluetoothTo("Ebot_S", EBOT8PRO);
  setBluetoothName("Ebot_M", EBOT8PRO);
}

void loop()
{
  if (isSerCharEqls(&mybluetoothRxA5, 'U'))
  {
    if (isSerCharEqls(&mybluetoothRxA0, 'A'))
    {
      if (CustomInput(A1) >= 0 && CustomInput(A1) <= 1023)
      {
        if (isSerCharEqls(&myserialRxA2, 'A'))
        {
          if (soundLevel(A3) >= 60 && soundLevel(A3) <= 100)
          {
            if (!digitalRead(16) && !digitalRead(17) && !digitalRead(18))
            {
              if (temp(16) >= 0 && temp(16) <= 100)
              {
                if (ultrasound(A4) >= 0 && ultrasound(A4) <= 250)
                {
                }
              }
            }
          }
          if (isSerStrEqls(&Serial, "KI||Press||a"))
          {
            strip0.setPixelColor(0, strip0.Color(255, 255, 255));
            strip0.show();
            delay(10);
            colorWipe(&strip11, 255, 255, 255, 100);
            myserialtx3.print(" ");
            myserialtx3.println();
            delay(100);

            myservo_1.write(90);

            myservo_2.write(0 * 9);
          }

          Serial.print("KO||Press||A"); //Command to Keyboard Out
          Serial.println();
          delay(100);
          array_item[0] = 0;
        }

        Serial.print("MCO||Click||Left"); //Command to MouseOutput
        Serial.println();
        delay(100);
        Serial.print("MMO||To||0||To||0"); //Command to Mouse Move Output
        Serial.println();
        delay(100);
        if (isSerStrEqls(&Serial, "MCI||Click||Left"))
        {
          digitalWrite(8, HIGH);
        }
      }
    }
  }

  if (readFromMPU(realAccelerationX) >= -5000 && readFromMPU(realAccelerationX) <= 5000)
  {
    if (isSerCharEqls(&Serial1, 'U'))
    {
      if (isSerCharEqls(&mybluetoothRxA0, 'A'))
      {
        if (button(A1, PRESSED))
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
              if (CustomInput(A4) >= 0 && CustomInput(A4) <= 1023)
              {
                if (readFromMPU(angleX, xOff) >= -180 && readFromMPU(angleX, xOff) <= 180)
                {
                  xOff = readFromMPU(angleX, 0);
                  yOff = readFromMPU(angleY, 0);
                  zOff = readFromMPU(angleZ, 0);
                  if (1)
                  {
                    if (ir(A6) >= 0 && ir(A6) <= 1023)
                    {
                      if (cds(A7) >= 0 && cds(A7) <= 1023)
                      {
                      }
                    }
                  }
                }
              }
            }
          }
          for (;;)
          {
            analogWrite(7, 0);
            if (analogRead(A0))
            {
              Serial.print("MMAP|D:*Cbits*Ebot*sound.mp3|>"); //Command to play Audio
              Serial.println();
              delay(100);
              Serial.print("MMFO|D:*Cbits*Ebot*sound.mp3|>"); //Command to open File
              Serial.println();
              delay(100);
              Serial.print("MMIO|D:*Cbits*Ebot*image.jpg|>"); //Command to open Image
              Serial.println();
              delay(100);
              Serial.print("MMVP|D:*Cbits*Ebot*video.mp4|>"); //Command to play Video
              Serial.println();
              delay(100);
            }
            Serial.print("MMAP||>"); //Command to play Audio
            Serial.println();
            delay(100);
            Serial.println("MMIC|>"); //Command to close Image
            Serial.println();
            delay(100);
            Serial.println("MMVS|>"); //Command to stop Video
            Serial.println();
            delay(100);
          }
          Serial1.print(" ");
          Serial1.println();
          delay(100);
          ebotSing(0);
          CustomOutput(ebot_pro_pin(0), HIGH);
          d1 = "$000CN";
          d1 += "";
          d1 += "#";
          lcd1.println(d1);
          delay(200);
          digitalWrite(8, HIGH);
          digitalWrite(ebot_pro_pin(2), HIGH);
          strip3.setPixelColor(0, strip3.Color(255, 255, 255));
          strip3.show();
          delay(10);
          delay(0);
          colorWipe(&strip11, 255, 255, 255, 100);
          myserialtx4.print(" ");
          myserialtx4.println();
          delay(100);
          myserialtx4.print(" ");
          myserialtx4.println();
          delay(100);

          myservo_5.write(90);

          myservo_6.write(0 * 9);

          Serial.print("MCO||Click||Left"); //Command to MouseOutput
          Serial.println();
          delay(100);
        }
      }
    }
  }
}
