#include "DHT.h"

#define DHTPIN 2
#define RLYPIN 3
#define LEDPIN 13
#define NCPIN 4
#define NOPIN 5
#define RLYIN 6
#define REFPIN 0
//#define NCPIN 8
//#define NOPIN 9
//#define RLYIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

bool evalTemp(double temp){return temp > 23.0;}

bool evalHumidity(double humidity){return humidity > 50;}

bool evalHI(double heatIndex){ return heatIndex > 25.0;}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");
  dht.begin();

  pinMode(LEDPIN,OUTPUT);
  pinMode(RLYPIN,OUTPUT);
}

void startCooler(void){
  digitalWrite(RLYPIN,HIGH);  
}

void endCooler(void){
  digitalWrite(RLYPIN,LOW);  
}

void loop() {
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!"); 
    return;
  }

  float heatIndex = dht.computeHeatIndex(temp, humidity, false);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("  Temperature (C): ");
  Serial.print(temp);
  Serial.print("  Heat Index:");
  Serial.println(heatIndex);

  if(evalTemp(temp) || evalHumidity(humidity) || evalHI(heatIndex)){
    Serial.println("Starting Cooler");
    startCooler();  
  } else {
    Serial.println("Ending Cooler");
    endCooler();  
  }
  delay(2000);
}

//void loop(){
//  Serial.println("Writing HIGH");
//  digitalWrite(RLYPIN,HIGH);
//  delay(5000);
//  Serial.println("Writing LOW");
//  digitalWrite(RLYPIN,LOW);
//  delay(5000);
//}

//void loop(){
//
//    Serial.println("Writing HIGH to NCPIN");
//    digitalWrite(NCPIN,HIGH);
//
//    Serial.print("RLYIN ");
//    Serial.println(analogRead(RLYIN));
//
//    digitalWrite(NCPIN,LOW);
//
//    Serial.println("WRITING HIGH TO NOPIN");
//    digitalWrite(NOPIN,HIGH);
//
//    Serial.print("RLYIN ");
//    Serial.println(analogRead(RLYIN));
//
//    digitalWrite(NOPIN,LOW);
//
//    delay(2000);
//}
//
//void loop(){
//  Serial.println("Turning on Signal to middle");
//  float ref = analogRead(REFPIN);
//  Serial.print("ref : ");
//  Serial.println(ref);
//  
//  digitalWrite(RLYPIN, HIGH);
//
//  //delay(100);
//
//  float ncOut = analogRead(NCPIN);
//  float noOut = analogRead(NOPIN);
//  Serial.print("NC:");
//  Serial.println(ncOut);
//
//  Serial.print("NO: ");
//  Serial.println(noOut);
//
//  delay(5000);
//
//   Serial.println("Turning OFF Signal to middle");
//  digitalWrite(RLYPIN, LOW);
//
//  ref = analogRead(REFPIN);
//  Serial.print("ref: ");
//  Serial.println(ref);
//
//  ncOut = analogRead(NCPIN);
//  noOut = analogRead(NOPIN);
//  Serial.print("NC:");
//  Serial.println(ncOut);
//
//  Serial.print("NO: ");
//  Serial.println(noOut);
//
//  delay(5000);
//}

