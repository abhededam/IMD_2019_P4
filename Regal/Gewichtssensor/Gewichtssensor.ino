
int piezoPin = 0;               

int wert = 0;

void setup() {

 Serial.begin(9600);
}

void loop() {
  
  wert = analogRead(piezoPin);  
  Serial.println(wert);

}
