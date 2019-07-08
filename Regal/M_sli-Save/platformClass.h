#include <Stepper.h>
class Platform{
  public: 
    Platform(String name, int irPin);
    String name;
    void update();
    int IRSensor;
    bool handDetected = false;
    int detecting;
    int beenDetected;
  private:
   

};

Platform::Platform(String name, int irPin)
: name(name), IRSensor(irPin){
    pinMode(IRSensor,INPUT);

}

void Platform::update(){
  detecting = digitalRead(IRSensor);
  if(detecting != beenDetected){
    Serial.print(name);
    Serial.print(" hat was entdeckt! :");
    Serial.println(digitalRead(IRSensor));
  }
  if(digitalRead(IRSensor) == 0){
    handDetected = true;
  }
  else{
    handDetected = false;
  }
  beenDetected=detecting;
}
