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
