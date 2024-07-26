#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>

#include <printf.h>

// #include <LiquidCrystal.h>

// int Contrast = 145;
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  

RF24 radio(7,8);
const byte Address[6] = "00009";
int led 2;

// Variables to store value
float t ;
float h ;

float m ;
float d ;
bool shock ;  
 
 void setup()
 {
    // analogWrite(6,Contrast);
    // lcd.begin(20, 4);
    pinMode(led,OUTPUT);

    radio.begin();
    radio.openReadingPipe(0,address);
    radio.startListening();
    serial.begin(9600);
   
  } 

  struct datapack{
  // bool toggleSwitch01 ;
  bool shock ;
  
  float temp ;
  float humidity ;

  float caobon_monoxide ;
  float carbon_dioxide ;  
};
datapack data;

 void loop()
 { 
   while(radio.available()){
    radio.read(&data, sizeof(data));
    t = data.temp;
    h = data.humidity;

    m = data.caobon_monoxide;
    d = data.carbon_dioxide;
    shock = data.shock;    

   }
   digitalWrite(led,LOW);
   if(shock == false){
     digitalWrite(led,HIGH);
   }
   Serial.println(data);

  //  lcd.clear();
  //  lcd.setCursor(0, 0);
  //  lcd.print("SMART HELMET");
   
  //  lcd.setCursor(0, 1);
  //  lcd.print("Temperature=");
  //  lcd.print(t);
  //  lcd.print(" *C\t");
   
  //  lcd.setCursor(0, 2);
  //  lcd.print("Humidity = ");
  //  lcd.print(h);
  //  Serial.print(" %\t");
  //  lcd.print("CO = ");
  //  lcd.print(m);
  //  lcd.print(" ppm\t");
   
  //  lcd.setCursor(3, 3);
  //  lcd.print("CO2 = ");
  //  lcd.print(d);
  //  lcd.print(" ppm\t");
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  // Serial.print(f);
  // Serial.print(" *F\t");
  Serial.print("Carbon Monoxide: ");
  Serial.print(m);
  Serial.print(" PPM\t");
  Serial.print("Carbon Dioxide: ");
  Serial.print(d);
  Serial.print(" PPM\t");

  Serial.println("");

   

   }