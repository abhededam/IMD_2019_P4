// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include <Stepper.h>

#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 15,0,4,2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  
      for(int i=0; i<4; i++){
        Serial.print("i: ");
        Serial.println(i);
        stepper.setSpeed(60); // 1 rpm
        stepper.step(400); // do 2038 steps -- corresponds to one revolution in one minute
      }

     for(int j=0; j<4; j++){
        Serial.print("j: ");
        Serial.println(j);
        stepper.setSpeed(60); // 1 rpm
        stepper.step(-400); // do 2038 steps -- corresponds to one revolution in one minute
     }
  
}
