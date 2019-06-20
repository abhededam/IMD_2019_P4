
int piezoPin = A0;               

int wert = 0;

void setup() {

 Serial.begin(9600);
}

void loop() {
  Serial.println(wert);
  wert = analogRead(piezoPin);  
  if(wert==0){
    Serial.print("Produkt entnommen");
  }
}
