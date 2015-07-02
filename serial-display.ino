/*
The Cuicuit:
 LCD RS pin to D12
 LCD Enable pin to D11
 LCD D4 pin to D5
 LCD D5 pin to D4
 LCD D6 pin to D3
 LCD D7 pin to D2
 LCD Vee tied to a pot to control brightness
 LCD Vss and R/W tied to ground
 LCD Vcc to +5V

 */
 
#include <LiquidCrystal.h>
// initialize the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include "LargeFont.h"

void setup() {
  // initialize serial:
  Serial.begin(9600);

  // sets the LCD's rows and colums:
  lcd.begin(16, 2);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int value = Serial.parseInt();
//    Serial.print("Parsed: ");
//    Serial.println(value);
//    printVEL(value);
  }
}
