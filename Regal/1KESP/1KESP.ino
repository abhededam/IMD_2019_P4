#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)
//

                                   //12, 14, 27, 26
MoveablePlatform goodCoffee(STEPS, 14, 27, 26, 25, 33, 12, "goodCoffee", false);

Platform noCoffee1("noCoffee1", 2, false);
Platform noCoffee2("noCoffee2", 15, false);

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

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/SmartMart") {
    if (coffee == "goodCoffee move") {
      //Serial.println("goodCoffee move");
        if(goodCoffee.movingOut == false && goodCoffee.hasMoved == false){
          goodCoffee.move();
          goodCoffee.waitingTime = 0;
          //Serial.println("Good Coffee fährt raus");
        }
      
    }
    if(coffee == "goodCoffee light"){
      goodCoffee.light();
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
    goodCoffee.update();
    noCoffee1.update();
    noCoffee2.update();


    
    
  


    if(noCoffee1.handDetected || noCoffee2.handDetected){
      client.publish("esp32/SmartMart", "noCoffee = on");
      client.publish("esp32/SmartMart", "bestCoffee light");
      client.publish("esp32/SmartMart", "worstCoffee light");
      goodCoffee.light();
      if(goodCoffee.movingOut == false && goodCoffee.hasMoved == false){
          goodCoffee.move();
          goodCoffee.waitingTime = 0;
          Serial.println("Good Coffee fährt raus");
      }
    }

   


    if(goodCoffee.handDetected){ 
            client.publish("esp32/SmartMart", "goodCoffee = on");
            client.publish("esp32/SmartMart", "bestCoffee light");
    }

    if(goodCoffee.handDetected==false&&noCoffee1.handDetected==false&&noCoffee2.handDetected==false){
      goodCoffee.dark();
      client.publish("esp32/SmartMart", "bestCoffee dark");
  
    }


  if(goodCoffee.movingOut && goodCoffee.moveCounter < 1000){
            goodCoffee.move();
    }
    

    


    

}
