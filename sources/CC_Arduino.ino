/////////////////////////////////////
// Title : CC_Arduino
// Arduino RC Car Connection and Control
// Author : Daeho Han
// 2015.08.15
/////////////////////////////////////

//---------------- Include ---------------------//
#include <SoftwareSerial.h>
//----------------- Define ---------------------//
#define mySerialRX 12
#define mySerialTX 13

//----------------- Global ---------------------//
SoftwareSerial mySerial (mySerialRX, mySerialTX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Connection from Xbee to CC_Arduino
  Serial.println("CC_Arduino Serial test!");

  mySerial.begin(9600); // Connection from CC_Arudino to Motor_Arduino
  mySerial.println("CC_Arduino mySerial test!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
    mySerial.write(Serial.read());
  if (mySerial.available())
    Serial.write(mySerial.read());
}
