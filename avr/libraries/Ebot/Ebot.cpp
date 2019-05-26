#include <Ebot.h>

//#include <SoftwareSerial.h>

#ifdef EBOT_8
#include "Ebot_bridge.h"
MCP7940_Class rtc; //rtc
#endif

//#ifdef  EBOT_8
EbotSound eboSound;
//#endif

//#ifdef EBOT_4
/* =========== For MPU6050 ============================*/
#include "I2Cdev.h"
#include "libraries/MPU6050/MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;        // [w, x, y, z]         quaternion container
VectorInt16 aa;      // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity; // [x, y, z]            gravity vector
float euler[3];      // [psi, theta, phi]    Euler angle container
float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
int16_t ax, ay, az;
int16_t gx, gy, gz;

uint8_t ebot_pro_pins[8] = {6, 7, 2, 3, 4, 5, 0, 1};
// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = {'$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n'};

//bluetooth
void setBluetoothName(String strName, uint8_t type)
{
    //Define which Ebot version used
    if (type == EBOT8PRO || type == EBOT4)
    {
        Serial1.print("AT"); //Initialize AT-commands
        delay(100);
        Serial1.print("AT+NAME" + strName); //Change The Name || MAX = 12
        delay(100);
        Serial1.print("AT+ROLE0"); //Put the bluetooth module in Slave mode
        delay(100);
        Serial1.print("AT+IMME0"); //Put the bluetooth module in Auto mode
        delay(100);
        Serial1.print("AT+RESET");
        delay(500);
    }
    else
    {
        Serial.print("AT"); //Initialize AT-commands
        delay(100);
        Serial.print("AT+NAME" + strName); //Change The Name || MAX = 5
        delay(100);
        Serial.print("AT+ROLE0"); //Put the bluetooth module in Slave mode
        delay(100);
        Serial.print("AT+IMME0"); //Put the bluetooth module in Auto mode
        delay(100);
        Serial.print("AT+RESET");
        delay(500);
    }
    //Serial.println("Name Changed to" + strName);
}

