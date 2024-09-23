#include "Motores.h"
#include "Sensores.h"
#include <esp32-hal-timer.h>
#include <esp_system.h>


const int AIN2 = 5, AIN1 = 4, STBY = 18, BIN1 = 19, BIN2 = 23; 
const int LineR = 13, LineL = 12;
const int DistR = 33, DistRM = 32, DistLM = 26, DistL = 25;
const int Dip1 = 35, Dip2 = 34;
const int LedR = 14, LedL = 27;
const int star = 15, stop = 2;

Motores motors(AIN1, AIN2, STBY, BIN1, BIN2);
Sensores sensores(DistR, DistRM, DistLM, DistL);
hw_timer_t *timer = NULL;

//volatile bool estado[4] = {0, 0, 0, 0};
volatile int lastAction = 0;
volatile int lineState = 0;
volatile int lecture = 0;
unsigned long startTime = 0;


void TimeDelay(int time){ //Delay con posibilidad de Interrupcion
  unsigned long startTime = millis(); 
  while(true){
    if (millis() - startTime >= time) {
      break; // Salir del bucle si el tiempo ha expirado
    }
    // Verifica si la condición de interrupción se ha cumplido
  if (lineState != 0 || (lastAction>=1 && lastAction<=5)) {
    //if ((lastAction>=1 && lastAction<=5)) { /////////////////////////////////////////////////Cambiar
      break; // Salir del bucle si la Linea se detecta o Algun objetivo se detecta
    }
  }
}

void TimeDelay_Line(int time,int line){ //Delay con posibilidad de Interrupcion
  unsigned long startTime = millis(); 
  while(true){
    if (millis() - startTime >= time) {
      break; // Salir del bucle si el tiempo ha expirado
    }
    // Verifica si la condición de interrupción se ha cumplido
    if(line =! lecture && lecture>6 && (lastAction>=1 && lastAction<=5)){
    // if ((lastAction>=1 && lastAction<=5)) {
      break; // Salir del bucle si la Linea se detecta o Algun objetivo se detecta
    }
  }
}



void MoveSens(int estrategia){ //Movimientos Fijos del Robot acorde a los sensores de line y de distancia
  int accion = (lineState == 0) ? 6 : 6 + lineState; ///Cambiar 6 por lastaaction
  //int  accion = lastAction; //////////////////////////////////////////// cambiar
  //////////////////////////
  //1: FRONT
  //2: FORWARD RIGHT
  //3: RIGHT
  //4: FORWARD LEFT
  //5: LEFT
  //6 :NOTHING and No LINE
  //7: LINE LEFT
  //8: LINE RIGHT
  //9: LINE FRONT
  switch(accion) {
  case 1: motors.motorForward(255,255);break;//TimeDelay(100);motors.motorForward(255,255); break;
  case 2: motors.motorRight(200,200); break;//motors.motorForward(200,255); break;
  case 3: motors.motorRight(200,200); break;
  case 4: motors.motorLeft(200,200); break;//motors.motorForward(255,200); break;
  case 5: motors.motorLeft(200,200); break;
  case 6: Seleccion(estrategia); break;
  case 7: motors.motorBack(255, 255);TimeDelay_Line(100,7);motors.motorRight(200,200);TimeDelay_Line(90,7);break;
  case 8: motors.motorBack(255, 255);TimeDelay_Line(100,8);motors.motorLeft(200,200);TimeDelay_Line(90,8); break;
  case 9: motors.motorStop();break;//motors.motorBack(255, 255);TimeDelay_Line(200,9);motors.motorRight(255,255);TimeDelay_Line(250,9); break;
  default: motors.motorStop(); break;
  }

}

void IRAM_ATTR onTimer() { //Timer de los Sensores de Distancia
  volatile int valor = sensores.readSensors();//Lee los Sensores y lo guarda en un valor entero
  lastAction = sensores.performAction(valor); //Modifica la variable global segun el estado de los sensores
  lecture = (lineState == 0) ? lastAction : 6 + lineState;
}

// void IRAM_ATTR resetDevice() {
//     esp_restart();  // Función para reiniciar el ESP32
// }

void lineSensorInterruption() { //Interrupcion de los sensores de Linea
  //motors.motorStop();
  int MSB = digitalRead(LineR); //Lectura de los Sensores
  int LSB = digitalRead(LineL);
  int OUT = (MSB << 1) | LSB; //Define los estados de los sensores como un int
  lineState = OUT; //Asignacion de la variable Global
}

void setup() {
  Serial.begin(115200);
  Serial.println("Inicio Programa");
  pinMode(star, INPUT);
  pinMode(stop, INPUT);
  //attachInterrupt(digitalPinToInterrupt(stop), resetDevice, CHANGE); 

  pinMode(Dip1, INPUT);
  pinMode(Dip2, INPUT);

  timer = timerBegin(0, 80, true); // Timer 0, prescaler 80, countUp true
  timerAttachInterrupt(timer, &onTimer, true); // Attach onTimer function
  timerAlarmWrite(timer, 1000, true); // Set timer for 50,000 microseconds (50ms)
  timerAlarmEnable(timer); // Enable timer
  pinMode(LineR, INPUT_PULLUP); // Configura el pin como entrada con resistencia pull-up
  pinMode(LineL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LineR), lineSensorInterruption, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LineL), lineSensorInterruption, CHANGE); 

}

void loop() {
  int estrategia = (digitalRead(Dip1)<<1) | digitalRead(Dip2);
  bool inicio = digitalRead(star);
  //bool final = digitalRead(stop);
  //
  // while(inicio){
  //   // Serial.println("Entro en el programa");
  //   // Serial.print("Estrategia #");Serial.println(estrategia);
  //   Serial.println(lecture);
  MoveSens(estrategia);
  //   motors.motorForward(100,100);
  //   if(!digitalRead(star)) motors.motorStop(); break;

  // }
  // if (lastAction != 0) {
  // sensores.readSensors(estado);
  // volatile int valor = sensores.getState(estado);
  //MoveSens(lastAction);
  //Serial.println(sensores.performAction(valor)); // Mueve la impresión al loop principal
  //   lastAction = 0; // Restablece la acción
  // }
  //Serial.print(estado[3]);Serial.print(estado[2]);Serial.print(estado[1]);Serial.println(estado[0]);
  // Serial.println(lecture);
  // TimeDelay(1000);
  // int estrategia = (digitalRead(Dip1)<<1) | digitalRead(Dip2);
  Serial.println(lecture);
  //motors.motorForward(200,200);

}
