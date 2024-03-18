// Morse-decodeerder
// (C) 2016 Demented hacker
#include <Arduino.h>
#include <Wire.h>
#include "PluggableUSBHID.h"
#include "USBKeyboard.h"
// #include <LiquidCrystal_I2C.h> // https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads ==> LiquidCrystal_V1.2.1.zip

// Verbind een tactile schakelaar (of seinsleutel) tussen pen 7 van de Arduino en GND.
// En sluit een buzzer aan tussen Arduino pen 8 en GND.
// Dan kun je met de schakelaar seinen. Bekijk de gedecodeerde Morse-code in de serial monitor.

#define SWITCH 21  // Seinsleutel van pen 7 naar GND
#define BUZZER 8   // Buzzer van pen 8 naar GND
#define LED_PIN 25

// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

USBKeyboard Keyboard;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  // lcd.begin(20, 4);
  // lcd.backlight();     
}

float SpaceDuration = 200.0;
boolean PrevS = false;
long tStartPress, tStartPause;
boolean S;
String symbol = "";
void loop() {

  S = !digitalRead(SWITCH);

  if (S) {
    if (S != PrevS) {
      tStartPress = millis();
      DecoderPause(tStartPause);
    }
    //Serial.println("Button");
    digitalWrite(BUZZER, HIGH);
  }
  else {
    if (S != PrevS) {
      tStartPause = millis();
      Decoder(tStartPress);
    }
    digitalWrite(BUZZER, LOW);
  }

  if (abs(millis() - tStartPause) > SpaceDuration * 10) {
    DecoderPause(tStartPause);
  }

  PrevS = S;
}

void Decoder(long starttijd) {
  char teken = '?';
  long tijd = abs(millis() - starttijd); // Tijdsduur van het geseinde teken (een punt of een streep)
  float PuntDuur = SpaceDuration / 3.0;

  if (tijd <= 2) return; // Denderonderdrukking

  if (tijd <= PuntDuur) teken = '.';
  else if (tijd > SpaceDuration) teken = '-';
  else if ((tijd > (SpaceDuration + PuntDuur) / 1.9) && tijd <= SpaceDuration) teken = '-';
  else teken = '.';

  if (teken == '-') {
    if (tijd > SpaceDuration) SpaceDuration++;
    if (tijd < SpaceDuration) SpaceDuration--;
  }
  else if (teken == '.') {
    if (tijd > SpaceDuration / 3.0) SpaceDuration++;
    if (tijd < SpaceDuration / 3.0) SpaceDuration--;
  }
  symbol += teken;
  //Serial.println(teken);
}

void DecoderPause(long starttijd) {
  if (symbol == "") return;

  char teken = '?';
  long tijd = abs(millis() - starttijd);
  if (tijd > SpaceDuration - SpaceDuration / 40) {
    DecodeSymbol();
    //Serial.print();
  }
  if (tijd > SpaceDuration * 2) {
    DecodeSymbol();
    Print_local(" "); 
    Serial.print(" ");
  }
  //else DecodeSymbol();
  //Serial.println(teken);
}

void DecodeSymbol() {
  static String letters[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
  };
  int i = 0;
  while (letters[i] != "E") {
    if (letters[i] == symbol) {
      Print_local((char)('A' + i));
      Serial.print((char)('A' + i));
      break;
    }
    i++;
  }
  if (letters[i] == "E") {
    Print_local(symbol);
    Serial.print(symbol);
  }
  symbol = "";
}

void Print_local(String &s) {
  for (int i = 0; i < s.length(); i++) {
    // Keyboard.printf(&s[i]);
    Keyboard.putc(s[i]);
    // Keyboard.write(&s[i]);
  }
}
void Print_local(char s) {
    // Keyboard.printf(&s);
    Keyboard.putc(s);
    // Keyboard.write(&s);
}
void Print_local(char *s) {
  for (int i = 0; i < strlen(s); i++) {
    // Keyboard.printf(&s[i]);
    Keyboard.putc(s[i]);
    // Keyboard.write(&s[i]);
  }
}