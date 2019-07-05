int period = 250;
unsigned long time_now = 0;
int vibrate = 23;

void setup() {
  Serial.begin(9600);
  pinMode(vibrate, OUTPUT);
}

void loop() {

  digitalWrite(vibrate,HIGH);  
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }  
    //----------------------------------------------------2222222
  
  digitalWrite(vibrate,HIGH);
  time_now = millis();  
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
     //----------------------------------------------------333333
  
  digitalWrite(vibrate,HIGH);  
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
    // ----------------------------------------------------4444444
  
 digitalWrite(vibrate,HIGH);
  
  time_now = millis();  
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
     //----------------------------------------------------55555555
 digitalWrite(vibrate,LOW);
  
  time_now = millis(); 
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
 //----------------------------------------------------66666666666666
  
  digitalWrite(vibrate,LOW);
  
  time_now = millis();
 while(millis() < time_now + period){
        //wait approx. [period] ms
    }
// ----------------------------------------------------777777777777
  digitalWrite(vibrate,HIGH);
  time_now = millis(); 
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
 //----------------------------------------------------888888888888888888
  
  digitalWrite(vibrate,HIGH);
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }
// ----------------------------------------------------99999999999999999999999
  
  digitalWrite(vibrate,LOW);
  time_now = millis();
  while(millis() < time_now + period){
        //wait approx. [period] ms
    }


}