void disconnectBluetooth(uint8_t type)
{
    if (type == EBOT8PRO || type == EBOT4)
    {
        Serial1.print("AT+IMME1"); //Disable automatic actions
        delay(100);
        Serial1.print("AT+ROLE0"); //Put the bluetooth module in Slave mode
        delay(100);
        Serial1.print("AT+RESET");
        delay(100);
    }
    else
    {
        Serial.print("AT+IMME1"); //Disable automatic actions
        delay(100);
        Serial.print("AT+ROLE0"); //Put the bluetooth module in Slave mode
        delay(100);
        Serial.print("AT+RESET");
        delay(100);
    }
}
void connectBluetoothTo(String strName, uint8_t type)
{
    String received = " ";
    //    String BtName;
    String BtMac;
    //Define which Ebot version used
    if (type == EBOT8PRO || type == EBOT4)
    {
        Serial1.print("AT");
        delay(200);
        Serial1.print("AT+IMME1"); //Disable automatic actions
        delay(100);
        Serial1.print("AT+ROLE1"); //Put the bluetooth module in Master mode
        delay(100);
        Serial1.print("AT+SHOW3"); //To show the Name and RSSI of devices in the search
        delay(100);
        Serial1.print("AT+RESET"); //Restart to apply changes
        delay(1000);
        Serial1.print("AT+DISC?"); //Search for available bluetooth devices

        while (Serial1.available() == 0)
            ;
        Serial1.setTimeout(3000);
        received = Serial1.readString();
    }
    else
    {
        strName = strName.substring(0, 5); //Only 5 char. allowed in the name

        Serial.print("AT");
        delay(200);
        Serial.print("AT+IMME1"); //Disable automatic actions
        delay(100);
        Serial.print("AT+ROLE1"); //Put the bluetooth module in Master mode
        delay(100);
        Serial.print("AT+SHOW1"); //To show the Name of devices in the search
        delay(100);
        Serial.print("AT+RESET"); //Restart to apply changes
        delay(1000);
        Serial.print("AT+DISC?"); //Search for available bluetooth devices

        while (Serial.available() == 0)
            ;
        Serial.setTimeout(3000);
        received = Serial.readString();
    }

    if (received.indexOf(strName) != -1)
    {                                        //Check if the entered bluetooth device is found or not
        int pos = received.indexOf(strName); //If found, save the position of the name of it

        //Connect to the found Mac address
        if (type == EBOT8PRO || type == EBOT4)
        {
            BtMac = received.substring(pos - 35, pos - 20); //Get the Mac based on the Name pos. with ':' before it and "OK" after it
            if (BtMac.substring(0, 1) == ":" && BtMac.substring(13, 15) == "OK")
            {                                   //Verifying
                BtMac = BtMac.substring(1, 13); //Clearifying
                //Serial.println("Found With MAC Addr. = "+BtMac);   //Debug
                Serial1.print("AT+IMME0");
                delay(100);
                Serial1.print("AT+CON" + BtMac);
                delay(100);
                //Serial.println("Connected to: "+strName+", MAC: "+BtMac);
            }
            else
            {
                Serial.println("Unable to connect. please try again!");
            }
        }
        else
        {
            BtMac = received.substring(pos - 21, pos - 6); //Get the Mac based on the Name pos. with ':' before it and "OK" after it
            if (BtMac.substring(0, 1) == ":" && BtMac.substring(13, 15) == "OK")
            {                                   //Verifying
                BtMac = BtMac.substring(1, 13); //Clearifying
                //Serial.println("Found With MAC Addr. = "+BtMac);  //Debug
                Serial.print("AT+IMME0");
                delay(100);
                Serial.print("AT+CON" + BtMac);
                delay(100);
                //Serial.println("Connected to: "+strName+", MAC: "+BtMac);
            }
            else
            {
                Serial.println("Unable to connect. please try again!");
            }
        }

        /* Another method: (searching for all blu. devices and selecting which one)
    
                    int pos1 = received.indexOf("NAME:"); //Take the pos. of the first name in the string
                    int pos2 = received.indexOf("DIS0:"); //Take the pos. of the first MAC in the string
                    int pos3 = -1;
                    int pos4 = -1;
            
                    BtName = received.substring(pos1+5, pos1+strName.length()+5); //Save the Name based on position
                    Serial.println("HEREEEEEEEEEEE is the NAME = "+BtName); //Debug
                    if (BtName == strName){ //Check If it's the same as the geven name
                            BtMac = received.substring(pos2+5, pos2+17); //Save the MAC based on position
                            Serial.println("Found from the first time = "+BtName); //Debug
                            Serial.println("With MAC Addr. "+BtMac); //Debug
                    } else { //If it's not the first detected one search for it
                            for (int c = 1 ; c < 6 ; c++){ //Max 6 dev.
                                    pos3 = received.indexOf("NAME:", pos1 + c ); //Take the next Name pos. found in the string
                                    pos4 = received.indexOf("DIS0:", pos1 + c ); //Take the next Mac pos. found in the string
                    
                                    BtName = received.substring(pos3+5, pos3+strName.length()+5); //Save them
                                    BtMac = received.substring(pos4+5, pos4+17);
                                    Serial.println("Found Name = "+BtName);
                                    Serial.println("Found Mac = "+BtMac);
                                    if (BtName == strName) break; //Compare if found break
                                    else { //If not then assign the already known pos. to the first two to search for the next one
                                            pos1 = pos3;
                                            pos2 = pos4;
                                    }
                            }
                    }
         */
    }
    else
    {
        Serial.println("Unable to connect. try again!");
    }

    //Serial.println(received + " == OUUUUUUT");
}

void mpu6050_init()
{
    // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
#endif

    mpu.initialize();
    if (mpu.testConnection() == 0)
        Serial.println("MPU6050 connection failed");

    // load and configure the DMP
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    // mpu.setXGyroOffset(220);
    // mpu.setYGyroOffset(76);
    // mpu.setZGyroOffset(-85);

    mpu.setXGyroOffset(0);
    mpu.setYGyroOffset(0);
    mpu.setZGyroOffset(0);
    mpu.setZAccelOffset(1688); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
    }
}

