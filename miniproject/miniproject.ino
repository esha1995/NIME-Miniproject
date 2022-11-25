#include "chords.h"
#include <Wire.h>
#include "Adafruit_Trellis.h"

#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define INTPIN A2
#define delayPin A0
#define randomPin A17

int randomVal;
int midiVal1;
int midiVal2;

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

int channel = 1;
float finger_delay = 10;
bool chordReleased = false;
bool changeChord = false;
bool majorMinor = true;
int chord = 0;
bool chordPressed = false;
int scale = 0;
int mapping[16] = {15,11,7,3,14,10,6,2,13,9,5,1,12,8,4,0}; 

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
    finger_delay = map(analogRead(delayPin), 1023, 0, 0,150); // reading delay pn
    randomVal = map(analogRead(randomPin), 1023,0,0,50);

    if(chordPressed){
      playChord(selectChord3(chord, 100, majorMinor, scale), finger_delay, randomVal);
      chordPressed = false;
     }
    
    trellis.setLED(12);
    if (trellis.readSwitches()) {
      // go through every button

      for (uint8_t i=0; i<numKeys; i++) {
        if(i == mapping[12]) {
          if(trellis.justPressed(mapping[12]) && changeChord == false) {
            changeChord = true;
          } 
          else if(trellis.justPressed(mapping[12]) && changeChord == true) {
            changeChord = false;
          }
        } 
        else if(i == mapping[13]) {
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
              if(mapping[i] != mapping[14] && mapping[i] != mapping[15] && mapping[i] != mapping[13] && mapping[i] != mapping[12]) {
                  trellis.setLED(mapping[i]);
                  if(trellis.justPressed(mapping[i])) {
                    scale = i;
                    changeChord = false;
                    Serial.println(i);
                  }
              }
           }
           else {
            if(mapping[i] != mapping[14] && mapping[i] != mapping[15] && mapping[i] != mapping[13] && mapping[i] != mapping[12]) {
            trellis.clrLED(mapping[i]);
              if (trellis.justPressed(mapping[i])) {
                // Serial.println(i);
                chordPressed = true;
                chord = i;
                trellis.setLED(mapping[i]);
               } 
                // if it was released, turn it off
              if (trellis.justReleased(mapping[i])) {
                
                stopChord(selectChord3(i, 0, majorMinor, scale)); 
                trellis.clrLED(mapping[i]);
              }
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

void playChord(int *chord, int delayValue, int randomVal) 
{
  
  int velocity1 = random(100-randomVal, 100);
  usbMIDI.sendNoteOn(chord[0], velocity1, channel);
  delay(delayValue);
  int velocity2 = random(100-randomVal, 100);
  usbMIDI.sendNoteOn(chord[1], velocity2, channel);
  delay(delayValue);
  int velocity3 = random(100-randomVal, 100);
  usbMIDI.sendNoteOn(chord[2], velocity3, channel);
}

void stopChord(int *chord) 
{
  usbMIDI.sendNoteOff(chord[0], 0, channel);
  usbMIDI.sendNoteOff(chord[1], 0, channel);
  usbMIDI.sendNoteOff(chord[2], 0, channel);
}

int * selectChord(int i, float velocity, bool isMajor, int scale) {
  int *chord;
  if (isMajor) {
    /// C
    if (scale == 0) {
      switch (i) {
              case 0:
                chord = Cmin;
                break;
              case 1:
                chord = Ddim;
                break;
              case 2:
                chord = Dsmaj;
                break;
              case 3:
                chord = Fmin;
                break;
              case 4:
                chord = Gmin;
                break;
              case 5:
                chord = Gsmaj;
                break;
              case 6:
                chord = Asmaj;
                break;
              case 7:
                chord = Cmin2;
                break;
              case 8:
                chord = Ddim2;
                break;
              case 9:
                chord = Dsmaj2;
                break;
              case 10:
                chord = Fmin2;
                break;
              case 11:
                chord = Gmin2;
                break;
              default:
                chord = Cmin;
                break;
            }

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

int * selectChord3(int i, float velocity, bool isMajor, int scale) {
  if (isMajor) {    
    switch (scale) {
        case 0:
            switch (i) {
              case 0:
                return Cmaj;
                break;
              case 1:
                return Dmin;
                break;
              case 2:
                return Emin;
                break;
              case 3:
                return Fmaj;
                break;
              case 4:
                return Gmin;
                break;
              case 5:
                return Amin;
                break;
              case 6:
                return Bdim;
                break;
              case 7:
                return Cmaj2;
                break;
              case 8:
                return Dmin2;
                break;
              case 9:
                return Emin2;
                break;
              case 10:
                return Fmaj2;
                break;
              case 11:
                return Gmin2;
                break;
              default:
                return Cmin;
                break;
            }
            break;
        case 1:
            switch (i) {
              case 0:
                return Csmaj;
                break;
              case 1:
                return Dsmin;
                break;
              case 2:
                return Fmin;  
                break;
              case 3:
                return Fsmaj;  
                break;
              case 4:
                return Gsmin;  
                break;
              case 5:
                return Asmin;  
                break;
              case 6:
                return Cdim;  
                break;
              case 7:
                return Csmaj2;  
                break;
              case 8:
                return Dsmin2;  
                break;
              case 9:
                return Fmin2;  
                break;
              case 10:
                return Fsmaj2;  
                break;
              case 11:
                return Gsmin2;  
                break;
              default:
                return Csmaj;
                break;
            }
            
            break;
        case 2:
            switch (i) {
              case 0:
                  return Dmaj;
                  break;
              case 1:
                  return Emin;
                  break;
              case 2:
                  return Fsmin;
                  break;
              case 3:
                  return Gmaj;
                  break;
              case 4:
                  return Amaj;
                  break;
              case 5:
                  return Bmin;
                  break;
              case 6:
                  return Csdim;
                  break;
              case 7:
                  return Dmaj2;
                  break;
              case 8:
                  return Emin2;
                  break;
              case 9:
                  return Fsmin2;
                  break;
              case 10:
                  return Gmaj2;
                  break;
              case 11:
                  return Amaj2;
                  break;
              default:
                return Dmaj;
                break;
            }
            
            break;
        case 3:
            switch (i) {
              case 0:
                return Dsmaj;
                break;
              case 1:
                return Fmin;
                break;  
              case 2:
                return Gmin;
                break;  
              case 3:
                return Gsmaj;
                break;  
              case 4:
                return Asmaj;
                break;  
              case 5:
                return Ddim;
                break;  
              case 6:
                return Ddim;
                break;  
              case 7:
                return Dsmaj2;
                break;  
              case 8:
                return Emin2;
                break;  
              case 9:
                return Fsmin2;
                break;  
              case 10:
                return Gmaj2;
                break;  
              case 11:
                return Amaj2;
                break; 
              default:
                return Dsmaj;
                break;
            }
            
            break;
        case 4:
            switch (i) {
              case 0:
                return Emaj;
                break;  
              case 1:
                return Fsmin;
                break;  
              case 2:
                return Gsmin;
                break;  
              case 3:
                return Amaj;
                break;  
              case 4:
                return Bmaj;
                break;  
              case 5:
                return Csmin;
                break;  
              case 6:
                return Dsdim;
                break;  
              case 7:
                return Emaj2;
                break;  
              case 8:
                return Fsmin2;
                break;  
              case 9:
                return Gsmin2;
                break;  
              case 10:
                return Amaj2;
                break;  
              case 11:
                return Bmaj2;
                break;  
              default:
                return Emaj;
                break;
            }
            
            break; 
        case 5:
            switch (i) {
              case 0:
                return Fmaj;
                break;  
              case 1:
                return Gmin;
                break; 
              case 2:
                return Amin;
                break; 
              case 3:
                return Asmaj;
                break; 
              case 4:
                return Cmaj;
                break; 
              case 5:
                return Dmin;
                break; 
              case 6:
                return Edim;
                break; 
              case 7:
                return Fmaj2;
                break;
              case 8:
                return Gmin2;
                break; 
              case 9:
                return Amin2;
                break; 
              case 10:
                return Asmaj2;
                break; 
              case 11:
                return Cmaj2;
                break; 
              default:
                return Fmaj;
                break;
            }
            
            break;
        case 6:
            switch (i) {
              case 0:
                return Fsmaj;
                break;  
              case 1:
                return Gsmin;
                break;
              case 2:
                return Asmin;
                break;  
              case 3:
                return Bmaj;
                break;
              case 4:
                return Csmaj; 
                break;
              case 5:
                return Dsmin;
                break; 
              case 6:
                return Fdim;
                break;
              case 7:
                return Fsmaj2; 
                break;
              case 8:
                return Gsmin2;
                break;
              case 9:
                return Asmin2; 
                break;
              case 10:
                return Bmaj2;
                break;
              case 11:
                return Csmaj2; 
                break;
              default:
                return Fsmaj;
                break;
            }
            break;
        case 7:
            switch (i) {
              case 0:
                return Gmaj;
                break;
              case 1:
                return Amin;
                break;
              case 2:
                return Bmin;
                break;    
              case 3:
                return Cmaj;
                break;
              case 4:
                return Dmaj;
                break;
              case 5:
                return Emin;
                break;
              case 6:
                return Fsdim;
                break;
              case 7:
                return Gmaj2;
                break;
              case 8:
                return Amin2;
                break;
              case 9:
                return Bmin2;
                break;
              case 10:
                return Cmaj2;
                break;
              case 11:
                return Dmaj2;
                break;
              default:
                return Gmaj;
                break;
            }
            
            break;
        case 8:
            switch (i) {
              case 0:
                return Gsmaj;
                break;
              case 1:
                return Asmin;
                break;    
              case 2:
                return Cmin;
                break;
              case 3:
                return Csmaj;
                break;
              case 4:
                return Dsmaj;
                break;                  
              case 5:
                return Fmin;
                break;
              case 6:
                return Gdim;
                break;
              case 7:
                return Gsmaj2;
                break;
              case 8:
                return Asmin2;
                break;
              case 9:
                return Cmin2;
                break;
              case 10:
                return Csmaj2;
                break;
              case 11:
                return Dsmaj2;
                break;
              default:
                return Gsmaj;
                break;
            }
            
            break;
        case 9:
            switch (i) {
              case 0:
                return Amaj;
                break;
              case 1:
                return Bmin;
                break;    
              case 2:
                return Csmin;
                break;
              case 3:
                return Dmaj;
                break;
              case 4:
                return Emaj;
                break;
              case 5:
                return Fsmin;
                break;
              case 6:
                return Gsdim;
                break;
              case 7:
                return Amaj2;
                break;
              case 8:
                return Bmin2;
                break;
              case 9:
                return Csmin2;
                break;
              case 10:
                return Dmaj2;
                break;
              case 11:
                return Emaj2;
                break;
              default:
                return Amaj;
                break;
            }
            
            break;
        case 10:
            switch (i) {
              case 0:
                return Asmaj;
                break;
              case 1:
                return Cmin;
                break;    
              case 2:
                return Dmin;
                break;
              case 3:
                return Dsmaj;
                break;
              case 4:
                return Fmaj;
                break;
              case 5:
                return Gmin;
                break;
              case 6:
                return Adim;
                break;
              case 7:
                return Asmaj2;
                break;
              case 8:
                return Cmin2;
                break;
              case 9:
                return Dmin2;
                break;
              case 10:
                return Dsmaj2;
                break;
              case 11:
                return Fmaj2;
                break;
              default:
                return Asmaj;
                break;
            }
            
            break;
        case 11:
            switch (i) {
              case 0:
                return Bmaj;
                break;
              case 1:
                return Csmin;
                break;    
              case 2:
                return Dsmin;
                break;
              case 3:
                return Emaj;
                break;
              case 4:
                return Fsmaj;
                break;    
              case 5:
                return Gsmin;
                break;    
              case 6:
                return Asdim;
                break;    
              case 7:
                return Bmaj2;
                break;    
              case 8:
                return Csmin2;
                break;    
              case 9:
                return Dsmin2;
                break;    
              case 10:
                return Emaj2;
                break;    
              case 11:
                return Fsmaj2;
                break;    
              default:
                return Bmaj;
                break;
            }
        default:
          return Cmaj;
          break;
        }
  } else {
    switch (scale) {
      case 0:
        switch (i) {
          case 0:
            return Cmin;
            break;
          case 1:
            return Ddim;
            break;
          case 2:
            return Dsmaj;
            break;
          case 3:
            return Fmin;
            break;
          case 4:
            return Gmin;
            break;
          case 5:
            return Gsmaj;
            break;
          case 6:
            return Asmaj;
            break; 
          case 7:
            return Cmin2;
            break;
          case 8: 
            return Ddim2; 
            break;
          case 9:
            return Dsmaj2;
            break;
          case 10:
            return Fmin2;
            break;
          case 11:
            return Gmin2;
            break;
          default:
            return Cmin;
            break;
        }
        
        break;
      case 1:
          switch (i) {
          case 0:
            return Csmin;
            break;
          case 1:
            return Dsdim;
            break;
          case 2:
            return Emaj;
            break;
          case 3:
            return Fsmin;
            break;
          case 4:
            return Gsmin;
            break;
          case 5:
            return Amaj;
            break;
          case 6:
            return Bmaj;
            break; 
          case 7:
            return Csmin2;
            break;
          case 8: 
            return Dsdim2; 
            break;
          case 9:
            return Fsmin2;
            break;
          case 10:
            return Gsmin2;
            break;
          case 11:
            return Gmin2;
            break;
          default:
            return Cmin;
            break;
        }
      
        break;
      case 2:
        switch (i) {
          case 0:
            return Dmin;
            break;
          case 1:
            return Edim;
            break;
          case 2:
            return Fmaj;
            break;
          case 3:
            return Gmin;
            break;
          case 4:
            return Amin;
            break;
          case 5:
            return Asmaj;
            break;
          case 6:
            return Cmaj;
            break; 
          case 7:
            return Dmin2;
            break;
          case 8: 
            return Edim2; 
            break;
          case 9:
            return Fmaj2;
            break;
          case 10:
            return Gmin2;
            break;
          case 11:
            return Amin2;
            break;
          default:
            return Dmin;
            break;
        }
        
        break;
      case 3:
        switch (i) {
            case 0:
              return Dsmin;
              break;
            case 1:
              return Fdim;
              break;
            case 2:
              return Fsmaj;
              break;
            case 3:
              return Gsmin;
              break;
            case 4:
              return Asmin;
              break;
            case 5:
              return Bmaj;
              break;
            case 6:
              return Csmaj;
              break; 
            case 7:
              return Dsmin2;
              break;
            case 8: 
              return Fdim2; 
              break;
            case 9:
              return Fsmaj2;
              break;
            case 10:
              return Gsmin2;
              break;
            case 11:
              return Asmin2;
              break;
            default:
              return Dsmin;
              break;
          }
          
        break;
      case 4:
          switch (i) {
            case 0:
              return Emin;
              break;
            case 1:
              return Fsdim;
              break;
            case 2:
              return Gmaj;
              break;
            case 3:
              return Amin;
              break;
            case 4:
              return Bmin;
              break;
            case 5:
              return Cmaj;
              break;
            case 6:
              return Dmaj;
              break; 
            case 7:
              return Emin2;
              break;
            case 8: 
              return Fsdim2; 
              break;
            case 9:
              return Gmaj2;
              break;
            case 10:
              return Amin2;
              break;
            case 11:
              return Bmin2;
              break;
            default:
              return Emin;
              break;
          }
          
        break;
      case 5:
          switch (i) {
            case 0:
              return Fmin;
              break;
            case 1:
              return Gdim;
              break;
            case 2:
              return Gsmaj;
              break;
            case 3:
              return Asmin;
              break;
            case 4:
              return Cmin;
              break;
            case 5:
              return Csmaj;
              break;
            case 6:
              return Dsmaj;
              break; 
            case 7:
              return Fmin2;
              break;
            case 8: 
              return Gdim2; 
              break;
            case 9:
              return Gsmaj2;
              break;
            case 10:
              return Asmin2;
              break;
            case 11:
              return Cmin2;
              break;
            default:
              return Fmin;
              break;
          }
          
        break;
      case 6:
          switch (i) {
            case 0:
              return Fsmin;
              break;
            case 1:
              return Gsdim;
              break;
            case 2:
              return Amaj;
              break;
            case 3:
              return Bmin;
              break;
            case 4:
              return Csmin;
              break;
            case 5:
              return Dmaj;
              break;
            case 6:
              return Emaj;
              break; 
            case 7:
              return Fsmin2;
              break;
            case 8: 
              return Gsdim2; 
              break;
            case 9:
              return Amaj2;
              break;
            case 10:
              return Bmin2;
              break;
            case 11:
              return Csmin2;
              break;
            default:
              return Fsmin;
              break;
          }
          
        break;
      case 7:
          switch (i) {
            case 0:
              return Gmin;
              break;
            case 1:
              return Adim;
              break;
            case 2:
              return Asmaj;
              break;
            case 3:
              return Cmin;
              break;
            case 4:
              return Dmin;
              break;
            case 5:
              return Dsmaj;
              break;
            case 6:
              return Fmaj;
              break; 
            case 7:
              return Gmin2;
              break;
            case 8: 
              return Adim2; 
              break;
            case 9:
              return Asmaj2;
              break;
            case 10:
              return Cmin2;
              break;
            case 11:
              return Dmin2;
              break;
            default:
              return Gmin;
              break;
          }
          
        break;
      case 8:
          switch (i) {
            case 0:
              return Gsmin;
              break;
            case 1:
              return Asdim;
              break;
            case 2:
              return Bmaj;
              break;
            case 3:
              return Csmin;
              break;
            case 4:
              return Dsmin;
              break;
            case 5:
              return Emaj;
              break;
            case 6:
              return Fsmaj;
              break; 
            case 7:
              return Gsmin2;
              break;
            case 8: 
              return Asdim2; 
              break;
            case 9:
              return Bmaj;
              break;
            case 10:
              return Csmin2;
              break;
            case 11:
              return Dsmin2;
              break;
            default:
              return Gsmin;
              break;
          }
          
        break;

      case 9:
          switch (i) {
            case 0:
              return Amin;
              break;
            case 1:
              return Bdim;
              break;
            case 2:
              return Cmaj;
              break;
            case 3:
              return Dmin;
              break;
            case 4:
              return Emin;
              break;
            case 5:
              return Fmaj;
              break;
            case 6:
              return Gmaj;
              break; 
            case 7:
              return Amin;
              break;
            case 8: 
              return Bdim2; 
              break;
            case 9:
              return Cmaj2;
              break;
            case 10:
              return Dmin2;
              break;
            case 11:
              return Emin2;
              break;
            default:
              return Amin;
              break;
          }
          
        break;
      case 10:
          switch (i) {
            case 0:
              return Asmin;
              break;
            case 1:
              return Cdim;
              break;
            case 2:
              return Csmaj;
              break;
            case 3:
              return Dsmin;
              break;
            case 4:
              return Fmin;
              break;
            case 5:
              return Fsmaj;
              break;
            case 6:
              return Gsmaj;
              break; 
            case 7:
              return Asmin2;
              break;
            case 8: 
              return Cdim2; 
              break;
            case 9:
              return Csmaj2;
              break;
            case 10:
              return Dsmin2;
              break;
            case 11:
              return Fmin2;
              break;
            default:
              return Asmin;
              break;
          }
          
        break;
      case 11:
          switch (i) {
            case 0:
              return Bmin;
              break;
            case 1:
              return Csdim;
              break;
            case 2:
              return Dmaj;
              break;
            case 3:
              return Emin;
              break;
            case 4:
              return Fsmin;
              break;
            case 5:
              return Gmaj;
              break;
            case 6:
              return Amaj;
              break; 
            case 7:
              return Bmin2;
              break;
            case 8: 
              return Csdim2; 
              break;
            case 9:
              return Dmaj2;
              break;
            case 10:
              return Emin2;
              break;
            case 11:
              return Fsmin2;
              break;
            default:
              return Bmin;
              break;
          }
          
        break;
      default:
        return Cmaj;
        break;
    }
  }
}
