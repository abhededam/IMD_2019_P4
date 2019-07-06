#include <Stepper.h>
class Platform{
  public: 
    Platform(String name, int irPin);
    String name;
    void update();
    int IRSensor;
    bool handDetected = false;
  private:
   

};

Platform::Platform(String name, int irPin)
: name(name), IRSensor(irPin){
    pinMode(IRSensor,INPUT);

}

void Platform::update(){
  if(digitalRead(IRSensor) == 0){
    handDetected = true;
  }
  else{
    handDetected = false;
  }
  
}
