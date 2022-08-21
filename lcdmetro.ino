
/*
 * Author: John Song
 * Date: August 17th, 2022
 * Purpose: Write a program for the Arduino potentiometer controlled, LCD display metronome.
 */

#include <LiquidCrystal.h>

#define PIEZO   10  //piezo buzzer pin
#define LED     13  //LED pin
#define POT     A0  //analog pin for potentiometer
#define MIN_BPM 30  //minimum beats per minute
#define MAX_BPM 300 //maximum beats per minute
#define FREQ  700   //frequency of beep note in Hz

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;   //pin setup for interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  //creates a variable "lcd" of type LiquidCrystal
int sensorValue = 0;

void setup() {
  pinMode(PIEZO, OUTPUT);
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  lcd.begin(16, 2); //start the LCD display on top left corner
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(POT);    //sensor value determined by position of potentiometer 
  int bpm = map(sensorValue, 0, 1023, MIN_BPM, MAX_BPM);  //adjust the minimum and maximum values from 0 & 1023 to given min and max bpms
  lcd.setCursor(0, 0);
  lcd.print("BPM: ");
  lcd.print(bpm);     //display the bpm on the LCD screen
  
  tone(PIEZO, FREQ);     //plays buzzer sound
  digitalWrite(LED, HIGH);  //turns LED on
  delay(6000/bpm);            //the time between two consecutive beats is 60000 miliseconds divided by the beats per minute. The beep & light lasts for 10% of that time.
  noTone(PIEZO);            //silences buzzer
  digitalWrite(LED, LOW);  //turns LED off
  delay(54000/bpm);  //silence/no light for 90% of the time between two consecutive beats
}
