#include "Sensores.h"


Sensores::Sensores(int DistR, int DistRM, int DistLM, int DistL)
: _DistR(DistR), _DistRM(DistRM), _DistLM(DistLM), _DistL(DistL){
  pinMode(_DistR, INPUT); 
  pinMode(_DistRM, INPUT); 
  pinMode(_DistLM, INPUT); 
  pinMode(_DistL, INPUT);
}

int Sensores::readSensors(){
  return (digitalRead(_DistR) << 3) | (digitalRead(_DistRM) << 2) | (digitalRead(_DistLM) << 1) | digitalRead(_DistL);

}


int Sensores::performAction(int valor) {
  switch(valor) {
    case 0b0000: return 1; //All Detect
    case 0b1001: return 1; //Front Detect
    case 0b0110: return 1; //Front Detect
    case 0b0001: return 2; //Semi All Detect Right
    case 0b0011: return 2; //Rigt Detecting
    case 0b0101: return 2; //Rigt Detecting
    case 0b0010: return 2; //Rigt Detecting
    case 0b1011: return 1; //Right Front
    case 0b0111: return 3; //Only Right
    case 0b1000: return 4; //Semi All Detect Left
    case 0b1100: return 4; //Left Detecting
    case 0b1010: return 4; //Left Detecting
    case 0b0100: return 4; //Left Detectin
    case 0b1101: return 1; //Left Front
    case 0b1110: return 5; //Only Left
    case 0b1111: return 6; //Nothing Detect
    default:     return 6;
  }
}