#include <Stepper.h>
class Platform{
  public: 
    Platform(String name, int irPin, int debugging);
    String name;
    void update();
    int IRSensor;
    bool handDetected = false;
    int detecting;
    int beenDetected;
    int Debugging;
  private:
   

};

Platform::Platform(String name, int irPin, int debugging)
: name(name), IRSensor(irPin), Debugging(debugging){
    pinMode(IRSensor,INPUT);

}

void Platform::update(){
  if(Debugging){
    detecting = digitalRead(IRSensor);
    if(detecting != beenDetected){
      Serial.print(name);
      Serial.print(" hat was entdeckt! :");
      Serial.println(digitalRead(IRSensor));
    }
  }
  if(digitalRead(IRSensor) == 0){
    handDetected = true;
  }
  else{
    handDetected = false;
  }
  beenDetected=detecting;
}
