#include "Motores.h"
#include "esp32-hal-ledc.h"

Motores::Motores(int AIN1, int AIN2, int STBY, int BIN1, int BIN2)
: _AIN1(AIN1), _AIN2(AIN2), _STBY(STBY), _BIN1(BIN1), _BIN2(BIN2) {
  pinMode(_AIN1, OUTPUT);
  pinMode(_AIN2, OUTPUT);
  pinMode(_STBY, OUTPUT);
  pinMode(_BIN1, OUTPUT);
  pinMode(_BIN2, OUTPUT);

  // Configurando los canales PWM
  ledcSetup(0, 5000, 8); // Canal 0
  ledcAttachPin(_AIN1, 0);
  ledcSetup(1, 5000, 8); // Canal 1
  ledcAttachPin(_AIN2, 1);
  ledcSetup(2, 5000, 8); // Canal 2
  ledcAttachPin(_BIN1, 2);
  ledcSetup(3, 5000, 8); // Canal 3
  ledcAttachPin(_BIN2, 3);
}

void Motores::motorForward(int speedL, int speedR) {
  digitalWrite(_STBY, HIGH);
  ledcWrite(0, speedL); // AIN1
  ledcWrite(1, 0);      // AIN2
  ledcWrite(2, speedR); // BIN1
  ledcWrite(3, 0);      // BIN2
}

void Motores::motorStop() {
  digitalWrite(_STBY, HIGH);
  ledcWrite(0, 255); // AIN1
  ledcWrite(1, 255); // AIN2
  ledcWrite(2, 255); // BIN1
  ledcWrite(3, 255); // BIN2
}

void Motores::motorLeft(int speedL, int speedR) {
  digitalWrite(_STBY, HIGH);
  ledcWrite(0, speedL); // AIN1
  ledcWrite(1, 0);      // AIN2
  ledcWrite(2, 0);      // BIN1
  ledcWrite(3, speedR); // BIN2
}

void Motores::motorRight(int speedL, int speedR) {
  digitalWrite(_STBY, HIGH);
  ledcWrite(0, 0);      // AIN1
  ledcWrite(1, speedL); // AIN2
  ledcWrite(2, speedR); // BIN1
  ledcWrite(3, 0);      // BIN2
}

void Motores::motorBack(int speedL, int speedR) {
  digitalWrite(_STBY, HIGH);
  ledcWrite(0, 0); // AIN1
  ledcWrite(1, speedL);      // AIN2
  ledcWrite(2, 0); // BIN1
  ledcWrite(3, speedR);      // BIN2
}

