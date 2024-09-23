#ifndef Motores_h
#define Motores_h

#include "Arduino.h"

class Motores {
  public:
    Motores(int AIN1, int AIN2, int STBY, int BIN1, int BIN2);
    void motorForward(int speedL, int speedR);
    void motorStop();
    void motorLeft(int speedL, int speedR);
    void motorRight(int speedL, int speedR);
    void motorBack(int speedL, int speedR);
  private:
    int _AIN1, _AIN2, _STBY, _BIN1, _BIN2;
};

#endif