#include <Stepper.h>
#include "moveablePlatformClass.h";
#include "platformClass.h";
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)

MoveablePlatform bestCoffee(STEPS, 27, 26, 33, 32, 12, 22, "bestCoffee", true);
MoveablePlatform worstCoffee(STEPS, 5, 18, 19, 21, 27, 23, "worstCoffee", true);


Platform noCoffee("Bob", 3, true);


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

//uncomment the following lines if you're using SPI
/*#include <SPI.h>
  #define BME_SCK 18
  #define BME_MISO 19
  #define BME_MOSI 23
  #define BME_CS 5*/



void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
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

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if (messageTemp == "on") {
      Serial.println("on");

    }
    else if (messageTemp == "off") {
      Serial.println("off");
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

  /*  Serial.print("MAC: ");
   *  Serial.println(WiFi.macAddress());
   */
     

      bestCoffee.update();
      worstCoffee.update();
      noCoffee.update();

      if(noCoffee.handDetected){
            if(bestCoffee.movingOut == false && bestCoffee.hasMoved == false){
          bestCoffee.moveFar();
          Serial.println("Best Muesli fährt raus");
          client.publish("esp32/SmartMart", "bla");
        }
        else{
          bestCoffee.waitingTime = 0;
        }
        if(worstCoffee.movingOut == false && worstCoffee.hasMoved == false){
            worstCoffee.move();
            Serial.println("Good Muesli fährt raus");

        }
        else{
            worstCoffee.waitingTime = 0;
        }
      }


          if(worstCoffee.handDetected){
            if(bestCoffee.movingOut == false && bestCoffee.hasMoved == false){
          bestCoffee.moveFar();
        }
        else{
          bestCoffee.waitingTime = 0;
        }
      }


      if(worstCoffee.movingOut && worstCoffee.moveCounter < 1000){
              worstCoffee.move();
      }
      if(bestCoffee.movingOut && bestCoffee.moveCounter < 1000){
              bestCoffee.moveFar();
      }





    }
