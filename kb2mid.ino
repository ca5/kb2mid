// Simple test of USB Host
//
// This example is in the public domain

#include "USBHost_t36.h"
#define NOTE_BD 36
#define NOTE_SS 37
#define NOTE_SD1 38
#define NOTE_SD2 40
#define NOTE_CHH 42
#define NOTE_FT 43
#define NOTE_PHH 44
#define NOTE_LT 45
#define NOTE_OHH 44
#define NOTE_MT 47
#define NOTE_HT 48
#define NOTE_CC 49
#define NOTE_RC 51
#define NOTE_RB 53
#define NOTE_SC 55

USBHost usbhost;
KeyboardController keyboard1(usbhost);
KeyboardController keyboard2(usbhost);

// the MIDI channel number to send messages
const int channel = 1;

void setup()
{
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("kb2mid");
  usbhost.begin();
  keyboard1.attachPress(OnPress);
  keyboard2.attachPress(OnPress);
  keyboard1.attachRelease(OnRelease);
  keyboard2.attachRelease(OnRelease);
}


void loop()
{
  usbhost.Task();
    // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

int midimap(int key){
  switch(key){
    case (int)'a':
    case (int)'A':
    case (int)';':
    case (int)':':
    case 32: //space
      Serial.println("BD");
      return NOTE_BD;

    case (int)'g':
    case (int)'G':
    case (int)'h':
    case (int)'H':
      Serial.println("OHH");
      return NOTE_OHH;

    case (int)'f':
    case (int)'F':
    case (int)'j':
    case (int)'J':
      Serial.println("CHH");
      return NOTE_CHH;

    case (int)'d':
    case (int)'D':
    case (int)'k':
    case (int)'K':
      Serial.println("SD1");
      return NOTE_SD1;

    case (int)'s':
    case (int)'S':
    case (int)'l':
    case (int)'L':
      Serial.println("SD2");
      return NOTE_SD2;

    case (int)'b':
    case (int)'B':
    case (int)'n':
    case (int)'N':
      Serial.println("SS");
      return NOTE_SS;

    case (int)'v':
    case (int)'V':
    case (int)'m':
    case (int)'M':
      Serial.println("PHH");
      return NOTE_PHH;

    case (int)'z':
    case (int)'Z':
    case (int)'/':
    case (int)'?':
    case 10: //enter
      Serial.println("CC");
      return NOTE_CC;

    case (int)'x':
    case (int)'X':
    case (int)'.':
    case (int)'>':
      Serial.println("SC");
      return NOTE_SC;

    case (int)'c':
    case (int)'C':
    case (int)',':
    case (int)'<':
      Serial.println("RC");
      return NOTE_RC;

    case (int)'t':
    case (int)'T':
    case (int)'y':
    case (int)'Y':
      Serial.println("RB");
      return NOTE_RB;

    case (int)'r':
    case (int)'R':
    case (int)'u':
    case (int)'U':
      Serial.println("HT");
      return NOTE_HT;

    case (int)'e':
    case (int)'E':
    case (int)'i':
    case (int)'I':
      Serial.println("MT");
      return NOTE_MT;

    case (int)'w':
    case (int)'W':
    case (int)'o':
    case (int)'O':
      Serial.println("LT");
      return NOTE_LT;

    case (int)'q':
    case (int)'Q':
    case (int)'p':
    case (int)'P':
      Serial.println("FT");
      return NOTE_FT;
  }
  return 0;
}

void OnPress(int key)
{
  Serial.print("key '");
  Serial.print((char)key);
  Serial.print("'  ");
  Serial.println(key);

  if(midimap(key) > 0){
    usbMIDI.sendNoteOn(midimap(key), 100, channel); 
  }
}

void OnRelease(int key)
{
  Serial.print("release key '");
  Serial.print((char)key);
  Serial.print("'  ");
  Serial.println(key);

  if(midimap(key) > 0){
    usbMIDI.sendNoteOff(midimap(key), 0, channel); 
  }
}


/* MPC MAPPING
C#3 - G3 - D#3 - F3
C3 - B2 - A2 - G2
E2 - D2 - A#2 - G#2
C#2 - C2 - F#2 - A#5
*/