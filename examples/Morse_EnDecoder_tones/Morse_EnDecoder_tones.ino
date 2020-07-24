/*
           MORSE ENDECODER TONE TEST

Sketch to test tone generation for Morse output and sidetone

This example generates one second tones at the pitches specified for the
morse output and the morse input sidetone.

Copyright (C) 2010, 2012 raron
  GNU GPLv3 license (http://www.gnu.org/li
*/

#include <MorseIO.h>

// Pin mapping
const byte morseSpkrPin = 11;

typedef void (morseSpeaker::*SpkrFunc)(boolean start);
SpkrFunc outTone = &morseSpeaker::outputTone;
SpkrFunc sideTone = &morseSpeaker::sideTone;

// Instantiate speaker object
morseSpeaker morseSound(morseSpkrPin);

void setup()
{
	// Enable encode and decode output
	morseSound.sideToneOn = true;
	morseSound.outputToneOn = true;
}

void loop()
{
  delay(1000);

  // Sound Morse Output tone
  playTone(1000, outTone);
	
	delay(1500);

  // Sound Morse sidetone
  playTone(1000, sideTone);
}

void playTone(int duration, SpkrFunc func)
{
  int ttp = duration;
  (morseSound.*func)(true);
  delay(ttp);
  (morseSound.*func)(false);
}
