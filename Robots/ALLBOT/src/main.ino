#include <Servo.h>
#include <ALLBOT.h>
#include <Arduino.h>

ALLBOT BOT(8);

enum MotorName{
    hipFrontLeft,
    hipFrontRight,
    hipRearLeft,
    hipRearRight,
    kneeFrontLeft,
    kneeFrontRight,
    kneeRearLeft,
    kneeRearRight,
};

void setup(){
    BOT.attach(hipFrontLeft, A1, 45, 0, 0);
    BOT.attach(hipFrontRight, A0, 45, 1, 0);
    BOT.attach(hipRearLeft, 9, 45, 1, 0);
    BOT.attach(hipRearRight, 4, 45, 0, 0);

    BOT.attach(kneeFrontLeft,  11,  0, 1, 0);
    BOT.attach(kneeFrontRight,  2,  0, 0, 0); 
    BOT.attach(kneeRearLeft,   10,  0, 1, 0); 
    BOT.attach(kneeRearRight,   3,  0, 0, 0);


    delay(500);

}

void loop(){
    leanleft(300);
    delay(300);
    leanright(300);
    wavefrontright(2,300);
    delay(300);
    wavefrontleft(2,300);
    delay(300);
}

void calibrate(int speedms){
    for (int i = 0; i < 8; i++)
    {
        BOT.move(i, 0);
        BOT.animate(speedms);
        BOT.move(i, 180);
        BOT.animate(speedms);
        BOT.move(i, 45);
        BOT.animate(speedms);
    }

}

void stand(){
    BOT.move(hipFrontLeft,45);
    BOT.move(hipFrontRight,20);
    BOT.move(hipRearLeft,90);
    BOT.move(hipRearRight,0);

    BOT.move(kneeFrontLeft, 0);
    BOT.move(kneeFrontRight, 0);
    BOT.move(kneeRearLeft, 0);
    BOT.move(kneeRearRight, 0);


}

//--------------------------------------------------------------
void waverearleft(int waves, int speedms){

    BOT.move(kneeRearLeft, 180);
    BOT.animate(speedms);
    
  for (int i = 0; i < waves; i++){
    BOT.move(hipRearLeft, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 65);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 45);
    BOT.animate(speedms);
  }    
  
    BOT.move(kneeRearLeft, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void waverearright(int waves, int speedms){

    BOT.move(kneeRearRight, 180);
    BOT.animate(speedms);
    
  for (int i = 0; i < waves; i++){
    BOT.move(hipRearRight, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 65);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 45);
    BOT.animate(speedms);
  }    
  
    BOT.move(kneeRearRight, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void wavefrontright(int waves, int speedms){

    BOT.move(kneeFrontRight, 180);
    BOT.animate(speedms);
    
  for (int i = 0; i < waves; i++){
    BOT.move(hipFrontRight, 0);
    BOT.animate(speedms);
    
    BOT.move(hipFrontRight, 65);
    BOT.animate(speedms);
    
    BOT.move(hipFrontRight, 0);
    BOT.animate(speedms);
    
    BOT.move(hipFrontRight, 45);
    BOT.animate(speedms);
  }    
  
    BOT.move(kneeFrontRight, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void wavefrontleft(int waves, int speedms){

    BOT.move(kneeFrontLeft, 180);
    BOT.animate(speedms);
    
  for (int i = 0; i < waves; i++){
    BOT.move(hipFrontLeft, 0);
    BOT.animate(speedms);
    
    BOT.move(hipFrontLeft, 65);
    BOT.animate(speedms);
    
    BOT.move(hipFrontLeft, 0);
    BOT.animate(speedms);
    
    BOT.move(hipFrontLeft, 45);
    BOT.animate(speedms);
  }    
  
    BOT.move(kneeFrontLeft, 45);
    BOT.animate(speedms);
}

//--------------------------------------------------------------
void leanright(int speedms){
    BOT.move(kneeFrontRight, 90);
    BOT.move(kneeRearRight, 90);
    BOT.animate(speedms);
    
    delay(speedms/2);
    
    BOT.move(kneeFrontRight, 45);
    BOT.move(kneeRearRight, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void leanleft(int speedms){
    BOT.move(kneeFrontLeft, 90);
    BOT.move(kneeRearLeft, 90);
    BOT.animate(speedms);
    
    delay(speedms/2);
    
    BOT.move(kneeFrontLeft, 45);
    BOT.move(kneeRearLeft, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void leanforward(int speedms){
    BOT.move(kneeFrontLeft, 90);
    BOT.move(kneeFrontRight, 90);
    BOT.animate(speedms);
    
    delay(speedms/2);
    
    BOT.move(kneeFrontLeft, 45);
    BOT.move(kneeFrontRight, 45);
    BOT.animate(speedms);
}
//--------------------------------------------------------------
void leanbackward(int speedms){
    BOT.move(kneeRearLeft, 90);
    BOT.move(kneeRearRight, 90);
    BOT.animate(speedms);
    
    delay(speedms/2);
    
    BOT.move(kneeRearLeft, 45);
    BOT.move(kneeRearRight, 45);
    BOT.animate(speedms);
}

//----------------------------------------------------------------
void walkforward(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearRight, 80);
    BOT.move(kneeFrontLeft, 80);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 80);
    BOT.move(hipFrontLeft, 20);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 0);
    BOT.move(kneeFrontLeft, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 45);
    BOT.move(hipFrontLeft, 45);
    BOT.animate(speedms);
    
    BOT.move(kneeRearRight, 45);
    BOT.move(kneeFrontLeft, 45);
    BOT.animate(speedms);
    
    BOT.move(kneeRearLeft, 80);
    BOT.move(kneeFrontRight, 80);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 80);
    BOT.move(hipFrontRight, 20);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 0);
    BOT.move(kneeFrontRight, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.animate(speedms);
    
    BOT.move(kneeRearLeft, 45);
    BOT.move(kneeFrontRight, 45);
    BOT.animate(speedms);
  }
}


void turnleft(int steps, int speedms){
  for (int i = 0; i < steps; i++){
    BOT.move(kneeRearRight, 80);
    BOT.move(kneeFrontLeft, 80);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 90);
    BOT.move(hipFrontLeft, 90);
    BOT.animate(speedms);

    BOT.move(kneeRearRight, 0);
    BOT.move(kneeFrontLeft, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearRight, 45);
    BOT.move(hipFrontLeft, 45);
    BOT.animate(speedms);
    
    BOT.move(kneeRearRight, 45);
    BOT.move(kneeFrontLeft, 45);
    BOT.animate(speedms);
    
    BOT.move(kneeRearLeft, 80);
    BOT.move(kneeFrontRight, 80);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 0);
    BOT.move(hipFrontRight, 0);
    BOT.animate(speedms);

    BOT.move(kneeRearLeft, 0);
    BOT.move(kneeFrontRight, 0);
    BOT.animate(speedms);
    
    BOT.move(hipRearLeft, 45);
    BOT.move(hipFrontRight, 45);
    BOT.animate(speedms);
    
    BOT.move(kneeRearLeft, 45);
    BOT.move(kneeFrontRight, 45);
    BOT.animate(speedms);
  }
}