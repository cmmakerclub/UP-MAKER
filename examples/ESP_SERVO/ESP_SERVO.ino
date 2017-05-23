/******************************************************************************
  Project  : NECTEC IoT Camp 2016
  Compiler : Arduino 1.6.7
  Board    : ESPresso Lite V2
  Device   : Motor Drive Module L298N, Gear Motor 1:48
  Author   : Chiang Mai Maker Club
*******************************************************************************/
#include <Servo.h>

Servo espservo;

void setup() {
  Serial.begin(115200);
  espservo.attach(14);
}

void loop() {
  int degree;espservo.write(90); 
//  for (degree = 0; degree <= 180; degree += 1) // goes from 0 degrees to 180 degrees
//  { // in steps of 1 degree
//    espservo.write(degree);              // tell servo to go to position in variable 'pos'
//    Serial.print("SERVO degree = ");
//    Serial.println(degree);
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (degree = 180; degree >= 0; degree -= 1) // goes from 180 degrees to 0 degrees
//  {
//    espservo.write(degree);              // tell servo to go to position in variable 'pos'
//    Serial.print("SERVO degree = ");
//    Serial.println(degree);
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
}

