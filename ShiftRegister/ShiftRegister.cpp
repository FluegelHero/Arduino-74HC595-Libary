#include "ShiftRegister.h"

SR_74HC595::SR_74HC595(int DATA_PIN, int SHIFT_PIN, int LAUNCH_PIN) {
  // save Pins in private Values
  _DATA_PIN = DATA_PIN;
  _SHIFT_PIN = SHIFT_PIN;
  _LAUNCH_PIN = LAUNCH_PIN;
  // set  Pinmodes for The Pins
  pinMode(_DATA_PIN, OUTPUT);
  pinMode(_SHIFT_PIN, OUTPUT);
  pinMode(_LAUNCH_PIN, OUTPUT);
  // set all Pins off
  digitalWrite(_DATA_PIN, LOW);
  digitalWrite(_SHIFT_PIN, LOW);
  digitalWrite(_LAUNCH_PIN, LOW);
}
void SR_74HC595::begin(int NumberShiftRegister, bool ShowOutput = false) {
  _NumberShiftRegister = NumberShiftRegister;
  _ShowOutput = ShowOutput;
  if (_ShowOutput) {
    Serial.println("74HC595 Ready....");
    Serial.println("Parameter to Connnect:");
    Serial.print("  - Data pin:   ");
    Serial.println(_DATA_PIN);
    Serial.print("  - Shift pin:  ");
    Serial.println(_SHIFT_PIN);
    Serial.print("  - Launch pin: ");
    Serial.println(_LAUNCH_PIN);
    Serial.println("");
  }
}
void SR_74HC595::Clear() {
  // switch all Pins off
  int MaxLeds = _NumberShiftRegister * 8;
  digitalWrite(_LAUNCH_PIN, LOW);
  for (int Pins = 0; Pins < MaxLeds; Pins++) {
    if (_ShowOutput) {
      Serial.print("Clear Pin: ");
      Serial.print(Pins);
      Serial.print(" | ");
    }
    _Render(LOW);
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
void SR_74HC595::Test(int WaitTime = 500) {
  // switches on all pins one after the other
  int MaxLeds = _NumberShiftRegister * 9;
  for (int Pins = 0; Pins < MaxLeds; Pins++) {
    if (_ShowOutput) {
      Serial.print("testing Pin: ");
      Serial.print(Pins);
      Serial.print(" >> ");
    }
    Clear();
    digitalWrite(_LAUNCH_PIN, LOW);
    for (int Pins_On = 0; Pins_On < Pins; Pins_On++) {
      _Render(HIGH);
    }
    digitalWrite(_LAUNCH_PIN, HIGH);
    delay(WaitTime);
  }
}
void SR_74HC595::TurnRandomOn() {
  // Randomize if the Pins are on or off
  digitalWrite(_LAUNCH_PIN, LOW);
  for (int Register = 0; Register < _NumberShiftRegister; Register++) {
    for (int Pin = 0; Pin < 8; Pin++) {
      digitalWrite(_SHIFT_PIN , LOW);
      int RandomNum = random(0, 2);
      if (RandomNum == 0) {
        digitalWrite(_DATA_PIN, LOW);
      } else {
        digitalWrite(_DATA_PIN, HIGH);
      }
      digitalWrite(_SHIFT_PIN, HIGH);
    }
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
void SR_74HC595::ShowCustom(int DataArry[][8], bool InvertStats = false) {
  if (sizeof(DataArry) == 0) {
    if (_ShowOutput) {
      Serial.println("Array for \"ShowCustom\" is to short");
    }
    return;
  }
  digitalWrite(_LAUNCH_PIN, LOW);
  for (int Register = 0; Register < sizeof(DataArry); Register++) {
    _RenderByte(DataArry[Register], InvertStats);
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
void SR_74HC595::AllOn() {
  //Turn all Pins on
  int MaxLeds = _NumberShiftRegister * 9;
  digitalWrite(_LAUNCH_PIN, LOW);
  for (int Pins = 0; Pins < MaxLeds; Pins++) {
    if (_ShowOutput) {
      Serial.print("Pins on: ");
      Serial.print(Pins);
      Serial.print(" ,");
    }
    _Render(HIGH);
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
void SR_74HC595::SetNumber(int Number, int Position) {
  // Shows the Number from 0-9 at the selectet Posoition
  digitalWrite(_LAUNCH_PIN, LOW);
  if (_ShowOutput) {
    Serial.print("SetNumber >> Number: ");
    Serial.print(Number);
    Serial.print(" at Position: ");
    Serial.println(Position);
  }
  for (int Register = 0; Register < _NumberShiftRegister; Register++) {
    if (Register == Position) {
      _RenderByte(NumberData[Number]);
      _SavePinStat(Register, Number);
    } else {
      _RenderByte(NumberData[_GetPinStat(Register)]);
    }
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
void SR_74HC595::SetNumbers(int Numbers[]) {
  //Shows all the Numbers that was given
  digitalWrite(_LAUNCH_PIN, LOW);
  for (int Number = 0; Number < sizeof(Numbers); Number++) {
    if (_ShowOutput) {
      Serial.print("SetNumbers >> Number: ");
      Serial.print(Numbers[Number]);
      Serial.print(" at Position: ");
      Serial.println(Number);
    }
    _RenderByte(NumberData[Numbers[Number]]);
    _SavePinStat(Number, Numbers[Number]);
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
void SR_74HC595::SetNumberAll(int Number) {
  if (_ShowOutput) {
    Serial.print("SetNumberAll >> Number: ");
    Serial.print(Number);
    Serial.println(" at all");
  }
  digitalWrite(_LAUNCH_PIN, LOW);
  for (int Register = 0; Register < _NumberShiftRegister; Register++) {
    _RenderByte(NumberData[Number]);
    _SavePinStat(Register, Number);
  }
  digitalWrite(_LAUNCH_PIN, HIGH);
}
