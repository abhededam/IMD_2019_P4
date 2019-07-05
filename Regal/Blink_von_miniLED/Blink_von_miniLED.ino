#include <Adafruit_NeoPixel.h>
 #define PIN 22
 #define NUMPIXELS 300
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

 //variables
 int ledPosition = 0;
 
 
 void setup() {
   pixels.begin();
   pixels.show();
 } 

 void loop() {  
   pixels.setPixelColor(0, pixels.Color(0, 40, 40)); 
   pixels.setPixelColor(1, pixels.Color(40, 0, 40));
   pixels.show();
   delay(100);
   pixels.setPixelColor(0, pixels.Color(0, 0, 0)); 
   pixels.setPixelColor(1, pixels.Color(0, 0, 0));
   pixels.show();
   delay(100);
}
