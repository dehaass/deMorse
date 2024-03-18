#include <Arduino.h>
#include <Wire.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"

const int switchPin = 21; // Switch connected to pin 7
int switchState = HIGH;  // Current state of the switch
int prevSwitchState = HIGH; // Previous state of the switch
unsigned long prevTime = 0; // Time of the last switch state change
String morseCode = ""; // String to store the Morse code
unsigned long debounceDelay = 30; // Debounce time in milliseconds

int maxDitTime = 70; // after this time, it's a dah
int maxCharDelay = 100; // after this time, it's a space

void setup() {
  Serial.begin(115200); // Initialize serial communication
  pinMode(switchPin, INPUT_PULLUP); // Set pin 7 as input with internal pull-up resistor
}

void loop() {
  unsigned long currentTime = millis(); // Get the current time
  switchState = digitalRead(switchPin); // Read the state of the switch

  // Check for switch state change and debounce
  if (switchState != prevSwitchState && currentTime - prevTime > debounceDelay) {
    if (switchState == LOW) { // If the switch is pressed
      if (currentTime - prevTime > maxCharDelay) { 
        morseCode += "-"; 
      } else {
        morseCode += "."; 
      }
    } else { // If the switch is released
      if (morseCode == ".-") { // If the Morse code is for 'A'
        Serial.print("A");
      } else if (morseCode == "-...") { // If the Morse code is for 'B'
        Serial.print("B");
      } else if (morseCode == "-.-.") { // If the Morse code is for 'C'
        Serial.print("C");
      } else if (morseCode == "-..") { // If the Morse code is for 'D'
        Serial.print("D");
      } else if (morseCode == ".") { // If the Morse code is for 'E'
        Serial.print("E");
      } else if (morseCode == "..-.") { // If the Morse code is for 'F'
        Serial.print("F");
      } else if (morseCode == "--.") { // If the Morse code is for 'G'
        Serial.print("G");
      } else if (morseCode == "....") { // If the Morse code is for 'H'
        Serial.print("H");
      } else if (morseCode == "..") { // If the Morse code is for 'I'
        Serial.print("I");
      } else if (morseCode == ".---") { // If the Morse code is for 'J'
        Serial.print("J");
      } else if (morseCode == "-.-") { // If the Morse code is for 'K'
        Serial.print("K");
      } else if (morseCode == ".-..") { // If the Morse code is for 'L'
        Serial.print("L");
      } else if (morseCode == "--") { // If the Morse code is for 'M'
        Serial.print("M");
      } else if (morseCode == "-.") { // If the Morse code is for 'N'
        Serial.print("N");
      } else if (morseCode == "---") { // If the Morse code is for 'O'
        Serial.print("O");
      } else if (morseCode == ".--.") { // If the Morse code is for 'P'
        Serial.print("P");
      } else if (morseCode == "--.-") { // If the Morse code is for 'Q'
        Serial.print("Q");
      } else if (morseCode == ".-.") { // If the Morse code is for 'R'
        Serial.print("R");
      } else if (morseCode == "...") { // If the Morse code is for 'S'
        Serial.print("S");
      } else if (morseCode == "-") { // If the Morse code is for 'T'
        Serial.print("T");
      } else if (morseCode == "..-") { // If the Morse code is for 'U'
        Serial.print("U");
      } else if (morseCode == "...-") { // If the Morse code is for 'V'
        Serial.print("V");
      } else if (morseCode == ".--") { // If the Morse code is for 'W'
        Serial.print("W");
      } else if (morseCode == "-..-") { // If the Morse code is for 'X'
        Serial.print("X");
      } else if (morseCode == "-.--") { // If the Morse code is for 'Y'
        Serial.print("Y");
      } else if (morseCode == "--..") { // If the Morse code is for 'Z'
        Serial.print("Z");
      } else if (morseCode == ".----") { // If the Morse code is for '1'
        Serial.print("1");
      } else if (morseCode == "..---") { // If the Morse code is for '2'
        Serial.print("2");
      } else if (morseCode == "...--") { // If the Morse code is for '3'
        Serial.print("3");
      } else if (morseCode == "....-") { // If the Morse code is for '4'
        Serial.print("4");
      } else if (morseCode == ".....") { // If the Morse code is for '5'
        Serial.print("5");
      } else if (morseCode == "-....") { // If the Morse code is for '6'
        Serial.print("6");
      } else if (morseCode == "--...") { // If the Morse code is for '7'
        Serial.print("7");
      } else if (morseCode == "---..") { // If the Morse code is for '8'
        Serial.print("8");
      } else if (morseCode == "----.") { // If the Morse code is for '9'
        Serial.print("9");
      } else if (morseCode == "-----") { // If the Morse code is for '0'
        Serial.print("0");
      }

      morseCode = ""; // Reset the Morse code string
    }
    prevTime = currentTime; // Update the previous time
  }

  prevSwitchState = switchState; // Update the previous switch state
}
