
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#include <MQUnifiedsensor.h>


#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 3    


#define DHTTYPE DHT11    




DHT dht(DHTPIN, DHTTYPE);




//MQ 7
int mq7 = A0;
float co;
//MQ 135
int mq135 = A1;
float co2;
//IR
int IR1 = 2;
int IR2 = 4;
//
int LEDR = 5;
int LEDB = 6;
//BUZZER
int buzzer = 9;






RF24 radio(7,8);
const byte Address[6] = "00009";


void setup() {

  pinMode(mq7,INPUT);
  pinMode(mq135,INPUT);
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(LEDR,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(buzzer,OUTPUT);
  dht.begin();

  radio.begin();
  radio.openWritingPipe(Address);
  radio.stopListening();

}

struct datapack{
  // bool toggleSwitch01 ;
  bool shock  ;
  
  float temp ;
  float humidity ;

  float caobon_monoxide ;
  float carbon_dioxide ;
   
};
datapack data;

void loop() {
  // Wait a few seconds between measurements.
  

  co = analogRead(mq7);
  co2 = analogRead(mq135);
   digitalWrite(LEDR, LOW);
   digitalWrite(LEDB,LOW);
   digitalWrite(buzzer, LOW);
  
  if(digitalRead(IR1)==1){
    digitalWrite(LEDR, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  if(co>150||co2>500){
    digitalWrite(LEDR, HIGH);
    digitalWrite(buzzer, HIGH);
  }
  if(digitalRead(IR1)==0){
    digitalWrite(LEDB,HIGH); 
  }

  // data.toggleSwitch01 = digitalRead(toggleSwitch01pin);
  // data.toggleSwitch02 = digitalRead(toggleSwitch02pin);

  data.temp = map(dht.readTemperature(), 0, 1023,0,255);
  data.humidity = map(dht.readHumidity(), 0, 1023,0,255);

  data.caobon_monoxide = map(analogRead(mq7) , 0, 1023,0,255); 
  data.carbon_dioxide = map(analogRead(mq135) , 0, 1023,0,255);
  data.shock = map(digitalRead(IR2) , 0, 1023,0,255);
  
  
  radio.write(&data, sizeof(data));

}
