/*  Copyright (c) Rajdeep Roy Chowdhury 2018 <rrajdeeproychowdhury@gmail.com>
*   This piece of code is part of my ECE213 Project "Distance Measurer"
*   of Btech CSE, Sem II (2017-2018)
*   at Lovely Professional University, Punjab, India
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of 
*   this software and associated documentation files (the "Software"), to deal in the Software 
*   without restriction, including without limitation the rights to use, copy, modify, merge, 
*   publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
*   to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or 
*   substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
*   BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
*   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
*   DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

//     Instructions
// Make the following connections in the Arduino
// Pin 2 --> D7 of the LCD
// Pin 3 --> D6 of the LCD
// Pin 4 --> D5 of the LCD
// Pin 5 --> D4 of the LCD
// Pin 11 --> Enable(E)
// Pin 12 --> Register Select(RS)
//

#include<string.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int BUZZER=-1; //@TODO
const int PUSH_BUTTON=-1; //@TODO
const int Con=80; //Contrast

void displayCredits();
void showLoadingDots(int,int,int);
void transPrint(const char*,int,int);
void setup()
{
  Serial.begin(9600);
  analogWrite(6,Con);
  lcd.begin(16,2);
  pinMode(BUZZER,OUTPUT);
  pinMode(PUSH_BUTTON,OUTPUT);
  displayCredits();
  //Init Serial Monitor
  //Init LCD with dimensions
  //Init Pinmode of Buzzer
  //Init Pinmode of pushButton
  //displayCredits()
  //calibratingText();
}
void loop()
{
  //init unit
  
}
//DEFINITIONS OF CUSTOM FUNCTIONS

void displayCredits()
{
  transPrint("DISTANCE",0,0);
  transPrint("MEASURER",8,1);
  //sing();
  delay(1000);
  lcd.clear();
  transPrint("by RAJDEEP,",0,0);
  transPrint("VISHAL, VIPUL",2,1);
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibrating");
  showLoadingDots(4,11,0);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibrating");
  showLoadingDots(4,11,0);
}
void transPrint(const char* str,int col=0,int row=0){
  lcd.setCursor(col,row);
  int len=strlen(str);
  for(int i=0;i<len;i++)
  {
    lcd.print(str[i]);
    delay(100);
  }
}
void showLoadingDots(int n,int col=0,int row=0){
  lcd.setCursor(col,row);
  for(int i=0;i<n;i++)
  {
    lcd.print(".");
    delay(300);
  }
}
