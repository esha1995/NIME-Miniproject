
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

boolean changeChord = false;
boolean majorMinor = true;

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

      
      for (uint8_t i=0; i<numKeys; i++) 
      {

        if(i == 12) 
        {
          if(trellis.justPressed(mapping[12]) && changeChord == false){
            changeChord = true;
            }
            
          else if(trellis.justPressed(mapping[12]) && changeChord == true){
            changeChord = false;
           }
         }
         else if(i == 8)
         {
          if(trellis.justPressed(mapping[13]) && majorMinor == false)
          {
            majorMinor = true; 
          }
          else if(trellis.justPressed(mapping[13]) && majorMinor == true)
          {
           majorMinor = false;
          }
         }

         
        else{
          // if in change scale mode
          if(changeChord){
              if(mapping[i] != mapping[14] && mapping[i] != mapping[15]){
                  trellis.setLED(mapping[i]);
                  if(trellis .justPressed(mapping[i]))
                  {
                    scale = i;
                    Serial.println(i);
                  }
                }
           }
           else{
            trellis.clrLED(mapping[i]);
            if (trellis.justPressed(mapping[i]))
               {
                Serial.println(i);
                usbMIDI.sendNoteOn(60 + i, 100, channel);
                trellis.setLED(mapping[i]);
               } 
                // if it was released, turn it off
              if (trellis.justReleased(mapping[i])) 
              {
                usbMIDI.sendNoteOff(60 + i, 0, channel);
                trellis.clrLED(mapping[i]);
              }
            }
        }
      }
     }

    if(majorMinor) trellis.setLED(mapping[13]);
    else trellis.clrLED(mapping[13]);
    trellis.writeDisplay();
  }


void majorChord(int i, float velocity)
{
  int *chord;
  
  if(i == row1) chord = Cmajor;
  if(i == row1 - 4) chord = Csmajor;
  if(i == row1 - (4*2)) chord = Dmajor;
  if(i == row1 - (4*3)) chord = Dsmajor;

  if(i == row1) chord = Cmajor;
  if(i == row1 - 4) chord = Csmajor;
  if(i == row1 - (4*2)) chord = Dmajor;
  if(i == row1 - (4*3)) chord = Dsmajor;  


  
  
}

void stopChord(int i)
{

}
