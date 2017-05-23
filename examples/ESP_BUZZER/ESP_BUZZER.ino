/******************************************************************************
  Project  : NECTEC IoT Camp 2016
  Compiler : Arduino 1.6.7
  Board    : ESPresso Lite V2
  Device   : 5 Volt Active Buzzer
  Author   : Chiang Mai Maker Club
*******************************************************************************/
#define BUZZER 0

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  delay(500);
}
