#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h> //in Git -> Regal -> pubsubclient-Ordner in arduino libraries Ordner verschieben
#include <Wire.h>

const char* ssid = "InteractiveMediaDesign";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)


MoveablePlatform bestMuesli(STEPS, 15, 0 , 4, 2, 32, 34);
MoveablePlatform goodMuesli(STEPS, 5,19,21,18, 33, 25);

Platform worstMuesli("Bob", 26);





void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:
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
    else{}
    

}
