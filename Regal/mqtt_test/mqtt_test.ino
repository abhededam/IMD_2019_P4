
//#include <WiFi.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <BLEDevice.h>

static boolean Verbinde = false;   // Phasen
static boolean Verbunden = false;
static boolean Suche = true;

int beacon = 0;
//int ir = 0;

int scanTime = 10;                // In Bluetooth Scanzeit in secunden
String BuetoothName = "RDL51822"; // Bluetooth Name des iTags
//String BuetoothName = "WGX ibeacon"; // Bluetooth Name des iTags

#define FilterFaktor 0.2          //  running average Filter Einstellung
float val_f;                      //  0,05 erhöht die Verspätung bei Änderung, macht aber das Wert stabiler
int zeler=1;

static BLEAddress *pServerAddress;
static BLEClient*  pClient;
static BLEAdvertisedDevice* myDevice;
static BLERemoteCharacteristic* pRemoteCharacteristic;
BLEScan* pBLEScan ;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice) // passiert wenn BLE Device ( beacon ) gefunden wurde
    {
      Serial.print(advertisedDevice.getAddress().toString().c_str()); // ibeacon Adresse anzeigen
      if (advertisedDevice.haveName())
        if (advertisedDevice.getName() == BuetoothName.c_str())       // ibeacon Adresse Vergleichen
        {
          Serial.print(" gefunden " + BuetoothName);                  // wenn überwache Adresse gefunden wurde                                    
          BLEDevice::getScan()->stop();                               // Scanvorgang beenden
          myDevice = new BLEAdvertisedDevice(advertisedDevice);
          Verbinde = true;
          Suche = false;
        } 
      Serial.println("");
    }
};

class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient) {
      Serial.println("Verbunden");
      Verbunden = true;
      Verbinde = false;
    }

    void onDisconnect(BLEClient* pclient) {
      Verbunden = false;
      Verbinde = false;
      Suche = true;
      Serial.println("Verbindung verloren");
    }
};


// Replace the next variables with your SSID/Password combination
const char* ssid = "InteractiveMediaDesign";
const char* password = "Q2gR9T-imd-2019";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "172.16.15.40";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// LED Pin
const int ledPin = 4;

void setup() {
  Serial.begin(115200);
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  //status = bme.begin();  
 
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);

  Serial.println("Starte RSSI Meter für " + BuetoothName);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); 
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->start(scanTime);
  
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
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
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
  long now = millis();
  
  if (Suche) pBLEScan->start(scanTime);
  
  if (Verbinde == true)
  {
    Serial.print("Verbinde mit ");
    Serial.println(myDevice->getAddress().toString().c_str());
    pClient = BLEDevice::createClient();
    pClient->setClientCallbacks(new MyClientCallback());
    pClient->connect(myDevice);
  }

  if (Verbunden) // Gepaart
  {
    delay(100);       // RSSI alle 100 mS abfragen
    
    // ----------------- Messwert Filter ------------------    
    val_f = pClient->getRssi() * FilterFaktor + val_f * (1 - FilterFaktor);
    
    if (!zeler)        // Ausgabe jeder 5 durchlauf (2x pro Sekunde)
    {
      Serial.print("Signal: ");
      Serial.println(int(round(val_f))); // Runden und Ganze Zahl bilden
      zeler = 5;
    }
    else  zeler--;
  }
  
  
  
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    // Temperature in Celsius
    //temperature = bme.readTemperature();   
    // Uncomment the next line to set temperature in Fahrenheit 
    // (and comment the previous temperature line)
    
    beacon = int(round(val_f)); // Temperature in Fahrenheit
    
    // Convert the value to a char array
    char beaconString[8];
    dtostrf(beacon, 1, 2, beaconString);
    
    //Serial.println(tempString);
    client.publish("esp32/beacon", beaconString);

    /*
    humidity = bme.readHumidity();
    
    // Convert the value to a char array
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("esp32/humidity", humString);*/
  }
}
