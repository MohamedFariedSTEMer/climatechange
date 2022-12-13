
  #include <dht.h>
 dht DHT;
  #define DHT11_PIN 2
  #define trigPin 13
  #define echoPin 12
  long duration, distance;

  #include <EEPROM.h>
  #include "GravityTDS.h"
 
  #define TdsSensorPin A0
 GravityTDS gravityTds;
 
  float Temperature = 25,tdsValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);
  gravityTds.setAdcRange(1024);  
  gravityTds.begin(); 

}
void loop() {
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println(" C");
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println(" %");

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("Cm");

  gravityTds.setTemperature(Temperature); 
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue(); 
  Serial.print(tdsValue);
  Serial.println("ppm");
  delay(1000);
}
