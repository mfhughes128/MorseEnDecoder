/*			Morse I/O
 
 Morse Input and Output classes for the MorseEnDecoder classes
 */
 
#include "MorseIO.h"
#include "Pitches.h"



morseSpeaker::morseSpeaker(int spkrPin)
{
  // Setup the speaker output pin
  spkrOut = spkrPin;
  pinMode(spkrOut, OUTPUT);
  digitalWrite(spkrOut, LOW);

  // Set initial state
  keyDown = false;
  outputToneOn = false;
  sideToneOn = false;
}


void morseSpeaker::outputTone(boolean start)
{
  if (outputToneOn && !keyDown)
  {
    if (start)
    {
      tone(spkrOut, NOTE_A3);
    } else {
      noTone(this->spkrOut);
    }
  }
}


void morseSpeaker::sideTone(boolean start)
{
  if (sideToneOn)
  {
    if (start)
    {
      keyDown = true;
      tone(spkrOut, NOTE_C4);
    } else {
      keyDown = false;
      noTone(spkrOut);
    }
  }
}
