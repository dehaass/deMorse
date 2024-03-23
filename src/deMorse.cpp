#include <Arduino.h>
//#include <Wire.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"
#include "usb_hid_keys.h"
#include "morse_keys.h"

#define US_KEYBOARD

const int switchPin = 21; 
int switchState = HIGH;  // Current state of the switch
int prevSwitchState = HIGH; // Previous state of the switch
unsigned long prevTime = 0; // Time of the last switch state change
String morseCode = ""; // String to store the Morse code
boolean pause = false;  // flag to indicate no input being decoded

unsigned long debounceDelay = 30; // Debounce time in milliseconds
unsigned long maxDitTime = 150; // after this time, it's a dah
unsigned long maxDahTime = 600; // after this, it's a special control
unsigned long maxMovementDelay = 300; // after this, it's a new symbol
unsigned long maxCharDelay = 1600; // after this time, it's a space

USBKeyboard Keyboard;

void setup() {
  Serial.begin(115200); 
  pinMode(switchPin, INPUT_PULLUP); 
}


// Generates the USB Keyboard outputs
// void print_keyboard(char s){
//   Keyboard.putc(s);
// }

// Outputs raw morse to serial terminal
void print_serial(){
  Serial.print(morseCode);
  Serial.print("  ");

return;
}

void DecodeSymbol(){

  for(const auto& code : codes){
    if(code.morse.equals(morseCode)){
      Keyboard.key_code_raw(code.key_code, code.modifier_keys);
      print_serial();
      morseCode = "";
      return;
    }
  }

  print_serial(); // no match found
  morseCode = "";
  return;
}

// convert raw morse to ASCII
// void OBSDecodeSymbol() {
//   static String letters[] = {
//     ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
//     ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
//   };
//   static String numbers[] = {
//     "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "E"
//   };
//   static String special[] = {
//     "....."
//   };

//   int i = 0;
//   while (letters[i] != "E") {
//     if (letters[i] == morseCode) {
//       print_keyboard((char)('A') + i);
//       print_serial();
//       break;
//     }
//     i++;
//   }

//   i=0;
//   while(numbers[i] != "E"){
//     if (numbers[i] == morseCode) {
//       print_keyboard((char)('0') + i);
//       print_serial();
//       break;
//     }
//     i++;
//   }

//   if(special[0] == morseCode){
//     Keyboard.key_code_raw(KEY_TAB, KEY_ALT);
//   }

//   if (numbers[i] == "E") {
//     //print_local(morseCode);
//     // Serial.print(morseCode);
//     print_serial();
//   }
//   morseCode = "";
//   return;
// }


void loop() {
  unsigned long movementTime = millis() - prevTime;
  switchState = digitalRead(switchPin); 

  if(switchState == HIGH && pause == false){
    if(movementTime > maxCharDelay){ // must be a space
      morseCode = "|";
      // print_keyboard((char)(' '));
      Keyboard.key_code(KEY_SPACE);
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