float getTempfromMPU()
{
    return mpu.getTemperatureDegreeC();
}

float readFromMPU(int choice)
{
    return readFromMPU(choice, 0);
}

float readFromMPU(int choice, int offset)
{
    float MPUdata;
    boolean validData = 0;
    while (validData == 0)
    {
        //Serial.print(".");
        mpuIntStatus = mpu.getIntStatus();
        // get current FIFO count
        fifoCount = mpu.getFIFOCount();
        // check for overflow (this should never happen unless our code is too inefficient)
        if ((mpuIntStatus & 0x10) || fifoCount == 1024)
        {
            // reset so we can continue cleanly
            mpu.resetFIFO();
            //Serial.println(F("FIFO overflow!"));
            // otherwise, check for DMP data ready interrupt (this should happen frequently)
        }
        else if (mpuIntStatus & 0x02)
        {
            // wait for correct available data length, should be a VERY short wait
            while (fifoCount < packetSize)
                fifoCount = mpu.getFIFOCount();
            // read a packet from FIFO
            mpu.getFIFOBytes(fifoBuffer, packetSize);

            validData = true;
            // track FIFO count here in case there is > 1 packet available
            // (this lets us immediately read more without waiting for an interrupt)
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
            int val;

            switch (choice)
            {
                /*case quaternionX:    MPUdata= ax;    break;
                    case quaternionY:    MPUdata= ay;    break;
                    case quaternionZ:    MPUdata= az;    break;
                    case quaternionW:    MPUdata= q.w;    break;
                    case euler0: MPUdata= euler[0]* 180/M_PI; break;
                    case euler1:    MPUdata= euler[1]* 180/M_PI; break;
                    case euler2:    MPUdata= euler[2]* 180/M_PI; break;

                    case yaw:    MPUdata= ypr[0] * 180/M_PI;   break;
                    case pitch:   MPUdata= ypr[1] * 180/M_PI;   break;
                    case roll:   MPUdata= ypr[2] * 180/M_PI;   break;

                    case realAccelerationX:   MPUdata= aaReal.x;   break;
                    case realAccelerationY:   MPUdata= aaReal.y;   break;
                    case realAccelerationZ:   MPUdata= aaReal.z;   break;

                    case accelerationX:   MPUdata= aaWorld.x;   break;
                    case accelerationY:   MPUdata= aaWorld.y;   break;
                    case accelerationZ:   MPUdata= aaWorld.z;   break;
                     */
            case realAccelerationX:
                MPUdata = aaReal.x;
                break;
            case realAccelerationY:
                MPUdata = aaReal.y;
                break;
            case realAccelerationZ:
                MPUdata = aaReal.z;
                break;

            case accelerationX:
                MPUdata = aaWorld.x;
                break;
            case accelerationY:
                MPUdata = aaWorld.y;
                break;
            case accelerationZ:
                MPUdata = aaWorld.z;
                break;

                //case angleZ:   MPUdata= relativeAngleZ(ypr[0] * 180/M_PI); break;//MPUdata= euler[0]* 180/M_PI; break; //euler0
                //case angleX:   MPUdata= relativeAngleX(ypr[2]  * 180/M_PI); break; //euler1 data is not reliable
                //case angleY:   MPUdata= relativeAngleY(ypr[1] * 180/M_PI); break;//MPUdata= euler[2]* 180/M_PI; break; //euler2

            case angleZ:
                MPUdata = relativeAngle(ypr[0] * 180 / M_PI, offset);
                break;   //MPUdata= euler[0]* 180/M_PI; break; //euler0
            case angleY: // MPUdata = ypr[1]* 180 / M_PI;//relativeAngle(euler[1]* 180 / M_PI, offset);
                val = (ypr[1] * 180 / M_PI);
                if (az < 0)
                    MPUdata = val;
                else if (val >= 0)
                    MPUdata = 180 - val;
                else if (val < 0)
                    MPUdata = -180 - val;
                MPUdata = relativeAngle(MPUdata, offset);
                break; //MPUdata= euler[2]* 180/M_PI; break; //euler2

            case angleX:
                val = (ypr[2] * 180 / M_PI);
                if (az < 0)
                    MPUdata = val;
                else if (val >= 0)
                    MPUdata = 180 - val;
                else if (val < 0)
                    MPUdata = -180 - val;

                MPUdata = relativeAngle(MPUdata, offset);
                break;

            default:
                MPUdata = 0;
                break;
            }
        }
    }
    return MPUdata;
}
//#endif
/*===========================End of MPU==========================*/

