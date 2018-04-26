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
// Pin 11 --> Enable(E) of the LCD
// Pin 12 --> Register Select(RS) of the LCD
// Pin 6 --> V0 of the LCD
// Pin 10 --> Buzzer
// Pin 9--> Echo of Ultrasonic sensor
// Pin 8--> Trigger of Ultrasonic sensor


#include<string.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const int BUZZER=10;
const int PUSH_BUTTON=-1; //@TODO
const int Con=80; //Contrast
const int ECHO_PIN=9;
const int TRIG_PIN=8;

// MELODY BEGINS
#define NOTE_E7  2637
#define NOTE_G7  3136
#define NOTE_G6  1568 
#define NOTE_C7  2093
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
};
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
}; 
void sing() {
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      int noteDuration = 1000 / tempo[thisNote];
      buzz(BUZZER, melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      buzz(BUZZER, 0, noteDuration);
    }
}
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2;
  long numCycles = frequency * length / 1000;
  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin, LOW);
    delayMicroseconds(delayValue);
  }
}
// MELODY ENDS

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
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  displayCredits();
}
void loop()
{
  //init unit
  long duration, inches, cm;
  digitalWrite(BUZZER,LOW);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  if(cm<7)
  {
    digitalWrite(BUZZER,HIGH);
    //delay(100);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance = ");
  lcd.print(cm);
  lcd.print(" cm");
  //lcd.clear();
  delay(100);
  lcd.clear();
  
}
//DEFINITIONS OF CUSTOM FUNCTIONS

void displayCredits()
{
  transPrint("DISTANCE",0,0);
  transPrint("MEASURER",8,1);
  sing();
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
    lcd.print(*(str+i));
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
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
