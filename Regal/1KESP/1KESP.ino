#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//

                                  //4, 2, 15, 0
                                  //13, 14, 27, 12
MoveablePlatform goodCoffee(STEPS, 12, 11, 27, 26, 33, 25, "goodCoffee", true);

Platform noCoffee1("noCoffee1", 2, true);
Platform noCoffee2("noCoffee2", 15, true);

void setup() {
  Serial.begin(9600);
}




void loop() {
    goodCoffee.update();
    noCoffee1.update();
    noCoffee2.update();


    
    
  


    if(noCoffee1.handDetected){
      if(goodCoffee.movingOut == false && goodCoffee.hasMoved == false){
          goodCoffee.move();
          goodCoffee.waitingTime = 0;
          Serial.println("Good Coffee 1 fährt raus");
      }
    }

       if(noCoffee2.handDetected){
      if(goodCoffee.movingOut == false && goodCoffee.hasMoved == false){
          goodCoffee.move();
          goodCoffee.waitingTime = 0;
          Serial.println("Good Coffee 2 fährt raus");
      }
    }


    if(goodCoffee.handDetected){ 
    }


    

    
    if(goodCoffee.movingOut && goodCoffee.moveCounter < 1000){
            goodCoffee.move();
    }


    

}
