/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int led = 7;
int lede = 6;
int ledee = 5;
int ledeee = 4;

int period = 250;
unsigned long time_now = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(lede, OUTPUT);
  pinMode(ledee, OUTPUT);
  pinMode(ledeee, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  1------------------------------------------------11111111
  digitalWrite(led, HIGH);  
  digitalWrite(lede, LOW); 
  digitalWrite(ledee, LOW); 
  digitalWrite(ledeee, HIGH);  
  
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }  
    ----------------------------------------------------2222222
  digitalWrite(led, HIGH);  
  digitalWrite(lede, HIGH); 
  digitalWrite(ledee, LOW); 
  digitalWrite(ledeee, HIGH);
  
  time_now = millis();  
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
     ----------------------------------------------------333333
  digitalWrite(led, HIGH);  
  digitalWrite(lede, HIGH); 
  digitalWrite(ledee, LOW); 
  digitalWrite(ledeee, LOW);  
  
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
     ----------------------------------------------------4444444
  digitalWrite(led, HIGH);  
  digitalWrite(lede, LOW); 
  digitalWrite(ledee, LOW); 
  digitalWrite(ledeee, LOW);
  
  time_now = millis();  
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
     ----------------------------------------------------55555555
  digitalWrite(led, LOW);  
  digitalWrite(lede, HIGH); 
  digitalWrite(ledee, HIGH); 
  digitalWrite(ledeee, HIGH); 
  
  time_now = millis(); 
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
 ----------------------------------------------------66666666666666
  digitalWrite(led, LOW);  
  digitalWrite(lede, HIGH); 
  digitalWrite(ledee, HIGH); 
  digitalWrite(ledeee, HIGH);  
  
  time_now = millis();
 while(millis() < time_now + period){
        //wait approx. [period] ms
    }
 ----------------------------------------------------777777777777
  digitalWrite(led, HIGH);  
  digitalWrite(lede, HIGH); 
  digitalWrite(ledee,LOW); 
  digitalWrite(ledeee, HIGH);

  time_now = millis(); 
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
 ----------------------------------------------------888888888888888888
  digitalWrite(led, HIGH);  
  digitalWrite(lede, HIGH); 
  digitalWrite(ledee, HIGH); 
  digitalWrite(ledeee, LOW);  
  
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
 ----------------------------------------------------99999999999999999999999
  digitalWrite(led, LOW);  
  digitalWrite(lede, LOW); 
  digitalWrite(ledee, HIGH); 
  digitalWrite(ledeee, LOW);  
  
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
}
