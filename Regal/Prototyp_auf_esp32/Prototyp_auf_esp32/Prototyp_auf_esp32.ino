// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 15,2,0,4);
//const int triggerpin = 12;     
//const int echopin = 13;  
int piezoPin = 34;   
int wert = 0;   
int productThere = 1;
int IRsensor = 32;
int IRstate = LOW; 
int attendance = 0;
//long time;                    //Variable for storing the time traveled
//int S;                        //Variable for storing the distance covered   
int show;
void setup() {
  /*pinMode(triggerpin, OUTPUT);  //Setting the triggerpin as output pin
  pinMode(echopin, INPUT);      //Setting the echo pin as input pin
  */
  pinMode(IRsensor,INPUT);
  pinMode(IRsensor,INPUT);
  Serial.begin(9600);
}

void loop() {
  wert = analogRead(piezoPin);
  attendance = digitalRead(IRsensor); 

  //Serial.println(wert);
  
if (attendance == LOW) {            // check if the input is LOW    
    if (IRstate == LOW) {
      //Serial.println("Motion detected!");
      IRstate = HIGH;
    }
  } else {
    if (IRstate == HIGH){
      //Serial.println("Motion ended!");
      IRstate = LOW;
    }
  }
  
  if(IRstate == HIGH){  //////wenn die Hand vor dem Regal ist
    if(show==0){ ///wenn das Regal nicht ausgefahren ist
      Serial.println("HAND! FÄHRT AUS!");
      for(int i=0; i<4; i++){
       // Serial.print("i: ");
        //Serial.println(i);
        stepper.setSpeed(18); // 1 rpm
        stepper.step(500); // do 2038 steps -- corresponds to one revolution in one minute
        
      }
      show=1; //regal = ausgefahren
    }
    if(wert>1000){ //wenn vibration erkannt
      if(productThere==0){ //wenn das gewählte Produkt nicht mehr da steht
        Serial.println("Produkt reingestellt");
        productThere=1;
        delay(350);
      }
      else if(productThere==1){ //wenn das gewählte Produkt noch da steht
        Serial.println("Produkt entnommen");
        for(int l=0; l<4; l++){
            Serial.println("FÄHRT EIN!");
            stepper.setSpeed(18); // 1 rpm
            stepper.step(-500); // do 2038 steps -- corresponds to one revolution in one minute
        }
        productThere=0; 
        show=0;
        
        
      } 
        
    } 
    
    
  }

  else if(IRstate == LOW){// wenn nichts vor dem Regal ist
   if(show==1){ //wenn Regal ausgefahren
     for(int j=0; j<4; j++){
       // Serial.print("j: ");
        //Serial.println(j);
        stepper.setSpeed(18); // 1 rpm
        stepper.step(-500); // do 2038 steps -- corresponds to one revolution in one minute
        Serial.println("WEG! FÄHRT EIN!");
      }
      show=0;
    }
  }
  /*
  digitalWrite(triggerpin, LOW);  
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH); //Setting the triggerpin high for 10us to generate a wave
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  time = pulseIn(echopin, HIGH); //Setting the echopin high to receive the wave
  S= time*0.034/2;                //Calculating the distance traveled in cm */
}
