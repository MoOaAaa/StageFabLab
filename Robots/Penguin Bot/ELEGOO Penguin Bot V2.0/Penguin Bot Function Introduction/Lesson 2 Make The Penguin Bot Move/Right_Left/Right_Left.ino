#include "Arduino.h"
#include "Oscillator.h"
#include <Servo.h>
/*
         ---------------
        |     O   O     |
        |---------------|
YR 2<== |               | <== YL 3
         ---------------
            ||     ||
            ||     ||
RR 0==^   -----   ------  v== RL 1
         |-----   ------|
*/

/* Hardware interface mapping*/
#define YL_PIN 10 
#define YR_PIN 9  
#define RL_PIN 12 
#define RR_PIN 6  

#define N_SERVOS 4
#define INTERVALTIME 10.0
Oscillator servo[N_SERVOS];
int t = 495;
#define CENTRE 90

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS];
int oldPosition[] = {CENTRE, CENTRE, CENTRE, CENTRE};

bool delays(unsigned long ms)
{
    for (unsigned long i = 0; i < ms; i++)
    {
        delay(1);
    }
    return false;
}

/*
    Setting the 90-degree position of the steering gear to make the penguin stand on its feet
*/
void homes(int millis_t)
{
    servo[0].SetPosition(90);
    servo[1].SetPosition(90);
    servo[2].SetPosition(90);
    servo[3].SetPosition(90);
    delay(millis_t);
}
bool moveNServos(int time, int newPosition[])
{
    for (int i = 0; i < N_SERVOS; i++)
    {
        increment[i] = ((newPosition[i]) - oldPosition[i]) / (time / INTERVALTIME);
    }
    final_time = millis() + time;
    iteration = 1;
    while (millis() < final_time)
    {
        interval_time = millis() + INTERVALTIME;
        oneTime = 0;
        while (millis() < interval_time)
        {
            if (oneTime < 1)
            {
                for (int i = 0; i < N_SERVOS; i++)
                {
                    servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
                }
                iteration++;
                oneTime++;
            }
        }
    }
    for (int i = 0; i < N_SERVOS; i++)
    {
        oldPosition[i] = newPosition[i];
    }
    return false;
}
/*
    Turn control realization:
*/
bool turn(int steps, int T, int dir)
{
    int move1[] = {90 - 55, 90 - 20, 90 + 20, 90 + 20};
    int move2[] = {90 - 20, 90 - 20, 90 + 20, 90 - 20};
    int move3[] = {90 + 20, 90 + 55, 90 + 20, 90 - 20};
    int move4[] = {90 + 20, 90 + 20, 90 - 20, 90 + 20};
    int move5[] = {90 - 55, 90 - 20, 90 - 20, 90 + 20};
    int move6[] = {90 - 20, 90 - 20, 90 + 20, 90 - 20};
    int move7[] = {90 + 20, 90 + 55, 90 + 20, 90 - 20};
    int move8[] = {90 + 20, 90 + 20, 90 - 20, 90 + 20};
  
    int move21[] = {90 + 20, 90 + 55, 90 + 20, 90 + 20};
    int move22[] = {90 + 20, 90 + 20, 90 + 20, 90 - 20};
    int move23[] = {90 - 55, 90 - 20, 90 + 20, 90 - 20};
    int move24[] = {90 - 20, 90 - 20, 90 - 20, 90 - 20};
    int move25[] = {90 + 20, 90 + 55, 90 - 20, 90 + 20};
    int move26[] = {90 + 20, 90 + 20, 90 + 20, 90 - 20};
    int move27[] = {90 - 55, 90 - 20, 90 + 20, 90 - 20};
    int move28[] = {90 - 20, 90 - 20, 90 - 20, 90 - 20};

    if (dir == 1)
    {
        for (int i = 0; i < steps; i++)
            if (
                moveNServos(T * 0.2, move1) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move2) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move3) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move4) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move5) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move6) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move7) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move8) ||
                delays(t / 5))
                return true;
    }
    else
    {
        for (int i = 0; i < steps; i++)
            if (
                moveNServos(T * 0.2, move21) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move22) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move23) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move24) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move25) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move26) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move27) ||
                delays(t / 5) ||
                moveNServos(T * 0.2, move28) ||
                delays(t / 5))
                return true;
    }

    return false;
}

void setup()
{
    servo[0].attach(RR_PIN);
    servo[1].attach(RL_PIN);
    servo[2].attach(YR_PIN);
    servo[3].attach(YL_PIN);
    homes(100);
}

void loop()
{
    for (int i = 0; i < 5; i++)
    {
        turn(1, t * 4, 1);
    }
    for (int i = 0; i < 5; i++)
    {
       turn(1, t * 4, -1);
    }
}
