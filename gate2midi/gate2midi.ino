/*
  24 ppqn (pulses per quarter note)
   6 times per MIDI beat (defined as a sixteenth note)

 This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
 If this circuit is connected to a MIDI synth, it will play
 the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.


 The circuit:
 * digital in 1 connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +5V through 220-ohm resistor
 Attach a MIDI cable to the jack, then to a MIDI synth, and play music.
 */


#define MIDI_CL_START    0xFA // counts as first tick
#define MIDI_CL_STOP     0xFC
#define MIDI_CL_TICK     0xF8
#define MIDI_CL_CONTINUE 0xFB


void setup() 
{
  Serial.begin(31250);
}

void loop() 
{
  if( 1 ) //pin high
  {
    Serial.write(MIDI_CL_TICK);
  }
}



