#include <Stepper.h>
class MoveablePlatform{
  public: 
    MoveablePlatform(int steps, int stepperPin1, int stepperPin2, int stepperPin3, int stepperPin4, int irPin, int led, String name, int debugging);
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
    int LED;
    int detecting;
    int beenDetected;
    int stopIt =false;
    Stepper myStepper;
    int Debugging;
};

MoveablePlatform::MoveablePlatform(int steps, int stepperPin1, int stepperPin2, int stepperPin3, int stepperPin4, int irPin, int led, String name, int debugging)
: Steps(steps), StepperPin1(stepperPin1), StepperPin2(stepperPin2), StepperPin3(stepperPin3), StepperPin4(stepperPin4), myStepper(steps, stepperPin1, stepperPin2, stepperPin3, stepperPin4), IRSensor(irPin), LED(led),name(name), Debugging(debugging){
  pinMode(LED, OUTPUT);
  pinMode(IRSensor,INPUT);
  myStepper.setSpeed(stepperSpeed);
  
}


void MoveablePlatform::move(){
  if(Debugging){
    Serial.print(name);
    Serial.println(": move()");
  
    Serial.println(stepsMade);
  }
  movingOut = true;
  myStepper.step(-2);
  moveCounter++;
  stepsMade -= 2; 
}

void MoveablePlatform::moveFar(){
  if(Debugging){
    Serial.print(name);
    Serial.println(": moveFar()");
  }
  movingOut = true;
  myStepper.step(-4);
  moveCounter++;
  stepsMade -= 4;
}

void MoveablePlatform::moveBack(){
  if(Debugging){
    Serial.print(name);
    Serial.println(": moveBack()");
  }
  if(hasMoved == true){
      hasMoved = false;
  }
  if(movingIn == false){
      movingIn = true;
  }
  myStepper.step(stepsMade/1000*(-1));
  moveCounter--;
}

void MoveablePlatform::update(){
  if((waitingTime == 100) && moveCounter > 0){
    moveBack();
    if(Debugging){
      Serial.print(name);
      Serial.println(" hat moveBack gestartet");
    }
  }
  
  if(Debugging){
    detecting = digitalRead(IRSensor);
    if(detecting != beenDetected){
      Serial.print(name);
      Serial.print(": hat was entdeckt!");
    }
  }
  if(digitalRead(IRSensor) == 0){
    handDetected = true;    
  }
  else{
    handDetected = false;
  }
  beenDetected=detecting;
  
  if(moveCounter == 1000 &&hasMoved==false){
    hasMoved = true;
    movingOut = false;
    if(Debugging){
      Serial.print(name);
      Serial.println(": ist angekommen ");
    }
  }
  
  if(moveCounter == 0 && movingIn == true){
    hasMoved = false;
    movingIn = false;
    waitingTime = 0;
    digitalWrite(LED,HIGH);
    stepsMade = 0;
    if(Debugging){
      if(stopIt){
        Serial.print(name);     
        Serial.println(": hasMoved = false; movingIn = false; waitingTime = 0; stepsMade = 0;");
      }
    
      Serial.print(".");
    }
  }

  if(hasMoved && waitingTime < 100){
    waitingTime++;
    if(Debugging){
      Serial.print("waiting time: ");     
      Serial.println(waitingTime);
    }
  }


    
  if((waitingTime == 100) && moveCounter > 0){
    
  }






  
  
}
