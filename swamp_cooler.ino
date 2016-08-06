#include "DHT.h"

#define DHTPIN 2
#define RLYPIN 3
#define LEDPIN 13
#define DHTTYPE DHT22
#define DELAY 2000

DHT dht(DHTPIN, DHTTYPE);

struct State {
  String status;
  float temp;
  float hum;
  float hi;  
} state;

boolean evalTemp(State state){
  if(state.status == "ON"){
    return state.temp > 23.0;
  } if(state.status == "OFF"){
    return state.temp > 20.0;  
  } else {
    return false;  
  }
}

boolean evalHumidity(State state){
  if(state.status == "ON"){
    return state.hum > 30.0;
  } if(state.status == "OFF"){
  return state.hum > 60.0;  
  } else {
  return false;  
  }
}

boolean evalHI(State state){ 
  if(state.status == "ON"){
    return state.hi > 20.0;
  } if(state.status == "OFF"){
    return state.hi > 25.0;  
  } else {
    return false;  
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");
  dht.begin();

  pinMode(LEDPIN,OUTPUT);
  pinMode(RLYPIN,OUTPUT);
}

void startCooler(){
  digitalWrite(RLYPIN,HIGH);  
}

void endCooler(){
  digitalWrite(RLYPIN,LOW);  
}

int handleCooler(){
  state.hum = dht.readHumidity();
  state.temp = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(state.hum) || isnan(state.temp)) {
    Serial.println("Failed to read from DHT sensor!"); 
    return -1;
  }

  state.hi = dht.computeHeatIndex(state.temp, state.hum, false);

  Serial.print("Humidity: ");
  Serial.print(state.hum);
  Serial.print("  Temperature (C): ");
  Serial.print(state.temp);
  Serial.print("  Heat Index:");
  Serial.println(state.hi);

  if(evalTemp(state) || evalHumidity(state) || evalHI(state)){
    state.status == "OFF" && Serial.println("Starting Cooler");
    startCooler();  
    state.status = "ON";
  } else {
    state.status == "ON" && Serial.println("Ending Cooler");
    endCooler();  
    state.status = "OFF";
  }
  return 0;
 }

void loop() {
  int hasFailed = handleCooler();

  if(hasFailed == 0){
    delay(DELAY);
  }
}

