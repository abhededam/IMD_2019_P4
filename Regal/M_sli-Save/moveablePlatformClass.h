#include <Stepper.h>
class MoveablePlatform{
  public: 
    MoveablePlatform(int steps, int stepperPin1, int stepperPin2, int stepperPin3, int stepperPin4, int irPin, int piezoPin, String name);
    int stepperSpeed = 140;
    String name;
    void move();
    void moveFar();
    bool hasMoved = false;
    bool pickedUp = false;
    int waitingTime = 0;
    void update();
    void moveBack();
    int IRSensor;
    int stepsMade = 0;
    int moveCounter = 0;
    int movingIn = false;
    int movingOut = false;
    bool handDetected = false;
    int piezoValue;
  private:
    int Steps;
    int StepperPin1;
    int StepperPin2;
    int StepperPin3;
    int StepperPin4;
    int PiezoPin;
    int detecting;
    int beenDetected;
    int stopIt =false;
    Stepper myStepper;

};

MoveablePlatform::MoveablePlatform(int steps, int stepperPin1, int stepperPin2, int stepperPin3, int stepperPin4, int irPin, int piezoPin, String name)
: Steps(steps), StepperPin1(stepperPin1), StepperPin2(stepperPin2), StepperPin3(stepperPin3), StepperPin4(stepperPin4), myStepper(steps, stepperPin1, stepperPin2, stepperPin3, stepperPin4), IRSensor(irPin), PiezoPin(piezoPin),name(name){
  pinMode(IRSensor,INPUT);
  myStepper.setSpeed(stepperSpeed);
  
}


void MoveablePlatform::move(){
  Serial.println("move()");

  Serial.println(stepsMade);
  movingOut = true;
  myStepper.step(-2);
  moveCounter++;
  stepsMade -= 2; 
}

void MoveablePlatform::moveFar(){
  Serial.print(name);
  Serial.println("moveFar()");
  movingOut = true;
  myStepper.step(-4);
  moveCounter++;
  stepsMade -= 4;
}

void MoveablePlatform::moveBack(){
  Serial.print(name);
  Serial.println("moveBack()");
  hasMoved = false;
  movingIn = true;
  myStepper.step(stepsMade/500*(-1));
  moveCounter--;
}

void MoveablePlatform::update(){
  
  detecting = digitalRead(IRSensor);
  if(detecting != beenDetected){
    Serial.print(name);
    Serial.print("hat was entdeckt!");
  }
  if(digitalRead(IRSensor) == 0){
    handDetected = true;    
  }
  else{
    handDetected = false;
  }
  beenDetected=detecting;
  
  if(moveCounter >= 500){
    hasMoved = true;
    movingOut = false;
    Serial.print(name);
    Serial.println(" ist angekommen (hasMoved= true && movingOut = false");
  }
  
  if(moveCounter <= 0){
    hasMoved = false;
    movingIn = false;
    waitingTime = 0;
    stepsMade = 0;
    if(stopIt){
      Serial.print(name);     
      Serial.println(" hasMoved = false; movingIn = false; waitingTime = 0; stepsMade = 0;");
    }
    Serial.print(".");
  }

  if(hasMoved && waitingTime < 50){
    waitingTime++;
    Serial.print("waiting time: ");     
    Serial.println(waitingTime);
  }


    
  if((waitingTime == 50) && moveCounter > 0){
    
  }
  if((waitingTime >= 50) && moveCounter > 0){
    moveBack();
    Serial.print(name);
    Serial.println(" hat moveBack gestartet");
  }





  
  
}
