#define CustomInput(x) analogRead(x)
#define cds(x) analogRead(x)
#define ir(x) analogRead(x)
#define colour(x) (senseColor(x))
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#define CustomOutput(p, x) digitalWrite(p, x)
#include <SoftwareSerial.h>
#include "Adafruit_NeoPixel.h"
#include "Adafruit_NeoPixel.h"
#include "Servo.h"
#include <SoftwareSerial.h>
#define ultrasound(x) ((analogRead(x) * 0.833) / 4)
#define temp(x) (analogRead(x) / 2.048)
#define soundLevel(x) ((analogRead(x) - 600) / 4.24)
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#include "Servo.h"
#include <SoftwareSerial.h>

#include "Ebot.h"
int item = 0;
int var0 = 0;

int array_item[0] = {};
IR rc5(A5);
SoftwareSerial myserialRxA4(A4, 255);
SoftwareSerial mybluetoothRxA6(A6, 255);
SoftwareSerial mybluetoothRxA7(A7, 255);
Servo myservo_0;
SoftwareSerial myserialtx1(255, 1);
IR rc4(A4);
int LightA3Count = 0;
SoftwareSerial mybluetoothRxA0(A0, 255);
SoftwareSerial mybluetoothTx0(255, 0);
SoftwareSerial lcd3(255, 3);
String d3;
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6 = Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800);
SoftwareSerial myserialtx7(255, 7);
Servo myservo_7;

void setup()
{
  //Initialisations
  ebot_setup();

  //Pin Modes
  rc4.enable(HW_CH);    //Remote
  pinMode(A7, INPUT);   //CustomInput
  pinMode(A6, INPUT);   //Light Sensor
  pinMode(A5, INPUT);   //IR
  pinMode(A3, INPUT);   //Light Sensor
  pinMode(A2, INPUT);   //Color Sensor
  Serial.begin(115200); //Multimedia, Mouse and Keyboard
  pinMode(A1, INPUT);   //Button
  mybluetoothRxA0.begin(9600);
  Serial.begin(9600);         //Serial Rx
  mybluetoothTx0.begin(9600); //Serial Tx
  ebotSingInit(1);            //Buzzer
  pinMode(2, OUTPUT);         //Custom Output
  lcd3.begin(2400);           //LCD
  pinMode(8, OUTPUT);         //LED
  pinMode(4, OUTPUT);         //Relay
  strip5.begin();
  strip5.show();
  pinMode(5, OUTPUT); //RGB LED
  pinMode(6, OUTPUT); //RGB LED
  strip6.begin();
  strip6.show();
  myserialtx7.begin(115200); //Serial Tx
  myservo_7.attach(7, -90, 90);
  rc5.enable(HW_CH); //Remote
  myserialRxA4.begin(9600);
  pinMode(A3, INPUT); //Ultra Sonic
  pinMode(A2, INPUT); //Temperature
  pinMode(A1, INPUT); //Sound Sensor
  mybluetoothRxA6.begin(9600);
  mybluetoothRxA7.begin(9600);
  pinMode(0, OUTPUT); //Servo Continuous
  myservo_0.attach(0, -270, 270);
  myserialtx1.begin(115200); //Serial Tx
  Serial.begin(115200);      //Multimedia, Mouse and Keyboard
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  connectBluetoothTo("Ebot_S", EBOT8);
  setBluetoothName("Ebot_M", EBOT8);
}

void loop()
{
  if (isSerCharEqls(&Serial, 'U'))
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
            if (ir_rc(&rc4, FW))
            {
              if (ir(A5) >= 0 && ir(A5) <= 1023)
              {
                if (cds(A6) >= 0 && cds(A6) <= 1023)
                {
                  if (CustomInput(A7) >= 0 && CustomInput(A7) <= 1023)
                  {
                  }
                }
              }
            }
          }
        }
        Serial.print("MMAP|D:*Cbits*Ebot*sound.mp3|>"); //Command to play Audio
        Serial.println();
        delay(100);
        Serial.print("MMFO|D:*Cbits*Ebot*image.jpg|>"); //Command to open File
        Serial.println();
        delay(100);
        Serial.print("MMIO|D:*Cbits*Ebot*image.jpg|>"); //Command to open Image
        Serial.println();
        delay(100);
        Serial.print("MMVP|D:*Cbits*Ebot*video.mp4|>"); //Command to play Video
        Serial.println();
        delay(100);
      }
    }
  }
  for (;;)
  {
    if (item == 0 ? item : map(var0, 0, 1023, 0, 255))
    {
      mybluetoothTx0.print(" ");
      mybluetoothTx0.println();
      delay(100);
      ebotSing(0);
      CustomOutput(2, HIGH);
      d3 = "$000CN";
      d3 += "";
      d3 += "#";
      lcd3.println(d3);
      delay(200);
      digitalWrite(8, HIGH);
      digitalWrite(4, HIGH);
      strip5.setPixelColor(0, strip5.Color(255, 255, 255));
      strip5.show();
      delay(10);
      colorWipe(&strip6, 255, 255, 255, 100);
      myserialtx7.print(" ");
      myserialtx7.println();
      delay(100);

      myservo_7.write(90);
      /* (Custom code) */
      int i = 0;
      delay(500); //Delay for 0 hours 0 mins 0 sec 500 ms
      delayMicroseconds(500);
      if (isSerStrEqls(&Serial, "KI||Press||a"))
      {

        Serial.print("KO||Press||A"); //Command to Keyboard Out
        Serial.println();
        delay(100);
      }
      array_item[0] = 0;

      Serial.print("MCO||Click||Left"); //Command to MouseOutput
      Serial.println();
      delay(100);
    }
  }
  if (isSerCharEqls(&mybluetoothRxA7, 'U'))
  {
    if (isSerCharEqls(&mybluetoothRxA6, 'A'))
    {
      if (soundLevel(A1) >= 60 && soundLevel(A1) <= 100)
      {
        if (temp(A2) >= 0 && temp(A2) <= 100)
        {
          if (ultrasound(A3) >= 0 && ultrasound(A3) <= 250)
          {
            if (isSerCharEqls(&myserialRxA4, 'A'))
            {
              if (ir_rc(&rc5, FW))
              {
              }
            }
          }
        }
      }
    }
  }
  if (analogRead(A0))
  {

    myservo_0.write(0 * 9);
  }
  else if (digitalRead(A0))
  {

    myservo_0.write(10 * 9);
  }
  else
  {
    myserialtx1.print(" ");
    myserialtx1.println();
    delay(100);

    Serial.print("KO||Press||h"); //Command to Keyboard Out
    Serial.println();
    delay(100);
    if (!item)
    {
      tone(3, 2093, 1000);
    }
    else if (item && NULL)
    {
      digitalWrite(2, 1);
      var0 = var0 + 1;
    }
    else if (constrain(var0, 5, 100))
    {
      var0 = var0 - 1;
    }
    var0 = array_item[0];
  }
}
