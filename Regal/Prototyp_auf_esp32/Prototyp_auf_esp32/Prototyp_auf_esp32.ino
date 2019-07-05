// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
/*
  Größtes Problem: Nichts funktioniert gleichzeitig!


*/
int checkPiezos = 0;

#include <Stepper.h>

#define STEPS 200 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepperGoodMuesli(STEPS, 15,0,4,2);
Stepper stepperMuesli(STEPS, 5,19,21,18);

int piezoPinGoodMuesli = 34;   
int piezoPinMuesli = 25;   

int wertGoodMuesli = 0;   
int productThereGoodMuesli = 1;
int IRsensorGoodMuesli = 32;
int IRstateGoodMuesli = LOW; 
int attendanceGoodMuesli = 0;
int showGoodMuesli;


int wertMuesli = 0;   
int productThereMuesli = 1;
int IRsensorMuesli = 33;
int IRstateMuesli = LOW; 
int attendanceMuesli = 0;
int showMuesli;

void setup() {
  pinMode(IRsensorGoodMuesli,INPUT);
  pinMode(IRsensorMuesli,INPUT);
  Serial.begin(9600);
  stepperGoodMuesli.setSpeed(120); 
  stepperMuesli.setSpeed(120);
}

void loop() {
  
  wertGoodMuesli = analogRead(piezoPinGoodMuesli);
  attendanceGoodMuesli = digitalRead(IRsensorGoodMuesli); 
  wertMuesli = analogRead(piezoPinMuesli);
  attendanceMuesli = digitalRead(IRsensorMuesli); 
  if(checkPiezos==1){
    Serial.println(wertMuesli);
    //Serial.println(wertGoodMuesli);
  }
  
  //-------------------------------call functions ones
  if (attendanceGoodMuesli == LOW) {            // check if the input is LOW    
    if (IRstateGoodMuesli == LOW) {
      IRstateGoodMuesli = HIGH;
    }
  } else {
    if (IRstateGoodMuesli == HIGH){
      IRstateGoodMuesli = LOW;
    }
  }

  //--------------------------------same but for the muesli
  if (attendanceMuesli == LOW) {            // check if the input is LOW    
    if (IRstateMuesli == LOW) {
      IRstateMuesli = HIGH;
    }
  } else {
    if (IRstateMuesli == HIGH){
      IRstateMuesli = LOW;
    }
  }


  //------------------------------------------------------------good Muesli recomendation
  if(IRstateGoodMuesli == HIGH){  //wenn die Hand vor dem Regal ist
    if(showGoodMuesli==0){ //wenn das Regal nicht ausgefahren ist
      if(checkPiezos==0){
         Serial.println("HAND! FÄHRT AUS! (goodMüsli)");
      }
      for(int i=0; i<4; i++){
        stepperGoodMuesli.step(-1000); // halbe Umdrehung      
      }
      showGoodMuesli=1; //regal = ausgefahren
    }
    if(wertGoodMuesli>1000){ //wenn vibration erkannt ---------------------------------------möglicherweise macht es mehr Sinn, dass das Regal einfach immer zurückfährt
      if(productThereGoodMuesli==0){ //wenn das gewählte Produkt nicht mehr da steht
        if(checkPiezos==0){
          Serial.println("Produkt reingestellt (goodMüsli)");
        }
        
        productThereGoodMuesli=1;
        delay(350);
      }
      else if(productThereGoodMuesli==1){ //wenn das gewählte Produkt noch da steht
        if(checkPiezos==0){
          Serial.println("Produkt entnommen (goodMüsli)");
        }
        for(int l=0; l<4; l++){
            if(checkPiezos==0){
              Serial.println("FÄHRT EIN! (goodMüsli)");
            }
            stepperGoodMuesli.step(1000); //halbe Umdrehung 
        }
        productThereGoodMuesli=0; 
        showGoodMuesli=0;  
      }   
    }     
  }

  else if(IRstateGoodMuesli == LOW){// wenn nichts vor dem Regal ist
   if(showGoodMuesli==1){ //wenn Regal ausgefahren
      delay(2000); //wartet 2 Sek
     for(int j=0; j<4; j++){
        stepperGoodMuesli.step(1000); // halbe Umdrehung
        if(checkPiezos==0){
          Serial.println("WEG! FÄHRT EIN! (goodMüsli)");
        }
      }
      showGoodMuesli=0;
    }
  }


  //----------------------------------------------------------------------------------same but for the muesli
  if(IRstateMuesli == HIGH){  //wenn die Hand vor dem Regal ist
    if(showMuesli==0){ //wenn das Regal nicht ausgefahren ist
      if(checkPiezos==0){
        Serial.println("HAND! FÄHRT AUS! (Müsli)");
      }
      for(int i=0; i<4; i++){
        stepperMuesli.step(-1000); // halbe Umdrehung      
      }
      showMuesli=1; //regal = ausgefahren
    }
    if(wertMuesli>1000){ //wenn vibration erkannt ---------------------------------------möglicherweise macht es mehr Sinn, dass das Regal einfach immer zurückfährt
      if(productThereMuesli==0){ //wenn das gewählte Produkt nicht mehr da steht
        if(checkPiezos==0){
          Serial.println("Produkt reingestellt (Müsli)");
        }
        productThereMuesli=1;
        delay(350);
      }
      else if(productThereMuesli==1){ //wenn das gewählte Produkt noch da steht
        if(checkPiezos==0){
          Serial.println("Produkt entnommen (Müsli)");
        }
        for(int l=0; l<4; l++){
          if(checkPiezos==0){
            Serial.println("FÄHRT EIN! (Müsli)");
          }
            stepperMuesli.step(1000); //halbe Umdrehung 
        }
        productThereMuesli=0; 
        showMuesli=0;  
      }   
    }     
  }

  else if(IRstateMuesli == LOW){// wenn nichts vor dem Regal ist
   if(showMuesli==1){ //wenn Regal ausgefahren
      delay(2000); //wartet 2 Sek
      if(checkPiezos==0){
        Serial.println("WEG! FÄHRT EIN! (Müsli)");
      }
     for(int j=0; j<4; j++){
        stepperMuesli.step(1000); // halbe Umdrehung
      }
      showMuesli=0;
    }
  }
  
}
