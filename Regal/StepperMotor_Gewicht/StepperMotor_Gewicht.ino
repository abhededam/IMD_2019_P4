// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include <Stepper.h>

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11);
const int triggerpin = 12;     
const int echopin = 13;  
int piezoPin = A0;   
int wert = 0;   
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
  Serial.println(wert);
  if(S <5){
    if(show==0){
      for(int i=0; i<4; i++){
       // Serial.print("i: ");
        //Serial.println(i);
        stepper.setSpeed(18); // 1 rpm
        stepper.step(500); // do 2038 steps -- corresponds to one revolution in one minute
      }
      show=1;
    }
    
    if(wert<100){
     for(int l=0; l<4; l++){
        stepper.setSpeed(18); // 1 rpm
        stepper.step(-500); // do 2038 steps -- corresponds to one revolution in one minute
      }
      show=0;
     }
    
  }

  else{
   if(show==1){
     for(int j=0; j<4; j++){
       // Serial.print("j: ");
        //Serial.println(j);
        stepper.setSpeed(18); // 1 rpm
        stepper.step(-500); // do 2038 steps -- corresponds to one revolution in one minute
      }
    }
    show=0;
  }
  digitalWrite(triggerpin, LOW);  
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH); //Setting the triggerpin high for 10us to generate a wave
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  time = pulseIn(echopin, HIGH); //Setting the echopin high to receive the wave
  S= time*0.034/2;                //Calculating the distance traveled in cm
  //Serial.print("Distance: ");
  //Serial.println(S);
  
}
