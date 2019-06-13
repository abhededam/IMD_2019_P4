#include <Servo.h>          //include the servo library

int servoPosition;         //the servo will move to this position
const int triggerpin = 12;     //Connect the trigger pin at pin 2
const int echopin = 11;        //Connect the echo pin at pin 3
long time;                    //Variable for storing the time traveled
int S;                        //Variable for storing the distance covered
int inch;                     //Variable for storing the distance in inches
int led = 10;

Servo myservo;              //create a servo object

void setup() {
  pinMode(triggerpin, OUTPUT);  //Setting the triggerpin as output pin
  pinMode(echopin, INPUT);      //Setting the echo pin as input pin
  Serial.begin(9600);
  myservo.attach(9);        //tell the servo object that its servo is plugged into pin 9
  pinMode(led, OUTPUT);

}

void loop() {
  if(S <30){
    digitalWrite(led,HIGH);
     servoPosition = 0;
  }
  else{
    digitalWrite(led,LOW);
    servoPosition = 180;
  }
  myservo.write(servoPosition);  
  digitalWrite(triggerpin, LOW);  
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH); //Setting the triggerpin high for 10us to generate a wave
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  time = pulseIn(echopin, HIGH); //Setting the echopin high to receive the wave
  S= time*0.034/2;                //Calculating the distance traveled in cm
  inch = time*0.0133/2;           //Calculating the disatnce traveled in inches
  Serial.print("Distance: ");
  Serial.print(S);
  Serial.print(" cm,  ");
  Serial.print(inch);
  Serial.println(" inch ");
}
