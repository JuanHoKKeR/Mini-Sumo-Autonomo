#ifndef Sensores_h
#define Sensores_h

#include "Arduino.h"

class Sensores {
public:
  Sensores(int DistR, int DistRM, int DistLM, int DistL);
  int readSensors();
  int performAction(int valor);

private:
  int _DistR, _DistRM, _DistLM, _DistL;
};

#endif