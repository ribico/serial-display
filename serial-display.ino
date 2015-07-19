/*
The Cuicuit:
 LCD RS pin to D12 (LCD4 -> Arduino D12)
 LCD Enable pin to D11 (LCD6 -> Arduino D11)
 LCD D4 pin to D5 (LCD11 -> Arduino D5)
 LCD D5 pin to D4 (LCD12 -> Arduino D4)
 LCD D6 pin to D3 (LCD13 -> Arduino D3)
 LCD D7 pin to D2 (LCD14 -> Arduino D2)
 LCD Vee tied to a pot to control brightness (LCD 3 -> ?? )
 LCD Vss and R/W tied to ground (LCD1 and LCD5 -> Arduino GND)
 LCD Vcc to +5V (LCD2 -> Arduino 5V)

 */

#include <LiquidCrystal.h>
// initialize the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include "LargeFont.h"

#define CONTRAST_PIN  A5


void setup() {
  // initialize serial:
  Serial.begin(9600);

  lcdCustomSetup();
  lcd.begin(20, 2);

  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite(CONTRAST_PIN,0);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
//    float value = Serial.parseFloat();
    int value = Serial.parseInt();

//    Serial.print("Parsed: ");
//    Serial.println(value);
    printVEL(value);
  }
}