#ifdef EBOT_4
#define NUMBER_OF_PINS 4
/*Adafruit_NeoPixel startup_strip = Adafruit_NeoPixel(4, 11, NEO_GRB + NEO_KHZ800);
uint8_t index = 0;
uint8_t rgb_startup_color[] =








void startup_colorWipe(uint32_t c, uint8_t wait) {
for(uint16_t i=0; i<startup_strip.numPixels(); i++) {
startup_strip.setPixelColor(i, c);
startup_strip.show();
delay(wait);
}
}*/
#endif

#ifdef EBOT_8
#define NUMBER_OF_PINS 8
static unsigned char remote_cu_key = OFF;
//static decode_results res;
decode_results results;
#endif

#ifdef EBOT_ARDUINO
#define NUMBER_OF_PINS 6
#endif

char serChar;
char serStr[31];

struct pinStatus edg[8], btn[8];

static Motors motors;

void ebot_setup()
{

    for (int i = 0; i < NUMBER_OF_PINS; i++)
    {
        btn[i].cu = btn[i].pre = HIGH;
        btn[i].acted = false;
        edg[i].cu = edg[i].pre = HIGH;
        edg[i].acted = false;
    }
#ifdef EBOT_4
    digitalWrite(17, LOW); //rx led
    pinMode(BLE_KEY, OUTPUT);
    digitalWrite(BLE_KEY, HIGH);
#endif

#ifdef EBOT_8 //ebot8 pro
    // turn SCL and SDA lines to 0
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    // BLE init
    pinMode(PB3, OUTPUT);
    digitalWrite(PB3, HIGH);

    pinMode(16, INPUT_PULLUP); //Slide Switches
    pinMode(17, INPUT_PULLUP); //Slide Switches
    pinMode(18, INPUT_PULLUP); //Slide Switches

    if (!digitalRead(18) && !digitalRead(17) && !digitalRead(16))
    { // if bridge mode is selected
        bridge_setup();
        while (1)
        {
            bridge_loop();
        }
    }
    // Serial1.begin(9600);
    // Serial1.print("AT");  delay(100);
    // Serial1.print("AT+RENEW");  delay(1000);
    // Serial1.print("AT+TYPE3");  delay(200);
    // Serial1.print("AT+MODE2");  delay(200);
    // Serial1.print("AT+NAMEEBot8Pro");  delay(200);
    // Serial1.print("AT+RESET");  delay(1000);
#endif
    /*#ifdef EBOT_4
    edg[6].cu = edg[6].pre = LOW ;
    edg[6].acted = false;
    edg[7].cu = edg[7].pre = LOW ;
    edg[7].acted = false;

    #endif
     */
    //#ifdef EBOT_4
    // Serial.begin(9600);
    // startup_strip.begin();
    // startup_strip.show();
    //for (uint8_t ii = 0; ii < 5; ii++) {
    //startup_colorWipe(startup_strip.Color(rgb_startup_color[index++], rgb_startup_color[index++], rgb_startup_color[index++]),50); // Red
    // delay(100);
    // }
    //#endif
    ////////////////////////////////////////
}

int senseColor(int pin)
{
    int val = analogRead(pin);
    if (val < 150)
        return map(val, 0, 150, 0, 70);
    else if (val < 300)
        return map(val, 151, 300, 71, 300);
    else if (val < 500)
        return 360;
    else
        return ((int)(val * 0.833));
}

#ifdef EBOT_8

int ebot_pro_pin(int p)
{
    return ebot_pro_pins[p];
}

