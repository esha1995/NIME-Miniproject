#include "chords.h"
#include <Wire.h>
#include "Adafruit_Trellis.h"

#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define INTPIN A2

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

int channel = 1;
float finger_delay = 10;

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
              playChord(selectChord(i, 100, majorMinor, scale), 0);
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

void playChord(int *chord, int delayValue) 
{
  usbMIDI.sendNoteOn(chord[0], 100, channel);
  delay(delayValue);
  usbMIDI.sendNoteOn(chord[1], 100, channel);
  delay(delayValue);
  usbMIDI.sendNoteOn(chord[2], 100, channel);
}

void stopChord(int *chord) 
{
  usbMIDI.sendNoteOff(chord[0], 100, channel);
  usbMIDI.sendNoteOff(chord[1], 100, channel);
  usbMIDI.sendNoteOff(chord[2], 100, channel);
}

int * selectChord(int i, float velocity, bool isMajor, int scale) {
  int *chord;
  if (isMajor) {
    /// C
    if (scale == 0) {
      // First row
      if(i == 0)  chord = Cmaj;
      if(i == 1)  chord = Dmin;
      if(i == 2)  chord = Emin;
      if(i == 3)  chord = Fmaj;
      
      // Second row
      if(i == 4)  chord = Gmin;
      if(i == 5)  chord = Amin;
      if(i == 6)  chord = Bdim;
      if(i == 7)  chord = Cmaj2;

      // Thid row
      if(i == 8)  chord = Dmin2;
      if(i == 9)  chord = Emin2;
      if(i == 10) chord = Fmaj2;
      if(i == 11) chord = Gmin2;

      // Fourth row
      if(i == 14) chord = Amin2;
      if(i == 15) chord = Bdim2;
    }
    
    /// C#
    if (scale == 1) {
      // First row
      if(i == 0)  chord = Csmaj;
      if(i == 1)  chord = Dsmin;
      if(i == 2)  chord = Fmin;
      if(i == 3)  chord = Fsmaj;
      
      // Second row
      if(i == 4)  chord = Gsmin;
      if(i == 5)  chord = Asmin;
      if(i == 6)  chord = Cdim;
      if(i == 7)  chord = Csmaj2;
      
      // Third row
      if(i == 8)  chord = Dsmin2;
      if(i == 9)  chord = Fmin2;
      if(i == 10) chord = Fsmaj2;
      if(i == 11) chord = Gsmin2;

      // Fourth row
      if(i == 14) chord = Asmin2;
      if(i == 14) chord = Cdim2;
    }

    /// D
    if (scale == 2) {
      // First row
      if(i == 0)  chord = Dmaj;
      if(i == 1)  chord = Emin;
      if(i == 2)  chord = Fsmin;
      if(i == 3)  chord = Gmaj;
      
      // Second row
      if(i == 4)  chord = Amaj;
      if(i == 5)  chord = Bmin;
      if(i == 6)  chord = Csdim;
      if(i == 7)  chord = Dmaj2;
      
      // Third row
      if(i == 8)  chord = Emin2;
      if(i == 9)  chord = Fsmin2;
      if(i == 10) chord = Gmaj2;
      if(i == 11) chord = Amaj2;

      // Fourth row
      if(i == 14) chord = Bmin2;
      if(i == 14) chord = Csdim2;
    }

    /// D#
    if (scale == 3) {
      // First row
      if(i == 0)  chord = Dsmaj;
      if(i == 1)  chord = Fmin;
      if(i == 2)  chord = Gmin;
      if(i == 3)  chord = Gsmaj;
      
      // Second row
      if(i == 4)  chord = Asmaj;
      if(i == 5)  chord = Cmin;
      if(i == 6)  chord = Ddim;
      if(i == 7)  chord = Dsmaj2;
      
      // Third row
      if(i == 8)  chord = Emin2;
      if(i == 9)  chord = Fsmin2;
      if(i == 10) chord = Gmaj2;
      if(i == 11) chord = Amaj2;

      // Fourth row
      if(i == 14) chord = Bmin2;
      if(i == 15) chord = Ddim2;
    }
    
    /// E
    if (scale == 4) {
      // First row
      if(i == 0)  chord = Emaj;
      if(i == 1)  chord = Fsmin;
      if(i == 2)  chord = Gsmin;
      if(i == 3)  chord = Amaj;
      
      // Second row
      if(i == 4)  chord = Bmaj;
      if(i == 5)  chord = Csmin;
      if(i == 6)  chord = Dsdim;
      if(i == 7)  chord = Emaj2;
      
      // Third row
      if(i == 8)  chord = Fsmin2;
      if(i == 9)  chord = Gsmin2;
      if(i == 10) chord = Amaj2;
      if(i == 11) chord = Bmaj2;

      // Fourth row
      if(i == 14) chord = Csmin2;
      if(i == 15) chord = Dsdim2;
    }

    /// F
    if (scale == 5) {
      // First row
      if(i == 0)  chord = Fmaj;
      if(i == 1)  chord = Gmin;
      if(i == 2)  chord = Amin;
      if(i == 3)  chord = Asmaj;
      
      // Second row
      if(i == 4)  chord = Cmaj;
      if(i == 5)  chord = Dmin;
      if(i == 6)  chord = Edim;
      if(i == 7)  chord = Fmaj2;
      
      // Third row
      if(i == 8)  chord = Gmin2;
      if(i == 9)  chord = Amin2;
      if(i == 10) chord = Asmaj2;
      if(i == 11) chord = Cmaj2;

      // Fourth row
      if(i == 14) chord = Dmin2;
      if(i == 15) chord = Edim2;
    }

    /// F#
    if (scale == 6) {
      // First row
      if(i == 0)  chord = Fsmaj;
      if(i == 1)  chord = Gsmin;
      if(i == 2)  chord = Asmin;
      if(i == 3)  chord = Bmaj;
      
      // Second row
      if(i == 4)  chord = Csmaj;
      if(i == 5)  chord = Dsmin;
      if(i == 6)  chord = Fdim;
      if(i == 7)  chord = Fsmaj2;
      
      // Third row
      if(i == 8)  chord = Gsmin2;
      if(i == 9)  chord = Asmin2;
      if(i == 10) chord = Bmaj2;
      if(i == 11) chord = Csmaj2;

      // Fourth row
      if(i == 14) chord = Dsmin2;
      if(i == 15) chord = Fdim2;
    }

    /// G
    if (scale == 7) {
      // First row
      if(i == 0)  chord = Gmaj;
      if(i == 1)  chord = Amin;
      if(i == 2)  chord = Bmin;
      if(i == 3)  chord = Cmaj;
      
      // Second row
      if(i == 4)  chord = Dmaj;
      if(i == 5)  chord = Emin;
      if(i == 6)  chord = Fsdim;
      if(i == 7)  chord = Gmaj2;
      
      // Third row
      if(i == 8)  chord = Amin2;
      if(i == 9)  chord = Bmin2;
      if(i == 10) chord = Cmaj2;
      if(i == 11) chord = Dmaj2;

      // Fourth row
      if(i == 14) chord = Emin2;
      if(i == 15) chord = Fsdim2;
    }

    /// G#
    if (scale == 8) {
      // First row
      if(i == 0)  chord = Gsmaj;
      if(i == 1)  chord = Asmin;
      if(i == 2)  chord = Cmin;
      if(i == 3)  chord = Csmaj;
      
      // Second row
      if(i == 4)  chord = Dsmaj;
      if(i == 5)  chord = Fmin;
      if(i == 6)  chord = Gdim;
      if(i == 7)  chord = Gsmaj2;
      
      // Third row
      if(i == 8)  chord = Asmin2;
      if(i == 9)  chord = Cmin2;
      if(i == 10) chord = Csmaj2;
      if(i == 11) chord = Dsmaj2;

      // Fourth row
      if(i == 14) chord = Fmin2;
      if(i == 15) chord = Gdim2;
    }

    /// A
    if (scale == 9) {
      // First row
      if(i == 0)  chord = Amaj;
      if(i == 1)  chord = Bmin;
      if(i == 2)  chord = Csmin;
      if(i == 3)  chord = Dmaj;
      
      // Second row
      if(i == 4)  chord = Emaj;
      if(i == 5)  chord = Fsmin;
      if(i == 6)  chord = Gsdim;
      if(i == 7)  chord = Amaj2;
      
      // Third row
      if(i == 8)  chord = Bmin2;
      if(i == 9)  chord = Csmin2;
      if(i == 10) chord = Dmaj2;
      if(i == 11) chord = Emaj2;

      // Fourth row
      if(i == 14) chord = Fsmin2;
      if(i == 15) chord = Fsdim2;
    }

    /// A#
    if (scale == 10) {
      // First row
      if(i == 0)  chord = Asmaj;
      if(i == 1)  chord = Cmin;
      if(i == 2)  chord = Dmin;
      if(i == 3)  chord = Dsmaj;
      
      // Second row
      if(i == 4)  chord = Fmaj;
      if(i == 5)  chord = Gmin;
      if(i == 6)  chord = Adim;
      if(i == 7)  chord = Asmaj2;
      
      // Third row
      if(i == 8)  chord = Cmin2;
      if(i == 9)  chord = Dmin2;
      if(i == 10) chord = Dsmaj2;
      if(i == 11) chord = Fmaj2;

      // Fourth row
      if(i == 14) chord = Gmin2;
      if(i == 15) chord = Adim2;
    }

    /// B
    if (scale == 11) {
      // First row
      if(i == 0)  chord = Bmaj;
      if(i == 1)  chord = Csmin;
      if(i == 2)  chord = Dsmin;
      if(i == 3)  chord = Emaj;
      
      // Second row
      if(i == 4)  chord = Fsmaj;
      if(i == 5)  chord = Gsmin;
      if(i == 6)  chord = Asdim;
      if(i == 7)  chord = Bmaj2;
      
      // Third row
      if(i == 8)  chord = Csmin2;
      if(i == 9)  chord = Dsmin2;
      if(i == 10) chord = Emaj2;
      if(i == 11) chord = Fsmaj2;

      // Fourth row
      if(i == 14) chord = Gsmin2;
      if(i == 15) chord = Asdim2;
    }
  } else {
    // C
    if (scale == 0) {
      // First row
      if(i == 0) chord = Cmin;
      if(i == 1) chord = Ddim;
      if(i == 2) chord = Dsmaj;
      if(i == 3) chord = Fmin;
      
      // Second row
      if(i == 4)  chord = Gmin;
      if(i == 5)  chord = Gsmaj;
      if(i == 6)  chord = Asmaj;
      if(i == 7)  chord = Cmin2;
      
      // Third row
      if(i == 8)  chord = Ddim2;
      if(i == 9)  chord = Dsmaj2;
      if(i == 10) chord = Fmin2;
      if(i == 11) chord = Gmin2;
      
      // Fourth row
      if(i == 14) chord = Gsmaj2;
      if(i == 15) chord = Asmaj2;
    }

    // C#
    if (scale == 1) {
      // First row
      if(i == 0) chord = Csmin;
      if(i == 1) chord = Dsdim;
      if(i == 2) chord = Emaj;
      if(i == 3) chord = Fsmin;
      
      // Second row
      if(i == 4)  chord = Gsmin;
      if(i == 5)  chord = Amaj;
      if(i == 6)  chord = Bmaj;
      if(i == 7)  chord = Csmin2;
      
      // Third row
      if(i == 8)  chord = Dsdim2;
      if(i == 9)  chord = Emaj2;
      if(i == 10) chord = Fsmin2;
      if(i == 11) chord = Gsmin2;
      
      // Fourth row
      if(i == 14) chord = Amaj2;
      if(i == 15) chord = Bmaj2;
    }

    // D
    if (scale == 2) {
      // First row
      if(i == 0) chord = Dmin;
      if(i == 1) chord = Edim;
      if(i == 2) chord = Fmaj;
      if(i == 3) chord = Gmin;
      
      // Second row
      if(i == 4)  chord = Amin;
      if(i == 5)  chord = Asmaj;
      if(i == 6)  chord = Cmaj;
      if(i == 7)  chord = Dmin2;
      
      // Third row
      if(i == 8)  chord = Edim2;
      if(i == 9)  chord = Fmaj2;
      if(i == 10) chord = Gmin2;
      if(i == 11) chord = Amin2;
      
      // Fourth row
      if(i == 14) chord = Asmaj2;
      if(i == 15) chord = Cmaj2;
    }

    // D#
    if (scale == 3) {
      // First row
      if(i == 0) chord = Dsmin;
      if(i == 1) chord = Fdim;
      if(i == 2) chord = Fsmaj;
      if(i == 3) chord = Gsmin;
      
      // Second row
      if(i == 4)  chord = Asmin;
      if(i == 5)  chord = Bmaj;
      if(i == 6)  chord = Csmaj;
      if(i == 7)  chord = Dsmin2;
      
      // Third row
      if(i == 8)  chord = Fdim2;
      if(i == 9)  chord = Fsmaj2;
      if(i == 10) chord = Gsmin2;
      if(i == 11) chord = Asmin2;
      
      // Fourth row
      if(i == 14) chord = Bmaj2;
      if(i == 15) chord = Csmaj2;
    }

    // E
    if (scale == 4) {
      // First row
      if(i == 0) chord = Emin;
      if(i == 1) chord = Fsdim;
      if(i == 2) chord = Gmaj;
      if(i == 3) chord = Amin;
      
      // Second row
      if(i == 4)  chord = Bmin;
      if(i == 5)  chord = Cmaj;
      if(i == 6)  chord = Dmaj;
      if(i == 7)  chord = Emin2;
      
      // Third row
      if(i == 8)  chord = Fsdim2;
      if(i == 9)  chord = Gmaj2;
      if(i == 10) chord = Amin2;
      if(i == 11) chord = Bmin2;
      
      // Fourth row
      if(i == 14) chord = Cmaj2;
      if(i == 15) chord = Dmaj2;
    }

    // F
    if (scale == 5) {
      // First row
      if(i == 0) chord = Fmin;
      if(i == 1) chord = Gdim;
      if(i == 2) chord = Gsmaj;
      if(i == 3) chord = Asmin;
      
      // Second row
      if(i == 4)  chord = Cmin;
      if(i == 5)  chord = Csmaj;
      if(i == 6)  chord = Dsmaj;
      if(i == 7)  chord = Fmin2;
      
      // Third row
      if(i == 8)  chord = Gdim2;
      if(i == 9)  chord = Gsmaj2;
      if(i == 10) chord = Asmin2;
      if(i == 11) chord = Cmin2;
      
      // Fourth row
      if(i == 14) chord = Csmaj2;
      if(i == 15) chord = Dsmaj2;
    }

    // F#
    if (scale == 6) {
      // First row
      if(i == 0) chord = Fsmin;
      if(i == 1) chord = Gsdim;
      if(i == 2) chord = Amaj;
      if(i == 3) chord = Bmin;
      
      // Second row
      if(i == 4)  chord = Csmin;
      if(i == 5)  chord = Dmaj;
      if(i == 6)  chord = Emaj;
      if(i == 7)  chord = Fsmin2;
      
      // Third row
      if(i == 8)  chord = Gsdim2;
      if(i == 9)  chord = Amaj2;
      if(i == 10) chord = Bmin2;
      if(i == 11) chord = Csmin2;
      
      // Fourth row
      if(i == 14) chord = Dmaj2;
      if(i == 15) chord = Emaj2;
    }

    // G
    if (scale == 7) {
      // First row
      if(i == 0) chord = Gmin;
      if(i == 1) chord = Adim;
      if(i == 2) chord = Asmaj;
      if(i == 3) chord = Cmin;
      
      // Second row
      if(i == 4)  chord = Dmin;
      if(i == 5)  chord = Dsmaj;
      if(i == 6)  chord = Fmaj;
      if(i == 7)  chord = Gmin2;
      
      // Third row
      if(i == 8)  chord = Adim2;
      if(i == 9)  chord = Asmaj2;
      if(i == 10) chord = Cmin2;
      if(i == 11) chord = Dmin2;
      
      // Fourth row
      if(i == 14) chord = Dsmaj2;
      if(i == 15) chord = Fmaj2;
    }

    // G#
    if (scale == 8) {
      // First row
      if(i == 0) chord = Gsmin;
      if(i == 1) chord = Asdim;
      if(i == 2) chord = Bmaj;
      if(i == 3) chord = Csmin;
      
      // Second row
      if(i == 4)  chord = Dsmin;
      if(i == 5)  chord = Emaj;
      if(i == 6)  chord = Fsmaj;
      if(i == 7)  chord = Gsmin2;
      
      // Third row
      if(i == 8)  chord = Asdim2;
      if(i == 9)  chord = Bmaj;
      if(i == 10) chord = Csmin2;
      if(i == 11) chord = Dsmin2;
      
      // Fourth row
      if(i == 14) chord = Emaj2;
      if(i == 15) chord = Fsmaj2;
    }

    // A
    if (scale == 9) {
      // First row
      if(i == 0) chord = Amin;
      if(i == 1) chord = Bdim;
      if(i == 2) chord = Cmaj;
      if(i == 3) chord = Dmin;
      
      // Second row
      if(i == 4)  chord = Emin;
      if(i == 5)  chord = Fmaj;
      if(i == 6)  chord = Gmaj;
      if(i == 7)  chord = Amin;
      
      // Third row
      if(i == 8)  chord = Bdim2;
      if(i == 9)  chord = Cmaj2;
      if(i == 10) chord = Dmin2;
      if(i == 11) chord = Emin2;
      
      // Fourth row
      if(i == 14) chord = Fmaj2;
      if(i == 15) chord = Gmaj2;
    }

    // A#
    if (scale == 10) {
      // First row
      if(i == 0) chord = Asmin;
      if(i == 1) chord = Cdim;
      if(i == 2) chord = Csmaj;
      if(i == 3) chord = Dsmin;
      
      // Second row
      if(i == 4)  chord = Fmin;
      if(i == 5)  chord = Fsmaj;
      if(i == 6)  chord = Gsmaj;
      if(i == 7)  chord = Asmin2;
      
      // Third row
      if(i == 8)  chord = Cdim2;
      if(i == 9)  chord = Csmaj2;
      if(i == 10) chord = Dsmin2;
      if(i == 11) chord = Fmin2;
      
      // Fourth row
      if(i == 14) chord = Fsmaj2;
      if(i == 15) chord = Gsmaj2;
    }
    
    // A#
    if (scale == 11) {
      // First row
      if(i == 0) chord = Bmin;
      if(i == 1) chord = Csdim;
      if(i == 2) chord = Dmaj;
      if(i == 3) chord = Emin;
      
      // Second row
      if(i == 4)  chord = Fsmin;
      if(i == 5)  chord = Gmaj;
      if(i == 6)  chord = Amaj;
      if(i == 7)  chord = Bmin2;
      
      // Third row
      if(i == 8)  chord = Csdim2;
      if(i == 9)  chord = Dmaj2;
      if(i == 10) chord = Emin2;
      if(i == 11) chord = Fsmin2;
      
      // Fourth row
      if(i == 14) chord = Gmaj2;
      if(i == 15) chord = Amaj2;
    }
  }
  
  return chord;
}
