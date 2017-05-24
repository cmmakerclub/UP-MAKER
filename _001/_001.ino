#include <Arduino.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
#include "CMMC_Blink.hpp"
CMMC_Blink blinker;
#define relayPin 15
#define DHTPIN 12
#define inTopic "CMMC/tong"
#define outTopic "CMMC/tong/out"
#define DHTTYPE DHT11

// Update these with values suitable for your network.
const char* ssid = "ESPERT-3020";
const char* password = "espertap";
const char* mqtt_server = "mqtt.cmmc.io";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
DHT dht(DHTPIN, DHTTYPE);
Servo espservo;
void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(relayPin, OUTPUT);
  Serial.begin(115200);
  pinMode(12, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  espservo.attach(14);
  dht.begin();
  blinker.init();
  blinker.blink(200, LED_BUILTIN);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  blinker.blink(50, LED_BUILTIN);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
    payload[length] = '\0';
  String stringOne =  String((char*)payload); 
  Serial.println(stringOne);
  if(stringOne.toInt() != 0){
    espservo.write(stringOne.toInt());
  }else{
      if (stringOne  == "ON") {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    digitalWrite(relayPin, HIGH);
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else if(stringOne  == "OFF") {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    digitalWrite(relayPin, LOW);
  }
  }
  // Switch on the LED if an 1 was received as first character
//  if ((char)payload[0] == 'L'){
//  if ((char)payload[1] == '1') {
//    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//    digitalWrite(relayPin, HIGH);
//    // but actually the LED is on; this is because
//    // it is acive low on the ESP-01)
//  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//    digitalWrite(relayPin, LOW);
//  }
//  }
//  if ((char)payload[0] == 'S'){
//    
//  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    String clientId = String(ESP.getChipId());
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      blinker.detach(HIGH);
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
boolean st_b = 1;
void loop() {

  if (!client.connected()) {
    blinker.blink(50, LED_BUILTIN);
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    ++value;
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
     if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }else{
    Serial.print(h);
    Serial.print(" ");
    Serial.print(t);
    Serial.print(" ");
    Serial.println();
    client.publish(outTopic"/temp", String(t,2).c_str());
    client.publish(outTopic"/humid", String(h,2).c_str());
  }
  }
  
  if(digitalRead(5)==0&&st_b==1){
    client.publish(outTopic"/bo","ปุ่มกำลังถูกกด");
  }
  st_b = digitalRead(5);
}

