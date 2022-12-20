/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-keypad
*/
//Inkluderar bibliotek
#include <Keypad.h>
#include "U8glib.h"
#include <Servo.h>

//Skapar instans för oled
U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);

//Deklarerar antal rader/kolumner för keypad
const int ROW_NUM = 4;     
const int COLUMN_NUM = 3;  
//Deklarerar vilken pin som servo är ansluten till
int servoPin = 13;

Servo Servo1;

//Deklarerar vad knapparna ska ha för output
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

//Deklarerar vilka pinnar som rader/kolumner är anslutna till
byte pin_rows[ROW_NUM] = { 2, 3, 4, 5 };     //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = { 8, 9, 10 };  //connect to the column pinouts of the keypad

//Skapar instans för keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

//Bestämmer kod
const String password = "6557";  // change your password here
String input_password;

void setup() {
  Serial.begin(9600);
  input_password.reserve(32);  // maximum input characters is 33, change if needed
  Servo1.attach(servoPin);
  Servo1.write(0);
}

void loop() {
  char key = keypad.getKey();
  oled.firstPage();
  do {
    draw();
  } while (oled.nextPage());

  if (key) {
    Serial.println(key);



    if (key == '*') {
      input_password = "";  // clear input password

    } else if (key == '#') {
      if (password == input_password) {
        Serial.println("password is correct");
        correct();

      } else {
        Serial.println("password is incorrect, try again");
        incorrect();
      }

      input_password = "";  // clear input password
    } else {
      input_password += key;  // append new character to input password string
    }
  }
}



//Funktion för om kod är rätt. Skriver "correct" på skärmen och väntar i tre sek
//Argument: Inga
//Output: Inga
void correct(void) {

  oled.setFont(u8g_font_helvB10);
  oled.firstPage();
  do {

    // Print s  trings
    oled.drawStr(0, 13, "Correct");
  } while (oled.nextPage());
  delay(3000);
}

//Funktion för om koden är inkorrekt. Skriver "Incorrect" på skärmen och rör servoarmen för att dela ut stöten.
//Argument: Inga
//Output: Inga
void incorrect(void) {

  oled.setFont(u8g_font_helvB10);
  oled.firstPage();
  do {

    
    oled.drawStr(0, 13, "Incorrect");
  } while (oled.nextPage());
  Servo1.write(90);

  delay(3000);

  Servo1.write(0);
 
}
//Funktion för att skriva på skärmen
//Argument: Inga
//Output: Inga
void draw(void) {
  // Set font to Helvetica size 10
  oled.setFont(u8g_font_helvB10);
  oled.firstPage();
  do {

    // Print s  trings
    oled.drawStr(0, 13, String(input_password).c_str());
  } while (oled.nextPage());
}
