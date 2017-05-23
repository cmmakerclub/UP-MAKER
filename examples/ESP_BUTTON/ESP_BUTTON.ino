/******************************************************************************
* Project  : NECTEC IoT Camp 2016                                             
* Compiler : Arduino 1.6.7                                                    
* Board    : ESPresso Lite V2                                                 
* Device   : Button on board espresso                                                           
* Author   : Chiang Mai Maker Club                                            
*******************************************************************************/

#define BUTTON1 0
#define BUTTON2 13

byte b1Value, b2Value;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
}

void loop() {
  b1Value = digitalRead(BUTTON1);
  b2Value = digitalRead(BUTTON2);

  if (b1Value == LOW) {
    delay(200);
    Serial.println("BUTTON 1 : Press");
  } 
  if (b2Value == LOW) {
    delay(200);
    Serial.println("BUTTON 2 : Press");
  } 
}
