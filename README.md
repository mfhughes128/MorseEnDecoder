# MorseEnDecoder
MorseEnDecoder

This library provides -
 - an encoder function, that translates a character into a string of dots and dashes
 - a decoder function which attempts to translate a string of dots and dashes to a character.

The included MorseOut classes support sending the encoder output to an Arduino pin for a digital signal or to the included Speaker class to generate an audible tone.
The MorseIn classes accept digital input, from a key for example, or a tone input. The digital input class supports side tone through the Speaker class.
As configured, the sidetone has priority over the input.

Other configurations are possible, for example it might be desirable for the encoder output to key a digital pin and generate a tone as well. New configurations
can be supported by writing additional sub-classes to MorseOut and MorseIn, but this is left as an exercise for the reader.
