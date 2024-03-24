/*
deMorse, a keyboard and mouse emulator that uses a 
single digital input (e.g. a morse key) to emulate 
a keyboard and mouse

Stuart de Haas
*/

#define US_KEYBOARD

#include <Arduino.h>
#include "PluggableUSBHID.h"
#include "USBMouseKeyboard.h"
//#include "usb_hid_keys.h"
#include "morse_keys.h"


const int switchPin = 21; 
const int buzzerPin = 20;
int switchState = HIGH;  // Current state of the switch
int prevSwitchState = HIGH; // Previous state of the switch
unsigned long prevTime = 0; // Time of the last switch state change
String morseCode = ""; // String to store the Morse code
String previousMorse = ""; // History for use with repeat commands and similar
boolean pause = false;  // flag to indicate no input being decoded
int MODE = 1;  // Current keyboard layer

int mouse_dist[] = {5, 50, 100};
int mouse_speed = 1;
const int num_mouse_speeds = 3;

bool mouse_left_pressed = false;

unsigned long debounceDelay = 30; // Debounce time in milliseconds
unsigned long maxDitTime = 150; // after this time, it's a dah
unsigned long maxDahTime = 600; // after this, it's a special control
unsigned long maxMovementDelay = 300; // after this, it's a new symbol
unsigned long maxCharDelay = 1600; // after this time, it's a space

USBMouseKeyboard MouseKeyboard;

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

void make_mouse_faster(bool faster){
  mouse_speed += faster ? 1 : (-1);

  if(mouse_speed >= num_mouse_speeds){
    mouse_speed = num_mouse_speeds - 1;
  }else if(mouse_speed <= 0){
    mouse_speed = 0;
  }
  return;
}

int HandleSpecialCode(){

  for(const auto& code : specialCodes){
    if( code.mode == MODE && code.morse.equals(morseCode)){
      if(code.name.equals("Toggle MODE")){
        MODE = MODE == 1 ? 2 : 1;
        MODE == 1 ? 
          MouseKeyboard.key_code('w',KEY_CTRL): //Runs AHK script for toast
          MouseKeyboard.key_code('q',KEY_CTRL);
        Serial.print(MODE);
      }else if(code.name.equals("m up")){
        int dist = (-1)*mouse_dist[mouse_speed];
        MouseKeyboard.move(0, (-1)*(mouse_dist[mouse_speed]));
        previousMorse = code.morse;
      }else if(code.name.equals("m dwn")){
        MouseKeyboard.move(0, mouse_dist[mouse_speed]);
        previousMorse = code.morse;
      }else if(code.name.equals("m rt")){
        MouseKeyboard.move(mouse_dist[mouse_speed], 0);
        previousMorse = code.morse;
      }else if(code.name.equals("m lt")){
        MouseKeyboard.move((-1)*mouse_dist[mouse_speed], 0);
        previousMorse = code.morse;
      }else if(code.name.equals("repeat")){
        morseCode = previousMorse;
        HandleSpecialCode();

      }else if(code.name.equals("mb left")){
        MouseKeyboard.click(MOUSE_LEFT);
        previousMorse = code.morse;
      }else if(code.name.equals("mb right")){
        MouseKeyboard.click(MOUSE_RIGHT);
        previousMorse = code.morse;
      }else if(code.name.equals("mb double left")){
        MouseKeyboard.doubleClick();
        previousMorse = code.morse;
      }else if(code.name.equals("m slow")){
        make_mouse_faster(false);
        previousMorse = code.morse;
      }else if(code.name.equals("m fast")){
        make_mouse_faster(true);
        previousMorse = code.morse;
      }else if(code.name.equals("mb click&hold left")){
        if(mouse_left_pressed){
          MouseKeyboard.release(MOUSE_LEFT);
          mouse_left_pressed = false;
        }else{
          MouseKeyboard.press(MOUSE_LEFT);
          mouse_left_pressed = true;
        }
        previousMorse = code.morse;
      }else{
        return false;
      }
      return true;
    }
  }
  return false;
}

void DecodeSymbol(){

  if(HandleSpecialCode()){
    print_serial();
    morseCode = "";
    return;
  }

  for(const auto& code : codes){
    if( code.mode == MODE && code.morse.equals(morseCode)){
      MouseKeyboard.key_code_raw(code.key_code, code.modifier_keys);
      print_serial();
      morseCode = "";
      return;
    }
  }

  print_serial(); // no match found
  morseCode = "";
  return;
}


void loop() {
  unsigned long movementTime = millis() - prevTime;
  switchState = digitalRead(switchPin); 

  if(switchState == LOW){
    digitalWrite(buzzerPin, HIGH);
  }else{
    digitalWrite(buzzerPin, LOW);
  }

  if(switchState == HIGH && pause == false){
    if(movementTime > maxCharDelay){ // must be a space
      morseCode = "|";
      // print_keyboard((char)(' '));
      // MouseKeyboard.key_code_raw(0x2c, 0);
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
