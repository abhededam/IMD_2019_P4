#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//

                                  //4, 2, 15, 0
MoveablePlatform bestMuesli(STEPS, 4, 2 , 15, 0, 32, 18, "bestMuesli", true);
                                  //13, 14, 27, 12
MoveablePlatform goodMuesli(STEPS, 13, 14, 27, 12, 33, 5, "goodMuesli", true);

Platform worstMuesli("Bob", 26, true);

void setup() {
  Serial.begin(9600);
}




void loop() {
    bestMuesli.update();
    goodMuesli.update();
    worstMuesli.update();
    
    if(worstMuesli.handDetected){
      bestMuesli.light();
      goodMuesli.light();
      if(bestMuesli.movingOut == false && bestMuesli.hasMoved == false){
        bestMuesli.moveFar();
        bestMuesli.waitingTime = 0;

        Serial.println("Best Muesli fährt raus");
      }
      if(goodMuesli.movingOut == false && goodMuesli.hasMoved == false){
          goodMuesli.move();
                  goodMuesli.waitingTime = 0;

                  Serial.println("Good Muesli fährt raus");
      }
    }
    else{
      bestMuesli.dark();
      goodMuesli.dark();
    }


    if(goodMuesli.handDetected){
      if(bestMuesli.movingOut == false && bestMuesli.hasMoved == false){
        bestMuesli.moveFar();
        bestMuesli.waitingTime = 0;
       }
       bestMuesli.light();
    }
    else{
      bestMuesli.dark();
    }
    
    
      

    
    if(goodMuesli.movingOut && goodMuesli.moveCounter < 1000){
            goodMuesli.move();
    }
    if(bestMuesli.movingOut && bestMuesli.moveCounter < 1000){
            digitalWrite(18, HIGH);
            bestMuesli.moveFar();
    } 

}
