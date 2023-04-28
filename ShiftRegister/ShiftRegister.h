#ifndef Ultrasonic_Sensor_lib_h
#define Ultrasonic_Sensor_lib_h
#include "Arduino.h"

class SR_74HC595{
  public:
    // init class with pins
    SR_74HC595(int DATA_PIN, int SHIFT_PIN, int LAUNCH_PIN);
    void begin(int NumberShiftRegister, bool ShowOutput = false);
    
    void Clear();
    void Test(int WaitTime = 500);    
    void TurnRandomOn();
    void ShowCustom(int DataArry[][8], bool InvertStats=false);
    void AllOn();
    void SetNumber(int Number, int Position);
    void SetNumbers(int Numbers[]);
    void SetNumberAll(int Number);
  
  private:
    const char* name;
    bool _ShowOutput;
    int _DATA_PIN;
    int _SHIFT_PIN;
    int _LAUNCH_PIN;
    int _NumberShiftRegister;
    const int NumberData[10][8] = {
    // a b c d e f g p  
      {1,1,1,1,1,1,0,0},// 0
      {0,1,1,0,0,0,0,0},// 1
      {1,1,0,1,1,0,1,1},// 2
      {1,1,1,1,0,0,1,1},// 3
      {0,1,1,0,0,1,1,1},// 4
      {1,0,1,1,0,1,1,1},// 5
      {1,0,1,1,1,1,1,1},// 6
      {1,1,1,0,0,0,0,1},// 7
      {1,1,1,1,1,1,1,1},// 8
      {1,1,1,1,0,1,1,1} // 9
    };
    int _LastPinStats[];

    void _Render(bool STATUS_DATA){
        digitalWrite(_SHIFT_PIN, LOW);
        digitalWrite(_DATA_PIN, STATUS_DATA);
        digitalWrite(_SHIFT_PIN, HIGH);
    }
    void _RenderByte(int DATA_ARRY[],  bool  InvertStats=false){
      if(sizeof(DATA_ARRY)==0){
        return;  
      }else{
        for(int Bit=0; Bit<8; Bit++){
          if(!InvertStats){
            if(DATA_ARRY[Bit] == 0){
              _Render(LOW);
            }else{
              _Render(HIGH);
            }
          }else{
            if(DATA_ARRY[Bit] == 0){
              _Render(HIGH);
            }else{
              _Render(LOW);
            }
          }
        }
      }
    }
    void _SavePinStat(int Position, int Number){
      _LastPinStats[Position] = Number;
    }
    int _GetPinStat(int Position){
      int Number = _LastPinStats[Position];
      return Number;
    }
};
  
#endif
