#include <Arduino.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"
// #include "USBMouse.h"
// #include "USBMouseKeyboard.h"
#include "usb_hid_keys.h"
#include "morse_keys.h"

#define US_KEYBOARD

const int switchPin = 21; 
int switchState = HIGH;  // Current state of the switch
int prevSwitchState = HIGH; // Previous state of the switch
unsigned long prevTime = 0; // Time of the last switch state change
String morseCode = ""; // String to store the Morse code
String lastCommand = "";
boolean pause = false;  // flag to indicate no input being decoded
int MODE = 1; // Different modes have different morse lookups

unsigned long debounceDelay = 30; // Debounce time in milliseconds
unsigned long maxDitTime = 150; // after this time, it's a dah
unsigned long maxDahTime = 600; // after this, it's a special control
unsigned long maxMovementDelay = 300; // after this, it's a new symbol
unsigned long maxCharDelay = 1600; // after this time, it's a space

// USBKeyboard Keyboard;
// USBMouse Mouse;
// USBMouseKeyboard MouseKeyboard;
USBKeyboard MouseKeyboard;

void setup() {
  Serial.begin(115200); 
  pinMode(switchPin, INPUT_PULLUP); 
}


// Outputs raw morse to serial terminal
void print_serial(){
  Serial.print(morseCode);
  Serial.print("  ");

return;
}

// int HandleSpecialCode(){

//   // Serial.println("HandleSpecialCode");

//   for(const auto& code : special_codes){
//     if( code.mode == MODE && code.morse.equals(morseCode)){
//       if(code.name == "Toggle MODE"){
//         MODE = MODE == 1 ? 2 : 1;
//       }else if(code.name == "m up"){
//         MouseKeyboard.move(0, 100);
//         lastCommand = code.morse;
//       }else if(code.name == "m dwn"){
//         MouseKeyboard.move(0, -100);
//         lastCommand = code.morse;
//       }else if(code.name == "m rt"){
//         MouseKeyboard.move(100, 0);
//         lastCommand = code.morse;
//       }else if(code.name == "m lt"){
//         MouseKeyboard.move(-100, 0);
//         lastCommand = code.morse;
//       }else if(code.name == "repeat"){
//         morseCode = lastCommand;
//         return HandleSpecialCode();
//       }else{
//         return false;
//       }

//       return true;
//     }
//   }
//   return false;

// }

  // if(HandleSpecialCode()){
  //   print_serial();
  //   morseCode = "";
  //   return;
  // }

void DecodeSymbol(){

  for(const auto& code : codes_lookup){
    if( code.morse == morseCode){
      MouseKeyboard.key_code(code.key_code, code.modifier_keys);
      print_serial();
      morseCode = "";
      return;
    }
  }

  print_serial(); // no match found
  Serial.print(" No match ");
  morseCode = "";
  return;
}


void loop() {
  unsigned long movementTime = millis() - prevTime;
  switchState = digitalRead(switchPin); 

  if(switchState == HIGH && pause == false){
    if(movementTime > maxCharDelay){ // must be a space
      morseCode = "|";
      // print_keyboard((char)(' '));
      // MouseKeyboard.key_code(KEY_SPACE);
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
