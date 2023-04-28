/*
  Copyright: FluegelHero
  GitHub: https://github.com/FluegelHero

  This is an Exaple code for how to use the Libary
  with LEDs
  
  last update of the Libary: 03.07.2022

*/

#include "ShiftRegister.h" // include the Libary

SR_74HC595 SA(8, 9, 10); // Defining the Control Pins (Data, Shift, Launch)

const int Data[1][8] = {{0,1,0,1,0,1,0,1}};

void setup() {
  SA.begin(1); // define the Number of Shift Register in a row
  SA.Clear();  // set all pins to 0
  SA.Test(100); // Tests if all LEDs and pins are working, and if everything is connected correctly
}

void loop() {
  SA.ShowCustom(Data); // Sets all LEDs according to the data from the array
  delay(1000); // wait 1000ms
  SA.ShowCustom(Data, true); // Sets all LEDs according to the data from the array but invertet
  delay(1000); // wait 1000ms
}
