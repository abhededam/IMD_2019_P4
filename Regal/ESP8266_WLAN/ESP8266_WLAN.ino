#include <TimeLib.h> //Library für Echtzeit braucht man glaub ich auch fürs WLAN
#include <LiquidCrystal.h> //Library für LCD Display
#include <ArduinoJson.h> //Library zum verschicken von Json (Version 6 funktioniert nicht, also nimm 5.xx)
#include <WiFiUdp.h> //Library fürs WLAN
#include <ESP8266WiFi.h> //Library fürs ESP8266 WLAN

#include <DNSServer.h> //Braucht man um server zu starten
#include <ESP8266WebServer.h> //Braucht man um server zu starten
#include <WiFiManager.h>  //Braucht man auch
                                                                                //Der Link:-http://192.168.43.40/Start

int RedPin = 5; //D1
int GreenPin = 4; //D2
int BluePin = 0; //D3
int KeyPin = 1; //TX
LiquidCrystal lcd(13, 12, 14, 16, 3, 2); //D7, D6, D5, D0, RX, D4
const int SENSOR_PIN = A0; //A0  

int count = 30;
int ButtonState = 0;
int lastButtonState = 0;
int lightR = 0;
int lightG = 0;
int lightB = 0;
int color = 0;

int storey = 20;
int changes = 0;
int push = 0;
int lastCount = 0;
int lastLastCount = 0;

int sec = second();
int minu = minute();
int ho = hour();
int da = day();
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;       
const long interval = 5000;

static const char ntpServerName[] = "us.pool.ntp.org"; //fürs WLAN
const int timeZone = 1; //fürs WLAN
WiFiUDP Udp;//fürs WLAN
unsigned int localPort = 8888;//fürs WLAN
time_t getNtpTime();//fürs WLAN
void digitalClockDisplay(); //fürs WLAN
void printDigits(int digits);//fürs WLAN
void sendNTPpacket(IPAddress &address);//fürs WLAN

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFiManager wifiManager; //fürs WLAN
  wifiManager.autoConnect("VARMA Prototyp"); //Name des WLANs
 
 
  while (WiFi.status() != WL_CONNECTED) { //fürs WLAN
    delay(500);//fürs WLAN
    Serial.print(".");//fürs WLAN
  }//fürs WLAN
  Serial.println("");//fürs WLAN
  Serial.println("WiFi connected");//fürs WLAN
 
  // Start the server//fürs WLAN
  server.begin();//fürs WLAN
  Serial.println("Server started");//fürs WLAN
 
  // Print the IP address//fürs WLAN
  Serial.print("Use this URL : ");//fürs WLAN
  Serial.print("http://");//fürs WLAN
  Serial.print(WiFi.localIP());//fürs WLAN
  Serial.println("/");//fürs WLAN
  
  pinMode(RedPin,OUTPUT);
  pinMode(GreenPin,OUTPUT);
  pinMode(BluePin,OUTPUT);
  
  pinMode(KeyPin, INPUT_PULLUP);
  
  Udp.begin(localPort);//fürs WLAN
  setSyncProvider(getNtpTime);//fürs WLAN
  setSyncInterval(300);//fürs WLAN
  
  lcd.begin(16, 2);               
  lcd.clear(); 
}

time_t prevDisplay = 0;//fürs WLAN

