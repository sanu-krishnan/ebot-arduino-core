#include <SoftwareSerial.h>
#define colour(x) (senseColor(x))
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#define CustomOutput(p,x) digitalWrite(p,x)
#define CustomOutput(p,x) analogWrite(p,x)
#include <SoftwareSerial.h>
#define ir(x) analogRead(x)
#define Potentiometer(x) (analogRead(x))
#define cds(x) analogRead(x)
#define CustomInput(x) analogRead(x)


#define Potentiometer(x) (analogRead(x))
#define ir(x) analogRead(x)
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#include "Adafruit_NeoPixel.h"
#include "Adafruit_NeoPixel.h"
#include "Servo.h"
#define ultrasound(x) ((analogRead(x)*0.833)/4)
#define temp(x) (analogRead(x) / 2.048)
#define soundLevel(x) ((analogRead(x)-600)/4.24)
#include <SoftwareSerial.h>


#include "Ebot.h"
int item = 0;

SoftwareSerial mybluetoothTx0(255,ebot_pro_pin(0));
SoftwareSerial mybluetoothRxA2(A2,255);
SoftwareSerial mybluetoothRxA0(A0,255);
SoftwareSerial lcd2(255,ebot_pro_pin(2));
String d2;
int RemoteA4Count=0;
IR rc4(A4);
int ButtonA4Count=0;
int EdgeA4Count=0;
int IRA4Count=0;

int PotentiometerA4Count=0;
int LightA4Count=0;
int xOff=0;
int yOff=0;
int zOff=0;
IR rc6(A6);


int array_item[0] = {};

