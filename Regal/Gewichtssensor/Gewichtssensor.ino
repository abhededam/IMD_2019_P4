
int piezoPin = A0;               

int wert;
int productThere = 1;

void setup() {

 Serial.begin(9600);
}

void loop() {
  Serial.println(wert);
  wert = analogRead(piezoPin);  
  if(wert>30){
    if(productThere==0){
      Serial.print("Produkt reingestellt");
      productThere=1;
      delay(350);
    }
    else if(productThere==1){
      Serial.print("Produkt entnommen");
      productThere=0;
      
    } 
    delay(350);  
  } 
}
