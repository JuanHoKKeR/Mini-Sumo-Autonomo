void Seleccion(int seleccion){
  Serial.println("Eentro Estrategia");
  if(seleccion == 0) Estrategia_1();
  else if(seleccion == 1) Estrategia_2();
  else motors.motorStop();
}

void Estrategia_1(){
  
  motors.motorForward(110,110);
  TimeDelay(400);
  //motors.motorStop();
  motors.motorRight(200,200);
  TimeDelay(200);
  motors.motorForward(110,110);
  TimeDelay(400);
  motors.motorLeft(200,200);
  TimeDelay(200);
  //Serial.println("Se detiene");
  // TimeDelay(2000);
}

void Estrategia_2(){
  //Serial.println("Entra");
  motors.motorForward(150,255);
  TimeDelay(200);
  motors.motorForward(255,150);
  TimeDelay(200);
  //motors.motorStop();
  motors.motorRight(255,255);
  TimeDelay(200);
  motors.motorBack(200,200);
  TimeDelay(200);
  motors.motorLeft(255,255);
  TimeDelay(400);
  motors.motorForward(255,255);
  TimeDelay(200);
  motors.motorLeft(255,255);
  TimeDelay(400);
  //Serial.println("Se detiene");
  // TimeDelay(2000);
}