IR rc1(A1);
SoftwareSerial mybluetoothRxA3(A3,255);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(1,ebot_pro_pin(2),NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip11 = Adafruit_NeoPixel(4,ebot_pro_pin(11),NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(4,ebot_pro_pin(3),NEO_GRB + NEO_KHZ800);
SoftwareSerial myserialtx4(255,ebot_pro_pin(4));
Servo myservo_5;
Servo myservo_6;
SoftwareSerial myserialRxA5(A5,255);



void setup()
{
    //Initialisations
    ebot_setup();

    //Pin Modes
    mpu6050_init();
    Serial1.begin(9600); //Serial Tx
    mybluetoothTx0.begin(9600); //Serial Tx
    ebotSingInit(12); //Buzzer
    pinMode(A3, INPUT); //Color Sensor
    mybluetoothRxA2.begin(9600);
    pinMode(A1, INPUT); //Button
    mybluetoothRxA0.begin(9600);
    Serial1.begin(9600); //Serial Rx
    pinMode(ebot_pro_pin(1), OUTPUT); //Custom Output
    pinMode(ebot_pro_pin(2), OUTPUT); //Custom Output
    pinMode(8, OUTPUT); //LED
    pinMode(ebot_pro_pin(3), OUTPUT); //LED
    pinMode(A4, INPUT); //Remote
    pinMode(A5, INPUT); //CustomInput
    rc6.enable(HW_CH); //Remote
    pinMode(A7, INPUT); //Light Sensor
      //setBluetoothName("Ebot_M", EBOT8PRO);
      //connectBluetoothTo("Ebot_S", EBOT8PRO);
      
      rc1.enable(HW_CH); //Remote
    Serial.begin(115200); //Multimedia, Mouse and Keyboard
    pinMode(A4, INPUT); //Potentiometer
    pinMode(A2, INPUT); //IR
    mybluetoothRxA0.begin(9600);
    mybluetoothRxA3.begin(9600);
    pinMode(16, INPUT_PULLUP); //Slide Switches
    pinMode(17, INPUT_PULLUP); //Slide Switches
    pinMode(18, INPUT_PULLUP); //Slide Switches
    mybluetoothTx0.begin(9600); //Serial Tx
    pinMode(ebot_pro_pin(1), OUTPUT); //Relay
    strip2.begin(); strip2.show();
    pinMode(ebot_pro_pin(2), OUTPUT); //RGB LED
    pinMode(ebot_pro_pin(11), OUTPUT); //RGB LED
    strip11.begin();
    strip11.show();
    pinMode(ebot_pro_pin(3), OUTPUT); //RGB LED
    strip3.begin();
    strip3.show();
    myserialtx4.begin(115200); //Serial Tx
    pinMode(ebot_pro_pin(5), OUTPUT); //Servo
    myservo_5.attach(ebot_pro_pin(5),-90,90);
    pinMode(ebot_pro_pin(6), OUTPUT); //Servo Continuous
    myservo_6.attach(ebot_pro_pin(6),-270,270);
    pinMode(A7, INPUT); //Ultra Sonic
    pinMode(16, INPUT); //Temperature
    pinMode(A6, INPUT); //Sound Sensor
    myserialRxA5.begin(9600);
}

void loop()
{
      if(readFromMPU(realAccelerationX) >=-5000 && readFromMPU(realAccelerationX) <=5000 )
      {
        if(readFromMPU(realAccelerationX) <=-5000 || readFromMPU(realAccelerationX) >=5000 )
        {
          if(readFromMPU(realAccelerationY) <=-5000 || readFromMPU(realAccelerationY) >=5000 )
          {
            if(readFromMPU(realAccelerationY) >=-5000 && readFromMPU(realAccelerationY) <=5000 )
            {
              if(readFromMPU(realAccelerationZ) >=-5000 && readFromMPU(realAccelerationZ) <=5000 )
              {
                if(readFromMPU(realAccelerationZ) <=-5000 || readFromMPU(realAccelerationZ) >=5000 )
                {
                  if(isSerCharEqls(&Serial1, 'U'))
                  {
                    if(isSerCharEqls(&mybluetoothRxA0,'U'))
                    {
                      if(button(A1,PRESSED))
                      {
                        if(button(A1,RELEASED))
                        {
                          if(isSerCharEqls(&mybluetoothRxA2, 'A'))
                          {
                            if(isSerStrEqls(&mybluetoothRxA2,"Some Text here"))
                            {
                              if(colour(A3)>=0  && colour(A3)<= 45)
                              {
                                if(colour(A3)>=850 && colour(A3)<=1023)
                                {
                                  if(colour(A3)>=600 && colour(A3)<=800)
                                  {
                                    Serial1.print("Some Text here");
                                    Serial1.println();
                                    delay(100);
                                    Serial1.print(item);
                                    Serial1.println();
                                    delay(100);
                                    mybluetoothTx0.print(item);
                                    mybluetoothTx0.println();
                                    delay(100);
                                    mybluetoothTx0.print("Some Text here");
                                    mybluetoothTx0.println();
                                    delay(100);
                                    ebotSing(0);
                                    tone(12, 2093, 1000);
                                    tone(12, 2093, item);
                                    tone(12, 1000, item);
                                    tone(12, 1000, 1000);
                                    tone(12, item, 1000);

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
              if(cds(A4)>=0 && cds(A4)<=1023)
              {
              delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
              LightA4Count++;
              }
              if(LightA4Count==0)
              {
              LightA4Count=0;
                if(Potentiometer(A4)>=0 && Potentiometer(A4)<=1023)
                {
                delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                PotentiometerA4Count++;
                }
                if(PotentiometerA4Count==0)
                {
                PotentiometerA4Count=0;
                  if(cds(A4)<=0 || cds(A4)>=1023)
                  {
                  delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                  LightA4Count++;
                  }
                  if(LightA4Count==0)
                  {
                  LightA4Count=0;
                    if(Potentiometer(A4)<=0|| Potentiometer(A4)>=1023)
                    {
                    delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                    PotentiometerA4Count++;
                    }
                    if(PotentiometerA4Count==0)
                    {
                    PotentiometerA4Count=0;
                      if(ir(A4)<=0|| ir(A4)>=1023)
                      {
                      delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                      IRA4Count++;
                      }
                      if(IRA4Count==0)
                      {
                      IRA4Count=0;
                        if(ir(A4)>=0 && ir(A4)<=1023)
                        {
                        delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                        IRA4Count++;
                        }
                        if(IRA4Count==0)
                        {
                        IRA4Count=0;
                          if(edge(A4,RISING))
                          {
                          delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                          EdgeA4Count++;
                          }
                          if(EdgeA4Count==0)
                          {
                          EdgeA4Count=0;
                            if(edge(A4,FALLING))
                            {
                            delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                            EdgeA4Count++;
                            }
                            if(EdgeA4Count==0)
                            {
                            EdgeA4Count=0;
                              if(button(A4,PRESSED))
                              {
                              delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                              ButtonA4Count++;
                              }
                              if(ButtonA4Count==0)
                              {
                              ButtonA4Count=0;
                                if(button(A4,RELEASED))
                                {
                                delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                                ButtonA4Count++;
                                }
                                if(ButtonA4Count==0)
                                {
                                ButtonA4Count=0;
                                  if(ir_rc(&rc4,FW))
                                  {
                                  delay(100); //Delay for 0 hours 0 mins 0 sec 100 ms
                                  RemoteA4Count++;
                                  }
                                  if(RemoteA4Count==0)
                                  {
                                  RemoteA4Count=0;
                                    CustomOutput(ebot_pro_pin(1),HIGH);
                                    CustomOutput(ebot_pro_pin(1),LOW);
                                    CustomOutput(ebot_pro_pin(1),item);
                                    CustomOutput(ebot_pro_pin(2),0);
                                    CustomOutput(ebot_pro_pin(2),item);
                                    d2="$000CN";
                                    d2+="Some text here";
                                    d2+="#";
                                    lcd2.println(d2);
                                    delay(200);
                                    d2="$081CN";
                                    d2+="Some text here";
                                    d2+="#";
                                    lcd2.println(d2);
                                    delay(200);
                                    d2="$081CN";
                                    d2+=item;
                                    d2+="#";
                                    lcd2.println(d2);
                                    delay(200);
                                    digitalWrite(8, HIGH);
                                    digitalWrite(8, LOW);
                                    digitalWrite(ebot_pro_pin(3), HIGH);
                                    digitalWrite(ebot_pro_pin(3), LOW);
                                    LeftMotor(0);
                                    LeftMotor(item);
                                    RightMotor(0);
                                    LeftMotor(item);
                                    RightMotor(item);
                                    RightMotor(item);
                                    RightMotor(0);

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
              if(CustomInput(A5)>=0 && CustomInput(A5)<=1023)
              {
                if(edge(A5, RISING))
                {
                  if(edge(A5, FALLING))
                  {
                    if(CustomInput(A5)<=0|| CustomInput(A5)>=1023)
                    {
                      if(readFromMPU(angleX,xOff) >=-180 && readFromMPU(angleX,xOff) <= 180)
                      {
                        if(readFromMPU(angleX,xOff) <=-180 || readFromMPU(angleX,xOff) >= 180)
                        {
                          if(ir_rc(&rc6,FW))
                          {
                            if(cds(A7)>=0 && cds(A7)<=1023)
                            {
                              if(cds(A7)<=0 || cds(A7)>=1023)
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
      
      if(isSerCharEqls(&mybluetoothRxA3,'U'))
      {
        if(isSerCharEqls(&mybluetoothRxA0, 'A'))
        {
          if(ir_rc(&rc1,FW))
          {
            if(ir(A2)>=0 && ir(A2)<=1023)
            {
              if(isSerCharEqls(&mybluetoothRxA3,'U'))
              {
                if(isSerStrEqls(&mybluetoothRxA0,"Some text here"))
                {
                  if(ir_rc(&rc1,FW))
                  {
                    if(ir(A2)<=0 || ir(A2)>=1023)
                    {
                      if(Potentiometer(A4)>=0 && Potentiometer(A4)<=1023)
                      {
                        if(Potentiometer(A4)<=0 || Potentiometer(A4)>=1023)
                        {
                          Serial.print("MMAP|D:*Cbits*Ebot*sound.mp3|>"); //Command to play Audio
                          Serial.println();
                          delay(100);
                          Serial.print("MMFO|D:*Cbits*Ebot*image.jpg|>"); //Command to open File
                          Serial.println();
                          delay(100);
                        }
                        else if(Potentiometer(A4)>=0 && Potentiometer(A4)<=1023)
                        {
                          Serial.print("MMIO|D:*Cbits*Ebot*image.jpg|>"); //Command to open Image
                          Serial.println();
                          delay(100);
                          Serial.print("MMVP|D:*Cbits*Ebot*video.mp4|>"); //Command to play Video
                          Serial.println();
                          delay(100);
                        }
                        else
                        {
                          Serial.println("MMIC|>"); //Command to close Image
                          Serial.println();
                          delay(100);
                          Serial.println("MMVS|>"); //Command to stop Video
                          Serial.println();
                          delay(100);
                        }

                      }
                    }

                  }

                }

              }
              if(isSerCharEqls(&myserialRxA5, 'A'))
              {
                if(isSerStrEqls(&myserialRxA5,"Some Text here"))
                {
                  if(!digitalRead(16) && !digitalRead(17) && !digitalRead(18)){
                    if(soundLevel(A6)>=60 && soundLevel(A6)<=100)
                    {
                      if(soundLevel(A6)<=60 || soundLevel(A6)>=100)
                      {
                        if(temp(16) >= 0 && temp(16) <= 100)
                        {
                          if(temp(16) <= 0 || temp(16) >= 100)
                          {
                            if(ultrasound(A7)>=0 && ultrasound(A7)<=250)
                            {
                              if(ultrasound(A7)<=0|| ultrasound(A7)>=250)
                              {
                                for (;;)
                                {
                                  mybluetoothTx0.print("Some TExt here");
                                  mybluetoothTx0.println();
                                  delay(100);
                                  mybluetoothTx0.print(item);
                                  mybluetoothTx0.println();
                                  delay(100);
                                  RightMotor(0);
                                  RightMotor(item);
                                  digitalWrite(ebot_pro_pin(1),HIGH);
                                  if (array_item[0] == digitalRead(A0)) {
                                    digitalWrite(ebot_pro_pin(1),LOW);
                                  }
                                  else if (analogRead(A0)) {
                                    strip2.setPixelColor(0,strip2.Color(255,255,255));
                                    strip2.show();
                                    delay(10);
                                  }
                                  strip2.setPixelColor(0,strip2.Color(item,item,item));
                                  strip2.show();
                                  delay(10);
                                  colorWipe(&strip11, 255,255,255, 100);
                                  rainbow(&strip11, 25);
                                  rainbow(&strip11, 25);


                                  strip11.setPixelColor(0, strip11.Color(0,0,255));
                                  strip11.setPixelColor(1, strip11.Color(0,255,21));
                                  strip11.setPixelColor(2, strip11.Color(255,242,0));
                                  strip11.setPixelColor(3, strip11.Color(255,0,72));
                                  strip11.show();
                                  delay(20);


                                  strip3.setPixelColor(0, strip3.Color(21,0,255));
                                  strip3.setPixelColor(1, strip3.Color(0,255,34));
                                  strip3.setPixelColor(2, strip3.Color(255,255,255));
                                  strip3.setPixelColor(3, strip3.Color(255,0,0));
                                  strip3.show();
                                  delay(20);
                                  colorWipe(&strip3, 255,255,255, 100);
                                  rainbow(&strip3, 25);
                                  colorWipe(&strip3, 255,255,255, 100);
                                  myserialtx4.print(" ");
                                  myserialtx4.println();
                                  delay(100);
                                  myserialtx4.print(item);
                                  myserialtx4.println();
                                  delay(100);
                                  delay(500); //Delay for 0 hours 0 mins 0 sec 500 ms

                                  myservo_5.write(90);

                                  myservo_5.write(item);

                                  myservo_6.write(10 * 9);

                                  myservo_6.write(10 * 9 + 0);

                                  myservo_6.write(item * 9 + 0);
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


}
