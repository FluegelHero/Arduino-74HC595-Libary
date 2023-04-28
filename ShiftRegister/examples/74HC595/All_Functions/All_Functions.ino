/*
  Copyright: FluegelHero
  GitHub: https://github.com/FluegelHero

  This is an overview of all the functions from the
  Shift register libary for the shift regitser 74HC595
  
  last update of the Libary: 03.07.2022

*/

#include "ShiftRegister.h" // include the Libary

SR_74HC595 SA(8, 9, 10); // Defining the Control Pins (Data, Shift, Launch)

void setup() {
  SA.begin(1); // define the Number of Shift Register in a row
  
  //general methods:
  SA.Clear(); //switch all pins off
  SA.Test(); // all pins are switched on slowly one after the other (you can set your own delay, default=500ms)

  // LED methods:
  SA.TurnRandomOn(); // randomly sets each individual pin on or off
  int TestData[1][8] = {{1,0,1,0,1,0,1,0}};
  SA.ShowCustom(TestData);  // need an array in which an 8-element long array for each segment, loads each pin status from array
  SA.ShowCustom(TestData, true); //  1 and 0 are swapped by "true" after the array
  SA.AllOn(); // shwitch all pins on
  
  // 7-Segiment methos:
  SA.SetNumber(1, 0); // select the Number to show between 0-9 and the position of the array (Number, Position)
  SA.SetNumbers({1}); // requires an array containing the digits to be displayed from 0-9
  SA.SetNumberAll(2); // shows the specified number in all 7-segment displays
  
}

void loop() {
  // Nothing Here
}
