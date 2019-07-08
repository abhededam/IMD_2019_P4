#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h> //in Git -> Regal -> pubsubclient-Ordner in arduino libraries Ordner verschieben
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)

MoveablePlatform bestMuesli(STEPS, 4, 2 , 15, 0, 32, 34);
MoveablePlatform goodMuesli(STEPS, 13, 14, 27, 12, 33, 25);

Platform worstMuesli("Bob", 26);

void setup() {
  Serial.begin(9600);
   
}




void loop() {
    bestMuesli.update();
    goodMuesli.update();
    worstMuesli.update();
    Serial.println(worstMuesli.handDetected);



    if(worstMuesli.handDetected){
          if(bestMuesli.movingOut == false && bestMuesli.hasMoved == false){
        bestMuesli.moveFar();
      }
      else{
        bestMuesli.waitingTime = 0;
      }
      if(goodMuesli.movingOut == false && goodMuesli.hasMoved == false){
          goodMuesli.move();
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
