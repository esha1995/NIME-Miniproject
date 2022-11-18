
#include "chords.h"
#include <Wire.h>
#include "Adafruit_Trellis.h"
int channel = 1;
float finger_delay = 10;


Adafruit_Trellis matrix0 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

#define NUMTRELLIS 1

#define numKeys (NUMTRELLIS * 16)

#define INTPIN A2

int row1 = numKeys - 1;
int row2 = numKeys - 2;
int row3 = numKeys - 3;
int row4 = numKeys - 4;

bool changeChord = false;
bool majorMinor = true;

int scale = 0;

int mapping[16] = {15, 11, 7, 3,14,10,6,2,13,9,5,1,12,8,4,0}; 

void setup() {
  Serial.begin(9600);
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);  // only one

  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }

  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
}


void loop() {
  delay(30);
    // If a button was just pressed or released...

    trellis.setLED(12);
    if (trellis.readSwitches()) {
      // go through every button

      for (uint8_t i=0; i<numKeys; i++) {
        if(i == 12) {
          if(trellis.justPressed(mapping[12]) && changeChord == false) {
            changeChord = true;
          } 
          else if(trellis.justPressed(mapping[12]) && changeChord == true) {
            changeChord = false;
          }
        } 
        else if(i == 8) {
          if(trellis.justPressed(mapping[13]) && majorMinor == false) {
            majorMinor = true; 
          } 
          
          else if(trellis.justPressed(mapping[13]) && majorMinor == true) {
              majorMinor = false;
          }
        }
        else {
          // if in change scale mode
          if(changeChord) {
              if(mapping[i] != mapping[14] && mapping[i] != mapping[15]) {
                  trellis.setLED(mapping[i]);
                  if(trellis .justPressed(mapping[i])) {
                    scale = i;
                    changeChord = false;
                    Serial.println(i);
                  }
              }
           }
           else {
            trellis.clrLED(mapping[i]);
            if (trellis.justPressed(mapping[i])) {
              Serial.println(i);
              playChord(selectChord(i, 100, majorMinor, scale));
              trellis.setLED(mapping[i]);
             } 
              // if it was released, turn it off
            if (trellis.justReleased(mapping[i])) {
              stopChord(selectChord(i, 100, majorMinor, scale));
              trellis.clrLED(mapping[i]);
            }
          }
        }
      }
     }
     
    if(majorMinor) {
      trellis.setLED(mapping[13]);
    }
    else{
      trellis.clrLED(mapping[13]);
    }
     
    
    trellis.writeDisplay();
  }


int * selectChord(int i, float velocity, bool isMajor, int scale) {
  int *chord;
  if (isMajor) {
        if (scale == 0 ) {
        // First row
        if(i == 0) chord = Cmaj;
        if(i == 1) chord = Dmin;
        if(i == 2) chord = Emin;
        if(i == 3) chord = Fmaj;
        
        // Second row
        if(i == 4) chord = Gmin;
        if(i == 5) chord = Amin;
        if(i == 6) chord = Bdim;
      }

      if (scale == 1 ) {
        // First row
        if(i == 0) chord = Csmaj;
        if(i == 1) chord = Dsmin;
        if(i == 2) chord = Fmin;
        if(i == 3) chord = Fsmaj;
        
        // Second row
        if(i == 4) chord = Gsmin;
        if(i == 5) chord = Asmin;
        if(i == 6) chord = Cdim;
      }
  } else {
      // C Minor
      if (scale == 0) {
        // First row
        if(i == 0) chord = Cmin;
        if(i == 1) chord = Dmin;
        if(i == 2) chord = Emin;
        if(i == 3) chord = Fmaj;
        
        // Second row
        if(i == 4) chord = Gmin;
        if(i == 5) chord = Amin;
        if(i == 6) chord = Bdim;
      }
  }
  
  return chord;
}

void playChord(int *chord) 
{
  usbMIDI.sendNoteOn(chord[0], 100, channel);
  usbMIDI.sendNoteOn(chord[1], 100, channel);
  usbMIDI.sendNoteOn(chord[2], 100, channel);
}

void stopChord(int *chord) 
{
  usbMIDI.sendNoteOff(chord[0], 100, channel);
  usbMIDI.sendNoteOff(chord[1], 100, channel);
  usbMIDI.sendNoteOff(chord[2], 100, channel);
}
