/* 2016-09-01
 
  24 ppqn (pulses per quarter note)
   6 times per MIDI beat (defined as a sixteenth note)

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play
  the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.


  The circuit:
   digital in 1 connected to MIDI jack pin 5
   MIDI jack pin 2 connected to ground
   MIDI jack pin 4 connected to +5V through 220-ohm resistor
  Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  LOW to trigger the interrupt whenever the pin is low,
  CHANGE to trigger the interrupt whenever the pin changes value
  RISING to trigger when the pin goes from low to high,
  FALLING for when the pin goes from high to low.

*/


#define MIDI_CL_START    0xFA // counts as first tick
#define MIDI_CL_STOP     0xFC
#define MIDI_CL_TICK     0xF8
#define MIDI_CL_CONTINUE 0xFB

#define STOP_TIME 1000

const byte interruptPin = 3;

#define STATE_START   1
#define STATE_TICK    2
#define STATE_STOP    3

volatile uint8_t  state = STATE_STOP;
volatile uint32_t stop_cnt = 0;

unsigned long previousMillis = 0;
unsigned long currentMillis  = 0;


void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(31250);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), clock_update, RISING );
}



void loop()
{
  currentMillis = millis();

  if ( currentMillis != previousMillis )
  {
    stop_cnt++;

    if ( stop_cnt >= STOP_TIME )
    {
      if ( state != STATE_STOP )
      {
        Serial.write(MIDI_CL_STOP);
        digitalWrite(13, HIGH);
        state = STATE_STOP;
      }
      stop_cnt = 0;
    }
    
    previousMillis = currentMillis;
  }
}



void clock_update(void)
{
  stop_cnt = 0;

  switch (state)
  {
    case STATE_TICK:
      {
        Serial.write(MIDI_CL_TICK);
        break;
      }
    case STATE_STOP:
      {
        Serial.write(MIDI_CL_START);
        digitalWrite(13, LOW);
        state = STATE_TICK;
        break;
      }
    default:
      break;
  }
}