void loop() { 
  
                                                                                      
                                                                             //wenn sich Stockwerkzahl von alleine ändert:
                                                                            /* und */ //löschen und Code erneut hochladen
                                                                                
                                                                                       /*   
                                                                                          lcd.clear();
                                                                                          lcd.setCursor(12,1);
                                                                                          lcd.print(sensorValue);
                                                                                      */
                                                                                          
                                                                    // eine neue Zahl (sensorValue) sollte auf dem Display erscheinen
                                                                             //bis zum nächsten Kommentar runterscrollen
                                                                                                 //
                                                                                                 //
                                                                                                 //
                                                                                  /* und */ //wieder hinzufügen
                                                                                     //code erneut hochladen
                                                                                   //fehler sollte behoben sein
 
  WiFiClient client = server.available();//fürs WLAN
  client.flush();//fürs WLAN
  int sensorValue;
  sensorValue = analogRead(SENSOR_PIN); 
  ButtonState = digitalRead(KeyPin);
  currentMillis = millis();
  StaticJsonBuffer<200> jsonBuffer;//fürs WLAN
  JsonObject& root = jsonBuffer.createObject();//da kannst du reinschreiben was verschickt werden soll

  root["Daten die das System vom Device bekommt, wenn der Nutzer in der Nutzer die Lobby betritt"];
  root["Stockwerk"] = lastLastCount; //das in root ist quasi der Variablen name und dann füllt man die Variable mit einem Wert
  root["Zielstockwerk"] = count;
  root["Wochentag"] = da;
  root["Stunde"] = ho;
  root["Minute"] = minu;
  root["Sekunde"] = sec;
  root["ID"] = 76492122;
  root["Prio"] = "1";
  root["Akku"] = "96%";
  
   if(changes==0){
           lcd.setCursor(0,1);               
           lcd.print("Etage:"); 
           lcd.setCursor(7,1);
           lcd.print(count);
           lcd.setCursor(0,0);
           lcd.print("Google");
           lcd.setCursor(8,0);
           lcd.print(storey);
       
        if (ButtonState==LOW) {
           turnOff();
           push=0;
           Serial.print("änderungs Modus: an");
           lastButtonState = ButtonState;  
           delay(500);
           lcd.clear();
           changes=1;
         }
      }
      
      else if(changes==1){ 
         lcd.setCursor(0,0);               
         lcd.print("Etage:      "); 
         lcd.setCursor(0,1);
         lcd.print("          "); 
         lcd.setCursor(0,1);               
         lcd.print(count);
         
         if(sensorValue > 50 && sensorValue < 250 && count < 130){
          count++;
          delay(20);
         }
         
         if(sensorValue > 30 && sensorValue < 50 && count < 130){
          count++;
          delay(100);
         }
         
         if(sensorValue < 30 && sensorValue > 20 && count > 0){
          count--;  
          delay(100);
         }
                                                                   //sensorValue>11-- 11 durch eine Zahl größer als die Zahl ersezen
                                                                                                 //
                                                                                       //wieder hochscrollen
         if(sensorValue < 20 && sensorValue > 11 && count > 0){
          count--;  
          delay(20);
         }
         
         if (ButtonState != lastButtonState) {
           if(count!= lastCount){
            storey = random(1,15);
           } 
           if(storey>count){
            storey = random(count);
           } 
           
           color = random(0,6);
           previousMillis = currentMillis;
           lastLastCount = lastCount;
           sec = second();
           minu = minute();
           ho = hour();
           da = day();
           lastCount = count;
           lcd.setCursor(0,1);               
           lcd.print("Etage:"); 
           lcd.setCursor(7,1);
           lcd.print(lastCount);
           lcd.setCursor(0,0);
           lcd.print("Google");
           lcd.setCursor(8,0);
           lcd.print(storey);
           lastButtonState = ButtonState;  
        }
        
        if (ButtonState == LOW) { 
          delay(500);
          push=1;
          changes=0;
        }        
      }

      if(push==1){
        if (currentMillis - previousMillis >= interval) {
          shine();
        }
         
        client.println("HTTP/1.1 200 OK"); //fürs WLAN
        client.println("Content-Type: application/json");//fürs WLAN
        client.println("Access-Control-Allow-Origin: *");//fürs WLAN
        client.println("");//fürs WLAN
        root.prettyPrintTo(client);//fürs WLAN
      }
      if(push==0){
          client.println("System bekommt keine Informationen vom Device");
      }
      
      char response = client.read();//fürs WLAN
      if(response == 0){
        analogWrite(RedPin, 100);
        analogWrite(GreenPin, 100);
        analogWrite(BluePin, 100);
      }
}

void shine(){
    if(color==0){
      red();
    }
    if(color==1){
      red();
    }
    if(color==2){
      orange();
    }
    if(color==3){
      yellow();
    }
    if(color==4){
      green();
    }
    if(color==5){
      cyan();
    }
    if(color==6){
      blue();
    }
    if(color==7){
      magenta();
    }
}

void red (){
  
    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 0);
}
void orange (){

    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 50);
    analogWrite(BluePin, 0);
}
void yellow (){

    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 100);
    analogWrite(BluePin, 0);
}
void green (){

    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 100);
    analogWrite(BluePin, 0);
}
void cyan (){

    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 100);
    analogWrite(BluePin, 100);
}
void blue (){

    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 100);
}
void magenta (){

    analogWrite(RedPin, 100);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 100);
}
void turnOff (){
  
    analogWrite(RedPin, 0);
    analogWrite(GreenPin, 0);
    analogWrite(BluePin, 0);
}


const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message //fürs WLAN
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets //fürs WLAN

time_t getNtpTime() //fürs WLAN
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address) //fürs WLAN
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
