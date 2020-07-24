#ifndef MorseIO_H
#define MorseIO_H

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif


class morseSpeaker
{
  public:
    morseSpeaker(int spkrPin);
    void outputTone(boolean start);  //Start or stop the Morse output tone
    void sideTone(boolean start);  //Start or stop the Morse input sidetone
    boolean outputToneOn;  // Enable tone output for encoded Morse
    boolean sideToneOn;  // Enable sidetone
  private:
    boolean keyDown;  //Asserted if sidetone playing
  protected:
    int spkrOut;
    void setup_signal();
};

#endif