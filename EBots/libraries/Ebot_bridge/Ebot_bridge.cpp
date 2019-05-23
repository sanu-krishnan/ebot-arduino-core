/*
This library is written to deeply embedded mobilephone pragramability in ebot8 pro

Coded on    :   29/04/2019
Updated On  :   29/04/2019
Coded by    :   sanu
Coded for   :   CBits
*/

#include "Ebot_bridge.h"
// #include "Ebot.h"
// #include "Servo.h"
// #include "EbotSound.h"
// #include "Adafruit_NeoPixel.h"
// #include "SoftwareSerial.h"
// #include "I2Cdev.h"
// #include "libraries/MPU6050/MPU6050_6Axis_MotionApps20.h"


int outputPinMap(int pinNum)
{
    //return ebot_pro_p[pinNum];
    return pinNum;
}

/**********************   Supporting Functions      ****************/
int analog_in(uint8_t pin)
{
    pinMode(pin, INPUT);
    return (int)(analogRead(pin));
    //return (int)(analogRead(pin) * 0.833);
}
int digital_in(uint8_t pin)
{
    pinMode(pin, INPUT);
    return (digitalRead(pin));
}
int temp(uint8_t pin)
{
    pinMode(pin, INPUT);
    return (int)((analogRead(pin)) / 2.048);
}
int distance(uint8_t pin)
{
    pinMode(pin, INPUT);
    return (int)(analogRead(pin) / 4);
}
void printES()
{
    SerialPort.print("$ES#");
}
void printED()
{
    SerialPort.print("$ED#");
}
void sSerialRead(uint8_t pin, int baud, char *read_Data)
{
    SoftwareSerial mySerial(pin, 255); //RX TX
    mySerial.begin(baud);
    while (mySerial.available() <= 0)
        ;
    byte size = mySerial.readBytesUntil('\n', read_Data, INPUT_SIZE);
    read_Data[size] = 0;
    mySerial.end();
}
char sSerialReadChar(uint8_t pin, int baud)
{
    SoftwareSerial mySerial(pin, 255); //RX TX
    mySerial.begin(baud);
    while (mySerial.available() <= 0)
        ;
    char d = mySerial.read();
    mySerial.end();
    return d;
}
/*******************    Command Decode Function    *******************/
int cmdDecode()
{
    while (SerialPort.available() <= 0);
    byte size = SerialPort.readBytesUntil('\n', input, INPUT_SIZE);
    input[size] = 0;
    char *command = strtok(input, " ");
    if (command != 0)
    {
        /*************************  Sound SENSOR/ MIC *************************/
        if ((command[0] == 'm') && (command[1] == 'i'))
        {
            int pin = _NEXT_INT;
            printED();
            SerialPort.println((int)((analog_in(pin) - 600) / 4.24));
            return 1;
        }

        /*************************  ULTRASONIC SENSOR *************************/
        else if ((command[0] == 'u') && (command[1] == 's'))
        {
            int pin = _NEXT_INT;
            printED();
            SerialPort.println(distance(pin));
            return 1;
        }

        /*************************  COLOR SENSOR *************************/
        if ((command[0] == 'c') && (command[1] == 'l') && (command[2] == 'r'))
        {
            int pin = _NEXT_INT;
            printED();
            SerialPort.println(senseColor(pin));
            return 1;
        }

        /*************************  SERVO *************************/
        else if ((command[0] == 's') && (command[1] == 'e'))
        {
            uint8_t pin = outputPinMap(_NEXT_INT);
            pinMode(pin, OUTPUT);
            myservo[pin].attach(pin, -270, 270);
            int v = _NEXT_INT;
            //SerialPort.println(pin);
            //SerialPort.println(v);
            myservo[pin].write(v);
            v = _NEXT_INT;
            printES();
            SerialPort.println(v);
            return 1;
        }

        /*************************  SERVO MULTIPLE *************************/
        // format SE <number of servos> <servo1 pin> <servo1 angle> <servo2 pin> <servo2 angle> ......
        //example SE 5 0 90 1 80 2 70 3 60 4 50
        else if ((command[0] == 'S') && (command[1] == 'E'))
        {
            uint8_t servoCount = _NEXT_INT;
            uint8_t pin;
            int angle;
            for (cc = 0; cc < servoCount; cc++)
            {
                pin = outputPinMap(_NEXT_INT);
                pinMode(pin, OUTPUT);
                myservo[servoIndexof(pin)].attach(pin, -270, 270);
                angle = _NEXT_INT;
                myservo[servoIndexof(pin)].write(angle);
            }
            pin = _NEXT_INT;
            printES();
            SerialPort.println(pin);
            return 1;
        }

        /*************************  MPU 6050  *************************/
        else if ((command[0] == 'm') && (command[1] == 'p'))
        {
            int pin = 0;
            if (command[2] == 'X')
                pin = readFromMPU(realAccelerationX);
            else if (command[2] == 'Y')
                pin = readFromMPU(realAccelerationY);
            else if (command[2] == 'Z')
                pin = readFromMPU(realAccelerationZ);
            else if (command[2] == 'x')
                pin = readFromMPU(angleX);
            else if (command[2] == 'y')
                pin = readFromMPU(angleY);
            else if (command[2] == 'z')
                pin = readFromMPU(angleZ);
            else
                return 0;

            printED();
            SerialPort.println(pin);
            return 1;
        }

        /*************************  TEMPERATURE SENSOR  *************************/
        else if ((command[0] == 't') && (command[1] == 'e'))
        {
            int pin = _NEXT_INT;
            printED();
            SerialPort.println(temp(pin));
            return 1;
        }
        /************************* ANALOG  *************************/
        else if (command[0] == 'a')
        {
            uint8_t pin = _NEXT_INT;
            if (command[1] == 'r') //READ
            {
                printED();
                SerialPort.println(analog_in(pin));
                return 1;
            }
            else if (command[1] == 'w')
            { //WRITE
                pinMode(pin, OUTPUT);
                analogWrite(pin, _NEXT_INT); // directly inserting strtok for pin in this line is not working !
                printES();
                SerialPort.println(_NEXT_INT);
                return 1;
            }
        }
        /*************************  DIGITAL *************************/
        else if (command[0] == 'd') //DIGITAL
        {
            uint8_t pin = _NEXT_INT;
            if (command[1] == 'w') //WRITE
            {
                pin = outputPinMap(pin);
                pinMode(pin, OUTPUT);
                digitalWrite(pin, _NEXT_INT); // directly inserting strtok for pin in this line is not working !
                pin = _NEXT_INT;
                printES();
                SerialPort.println(pin);
                return 1;
            }
            else if (command[1] == 'r')
            { //READ
                printED();
                SerialPort.println(digital_in(pin));
                return 1;
            }
        }
        /*************************  RGBLED  *************************/
        else if ((command[0] == 'c') && (command[1] == 'l'))
        {
            uint8_t pin = outputPinMap(_NEXT_INT);
            pinMode(pin, OUTPUT);
            //static Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);
            uint8_t r = _NEXT_INT;
            uint8_t g = _NEXT_INT;
            uint8_t b = _NEXT_INT;
            if (pin == 11)
            { //default pin in EBOT4, scale brightness to 100
                r /= 2.5;
                g /= 2.5;
                b /= 2.5;
            }

            pixelArray[pin].setPixelColor(0, pixelArray[pin].Color(r, g, b));
            pixelArray[pin].show();
            pin = _NEXT_INT;
            printES();
            SerialPort.println(pin);
            return 1;
        }

        /******************************  RGBLED Strip ***********************************/
        /*assumption -> number of LEDs will be always 10
    difference in block UI -> setting individual color will have option to set color of 1 pixel only (10 pixels with corrsponding r,g,b values need long commands)
    ********    color Wipe Syntax
                  CL <pin> 0 <r> <g> <b> <delay> <uniqNumb>
    *******   rainbow Syntax
                  CL <pin> 1  <delay> <uniqNumb>
    *********   individual colors Syntax
                  CL <pin> 2 <pixelNUmb> <r> <g> <b>  <uniqNumb>
                  //Pixel number ranges from 0 to 9
    *********    Gadient Syntax
                  CL <pin> 3 <r1> <g1> <b1> <r2> <g2> <b2>  <uniqNumb>
    */
        else if ((command[0] == 'C') && (command[1] == 'L'))
        {
            uint8_t pin = outputPinMap(_NEXT_INT);
            pinMode(pin, OUTPUT);
            stripArray[pin].begin();
            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t d;
            uint8_t pin2 = _NEXT_INT; //dummy read for number of LEDs
            pin2 = _NEXT_INT;
            if (pin2 == 0)
            { // color wipe
                r = _NEXT_INT;
                g = _NEXT_INT;
                b = _NEXT_INT;
                d = _NEXT_INT; //delay
                colorWipe(&stripArray[pin], r, g, b, d);
            }
            else if (pin2 == 1)
            { //rainbow
                d = _NEXT_INT;
                rainbow(&stripArray[pin], d);
            }
            else if (pin2 == 2)
            {                  //individual colors
                d = _NEXT_INT; //pixel numb
                r = _NEXT_INT;
                g = _NEXT_INT;
                b = _NEXT_INT;
                stripArray[pin].setPixelColor(d, stripArray[pin].Color(r, g, b));
                stripArray[pin].show();
            }
            else if (pin2 == 3)
            { //gradient
                r = _NEXT_INT;
                g = _NEXT_INT;
                b = _NEXT_INT;
                uint8_t r1 = _NEXT_INT;
                uint8_t g1 = _NEXT_INT;
                uint8_t b1 = _NEXT_INT;
                colorGradient(&stripArray[pin], r, g, b, r1, g1, b1);
                //200 bytes
            }
            else
            {
                return false;
            }
            pin = _NEXT_INT;
            printES();
            SerialPort.println(pin);
            return 1;
        }
        /************************* TONE FOR BUZZER *************************/
        else if ((command[0] == 't') && (command[1] == 'n'))
        {
            uint8_t pin = outputPinMap(_NEXT_INT);
            ;
            pinMode(pin, OUTPUT);
            int frequency = _NEXT_INT;
            int duration = _NEXT_INT;
            printES();
            SerialPort.println(_NEXT_INT);
            tone(pin, frequency, duration);
            return 1;
        }
        /*************************  Sing *************************/
        // sg <pin> <sondIndex>
        // eg: pin 0, song index 3
        //	sg 0 3
        else if ((command[0] == 's') && (command[1] == 'g'))
        {
            uint8_t pin = outputPinMap(_NEXT_INT);
            uint8_t frequency = _NEXT_INT;
            ebotSingInit(pin); //Buzzer
            ebotSing(frequency);
            printES();
            SerialPort.println(_NEXT_INT);
            return 1;
        }

        /*************************  DC MOTORS *************************/

        else if (command[0] == 'm')
        {
            int speed = _NEXT_INT;
            if (speed <= 10)
                LeftMotor(speed);
            speed = _NEXT_INT;
            if (speed <= 10)
                RightMotor(speed);
            printES();
            SerialPort.println(_NEXT_INT);
            return 1;
        }

        /*************************  SOFT SERIAL & LCD   *************************/
        else if (command[0] == 's')
        {
            int pin = outputPinMap(_NEXT_INT);
            int baud = _NEXT_INT;
            if (command[1] == 's')
            {                                      //serial sent
                SoftwareSerial mySerial(255, pin); //RX TX
                mySerial.begin(baud);
                mySerial.println(strtok(0, "||"));
                pin = atoi(strtok(0, "||"));
                delay(250);
                mySerial.end();
                printES();
                SerialPort.println(pin);
                return 1;
            }

            //700 bytes
        }
        /*************************  DIP switches  *************************/
        else if ((command[0] == 'D') && (command[1] == 'I') && (command[2] == 'P'))
        {
            pinMode(16, INPUT_PULLUP);
            pinMode(17, INPUT_PULLUP);
            pinMode(18, INPUT_PULLUP);
            printED();
            SerialPort.println((!digitalRead(16)) * 4 + (!digitalRead(17)) * 2 + (!digitalRead(18)) * 1);
            return 1;
        }

        /************************* Firmware & Hardware Query*************/
        else if ((command[0] == 'V') && (command[1] == 'E') && (command[2] == 'F'))
        {
            SerialPort.println(EBOT_BRIDGE_VER);
            return 1;
        }
        else if ((command[0] == 'V') && (command[1] == 'E') && (command[2] == 'H'))
        {
            SerialPort.println("EBOT_8");

            return 1;
        }

        //150Bytes
        /*************************  STOP command *************************/
        else if ((command[0] == 'X') && (command[1] == 'X'))
        {
            for (int i = 0; i < 8; i++)
            {
                digitalWrite(i, LOW);
                RightMotor(0);
                LeftMotor(0);
            }
            printES();
            SerialPort.println(_NEXT_INT);
            return 1;
        }
    } // end of valid command
    else
        return 0;
}
/************************* Setup *************************/
void bridge_setup()
{
    mpu6050_init();
    SerialPort.begin(9600);
    for (int i = 0; i <= 8; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
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
}
/************************* Loop *************************/
void bridge_loop()
{
    cmdDecode();
}