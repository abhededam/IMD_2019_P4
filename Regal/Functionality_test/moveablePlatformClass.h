#include <Stepper.h>
class MoveablePlatform{
  public: 
    MoveablePlatform(int steps, int stepperPin1, int stepperPin2, int stepperPin3, int stepperPin4, int irPin, int piezoPin);
    int stepperSpeed = 140;
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
  private:
    int Steps;
    int StepperPin1;
    int StepperPin2;
    int StepperPin3;
    int StepperPin4;
    int PiezoPin;
    Stepper myStepper;

};

MoveablePlatform::MoveablePlatform(int steps, int stepperPin1, int stepperPin2, int stepperPin3, int stepperPin4, int irPin, int piezoPin)
: Steps(steps), StepperPin1(stepperPin1), StepperPin2(stepperPin2), StepperPin3(stepperPin3), StepperPin4(stepperPin4), myStepper(steps, stepperPin1, stepperPin2, stepperPin3, stepperPin4), IRSensor(irPin), PiezoPin(piezoPin){
  pinMode(IRSensor,INPUT);
  myStepper.setSpeed(stepperSpeed);
}


void MoveablePlatform::move(){
  movingOut = true;
  myStepper.step(-2);
  moveCounter++;
  stepsMade += -2;
}

void MoveablePlatform::moveFar(){
  movingOut = true;
  myStepper.step(-4);
  moveCounter++;
  stepsMade += -4;
}

void MoveablePlatform::moveBack(){
  hasMoved = false;
  movingIn = true;
  myStepper.step(stepsMade/1000*(-1));
  moveCounter--;
}

void MoveablePlatform::update(){
  if(analogRead(PiezoPin)>1000){
    pickedUp = true;
  }
  if(digitalRead(IRSensor) == 0){
    handDetected = true;
  }
  else{
    handDetected = false;
  }
  if(moveCounter >= 1000){
    hasMoved = true;
    movingOut = false;
  }
  if(moveCounter <= 0){
    hasMoved = false;
    movingIn = false;
    waitingTime = 0;
    stepsMade = 0;
  }

  if(hasMoved && waitingTime < 2000){
    waitingTime++;
  }
  if((waitingTime >= 2000 || pickedUp) && moveCounter > 0){
    moveBack();
  }





  
  
}
