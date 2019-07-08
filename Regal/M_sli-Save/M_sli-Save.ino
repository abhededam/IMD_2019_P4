#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//

                                  //4, 2, 15, 0
MoveablePlatform bestMuesli(STEPS, 4, 2 , 15, 0, 32, 34, "bestMuesli", false);
                                  //13, 14, 27, 12
MoveablePlatform goodMuesli(STEPS, 13, 14, 27, 12, 33, 25, "goodMuesli", false);

Platform worstMuesli("Bob", 26,false);

void setup() {
  Serial.begin(9600);
}




void loop() {
    bestMuesli.update();
    goodMuesli.update();
    worstMuesli.update();

    
    
  


    if(worstMuesli.handDetected){
      if(bestMuesli.movingOut == false && bestMuesli.hasMoved == false){
        bestMuesli.moveFar();
        Serial.println("Best Muesli fährt raus");
      }
      else if(bestMuesli.movingOut == false && bestMuesli.hasMoved == true){
        bestMuesli.waitingTime = 0;
      }
      if(goodMuesli.movingOut == false && goodMuesli.hasMoved == false){
          goodMuesli.move();
                  Serial.println("Good Muesli fährt raus");

      }
      else{
          goodMuesli.waitingTime = 0;
      }
    }


    if(goodMuesli.handDetected){
      if(bestMuesli.movingOut == false && bestMuesli.hasMoved == false){
        bestMuesli.moveFar();
       }
      else{
        bestMuesli.waitingTime = 0;
      }
    }

    
    if(goodMuesli.movingOut && goodMuesli.moveCounter < 1000){
            goodMuesli.move();
    }
    if(bestMuesli.movingOut && bestMuesli.moveCounter < 1000){
            bestMuesli.moveFar();
    }


    

}
