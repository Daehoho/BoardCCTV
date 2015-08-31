/////////////////////////////////////
// Title : Motor_Arduino
// Arduino RC Car control Motor
// Author : Daeho Han
// 2015.08.15
/////////////////////////////////////

//-------------------- Include ----------------//
#include <SoftwareSerial.h>
//-------------------- Define ----------------//
#define mySerialRX 2
#define mySerialTX 4

#define DIRA 12 // DC Motor A Direction
#define PWMA 3 // DC Motor A Speed
#define BRAKEA 9 // DC Motor A Brake | HIGH : Brake LOW : Run

#define DIRB 13 // DC Motor B Direction
#define PWMB 11  // DC Motor B Speed
#define BRAKEB 8 // DC Motor B Brake | HIGH : Brake LOW : Run
//-------------------- Global -----------------//
SoftwareSerial mySerial (mySerialRX, mySerialTX);

int carSpeed = 50;
int leftWheelSpeed = 50;
int rightWheelSpeed = 50;
int currentMove = 0; // 0:stop, 1:start
int currentTurn = 0; // 0:straight, 1:left, 2:right
int currentDir = HIGH; // HIGH:forward, LOW:backward

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Connection from PC to CC_Arduino
  Serial.println("Motor_Arduino Serial Test!");
  
  mySerial.begin(9600); // Connection from Motor_Arduino to CC_Arduino
  mySerial.println("Motor_Arduino Serial Test!");

  pinMode (DIRA, OUTPUT);
  pinMode (DIRB, OUTPUT);
  pinMode (BRAKEA, OUTPUT);
  pinMode (BRAKEB, OUTPUT);

  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, HIGH);
  digitalWrite(BRAKEA, HIGH);
  digitalWrite(BRAKEB, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  char input = mySerial.read();

  switch (input) {
    case 'w' :
      speedUp();
      break;
    case 's' :
      speedDown();
      break;
    case 'a' :
      turnLeft();
      break;
    case 'd' :
      turnRight();
      break;
    case 'r' :
      reverse();
      break;
    case ' ' :
      SS_RC();
      break;
    default :
      break;
      
  }
delay(800);  
}


void SS_RC() { //Start and Stop
  Serial.println("SS_RC()");
  if (currentMove == 0) {
    Serial.println("CurrentMove 0");
    digitalWrite(BRAKEA, LOW); digitalWrite(BRAKEB, LOW);  
    digitalWrite(DIRA, currentDir); analogWrite(PWMA, carSpeed);
    digitalWrite(DIRB, currentDir); analogWrite(PWMB, carSpeed);
    currentMove = 1;
  } else {
    Serial.println("CurrentMove 1");
    digitalWrite(BRAKEA, HIGH); digitalWrite(BRAKEB, HIGH);
    currentMove = 0;
  }
  showState(); 
}
void speedUp() {
  Serial.println("Speed UP()");
  if (carSpeed < 250 && carSpeed >= 0)
  {
    carSpeed += 50;
    if (carSpeed == 0)
    {
      digitalWrite(BRAKEA, HIGH); digitalWrite(BRAKEB, HIGH);
    }

    Serial.println("Speed UP!");
    Serial.print("Current Direction : ");

    if (currentDir == HIGH)
    {
      Serial.println("Forward");
    }

    else
    {
      Serial.println("Backward");
    }

    Serial.print("Current Speed : ");
    Serial.println(carSpeed, DEC);
  }

  else if (carSpeed >= 250)
  {
    Serial.println("Max Speed!");
  }

  else
  {
    Serial.println("Incorrect Input!");
  }

  rcRun();
}

void speedDown() {
  Serial.println("SpeedDown()");
  if (carSpeed <= 250 && carSpeed > 0)
  {
    carSpeed -= 50;
    if (carSpeed == 0)
    {
      digitalWrite(BRAKEA, HIGH); digitalWrite(BRAKEB, HIGH);
    }

    Serial.println("Speed Down!");
    Serial.print("Current Direction : ");

    if (currentDir == HIGH)
    {
      Serial.println("Forward");
    }
    else
    {
      Serial.println("Backward");
    }

    Serial.print("Current Speed : ");
    Serial.println(carSpeed, DEC);
  }

  else if (carSpeed <= 0)
  {
    Serial.println("Minimum Speed!");
  }

  else
  {
    Serial.println("Incorrect Input!");
  }

  rcRun();
}

void rcRun() {
  digitalWrite(BRAKEA, LOW); digitalWrite(BRAKEB, LOW);
  digitalWrite(DIRA, currentDir); analogWrite(PWMA, carSpeed);
  digitalWrite(DIRB, currentDir); analogWrite(PWMB, carSpeed);
  showState();
}
void rcTurn() {
  digitalWrite(BRAKEA, LOW); digitalWrite(BRAKEB, LOW);
  digitalWrite(DIRA, currentDir); analogWrite(PWMA, leftWheelSpeed);
  digitalWrite(DIRB, currentDir); analogWrite(PWMB, rightWheelSpeed);
  showState();
}

void reverse() {
  if (currentDir == HIGH) {
    Serial.println("Foward to Backward!");
    currentDir = LOW;
  } else {
    Serial.println("Backward to Forward!");
    currentDir = HIGH;
  }
  rcRun();
}

void turnLeft() {
  if (currentTurn == 2) {
     rightWheelSpeed = carSpeed;
     rightWheelSpeed = rightWheelSpeed * 2;
    // rightWheelSpeed = rightWheelSpeed / 3;
     currentTurn = 0;
  } else if (currentTurn == 0) {
    leftWheelSpeed = carSpeed;
    leftWheelSpeed = leftWheelSpeed / 2;
    //leftWheelSpeed *= 3; 
    currentTurn = 1;
  } else {
    Serial.println ("Already Turn Left!");  
  }
  rcTurn();
  
}

void turnRight() {
   if (currentTurn == 1) {
     leftWheelSpeed = carSpeed;
     leftWheelSpeed = leftWheelSpeed * 2;
     //leftWheelSpeed = leftWheelSpeed / 3;
     currentTurn = 0;
  } else if (currentTurn == 0) {
    rightWheelSpeed = carSpeed;
    rightWheelSpeed = rightWheelSpeed / 2;
    //rightWheelSpeed *= 3;
    currentTurn = 2;
  }
  else
  {
    Serial.println ("Already Turn Right!");  
  }
  rcTurn();
}

void showState() {
  if (currentDir == HIGH) {
    Serial.println("Forward");
  } else {
    Serial.println("Backward");
  }

  if (currentTurn == 2) {
    Serial.println("Turn Right!");
  } else if (currentTurn == 0) {
    Serial.println("Go Straight!");
  } else {
    Serial.println("Turn Left!");
  }
    
  Serial.print("Current Speed: ");
  Serial.println(carSpeed, DEC);
}
