#ifndef __EBOTBRIDGE_H__
#define __EBOTBRIDGE_H__

#include "Ebot.h"
#include "Servo.h"
#include "Adafruit_NeoPixel.h"
#include "SoftwareSerial.h"

// #include "I2Cdev.h"
// #include "libraries/MPU6050/MPU6050_6Axis_MotionApps20.h"

#define EBOT_BRIDGE_VER 200
#define INPUT_SIZE 60
#define timeOut 500
#define _NEXT_INT (atoi(strtok(0, " ")))
#define _NEXT_CHAR (strtok(0, " "))

const int ebot_pro_p[9] = {6, 7, 2, 3, 4, 5, 0, 1, 8};
#define SerialPort Serial1

#define numberOfPins 8
#define servoIndexof(x) (x)

static Adafruit_NeoPixel stripArray[] = {
    Adafruit_NeoPixel(10, 0, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 1, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 2, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 3, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 4, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 5, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 6, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(10, 7, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(4, 11, NEO_GRB + NEO_KHZ800), // sent 8 as pin number from smartphone
};
static Adafruit_NeoPixel pixelArray[] = {
    Adafruit_NeoPixel(1, 0, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 1, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 2, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 3, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 4, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 5, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(1, 7, NEO_GRB + NEO_KHZ800),
};


static Servo myservo[numberOfPins];
static volatile uint8_t servoResp = 0;
static char input[INPUT_SIZE + 1];
static uint8_t cc = 0;
static String strData;
static char charData;


void sSerialRead(uint8_t pin, int baud, char *readString);
char sSerialReadChar(uint8_t pin, int baud);
int outputPinMap(int pinNum);


int analog_in(uint8_t pin);
int digital_in(uint8_t pin);
int digital_in(uint8_t pin);
int temp(uint8_t pin);
int distance(uint8_t pin);
void printES();
void printED();
void sSerialRead(uint8_t pin, int baud, char* read_Data);
char sSerialReadChar(uint8_t pin, int baud);
int cmdDecode();

void bridge_setup();
void bridge_loop();

#endif
