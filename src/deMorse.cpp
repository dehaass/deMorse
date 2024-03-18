#include <Arduino.h>
// #include <Wire.h>
// #include "PluggableUSBHID.h"
// #include "USBKeyboard.h"

const int switchPin = 21; // Switch connected to pin 7
int switchState = HIGH;  // Current state of the switch
int prevSwitchState = HIGH; // Previous state of the switch
unsigned long prevTime = 0; // Time of the last switch state change
String morseCode = ""; // String to store the Morse code
boolean pause = false;

unsigned long debounceDelay = 30; // Debounce time in milliseconds
unsigned long maxDitTime = 150; // after this time, it's a dah
unsigned long maxDahTime = 600; // after this, it's a special control
unsigned long maxMovementDelay = 300; // after this, it's a new symbol
unsigned long maxCharDelay = 1600; // after this time, it's a space

void setup() {
  Serial.begin(115200); // Initialize serial communication
  pinMode(switchPin, INPUT_PULLUP); // Set pin 7 as input with internal pull-up resistor
}

void DecodeSymbol() {
  static String letters[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
  };
  int i = 0;
  while (letters[i] != "E") {
    if (letters[i] == morseCode) {
      //print_local((char)('A' + i));
      Serial.print((char)('A' + i));
      break;
    }
    i++;
  }
  if (letters[i] == "E") {
    //print_local(morseCode);
    Serial.print(morseCode);
  }
  morseCode = "";
  return;
}


void print_local(){
  Serial.print(morseCode);
  Serial.print("  ");

return;
}

// void DecodeSymbol(){
//   Serial.print(morseCode);
//   Serial.print("  ");
//   morseCode = "";
//   return;
// }


void sendSymbol(char symbol){
return;
}


void loop() {
  unsigned long movementTime = millis() - prevTime;
  switchState = digitalRead(switchPin); 

  if(switchState == HIGH && pause == false){
    if(movementTime > maxCharDelay){ // must be a space
      morseCode = "|";
      DecodeSymbol();
      pause = true;
    }else if(movementTime > maxMovementDelay && morseCode != ""){ // character is finished
      DecodeSymbol();
      //prevTime = millis(); 
    }
  }
  
  if (switchState != prevSwitchState && movementTime > debounceDelay) { // Check for switch state change and debounce
    prevSwitchState = switchState; 
    prevTime = millis();
    pause = false;

    if (switchState == HIGH) { // If the switch is released
      if(movementTime > maxDahTime){
        // Do something cool. Maybe delete? 
      }else if (movementTime > maxDitTime) { 
        morseCode += "-"; 
      } else {
        morseCode += "."; 
      }
    }
  }

}
