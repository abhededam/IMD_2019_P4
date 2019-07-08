/*
  TroubleShooting:
    Wenn etwas nicht klappt => 
      checken ob Motoren alle durchgängig Strom haben (rote Lämpchen leuchten)
      Checken ob Infrarot Sensoren richtig auslösen (Kontrolllämpchen an den Sensoren selbst)
      
      
*/

#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//
                                  //26, 25, 33, 32
MoveablePlatform bestCoffee(STEPS, 26, 25, 33, 32, 14, 22, "bestCoffee", true);
                                    //21, 19, 18, 5
MoveablePlatform worstCoffee(STEPS, 21, 19, 18, 5, 12, 23, "worstCoffee", true);


Platform noCoffee("Bob", 13, true);


const char* ssid = "InteractiveMediaDesign";
const char* password = "Q2gR9T-imd-2019";
const char* mqtt_server = "postman.cloudmqtt.com";
const int mqtt_port = 12666;
const char* mqtt_username = "ybudyjxr";
const char* mqtt_password = "9thhh0B-DhNJ";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  Serial.println(WiFi.macAddress());
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

void callback(char* topic, byte* message, unsigned int length) {
  //Serial.print("Message arrived on topic: ");
  //Serial.print(topic);
  //Serial.print(". Message: ");
  String coffee;

  for (int i = 0; i < length; i++) {
    //Serial.print((char)message[i]);
    coffee += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/SmartMart") {
    if (coffee == "goodCoffee = on") {
      Serial.println("goodCoffee: on");
    }
    else if (coffee == "noCoffee = on") {
      Serial.println("noCoffee: on");
      if(bestCoffee.movingOut == false && bestCoffee.hasMoved == false){
          if(bestCoffee.movingOut == false && bestCoffee.hasMoved == false){
          bestCoffee.moveFar();
          bestCoffee.waitingTime = 0;
     }
          Serial.println("best Coffee fährt raus");
         }
        client.publish("esp32/SmartMart", "goodCoffee should move");
        if(worstCoffee.movingOut == false && worstCoffee.hasMoved == false){
            worstCoffee.move();
            Serial.println("worst Coffee fährt raus");
            worstCoffee.waitingTime = 0;

        }
    }

  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish("/icircuit/presence/ESP32/", "hello world");
      // ... and resubscribe
      client.subscribe("esp32/SmartMart");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
   if (!client.connected()) {
    reconnect();
   }
   client.loop();
   bestCoffee.update();
   worstCoffee.update();
   noCoffee.update();
    
   if(noCoffee.handDetected){
        if(bestCoffee.movingOut == false && bestCoffee.hasMoved == false){
          bestCoffee.moveFar();
          Serial.println("best Coffee fährt raus");
          bestCoffee.waitingTime = 0;
         }
        client.publish("esp32/SmartMart", "goodCoffee should move");
        if(worstCoffee.movingOut == false && worstCoffee.hasMoved == false){
            worstCoffee.move();
            Serial.println("worst Coffee fährt raus");
            worstCoffee.waitingTime = 0;
        }
        client.publish("esp32/SmartMart", "goodCoffee = on");
   }

   if(worstCoffee.handDetected){
     if(bestCoffee.movingOut == false && bestCoffee.hasMoved == false){
          bestCoffee.moveFar();
          bestCoffee.waitingTime = 0;
     }
     client.publish("esp32/SmartMart", "goodCoffee move");
   }

    
   if(worstCoffee.movingOut && worstCoffee.moveCounter < 1000){
         worstCoffee.move();
   }
   if(bestCoffee.movingOut && bestCoffee.moveCounter < 1000){
         bestCoffee.moveFar();
   }
}
