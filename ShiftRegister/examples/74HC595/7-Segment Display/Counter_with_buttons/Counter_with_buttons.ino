/*
  Copyright: FluegelHero
  GitHub: https://github.com/FluegelHero

  This is an Exaple code for an counter with buttons
  
  last update of the Libary: 03.07.2022

*/
#include "ShiftRegister.h" // include the Libary

SR_74HC595 SA(8, 9, 10); // Defining the Control Pins (Data, Shift, Launch)

int Data[2] = {0, 0};
const int TasterUP = 6; // defer the pin for the button to increase
const int TasterDOWN = 7; // defer the pin for the button to decrease

void setup() {
  Serial.begin(9600);
  SA.begin(2, true); // define the Number of Shift Register in a row
  SA.SetNumbers(Data); // displays the number 0 on both displays
  pinMode(TasterUP, INPUT_PULLUP);
  pinMode(TasterDOWN, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(TasterUP)) {
    while (!digitalRead(TasterUP));
    Data[1]++;
    if (Data[0] >= 9 && Data[1] >= 10) {
      Data[0] = 0;
      Data[1] = 0;
    }
    if (Data[1] > 9) {
      Data[0]++;
      Data[1] = 0;
    }
    SA.SetNumbers(Data); // displays the numbers from the array on the displays
  }

  if (!digitalRead(TasterDOWN)) {
    while (!digitalRead(TasterDOWN));
    Data[1]--;
    if (Data[0] == 0 && Data[1] < 0) {
      Data[0] = 9;
      Data[1] = 9;
    }
    if (Data[1] < 0) {
      Data[0]--;
      Data[1] = 9;
    }
    SA.SetNumbers(Data); // displays the numbers from the array on the displays
  }
}
