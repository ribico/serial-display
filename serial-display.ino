/*
The Cuicuit:
 LCD RS pin to D2 (LCD4 -> Arduino D2)
 LCD Enable pin to D3 (LCD6 -> Arduino D3)
 LCD D4 pin to D5 (LCD11 -> Arduino D5)
 LCD D5 pin to D4 (LCD12 -> Arduino D4)
 LCD D6 pin to D7 (LCD13 -> Arduino D7)
 LCD D7 pin to D6 (LCD14 -> Arduino D6)
 LCD Vee tied to a pot to control brightness (LCD 3 -> A0 )
 LCD Vss and R/W tied to ground (LCD1 and LCD5 -> Arduino GND)
 LCD Vcc to +5V (LCD2 -> Arduino 5V)

 */

#define CONTRAST_PIN    A0
#define BTN1_PIN        1
#define BTN2_PIN        0
#define RS_LCD14_PIN    2
#define ENABLE_LCD6_PIN 3
#define D4_LCD11_PIN    5
#define D5_LCD12_PIN    4
#define D6_LCD13_PIN    7
#define D7_LCD14_PIN    6

int giBtn1_PreviousStatus = HIGH;
int giBtn2_PreviousStatus = HIGH;

#include <LiquidCrystal.h>
LiquidCrystal lcd (RS_LCD14_PIN, ENABLE_LCD6_PIN, D4_LCD11_PIN, D5_LCD12_PIN, D6_LCD13_PIN, D7_LCD14_PIN);

#include "LargeFont.h"



void setup()
{
  // initialize serial:
  Serial.begin(9600);

  lcdCustomSetup();
  lcd.begin(20, 2);

  pinMode(CONTRAST_PIN, OUTPUT);
  analogWrite(CONTRAST_PIN,0);

  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
}

void loop()
{
  String str1, str2, str3;
  

  while (Serial.available() > 0) 
  {
    str1 = Serial.readStringUntil('\n');
    str2 = Serial.readStringUntil('\n');
    str3 = Serial.readStringUntil('\n');

    printLCD_Strings(str1, str2);
    printLCD_BIG_Number(str3);
  }

  int iBtn1_CurrentStatus = digitalRead(BTN1_PIN);
  int iBtn2_CurrentStatus = digitalRead(BTN2_PIN);
  
  if (giBtn1_PreviousStatus == HIGH && iBtn1_CurrentStatus == LOW)
    Serial.println("BTN1");
  
  if (giBtn2_PreviousStatus == HIGH && iBtn2_CurrentStatus == LOW)
    Serial.println("BTN2");

  giBtn1_PreviousStatus = iBtn1_CurrentStatus;
  giBtn2_PreviousStatus = iBtn2_CurrentStatus;
}
