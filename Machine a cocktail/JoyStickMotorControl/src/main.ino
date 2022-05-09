#include <LiquidCrystal.h>
#include "Wire.h"

#define moteur1 8
#define moteur2 9
#define moteur3 10

const int  moteurs[] = {moteur1, moteur2, moteur3};

//LCD part
const int contrast = 60;
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//LiquidCrystal lcd(11, 12, 2, 3, 4, 5);

//Joystick pin
#define VRy A0
#define SW 13

//Joystick values
#define up 0
#define down 1
#define enter 2
#define none 3

int currentMotorWorking;
int lastJoystickRead;

int readJostick(){
    int output = none;

    int yAxis = analogRead(VRy); //read Y axis value
    yAxis = map(yAxis, 0, 1023, -512, 512);
   
    int switchValue = digitalRead(SW); // read switch button value
    switchValue = map(switchValue, 0, 1, 1, 0);  // invert the input from the switch to be high when pressed

    if (switchValue == 1)
    {
        output = enter; 
    } else if (yAxis >= 400)
    {
        output = up;
    } else if (yAxis <= -400)
    {
        output = down;
    }

    return output;
}

void moveUp(){
    if (currentMotorWorking <= 0)
    {
        currentMotorWorking = (int)sizeof(moteurs)/sizeof(moteurs[0]) - 1;
    }else{
        currentMotorWorking--;
    }
    
}

void moveDown(){
    if (currentMotorWorking >= (int)sizeof(moteurs)/sizeof(moteurs[0]) - 1)
    {
        currentMotorWorking = 0;
    }else{
        currentMotorWorking++;
    }
}

void printMotorWorking(int motorWorking){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Moteur pin");
    lcd.setCursor(12, 0);
    lcd.print(motorWorking);
    lcd.setCursor(0,1);
    lcd.print("en fonction");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(moteur1, OUTPUT);
  pinMode(moteur2, OUTPUT);
  pinMode(moteur3, OUTPUT);

  lcd.begin(16, 2);
  analogWrite(6, contrast);

  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
    int currentJoystickRead = readJostick();

  if (currentJoystickRead != lastJoystickRead)
  {
    lastJoystickRead = currentJoystickRead;
      
    for (int moteur : moteurs){
      analogWrite(moteur, LOW);
    }

    switch (currentJoystickRead){
        case up :
          moveUp();
          break;
        case down : 
          moveDown();
          break;
        default : break;
    }

    digitalWrite(moteurs[currentMotorWorking], HIGH);
    printMotorWorking(currentMotorWorking);
  }
  
}