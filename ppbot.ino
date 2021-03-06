// VERSION 0.1.1
#include <SPI.h>
#include <Andee.h>

// interface buttons
AndeeHelper btnForward;
AndeeHelper btnLeft;
AndeeHelper btnRight;
AndeeHelper btnBack;

// constants (3,8,9,11,12,13)
// andee CONFLICT 3 & 8
const int MOTORA = 12;
const int BREAKA = 9;
const int SPEEDA = 3;
const int MOTORB = 13;
const int BREAKB = 8;
const int SPEEDB = 11;

void setup() {
  
  // Init Serial
  Serial.begin(115200);
  
  // Motor A
  pinMode(MOTORA, OUTPUT); // Motor Channel A
  pinMode(BREAKA, OUTPUT); // Break Channel A
  pinMode(SPEEDA, OUTPUT); // Speed Channel A
  
  // Motor B
  pinMode(MOTORB, OUTPUT); // Motor Channel B
  pinMode(BREAKB, OUTPUT); // Break Channel B
  pinMode(SPEEDB, OUTPUT); // Speed Channel B
  
  // BREAK A && B
  digitalWrite(BREAKA, HIGH); // engage the Brake for Channel A
  digitalWrite(BREAKB, HIGH); // engage the Brake for Channel B 
  
  // Initialize Andee
  Andee.begin();
  Andee.clear();
  
  // Push Buttons
  initAndee();
  btnForward.update();
  btnLeft.update();
  btnRight.update();
  btnBack.update();  
  
}

void initAndee() {
  
  btnForward.setId(0);
  btnForward.setType(BUTTON_IN);
  btnForward.setLocation(0,1,FULL);
  btnForward.setTitle("Forward");
  btnForward.requireAck(false);
  
  btnLeft.setId(1);
  btnLeft.setType(BUTTON_IN);
  btnLeft.setLocation(1,1,FULL);
  btnLeft.setTitle("Left");
  btnLeft.requireAck(false);
  
  btnRight.setId(2);
  btnRight.setType(BUTTON_IN);
  btnRight.setLocation(2,1,FULL);
  btnRight.setTitle("Right");
  btnRight.requireAck(false);
  
  btnBack.setId(3);
  btnBack.setType(BUTTON_IN);
  btnBack.setLocation(3,1,FULL);
  btnBack.setTitle("Reverse");
  btnBack.requireAck(false);
  
}

void goForward(int dist) {
  
    // MOTOR A && B
    digitalWrite(MOTORA, LOW); // Establishes forward direction of Channel A
    digitalWrite(MOTORB, LOW); // Establishes forward direction of Channel B
    digitalWrite(BREAKA, LOW); // Disengage the Brake for Channel A
    digitalWrite(BREAKB, LOW); // Disengage the Brake for Channel B
    analogWrite(SPEEDA, 255);  // Spins the motor on Channel A at speed given
    analogWrite(SPEEDB, 255);  // Spins the motor on Channel B at Speed given  
    
    delay(dist);
  
    // STOP A && B
    digitalWrite(BREAKA, HIGH); // engage the Brake for Channel A
    digitalWrite(BREAKB, HIGH); // engage the Brake for Channel B  
}

void goBack(int dist) {
  
    // MOTOR A && B
    digitalWrite(MOTORA, HIGH); // Establishes backward direction of Channel A
    digitalWrite(MOTORB, HIGH); // Establishes backward direction of Channel B
    digitalWrite(BREAKA, LOW); // Disengage the Brake for Channel A
    digitalWrite(BREAKB, LOW); // Disengage the Brake for Channel B
    analogWrite(SPEEDA, 255);  // Spins the motor on Channel A at speed given
    analogWrite(SPEEDB, 255);  // Spins the motor on Channel B at Speed given  
    
    delay(dist);
  
    // STOP A && B
    digitalWrite(BREAKA, HIGH); // engage the Brake for Channel A
    digitalWrite(BREAKB, HIGH); // engage the Brake for Channel B  
}

void loop() {
  
   // FORWARD
   if(btnForward.isPressed()) {
     btnForward.ack();
     goForward(500);
     Serial.println("forward");
   }
   
   // BACKWARD
   if(btnBack.isPressed()) {
     btnBack.ack();
     goBack(500);
     Serial.println("backward");
   }
   
   // LEFT
   if(btnLeft.isPressed()) {
     btnLeft.ack();
     Serial.println("left");
   }
   
    // RIGHT
   if(btnRight.isPressed()) {
     btnRight.ack();
     Serial.println("right");
   }
   
}
