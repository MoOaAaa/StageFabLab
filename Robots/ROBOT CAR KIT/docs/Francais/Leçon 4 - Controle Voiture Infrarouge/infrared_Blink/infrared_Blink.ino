//www.elegoo.com

#include <IRremote.h>

#define RECV_PIN  12        //Infrared signal receiving pin
#define LED       13        //define LED pin
#define L         16738455
#define UNKNOWN_L 1386468383

bool state = LOW;           //define default input mode
unsigned long val; 

IRrecv irrecv(RECV_PIN);   //initialization
decode_results results;   //Define structure type

void stateChange() {
  state = !state;          
  digitalWrite(LED, state);
}

void setup() {
  pinMode(LED, OUTPUT); //initialize LED as an output
  Serial.begin(9600);  // debug output at 9600 baud
  irrecv.enableIRIn();  // Start receiving
}

void loop() {
  if (irrecv.decode(&results)) { 
    val = results.value;
    Serial.println(val);
    irrecv.resume();      // Receive the next value
    delay(150);
    if(val == L || val == UNKNOWN_L) {  
      stateChange();
    }
  }
}

