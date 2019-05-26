/***************************************************|
|                   modified                        |
|            MIGHTYCORE STANDARD PINOUT             |
|       https://github.com/MCUdude/MightyCore       |
|                                                   |
| An Arduino core for:                              |
| ebot 8 and pro                                    |
|                                                   |
|***************************************************/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS (32)

#define digitalPinHasPWM(p) ((p) == 2 || (p) == 4 || (p) == 6 || (p) == 7)

// Builtin LED
#define LED_BUILTIN (8)
static const uint8_t LED = LED_BUILTIN;

// Analog pins
#define PIN_A0 (19)
#define PIN_A1 (20)
#define PIN_A2 (21)
#define PIN_A3 (22)
#define PIN_A4 (23)
#define PIN_A5 (24)
#define PIN_A6 (25)
#define PIN_A7 (26)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

#define NUM_ANALOG_INPUTS (8)
#define analogInputToDigitalPin(p) ((p < NUM_ANALOG_INPUTS) ? (p) + 19 : -1)
#define analogPinToChannel(p) ((p) < NUM_ANALOG_INPUTS ? (p) : (p) >= 19 ? (p)-19 : -1)

// SPI
#define PIN_SPI_SS (2)
#define PIN_SPI_MOSI (3)
#define PIN_SPI_MISO (4)
#define PIN_SPI_SCK (5)
static const uint8_t SS = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

// i2c
#define PIN_WIRE_SDA (7)
#define PIN_WIRE_SCL (6)
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Interrupts
#define EXTERNAL_NUM_INTERRUPTS (3)
// no pins in ebot that support interrupt is taken out. Hence following line is just to make compile happy
#define digitalPinToInterrupt(p) ((p) == 2 ? 2 : ((p) == 10 ? 0 : ((p) == 11 ? 1 : NOT_AN_INTERRUPT)))

//Pin chage interrupts are per port, and the pins in e-bot boad are not in sequence
//so soft serial and other libraries which use this need pin number from arduino to be able to use this
//#define digitalPinToPCICR(p)    (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICR(p) (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (&PCICR) : ((uint8_t *)0))
//#define digitalPinToPCICRbit(p) (((p) <= 7) ? 1 : (((p) <= 15) ? 3 : (((p) <= 23) ? 2 : 0)))
//#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
//
//#define digitalPinToPCICRbit(p) (((p) == 0)?2:((p)==1)?2:((p)==2)?1:((p)==3)?1:((p)==4)?1:((p)==5)?1:((p)==6)?3:((p)==7)?3:0)
#define digitalPinToPCICRbit(p) (((p) <= 1) ? 2 : ((p) <= 5) ? 1 : ((p) <= 7) ? 3 : 0)

//
//
//#define digitalPinToPCMSK(p) (((p)==0?(&PCMSK2):((p)==1)?(&PCMSK2):((p)==2)?(&PCMSK1):((p)==3)?(&PCMSK1):((p)==4)?(&PCMSK1):((p)==5)?(&PCMSK1):((p)==6)?(&PCMSK3):((p)==7)?(&PCMSK3):((uint8_t *)0)))
//#define digitalPinToPCMSK(p) (((p)==0?(&PCMSK2):((p)==1)?(&PCMSK2):((p)==2)?(&PCMSK1):((p)==3)?(&PCMSK1):((p)==4)?(&PCMSK1):((p)==5)?(&PCMSK1):((p)==6)?(&PCMSK3):((p)==7)?(&PCMSK3):(&PCMSK0)))
#define digitalPinToPCMSK(p) ((p) <= 1 ? (&PCMSK2) : ((p <= 5) ? (&PCMSK1) : ((p) <= 7) ? (&PCMSK3) : (&PCMSK0)))
//
//#define digitalPinToPCMSKbit(p) ((p) % 8)
#define digitalPinToPCMSKbit(p) (((p) <= 1) ? (p) : ((p) <= 5) ? (p) + 2 : ((p) <= 7) ? (p) : (p)-19)

#ifdef ARDUINO_MAIN

#define PA 1
#define PB 2
#define PC 3
#define PD 4

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
    {
        NOT_A_PORT,
        (uint16_t)&DDRA,
        (uint16_t)&DDRB,
        (uint16_t)&DDRC,
        (uint16_t)&DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] =
    {
        NOT_A_PORT,
        (uint16_t)&PORTA,
        (uint16_t)&PORTB,
        (uint16_t)&PORTC,
        (uint16_t)&PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
    {
        NOT_A_PORT,
        (uint16_t)&PINA,
        (uint16_t)&PINB,
        (uint16_t)&PINC,
        (uint16_t)&PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
    {
        PD, // 6 | d6
        PD, // 7 | d7
        // PC , // 0 | d0
        // PC , // 1 | d1
        PB, // 4 | d2 SS
        PB, // 5 | d3 MOSI
        PB, // 6 | d4 MISO
        PB, // 7 | d5 SCK
        // PD , // 6 | d6
        // PD , // 7 | d7
        PC, // 0 | d0
        PC, // 1 | d1

        PC, // 2 | LED

        PB, // 0 | M1 9
        PB, // 1 | M2 10
        PB, // 2 | M3 11
        PC, // 7 | M4 12
        PD, // 4 | PWM1  13
        PD, // 5 | PWM2 14
        PC, // 3 | STDBY 15

        PC, // IR0
        PC, // IR1
        PC, // IR2

        PA, // 0 | ADC 0
        PA, // 1 | ADC 1
        PA, // 2 | ADC 2
        PA, // 3 | ADC 3
        PA, // 4 | ADC 4
        PA, // 5 | ADC 5
        PA, // 6 | ADC 6
        PA, // 7 | ADC 7

        PD, // 27 built in RGB
        PD, // 28 BT key
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
    {
        _BV(6),
        _BV(7), // 7
        // _BV(0),
        // _BV(1),
        _BV(4),
        _BV(5),
        _BV(6),
        _BV(7),
        // _BV(6),
        // _BV(7), // 7
        _BV(0),
        _BV(1),

        _BV(2),

        _BV(0),
        _BV(1),
        _BV(2),
        _BV(7),
        _BV(4),
        _BV(5),
        _BV(3),

        _BV(6),
        _BV(5),
        _BV(4),

        _BV(0),
        _BV(1),
        _BV(2),
        _BV(3),
        _BV(4),
        _BV(5),
        _BV(6),
        _BV(7),

        _BV(2), //27
        _BV(3), //28
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
    {
        TIMER2B, //6
        TIMER2A, //7
        // NOT_ON_TIMER, //0
        // NOT_ON_TIMER,//1
        TIMER0B,      //2
        NOT_ON_TIMER, //3
        TIMER3A,      //4
        TIMER3B,      //5
        // TIMER2B,//6
        // TIMER2A, //7
        NOT_ON_TIMER, //0
        NOT_ON_TIMER, //1

        NOT_ON_TIMER,

        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        TIMER1B, // Motor
        TIMER1A,
        NOT_ON_TIMER,

        NOT_ON_TIMER, // IR
        NOT_ON_TIMER,
        NOT_ON_TIMER,

        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,
        NOT_ON_TIMER,

        NOT_ON_TIMER, //27
        NOT_ON_TIMER, //28
};

#endif

#endif // Pins_Arduino_h
// vim:ai:cin:sts=2 sw=2 ft=cpp
