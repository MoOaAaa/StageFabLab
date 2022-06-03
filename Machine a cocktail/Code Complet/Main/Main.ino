#include <Stepper.h>

const int stepsPerRevolution = 2038;

//Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // originally blue green yellow orange, now irrelevant
//Stepper myStepper(stepsPerRevolution, 8, 9, 11, 10);
//Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
//Stepper myStepper(stepsPerRevolution, 8, 10, 11, 9);
//Stepper myStepper(stepsPerRevolution, 8, 11, 10, 9); //close right
//Stepper myStepper(stepsPerRevolution, 8, 11, 9, 10); //cr
//Stepper myStepper(stepsPerRevolution, 11, 8, 9, 10); //cr
//Stepper myStepper(stepsPerRevolution, 11, 8, 10, 9); cr
//Stepper myStepper(stepsPerRevolution, 11, 9, 8, 10);
//Stepper myStepper(stepsPerRevolution, 11, 9, 10, 8);
//Stepper myStepper(stepsPerRevolution, 11, 10, 9, 8);
//Stepper myStepper(stepsPerRevolution, 11, 10, 8, 9);
//Stepper myStepper(stepsPerRevolution, 9, 10, 11, 8);
//Stepper myStepper(stepsPerRevolution, 9, 10, 8, 11); cr
//Stepper myStepper(stepsPerRevolution, 9, 8, 10, 11);
//Stepper myStepper(stepsPerRevolution, 9, 8, 11, 10);
//Stepper myStepper(stepsPerRevolution, 9, 11, 8, 10); cl
//Stepper myStepper(stepsPerRevolution, 9, 11, 10, 8); //strong
//Stepper myStepper(stepsPerRevolution, 10, 11, 8, 9);
//Stepper myStepper(stepsPerRevolution, 10, 11, 9, 8);
Stepper myStepper(stepsPerRevolution, 10, 8, 11, 9); //strong
//Stepper myStepper(stepsPerRevolution, 10, 8, 9, 11); // backwards
//Stepper myStepper(stepsPerRevolution, 10, 9, 11, 8);
//Stepper myStepper(stepsPerRevolution, 10, 9, 8, 11);

void setup(){}

void loop(){
  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution);
}
