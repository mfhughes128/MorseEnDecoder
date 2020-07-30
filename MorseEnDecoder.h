#ifndef MorseEnDecoder_H
#define MorseEnDecoder_H

#include <Arduino.h>
#include "MorseIO.h"

#define MORSE_AUDIO true
#define MORSE_KEYER false
#define MORSE_ACTIVE_LOW true
#define MORSE_ACTIVE_HIGH false


/*
  Morse Decoder Class
    - decode
    - setspeed
    - read
    - available
*/
class MorseDecoder
{
  public:
    MorseDecoder(MorseIn *);
    void decode();
    void setspeed(int);
    char read();
    boolean available();
    char decodedMorseChar;  // The last decoded Morse character
  private:
    MorseIn *MorseIn_p;         // Pointer to the input handler
    boolean lastKeyState;
    int morseTablePointer;
    boolean morseSpace;     // Flag to prevent multiple received spaces
    boolean gotLastSig;     // Flag that the last received morse signal is decoded as dot or dash
    long markTime;          // timers for mark and space in morse signal
    long spaceTime;         // E=MC^2 ;p
  protected:
    int wpm;                // Word-per-minute speed
    long dotTime;           // morse element times in ms
    long dashTime;
    long wordSpace;
};


/*
  MorseEncoder Class:
    - encode
    - setspeed
    - write
    - available
    - setmillis
*/
class MorseEncoder
{
  public:
    MorseEncoder(MorseOut *);
    void encode();
    void setspeed(int);
    void write(char);
    boolean available();
    void setmillis(unsigned long (*millis)());
    int morseSignals;         // nr of morse signals to send in one morse character
    char morseSignalString[7];// Morse signal for one character as temporary ASCII string of dots and dashes
  private:
    MorseOut *MorseIO_p;     // Pointer to output handler
    char encodeMorseChar;    // ASCII character to encode
    boolean sendingMorse;    // Flag indicating sending is in process
    int morseSignalPos;
    int sendingMorseSignalNr;
    long sendMorseTimer;
    long currentTime;
    unsigned long (*millis)();
  protected:
    int wpm;                 // Word-per-minute speed
    long dotTime;            // morse element times in ms
    long dashTime;
    long wordSpace;
};

#endif
