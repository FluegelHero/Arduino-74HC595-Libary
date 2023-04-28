/*
  Copyright: FluegelHero
  GitHub: https://github.com/FluegelHero

  Exaple to how you can use the Libary
  Here you can  see all Numbers on the 7-Segiment Display in a row
*/

#include "ShiftRegister.h" // include the Libary

SR_74HC595 SA(8, 9, 10); // Defining the Control Pins (Data, Shift, Launch)

void setup() {
  Serial.begin(9600); // start connection to Monitor
  SA.begin(2); // define the number of Register in a row
}

void loop() {
  SA.Clear(); // clear all from the 7-Segiment Display
  for(int Num=0; Num<10; Num++){
    SA.SetNumberAll(Num); // show the Number 
    delay(1000);
  }
  delay(2000);
}
