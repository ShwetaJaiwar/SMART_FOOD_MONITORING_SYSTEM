#include "DHT.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTPIN 7 
#define MQ3_PIN A0 
#define LDR_PIN A1
#define DHTTYPE DHT11    

DHT dht(DHTPIN, DHTTYPE);

void setup() {
     dht.begin();
//  Serial.begin(115200);
  lcd.begin(16, 2); 
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  //Serial.println("DHT11 test!");
   lcd.clear();
   lcd.print("TEMPERATURE :");
   lcd.setCursor(0,1);
   delay(1000);
   }

void loop() {
  float t = dht.readTemperature();
lcd.clear();
  lcd.print("TEMPERATURE :");
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.print(" C");
  if(t>31)//If the temperature is above 90 °F, food should not be left out more than 1 hour.
  {
    digitalWrite(8,HIGH);
  } 
  delay(2000); 
  digitalWrite(8,LOW);  
  
  float h = dht.readHumidity();
  lcd.clear();
  lcd.print("HUMIDITY :");
  lcd.setCursor(0,1);
  lcd.print(h);
  lcd.print(" %");
if(h>42)//A few fruits and vegetables require cool temperatures between 40 and 50 Fahrenheit with high humidity for their storage.
  {
    digitalWrite(8,HIGH);
  } 
  delay(2000); 
  digitalWrite(8,LOW);   
  // Read temperature as Celsius
   // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  float hi = dht.computeHeatIndex(f, h);

  lcd.clear();
  lcd.print("Heat index :");
  lcd.setCursor(0,1);
  lcd.print(hi);
  lcd.print(" F");
if(f>83)
  {
    digitalWrite(8,HIGH);
  } 
  delay(2000); 
  digitalWrite(8,LOW); 
  float m=analogRead(MQ3_PIN);
  lcd.clear();
  lcd.print("MQ3 :");
  lcd.setCursor(0,1);
  lcd.print(m);
  lcd.print(" MG/L");
if(m>300)
  {
    digitalWrite(8,HIGH);
  } 
  delay(2000); 
  digitalWrite(8,LOW); 
  float l = analogRead(LDR_PIN);
  lcd.clear();
  lcd.print("LDR :");
  lcd.setCursor(0,1);
  lcd.print(l);
  lcd.print(" L");
if(l>300)
  {
    digitalWrite(8,HIGH);
  } 
  delay(2000); 
  digitalWrite(8,LOW);
  if (isnan(h) || isnan(t) || isnan(f) || isnan(m) || isnan(l)) {
    Serial.println("Failed to read from sensors!");
    return;
  }


  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
  Serial.print("Sensor Value: ");
  Serial.println(m);
  Serial.print("LDR ");
  Serial.println(l);
  
}
