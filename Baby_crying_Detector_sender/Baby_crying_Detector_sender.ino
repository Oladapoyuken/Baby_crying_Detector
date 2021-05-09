#include <VirtualWire.h>

#define music 4

#define cry A0
int initial_env = 0;
int global = 0;
int counter = 0;
bool state = true;
bool check = false;
int timer = 0;

void setup() {
  
  pinMode(cry,INPUT);
  pinMode(music,OUTPUT);
  vw_setup(2000);

  Serial.begin(9600);
  
}

void loop() {

//  send("2");
//  delay(1000);
  
//  
  delay(200);
  int val = analogRead(cry);
  state = true; 
  global = 0;
  if(val > 600){
    while(state == true){
      delay(500);
      counter++;
      int temp = analogRead(cry);
      if(temp > 550){
        
        global++;
      }
      if(global > 2){
        if(check == true){
          send("2");
          check = false;
          Serial.println("Baby is crying");
        }
        global = 0;
        counter = 0;
        digitalWrite(music, HIGH);
        delay(40000);
        digitalWrite(music, LOW);
        Serial.println("Song is playing");
        check = true;
      }
      if(counter > 5){
        Serial.println("Time completed");
        counter = 0;
        state = false;
        break;
      }
    }
    Serial.println(val);
  }
  
}

void send (char *message){
  
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  delay(100);
}
