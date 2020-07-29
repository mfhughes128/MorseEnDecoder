#ifndef MorseIO_H
#define MorseIO_H

#include <Arduino.h>
#include "Pitches.h"

#define ACTIVE_LOW true
#define ACTIVE_HIGH false


/*
  Morse Speaker Class
    Generates audible output for encoder and sidetone for
    decoder. Sidetone over-rides output.
*/
class MorseSpeaker
{
  public:
    MorseSpeaker(int);
    void outputTone(boolean);  // Start or stop the Morse output tone
    void sideTone(boolean);    // Start or stop the Morse input sidetone
    boolean outputToneOn;  // Enable tone output
    boolean sideToneOn;    // Enable sidetone
  private:
    boolean keyDown;  // Asserted if sidetone playing
    int spkrOut;      // Speaker output pin
};

/*
  Morse Output Classes
    MorseOut - Base class for all encoder output configurations
    MorseOutKey - Digital output to a pin
    MorseOutTone - Audible output via the Speaker class
*/
class MorseOut
{
  public:
    MorseOut(void);
    virtual void keyDown();  // Assert output
    virtual void keyUp();    // De-assert output
};

class MorseOutKey: public MorseOut
{
  public:
    MorseOutKey(int, boolean);
    void keyDown();
    void keyUp();
   private:
    int pinOut;
    boolean pinSense;
};

class MorseOutTone: public MorseOut
{
  public:
    MorseOutTone(MorseSpeaker *);
    void keyDown();
    void keyUp();
  private:
    MorseSpeaker *Speaker_p;
};

#endif