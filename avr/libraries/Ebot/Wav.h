/*Library by TMRh20 2012-2013*/

#ifndef Wav_h //
#define Wav_h // #define this so the compiler knows it has been included

//Comment or Uncomment to en/disable RF streaming of wav files
//Make sure to Comment if not using radio
//#define ENABLE_RF

#include <Arduino.h>

class Wav
{
public:
    void play(char *filename);
    void stop();
    void volume(int vol);
    void setVolume(int vol);
    void disable();
    void pause();
    void quality(boolean q);
    int speakerPin;
    boolean wavInfo(char *filename);
    boolean isPlaying();
    boolean rfPlaying;
    unsigned int SAMPLE_RATE;

private:
    int lastSpeakPin;
    void setPin();
};

#endif