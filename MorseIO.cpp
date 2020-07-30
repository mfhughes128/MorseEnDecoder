/*			Morse I/O
 
 Morse Input and Output classes for the MorseEnDecoder classes
 */
 
#include "MorseIO.h"
#include "Pitches.h"


/*
  Morse Speaker Class
    Generates audible output for encoder and sidetone for
    decoder. Sidetone over-rides output.
*/
MorseSpeaker::MorseSpeaker(int t_spkrPin)
{
  // Setup the speaker output pin
  spkrOut = t_spkrPin;
  pinMode(spkrOut, OUTPUT);
  digitalWrite(spkrOut, LOW);

  // Set initial state
  keyDown = false;
  outputToneOn = false;
  sideToneOn = false;
}

void MorseSpeaker::outputTone(boolean t_on)
{
  if (outputToneOn && !keyDown) {
    if (t_on) {
      tone(spkrOut, NOTE_A3);
    } else {
      noTone(spkrOut);
    }
  }
}

void MorseSpeaker::sideTone(boolean t_on) {
  if (sideToneOn) {
    if (t_on) {
      keyDown = true;
      tone(spkrOut, NOTE_C4);
    } else {
      keyDown = false;
      noTone(spkrOut);
    }
  }
}


/*
  Morse Output Classes
    MorseOut - Base class for all encoder output configurations
    MorseOutKey - Digital output to a pin
    MorseOutTone - Audible output via the Speaker class
*/

// MorseOut base class
MorseOut::MorseOut()
{
  /* --- */
}

// MorseOut digital output class
MorseOutKey::MorseOutKey(int t_pinNumber, boolean t_pinSense)
{
  pinOut = t_pinNumber;
  pinSense = t_pinSense;
  
  pinMode(pinOut, OUTPUT);
  if (pinSense == ACTIVE_LOW) {
    digitalWrite(pinOut, HIGH);
  } else {
    digitalWrite(pinOut, LOW);
  }
}

void MorseOutKey::keyDown()
{
  if (pinSense == ACTIVE_LOW) {
    digitalWrite(pinOut, LOW);
  } else {
    digitalWrite(pinOut, HIGH);
  }
}

void MorseOutKey::keyUp()
{
  if (pinSense == ACTIVE_LOW) {
    digitalWrite(pinOut, HIGH);
  } else {
    digitalWrite(pinOut, LOW);
  }
}

//MorseOut tone output class
MorseOutTone::MorseOutTone(MorseSpeaker *t_Speaker_p)
{
  Speaker_p = t_Speaker_p;
  Speaker_p->outputTone(false);
}

void MorseOutTone::keyDown()
{
  Speaker_p->outputTone(true);
}

void MorseOutTone::keyUp()
{
  Speaker_p->outputTone(false);
}


/*
  Morse Input Classes Morse
    MorseIn - Base class for all decoder input configurations
    MorseInKey - Digital input from a pin with sidetone
    MorseInTone - Analog tone input (Note: must be assigned an analog pin)
*/

// MorseIn base class
MorseIn::MorseIn()
{
  /* --- */
}

// MorseIn digital input with sidetone
MorseInKey::MorseInKey(int t_pinNumber, boolean t_pinSense, MorseSpeaker *t_Speaker_p)
{
  pinIn = t_pinNumber;
  pinSense = t_pinSense;
  Speaker_p = t_Speaker_p;
  
  pinMode(pinIn, INPUT);
  if (pinSense == ACTIVE_LOW) digitalWrite(pinIn, HIGH);

  debounceDelay = 20;

  lastKeyIn = LOW;
  lastDebounceTime = 0;
  debouncedKey = LOW;
}

boolean MorseInKey::read(long t_currentTime)
{
  // Read Morse key input (digital)
  boolean keyIn = digitalRead(pinIn);
  if (pinSense == ACTIVE_LOW) keyIn = !keyIn;

  // Debounce the key input
  if (keyIn != lastKeyIn) {  // If key state has changed...
    lastDebounceTime = t_currentTime;  // ...reset the debounce timer...
    Speaker_p->sideTone(keyIn);  // ...update sidetone state...
    lastKeyIn = keyIn;  // ...and save the new key state.
  } else if ((t_currentTime - lastDebounceTime) > debounceDelay) {  // If debounce timer expired...
    debouncedKey = keyIn;  // ...update key state...
  }
  return debouncedKey;
}

// MorseIn analog tone input
MorseInTone::MorseInTone(int t_pinIn)
{
  pinIn = t_pinIn;
  pinMode(pinIn, INPUT);
  
  audioThreshold = 700;
  debounceDelay = 25;

  lastKeyIn = LOW;
  lastDebounceTime = 0;
  debouncedKey = LOW;
}

boolean MorseInTone::read(long t_currentTime)
{
  // Read Morse audio input (analog)
  boolean keyIn;
  int audioSignal = analogRead(pinIn);
  if (audioSignal > audioThreshold) keyIn = HIGH; else keyIn = LOW;

  // Debounce the key input
  if (keyIn != lastKeyIn) {  // If key state has changed...
    lastDebounceTime = t_currentTime;  // ...reset the debounce timer...
    lastKeyIn = keyIn;  // ...and save the new key state.
  } else if ((t_currentTime - lastDebounceTime) > debounceDelay) {  // If debounce timer expired...
    debouncedKey = keyIn;  // ...update key state...
  }
  return debouncedKey;
  }