void rtc_init()
{
    //  rtc.begin();
    //  rtc.configure(0x98);
    //while (!rtc.isset());//wait till clock starts ticking
    while (!rtc.begin())
    {                                                                        // Initialize RTC communications    //
        Serial.println(F("Unable to find MCP7940M. Checking again in 3s.")); // Show error text
        delay(3000);                                                         // wait a second
    }                                                                        // of loop until device is located
    //Serial.println(F("MCP7940 initialized."));
    while (!rtc.deviceStatus())
    {                                                           // Turn oscillator on if necessary  //
        Serial.println(F("Oscillator is off, turning it on.")); //                                  //
        bool deviceStatus = rtc.deviceStart();                  // Start oscillator and return state//
        if (!deviceStatus)
        {                                                                 // If it didn't start               //
            Serial.println(F("Oscillator did not start, trying again.")); // Show error and                   //
            delay(1000);                                                  // wait for a second                //
        }                                                                 // of if-then oscillator didn't start                                   //                                  //
    }                                                                     // of while the oscillator is off                                         //                                  //
    rtc.setBattery(true);
}
#endif

#ifdef EBOT_8

void setTime(DateTime &dt)
{
    rtc.adjust(dt);
}

void setPCTime()
{
    rtc.adjust();
}

DateTime getTime()
{
    return rtc.now();
}

uint16_t getYear()
{
    return rtc.now().year();
}

uint8_t getMonth()
{
    return rtc.now().month();
}

uint8_t getDay()
{
    return rtc.now().day();
}

uint8_t getHour()
{
    return rtc.now().hour();
}

uint8_t getMinute()
{
    return rtc.now().minute();
}

uint8_t getSecond()
{
    return rtc.now().second();
}

uint8_t getDayOfWeek()
{
    return rtc.now().dayOfTheWeek();
}

bool ir_rc(IR *ir, unsigned char key)
{
    if (ir->decode(&results))
    {
        if (ir->channel() == results.channel)
        {
            remote_cu_key = results.value;
        }
        else
            remote_cu_key = KEY_IDLE;

        //remote_cu_key = results.value; // no channels for ebot 4
        ir->resume();
    }

    if (remote_cu_key == key)
    {
        remote_cu_key = KEY_IDLE;
        return true;
    }

    return false;
}
#endif

//#ifdef EBOT_4

//bool ir_rc(IR *ir, unsigned char key)
//{
//  if(ir->decode(&results))
//  {
//    remote_cu_key = results.value; // no channels for ebot 4
//    ir->resume();
// }
// if(remote_cu_key == key)
// {
//    remote_cu_key = KEY_IDLE;
//    return true;
// }
// return false;
//}
//#endif

/////////////////////////////////sofserial//////////////////////////////////

bool isSerCharEqls(SoftwareSerial *s, char c)
{
    if (s->available() > 0)
    {
        serChar = s->read();
    }

    if (serChar == c)
    {
        c = ' ';
        return true;
    }
    else
        return false;
}

bool isSerStrEqls(SoftwareSerial *s, char *c)
{
    if (s->available() > 0)
    {
        s->setTimeout(200);
        byte size = s->readBytesUntil('\n', serStr, 30);
        serStr[size] = 0;
        if (serStr[size - 1] == '\r') //to discard carriage return
            serStr[size - 1] = 0;
    }

    if (!(strcmp(serStr, c)))
    {
        strcpy(serStr, 0);
        return true;
    }
    else
        return false;
}
/////////////////////////////Serial///////////////////////////////

bool isSerCharEqls(HardwareSerial *s, char c)
{

    if (s->available() > 0)
    {
        serChar = s->read();
    }

    if (serChar == c)
    {
        serChar = ' ';
        return true;
    }
    else
        return false;
}

bool isSerStrEqls(HardwareSerial *s, char *c)
{
    if (s->available() > 0)
    {
        s->setTimeout(200);
        byte size = s->readBytesUntil('\n', serStr, 30);
        serStr[size] = 0;
        if (serStr[size - 1] == '\r') //to discard carriage return
            serStr[size - 1] = 0;
    }

    if (!(strcmp(serStr, c)))
    {
        strcpy(serStr, 0);
        return true;
    }
    else
        return false;
}

