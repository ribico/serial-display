/*
The Cuicuit:
 LCD RS pin to D2 (LCD4 -> Arduino D1)
 LCD Enable pin to D3 (LCD6 -> Arduino D3)
 LCD D4 pin to D5 (LCD11 -> Arduino D5)
 LCD D5 pin to D4 (LCD12 -> Arduino D4)
 LCD D6 pin to D7 (LCD13 -> Arduino D7)
 LCD D7 pin to D6 (LCD14 -> Arduino D6)
 LCD Vee tied to a pot to control brightness (LCD 3 -> Arduino GND )
 LCD Vss and R/W tied to ground (LCD1 and LCD5 -> Arduino GND)
 LCD Vcc to +5V (LCD2 -> Arduino 5V)

 */

#define BTN1_PIN        A2
#define BTN2_PIN        A3
#define BTN3_PIN        A4
#define BTN4_PIN        A1  // CONTRAST CONTROL BUTTON

#define RS_LCD14_PIN    0
#define ENABLE_LCD6_PIN 1
#define D4_LCD11_PIN    5
#define D5_LCD12_PIN    4
#define D6_LCD13_PIN    7
#define D7_LCD14_PIN    6
#define CONTRAST_PIN    3


int giBtn1_PreviousStatus = HIGH;
int giBtn2_PreviousStatus = HIGH;
int giBtn3_PreviousStatus = HIGH;
int giBtn4_PreviousStatus = HIGH;
int giContrastPwm = 200;

#include <LiquidCrystal.h>
LiquidCrystal lcd (RS_LCD14_PIN, ENABLE_LCD6_PIN, D4_LCD11_PIN, D5_LCD12_PIN, D6_LCD13_PIN, D7_LCD14_PIN);

#include "LargeFont.h"

#define DISP_COL_COUNT    20
#define DISP_ROW_COUNT    4
#define ROW1              0
#define ROW2              1
#define ROW3              2
#define ROW4              3
#define LEFT_STR_OFFSET   0
#define RIGHT_STR_OFFSET  10


void setup()
{
  // initialize serial:
  Serial.begin(9600);

  lcdCustomSetup();
  lcd.begin(DISP_COL_COUNT, DISP_ROW_COUNT);

  pinMode(BTN1_PIN, INPUT);
  pinMode(BTN2_PIN, INPUT);
}

String str1 = "str1";
String str2 = "str2";
String str_num = "123.4";
String str3 = "str3";
String str3a = "str3a";
String str4 = "str4";
String str4a = "str4a";

void loop()
{
  int iBtn1_CurrentStatus = digitalRead(BTN1_PIN);
  int iBtn2_CurrentStatus = digitalRead(BTN2_PIN);
  int iBtn3_CurrentStatus = digitalRead(BTN3_PIN);
  int iBtn4_CurrentStatus = digitalRead(BTN4_PIN);

  if (giBtn1_PreviousStatus == 1 && iBtn1_CurrentStatus == 0)
  {
    Serial.println("BTN1");
    str4 = "BTN1 PRESSED";//Serial.readStringUntil('\n');
    str4a = "";
  }

  if (giBtn2_PreviousStatus == 1 && iBtn2_CurrentStatus == 0)
  {
      Serial.println("BTN2");
      str4 = "BTN2 PRESSED";//Serial.readStringUntil('\n');
      str4a = "";
  }

  if (giBtn3_PreviousStatus == 1 && iBtn3_CurrentStatus == 0)
  {
      Serial.println("BTN3");
      str4 = "BTN3 PRESSED";//Serial.readStringUntil('\n');
      str4a = "";
  }

  if (giBtn4_PreviousStatus == 1 && iBtn4_CurrentStatus == 0)
  {
    Serial.println("BTN4");

    if (giContrastPwm < 250)
      giContrastPwm += 25;
    else
      giContrastPwm = 25;

      analogWrite(CONTRAST_PIN, giContrastPwm);

      str4 = "Contrast :";//Serial.readStringUntil('\n');
      str4a = String((int)(giContrastPwm/255.0*100.0));
  }


  giBtn1_PreviousStatus = iBtn1_CurrentStatus;
  giBtn2_PreviousStatus = iBtn2_CurrentStatus;
  giBtn3_PreviousStatus = iBtn3_CurrentStatus;
  giBtn4_PreviousStatus = iBtn4_CurrentStatus;

  if( Serial.available() > 0 ) // some string to be read
  {
    str1 = Serial.readStringUntil('\n');
    str2 = Serial.readStringUntil('\n');
    str_num = Serial.readStringUntil('\n');
    str3 = Serial.readStringUntil('\n');
    str3a = Serial.readStringUntil('\n');
    str4 = Serial.readStringUntil('\n');
    str4a = Serial.readStringUntil('\n');
  }

  // PRINT ROW1
  printLCD_String(LEFT_STR_OFFSET, ROW1, str1);
  refreshLCD_EmptyDigits(str1.length(), BIG_NUM_POS, ROW1);

  // PRINT ROW2
  printLCD_String(LEFT_STR_OFFSET, ROW2, str2);
  refreshLCD_EmptyDigits(str2.length(), BIG_NUM_POS, ROW2);

  // PRINT BIG NUMBER
  printLCD_BIG_Number(str_num);

  // PRINT ROW3
  printLCD_String(LEFT_STR_OFFSET, ROW3, str3);
  if( str3a.length() > 0 )
  {
    refreshLCD_EmptyDigits(str3.length(), RIGHT_STR_OFFSET, ROW3);
    printLCD_String(RIGHT_STR_OFFSET, ROW3, str3a);
    refreshLCD_EmptyDigits(str3a.length()+RIGHT_STR_OFFSET, DISP_COL_COUNT, ROW3);
  }
  else
  {
    refreshLCD_EmptyDigits(str3.length(), DISP_COL_COUNT, ROW3);
  }

  // PRINT ROW4
  printLCD_String(LEFT_STR_OFFSET, ROW4, str4);
  if( str4a.length() > 0 )
  {
    refreshLCD_EmptyDigits(str4.length(), RIGHT_STR_OFFSET, ROW4);
    printLCD_String(RIGHT_STR_OFFSET, ROW4, str4a);
    refreshLCD_EmptyDigits(str4a.length()+RIGHT_STR_OFFSET, DISP_COL_COUNT, ROW4);
  }
  else
  {
    refreshLCD_EmptyDigits(str4.length(), DISP_COL_COUNT, ROW4);
  }

}


void printLCD_String(short col, short row, String str)
{
  lcd.setCursor(col, row);
  lcd.print(str);
}

void refreshLCD_EmptyDigits(short col_start, short col_end, short row)
{
  for(int i=col_start; i<col_end; i++)
  {
    lcd.setCursor(i,row);
    lcd.print(' ');
  }
}
