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


/*
  Morse Input Classes Morse
    MorseIN - Base class for all decoder input configurations
    MorseInKey - Digital input from a pin with sidetone
    MorseInTone - Analog tone input (Note: must be assigned an analog pin)
*/
class MorseIn
{
  public:
    MorseIn(void);
    virtual boolean read(long);
};

class MorseInKey: public MorseIn
{
  public:
    MorseInKey(int, boolean, MorseSpeaker *);
    boolean read(long);
  private:
    int pinIn;
    boolean pinSense;
    MorseSpeaker *Speaker_p;
    
    long debounceDelay;

    boolean lastKeyIn;
    long lastDebounceTime;
    boolean debouncedKey;
};

class MorseInTone: public MorseIn
{
  public:
    MorseInTone(int);
    boolean read(long);
  private:
    int pinIn;
    
    int audioThreshold;
    long debounceDelay;
    
    boolean lastKeyIn;
    long lastDebounceTime;
    boolean debouncedKey;

};

#endif