//////////////////ebot4 specific Serial////////////////////////////////

bool isSerCharEqls(char c)
{

    if (Serial.available() > 0)
    {
        serChar = Serial.read();
    }

    if (serChar == c)
    {
        serChar = ' ';
        return true;
    }
    else
        return false;
}

bool isSerStrEqls(char *c)
{
    if (Serial.available() > 0)
    {
        Serial.setTimeout(200);
        byte size = Serial.readBytesUntil('\n', serStr, 30);
        serStr[size] = 0;
        if (serStr[size - 1] == '\r') //to discard carriage return
            serStr[size - 1] = 0;
    }

    if (!(strcmp(serStr, c)))
    {
        strcpy(serStr, 0);
        return true;
    }
    else
        return false;
}
////////////////////////////BUTTON////////////////////////////////

unsigned char button(unsigned char PinNumber, unsigned char State)
{
    //unsigned char pin;
    boolean digitialValue = digitalRead(PinNumber);
#ifdef EBOT_4

    if (State == PRESSED)
    {
        return ((PinNumber == SW_1) || (PinNumber == SW_2) ? digitialValue : !digitialValue);
    }
    else if (State == RELEASED)
    {
        return ((PinNumber == SW_1) || (PinNumber == SW_2) ? !digitialValue : digitialValue);
    }

#endif

#ifdef EBOT_8
    if (State == PRESSED)
    {
        return (!digitialValue);
    }
    else if (State == RELEASED)
    {
        return (digitialValue);
    }

#endif
    /*switch(PinNumber)
            {
                    case A0:
                    pin = 0;
                    break;
                    case A1:
                    pin = 1;
                    break;
                    case A2:
                    pin = 2;
                    break;
                    case A3:
                    pin = 3;
                    break;
                    case A4:
                    pin = 4;
                    break;
                    case A5:
                    pin = 5;
                    break;
                    case A6:
                    pin = 6;
                    break;
                    case A7:
                    pin = 7;
                    break;
                    #ifdef EBOT_4
                    //if((PinNumber==SW_1)||(PinNumber==SW_2)){
                    // return (digitalRead(PinNumber));
                    //}
                    case SW_1:
                    pin = 6;
                    break;
                    case SW_2:
                    pin = 7;
                    break;
                    #endif

                    default:
                    return false;
            }

            btn[pin].pre = btn[pin].cu;
            if(digitalRead(PinNumber))
            {
                    //delay(50);
                    if(digitalRead(PinNumber))
                    {
                            //btn[pin].cu = ((PinNumber==SW_1)||(PinNumber==SW_2))?LOW: HIGH; // because it's active high. //HIGH;
                            btn[pin].cu = HIGH; // because it's active high. //HIGH;
                    }
            }
            else
            //btn[pin].cu = ((PinNumber==SW_1)||(PinNumber==SW_2))?HIGH: LOW; //LOW;
      btn[pin].cu =LOW;

            if(State == PRESSED)
            {

                    if((btn[pin].cu == HIGH) && (btn[pin].pre == LOW))
                    {
                            btn[pin].acted = true;
                            return true;
                    }
                    return false;
            }
            if(State == RELEASED)
            {
                    if((btn[pin].acted == true) && (btn[pin].cu == LOW))
                    {
                            btn[pin].acted = false;
                            return true;
                    }
                    else if((btn[pin].cu == LOW) && (btn[pin].pre == HIGH))
                    {
                            return true;
                    }

                    return false;
            }
            return false;
     */
}
///////////////////////////////////////////////////////////////

