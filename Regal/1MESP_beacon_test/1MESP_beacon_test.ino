#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//iBeacon Adresse: 54:4a:16:38:8c:2d
bool known = false;
String korbAddress = "54:4a:16:38:8c:2d";

#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//

                                  //4, 2, 15, 0
MoveablePlatform bestMuesli(STEPS, 4, 2 , 15, 0, 32, 18, "bestMuesli", false);
                                  //13, 14, 27, 12
MoveablePlatform goodMuesli(STEPS, 13, 14, 27, 12, 33, 5, "goodMuesli", false);

Platform worstMuesli("Bob", 26, false);


int scanTime = 5; //In seconds
static BLEAddress *ScannedServerAddress;
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: 
    public BLEAdvertisedDeviceCallbacks 
      {
      void onResult(BLEAdvertisedDevice advertisedDevice) 
        {
          ScannedServerAddress = new BLEAddress(advertisedDevice.getAddress());
            
          if (strcmp(ScannedServerAddress->toString().c_str(), korbAddress.c_str()) == 0){
            known = true;
          }
          if (strcmp(ScannedServerAddress->toString().c_str(), korbAddress.c_str()) != 0){
            known = false;
          }
     }
  };

void setup() {
  Serial.begin(9600);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99); 
}




void loop() {
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    pBLEScan->clearResults();
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
    else if(worstMuesli.handDetected == false && goodMuesli.handDetected == false&&known==true){
      goodMuesli.dark();
    }
    else if(worstMuesli.handDetected == false && goodMuesli.handDetected == false&&known==false){
      goodMuesli.dark();
      bestMuesli.dark();
    }

   
    if(known){
      bestMuesli.moveFar();
      bestMuesli.waitingTime = 0;
      Serial.println("Best Muesli fährt raus");
    }
    
      

    
    if(goodMuesli.movingOut && goodMuesli.moveCounter < 1000){
            goodMuesli.move();
    }
    if(bestMuesli.movingOut && bestMuesli.moveCounter < 1000){
            bestMuesli.moveFar();
    } 

}
