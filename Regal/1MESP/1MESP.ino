#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//

                //lolin esp32 pro  4, 2, 15, 0, 32, 18 
MoveablePlatform bestMuesli(STEPS, 16,  0, 2, 4, 35, 19, "bestMuesli", false);
                                  
                // lolin esp32 pro 13, 14, 27, 12, 33, 5
MoveablePlatform goodMuesli(STEPS, 12, 27, 26, 14, 32, 18, "goodMuesli", false);

Platform worstMuesli("Bob", 25, false);

void setup() {
  Serial.begin(9600);
}




void loop() {
    bestMuesli.update();
    goodMuesli.update();
    worstMuesli.update();
    
    if(goodMuesli.handDetected){
       bestMuesli.light();
      if(bestMuesli.movingOut == false && bestMuesli.hasMoved == false){
        bestMuesli.moveFar();
        bestMuesli.waitingTime = 0;
       }
    }
    else{
      bestMuesli.dark();
    }
    
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
    else if(worstMuesli.handDetected == false && goodMuesli.handDetected == false){
      goodMuesli.dark();
      bestMuesli.dark();
    }

   
    
    
      

    
    if(goodMuesli.movingOut && goodMuesli.moveCounter < 1000){
            goodMuesli.move();
    }
    if(bestMuesli.movingOut && bestMuesli.moveCounter < 1000){
            bestMuesli.moveFar();
    } 

}