unsigned char edge(unsigned char PinNumber, unsigned char State)
{
    digitalWrite(PinNumber, HIGH);

    unsigned char pin;
    switch (PinNumber)
    {
    case A0:
        pin = 0;
        break;
    case A1:
        pin = 1;
        break;
    case A2:
        pin = 2;
        break;
    case A3:
        pin = 3;
        break;
    case A4:
        pin = 4;
        break;
    case A5:
        pin = 5;
        break;
    case A6:
        pin = 6;
        break;
    case A7:
        pin = 7;
        break;
    default:
        return false;
    }

    edg[pin].pre = edg[pin].cu;
    if (!digitalRead(PinNumber))
    {
        edg[pin].cu = HIGH;
    }
    else
        edg[pin].cu = LOW;

    if (State == FALLING)
    {
        if ((edg[pin].cu == HIGH) && (edg[pin].pre == LOW))
        {
            return true;
        }
        return false;
    }
    else if (State == RISING)
    {
        if ((edg[pin].cu == LOW) && (edg[pin].pre == HIGH))
        {
            return true;
        }

        return false;
    }
    return false;
}
////////////////////////

void LMotor_1(int speed)
{
#if defined(EBOT_8) || defined(EBOT_4)
    motors.setMLSpeed(speed * 25.5);
#endif
#ifdef EBOT_X
    motors.setML1Speed(speed * 25.5);
#endif
}
//////////////////////

void RMotor_1(int speed)
{
#if defined(EBOT_8) || defined(EBOT_4)
    motors.setMRSpeed(speed * 25.5);
    //motors.setMRSpeed(255);
#endif
#ifdef EBOT_X
    motors.setMR1Speed(speed * 25.5);
#endif
}
#ifdef EBOT_8

/* Minimal GPIO implementation with NOT gates */
void LeftMotor(int speed)
{
    motors.setLeftMotorSpeed(speed * 25.5);
}
//////////////////////

void RightMotor(int speed)
{
    motors.setRightMotorSpeed(speed * 25.5);
}
#endif

///////////////////////
#ifdef EBOT_X

void LMotor_2(int speed)
{
    motors.setML2Speed(speed * 25.5);
}
/////////

void RMotor_2(int speed)
{
    motors.setMR2Speed(speed * 25.5);
}
#endif

//////////////////////////    RGB LED STRIP    ////////////////////////

uint32_t Wheel(Adafruit_NeoPixel *strip, byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip->Color((255 - WheelPos * 3) / 2.5, 0, WheelPos * 3 / 2.5);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip->Color(0, WheelPos * 3 / 2.5, (255 - WheelPos * 3) / 2.5);
    }
    WheelPos -= 170;
    return strip->Color(WheelPos * 3 / 2.5, (255 - WheelPos * 3) / 2.5, 0);
}

void colorWipe(Adafruit_NeoPixel *strip, uint8_t r, uint8_t g, uint8_t b, uint8_t wait)
{
    for (uint16_t i = 0; i < strip->numPixels(); i++)
    {
        strip->setPixelColor(i, strip->Color(r / 2.5, g / 2.5, b / 2.5)); // reduce brightness to avoid heating
        strip->show();
        delay(wait);
    }
}

void rainbow(Adafruit_NeoPixel *strip, uint8_t wait)
{
    uint16_t i, j;
    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < strip->numPixels(); i++)
        {
            strip->setPixelColor(i, Wheel(strip, ((i + j) & 255)));
        }
        strip->show();
        delay(wait);
    }
}

void colorGradient(Adafruit_NeoPixel *strip, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
    int rd, gd, bd;
    rd = (r2 - r1) / ((strip->numPixels()) - 1);
    gd = (g2 - g1) / ((strip->numPixels()) - 1);
    bd = (b2 - b1) / ((strip->numPixels()) - 1);
    for (uint8_t i = 0; i < ((strip->numPixels()) - 1); i++)
    {
        strip->setPixelColor(i, strip->Color((r1 + i * rd) / 2.5, (g1 + i * gd) / 2.5, (b1 + i * bd) / 2.5));
    }
    strip->setPixelColor((strip->numPixels()) - 1, strip->Color(r2 / 2.5, g2 / 2.5, b2 / 2.5));
    strip->show();
    delay(20);
}
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////Sound//////////////////////////////////////////
//#ifdef EBOT_8

void ebotSing(int index)
{
    eboSound.sing(index);
}

void ebotSingInit(uint8_t index)
{
    eboSound.init(index);
}

//void noTone(uint8_t _pin)
//{
//  digitalWrite(_pin, 0);
//}

//#endif
///////////////////////////////////////////////////////
