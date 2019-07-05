#include <Adafruit_NeoPixel.h>
#define PIN 22
#define NUMPIXELS 300
int vibrate = 23;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int period = 250;
unsigned long time_now = 0;

void setup() {
   pinMode(vibrate, OUTPUT);
   pixels.begin();
   pixels.show();
}

void loop() {
  //------------------------------------------------first eight note (0-250
  time_now = millis();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // first LED off
  pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // second LED off
  digitalWrite(vibrate,LOW); 
  pixels.show(); 
  Serial.println(time_now);
  while(millis() < time_now + period){
        //hold for a quater second
    }  
     Serial.println(time_now);
  //----------------------------------------------------second eight note
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // first LED off
  pixels.setPixelColor(1, pixels.Color(240, 0, 240)); // second LED on
  digitalWrite(vibrate,LOW);
  pixels.show();  
  time_now = millis();  
  while(millis() < time_now + period){
        //hold for a quater second
    }
    
  //----------------------------------------------------third eight note
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // first LED off
  pixels.setPixelColor(1, pixels.Color(240, 0, 240)); // second LED on
  digitalWrite(vibrate,LOW);
  pixels.show();
  time_now = millis();
  while(millis() < time_now + period){
        //hold for a quater second
    }

    
  // ----------------------------------------------------fourth eight note  
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // first LED off
  pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // second  LED off
  digitalWrite(vibrate,LOW);
  pixels.show();
  time_now = millis();  
  while(millis() < time_now + period){
        //hold for a quater second
    }

    
  //----------------------------------------------------fifth eight note   
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));  // first LED off
  pixels.setPixelColor(1, pixels.Color(240, 0, 240)); // second LED on
  digitalWrite(vibrate,LOW);
  pixels.show();  
  time_now = millis(); 
  while(millis() < time_now + period){
        //hold for a quater second
    }
    
 //----------------------------------------------------sixth eight note
  pixels.setPixelColor(0, pixels.Color(240, 0, 240));  // first LED on
  pixels.setPixelColor(1, pixels.Color(240, 0, 240)); // second LED on
  digitalWrite(vibrate,HIGH);
  
  
  pixels.show();
  time_now = millis();
 while(millis() < time_now + period){
        //hold for a quater second
    }
    
// ----------------------------------------------------seventh eight note
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // first LED off
  pixels.setPixelColor(1, pixels.Color(240, 0, 240)); // second LED on
  digitalWrite(vibrate,LOW);
  pixels.show(); 
  time_now = millis(); 
  while(millis() < time_now + period){
        //hold for a quater second
    }

    
 //----------------------------------------------------eight eight note
  pixels.setPixelColor(0, pixels.Color(240, 0, 240)); // first LED on
  pixels.setPixelColor(1, pixels.Color(240, 0, 240)); // second LED on
  digitalWrite(vibrate,HIGH);
  pixels.show();
  
  time_now = millis();
  while(millis() < time_now + period){
        //hold for a quater second
    }

    
// ----------------------------------------------------nith eight note
  pixels.setPixelColor(0, pixels.Color(240, 0, 240));  // first LED on
  pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // second LED off
  digitalWrite(vibrate,HIGH); 
  pixels.show();  
  
  time_now = millis();
  while(millis() < time_now + period){
        //hold for a quater second
    }
}
