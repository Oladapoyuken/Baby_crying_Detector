#include <VirtualWire.h>
#include <SoftwareSerial.h>

#define buzz 8

byte message[VW_MAX_MESSAGE_LEN];
byte msgLength = VW_MAX_MESSAGE_LEN;

SoftwareSerial SIM800L(2, 3);
String number = "+2348038110422";//+2348161183988";
int _timeout;
String _buffer;

bool state = true;
int val = 0; 
void setup() {
  Serial.begin(9600);
  SIM800L.begin(9600);

  _buffer.reserve(50);
  
  pinMode(buzz, OUTPUT);
  vw_setup(2000);
  vw_rx_start();
  
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
  delay(15000);

  callNumber();
  digitalWrite(buzz, HIGH);
  delay(500);
  digitalWrite(buzz, LOW);
  
}

void callNumber() {
  SIM800L.print (F("ATD"));
  SIM800L.print (number);
  SIM800L.print (F(";\r\n"));
  delay(10000);
  SIM800L.println("AT+CMGF=1");
}

String _readSerial() 
{
  _timeout = 0;
  while  (!SIM800L.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  
  if (SIM800L.available()) 
  {
    return SIM800L.readString();
  }
}



void loop() {


  if(vw_get_message(message, &msgLength)){
    for(int i = 0; i < msgLength; i++){
      int x = message[i]-'0'; //ASCII code
      val = x;
      Serial.println(val);
      if(x == 2){
        digitalWrite(buzz, HIGH);  
        callNumber();
      }
      else{
        digitalWrite(buzz, LOW);
        }
    }
    delay(100);
    
  }
}
