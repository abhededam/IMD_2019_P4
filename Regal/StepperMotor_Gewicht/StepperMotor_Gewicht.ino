// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11);
const int triggerpin = 12;     
const int echopin = 13;  
int piezoPin = A0;   
int wert = 0;   
int productThere = 1;
long time;                    //Variable for storing the time traveled
int S;                        //Variable for storing the distance covered   
int show;
void setup() {
  pinMode(triggerpin, OUTPUT);  //Setting the triggerpin as output pin
  pinMode(echopin, INPUT);      //Setting the echo pin as input pin
  Serial.begin(9600);
}

void loop() {
  wert = analogRead(piezoPin); 
  Serial.println(S);
  //Serial.println(wert);
  if(S <5){  //////wenn die Hand vor dem Regal ist
    if(show==0){ ///wenn das Regal nicht ausgefahren ist
      Serial.print("HAND! FÄHRT AUS!");
      for(int i=0; i<4; i++){
       // Serial.print("i: ");
        //Serial.println(i);
        stepper.setSpeed(18); // 1 rpm
        stepper.step(500); // do 2038 steps -- corresponds to one revolution in one minute
        
      }
      show=1; //regal = ausgefahren
    }
    if(wert>30){ //wenn vibration erkannt
      if(productThere==0){ //wenn das gewählte Produkt nicht mehr da steht
        Serial.print("Produkt reingestellt");
        productThere=1;
        delay(350);
      }
      else if(productThere==1){ //wenn das gewählte Produkt noch da steht
        Serial.print("Produkt entnommen");
        for(int l=0; l<4; l++){
             Serial.print("FÄHRT EIN!");
            stepper.setSpeed(18); // 1 rpm
            stepper.step(-500); // do 2038 steps -- corresponds to one revolution in one minute
        }
        productThere=0; 
        show=0;
        
        
      } 
        
    } 
    
    
  }

  else if(S>10&&S<2000){// wenn nichts vor dem Regal ist
   if(show==1){ //wenn Regal ausgefahren
     for(int j=0; j<4; j++){
       // Serial.print("j: ");
        //Serial.println(j);
        stepper.setSpeed(18); // 1 rpm
        stepper.step(-500); // do 2038 steps -- corresponds to one revolution in one minute
        Serial.print("WEG! FÄHRT EIN!");
      }
      show=0;
    }
  }
  digitalWrite(triggerpin, LOW);  
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH); //Setting the triggerpin high for 10us to generate a wave
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  time = pulseIn(echopin, HIGH); //Setting the echopin high to receive the wave
  S= time*0.034/2;                //Calculating the distance traveled in cm  
}
