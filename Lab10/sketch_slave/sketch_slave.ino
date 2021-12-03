int sensorPin = A0;
#define _1 0x1A
#define _2 0x2A
#define _3 0x3A
#define _4 0x4A
#define _5 0x5A
#define _6 0x6A
#define _7 0x7A
#define _8 0x8A
#define _9 0x9A
#define _0 0x0A
#define _DOT 0xFF

const uint32_t TRHSTEP   = 5000UL;
byte test;
float tempD;

uint16_t rawData;
float temperature;
float humidity;
float dewpoint;
bool isAddress = true;
byte address;
bool isCommand = false;
byte command;
byte data;


unsigned long trhMillis = 0;            
unsigned long blinkMillis = 0;
float temperatureC =0;
void setWriteModeRS485() {
  PORTD |= 1 << PD2;
  ADCSRA |= 1<<ADSC;
  delay(1);
}
float arr[]={30.00,32.00,28.00,25.00};
int inc=0;                           
ISR(USART_TX_vect) {
 
  PORTD &= ~(1 << PD2); 
}
ISR(ADC_vect)
{
char Sbuf[6];
float Vin = ADC*5.0/1024;
temperatureC = (Vin - 0.5) * 100 ; 
}
int raw_temp;
float temp;

   String  stringOne;
byte message[]={};
  String dataT[]={};
int writeData(float temp) {
  
 
 stringOne = String(temp);
  
    byte message[stringOne.length()+2] = {};
     for(int i=0;i<stringOne.length();i++){
  if(stringOne[i]=='0'){
       
        message[i]=_0;
}
     if(stringOne[i]=='1'){
     
        message[i]=_1;
 }
     if(stringOne[i]=='2'){
       message[i]=_2;
    }
     if(stringOne[i]=='3'){
     message[i]=_3;
   }
     if(stringOne[i]=='4'){
        message[i]=_4;
   }
     if(stringOne[i]=='5'){
       message[i]=_5;
    }
     if(stringOne[i]=='6'){
      message[i]=_6;
    }
     if(stringOne[i]=='7'){
       message[i]=_7;
    }
     if(stringOne[i]=='8'){
      
       message[i]=_8;
  }
     if(stringOne[i]=='9'){
       message[i]=_9;
   }
     if(stringOne[i]=='.'){
      
       message[i]=_DOT;
  
    }
    
}

 
  
  
  
  

  byte reflected[stringOne.length()];
  for (int i = 0; i < stringOne.length(); i++) {
    reflected[i] = ReverseByte(message[i]);
  }
  message[5] = 0x00;
  message[6] =0x00;
  unsigned short checkSum = Compute_CRC8(reflected);
  byte firstByteOfCheckSum = (checkSum >> 8) & 0xFF;
  byte secondByteOfCheckSum = checkSum & 0xFF;

  message[stringOne.length()] = firstByteOfCheckSum;
  message[stringOne.length()+1] = secondByteOfCheckSum;

for(int sendMess=0;sendMess<7;sendMess++){
 Serial.write(message[sendMess]);
}
}


void setup() {

  delay(1000);

   

  DDRD = 0b00000111;
  PORTD = 0b11111000;

  Serial.begin(9600, SERIAL_8N1);
  UCSR0B |= (1 << UCSZ02) | (1 << TXCIE0);
  UCSR0A |= (1 << MPCM0);

  delay(1);

  address = 0x7B;
DDRC = 0x00;
PORTC = 0b11111110;
ADMUX = 1<<REFS0;
ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1);
pinMode(A0,INPUT);
}



void loop() {
         

        
         if (Serial.available()) {
              byte inByte = Serial.read();
              if (isAddress) {
               if (address == inByte) {
            isAddress = false;
          isCommand = true;
          UCSR0A &= ~(1 << MPCM0);
        }
    } else if (isCommand) {
      command = inByte;
      isCommand = false;
      if (command = 0xB1) {
        if(inc==4){
          inc=0;}

          isAddress = true;
          setWriteModeRS485();
          
          writeData(arr[inc]);
          inc++;
     
        }
    }
  }


  
}




unsigned short Compute_CRC8(byte* bytes) {
 const unsigned short generator = 0xD5;
  unsigned short crc = 0x00;

  for (int b = 0; b < 5; b++) {
    crc ^= (unsigned short) (bytes[b] << 8);

    for (int i = 0; i < 8; i++) {
      if ((crc & 0x8000) != 0) {
        crc = (unsigned short) ((crc << 1) ^ generator);
      } else {
        crc <<= 1;
      }
    }
  }
  unsigned short myNewResult = Reflect8(crc);
  return myNewResult;
}


unsigned short Reflect8(unsigned short val) {
  unsigned short resVal = 0;
  for (int i = 0; i < 16; i++) {
    if ((val & (1 << i)) != 0) {
      resVal |= (unsigned short)(1 << (15 - i));
    }
  }
  return resVal;
}

byte ReverseByte(byte b) {
  int a = 0;
  for (int i = 0; i < 8; i++) {
    if ((b & (1 << i)) != 0) {
      a |= 1 << (7 - i);
    }
  }
  return (byte) a;
}

int CombineBytes(byte b1, byte b2) {
  int combined = b1 << 8 | b2;
  return combined;
}
