const int ledPin = A0; 
const int buttonPin = 49;
int ledPins[8];

void setup() {
  for (int i = 0; i < 8; i++){
      ledPins[i] = ledPin;
      ledPins[i] += i;
      pinMode(ledPins[i], OUTPUT);
  }
}

void mainAlgorithm(){
   int previousNum;
   int i;
  
   for( i = 0; i < 8; i++ ){
      int ledNum;
      if(i == 0) {
          ledNum = i;
          
      } else {
          if(i % 2 != 0) {
              ledNum = previousNum + 8 - i;
          } else {
              ledNum = previousNum - 8 + i;
          }
          
      }
      
      digitalWrite(ledPins[ledNum], HIGH);
      delay(700);
      digitalWrite(ledPins[ledNum], LOW);
      previousNum = ledNum;
   }
}

void loop() {
  if (!digitalRead(buttonPin)) {
    mainAlgorithm();
  }
}
