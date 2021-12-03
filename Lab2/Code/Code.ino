#define DELAY_MS 700
#define BUTTON1 65
#define BUTTON2 66
#define LEDS_NUMBER 8

const int ledPins[] = {42, 43, 44, 45, 46, 47, 48, 49};

inline void turnOnLedsAlgortihm1(const int& msDelay);
inline void turnOnLedsAlgortihm2(const int& msDelay);
inline void sendAlgorithm1ToSerial(const int& msDelay);
inline void sendAlgorithm2ToSerial(const int& msDelay);

void setup() {
  for (auto& ledPin : ledPins) {
    pinMode(ledPin, OUTPUT);
  }
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      
    case 0xA1:
      turnOnLedsAlgortihm1(DELAY_MS);
      break;

    case 0xB1:
      turnOnLedsAlgortihm2(DELAY_MS);
      break;
    }
  }
  if (!digitalRead(BUTTON1)) {
    sendAlgorithm1ToSerial(DELAY_MS);
    delay(50);
  }
  if (!digitalRead(BUTTON2)) {
    sendAlgorithm2ToSerial(DELAY_MS);
    delay(50);
  }
}

inline void turnOnLedsAlgortihm1(const int& msDelay) {
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
      delay(msDelay);
      digitalWrite(ledPins[ledNum], LOW);
      previousNum = ledNum;
   }
}

inline void turnOnLedsAlgortihm2(const int& msDelay) {
  for (int led = 0; led <= LEDS_NUMBER; led++) {
    digitalWrite(ledPins[led], HIGH);
    delay(msDelay);
    digitalWrite(ledPins[led], LOW);
  }
}

inline void sendAlgorithm1ToSerial(const int& msDelay) {
  Serial.write(0xB1);
}

inline void sendAlgorithm2ToSerial(const int& msDelay) {
  Serial.write(0xA1);
}
