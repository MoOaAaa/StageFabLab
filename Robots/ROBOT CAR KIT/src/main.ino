#include <Arduino.h>

const int FR_WHEEL = 7; 
const int FL_WHEEL = 8; 
const int RR_WHEEL = 9; 
const int RL_WHEEL = 11;

void setup(){
    pinMode(FR_WHEEL, OUTPUT);
    pinMode(FL_WHEEL, OUTPUT);
    pinMode(RR_WHEEL, OUTPUT);
    pinMode(RL_WHEEL, OUTPUT);
}

void loop(){
    analogWrite(FR_WHEEL, 255);
    analogWrite(FL_WHEEL, 255);
    analogWrite(RR_WHEEL, 255);
    analogWrite(RL_WHEEL, 255);
    
    delay(3000);
}