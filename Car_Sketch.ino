#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

const int controlPin1 = 3;
const int controlPin2 = 4;
const int leftWheel = 5;
const int rightWheel = 6;
const int ledPin = 13;

void brake(){
  digitalWrite(rightWheel, LOW);
  digitalWrite(leftWheel,LOW);
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);
}
void right(){
  digitalWrite(rightWheel, HIGH);
  digitalWrite(leftWheel,LOW);
}
void left(){
  digitalWrite(rightWheel, LOW);
  digitalWrite(leftWheel,HIGH);
}
void straight(){
  digitalWrite(rightWheel, HIGH);
  digitalWrite(leftWheel,HIGH);
}
void front(){
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, HIGH);
}
void back(){
  digitalWrite(controlPin1, HIGH);
  digitalWrite(controlPin2, LOW);
}
void R_forward(){
  right();
  front();
}
void L_forward(){
  left();
  front();
}
void R_backward(){
  right();
  back();
}
void L_backward(){
  left();
  back();
}
void moveForward(){
  straight();
  front();
}
void moveBackward(){
  straight();
  back();
}
void setup(){
  Serial.begin(9600);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(rightWheel, OUTPUT);
  pinMode(leftWheel, OUTPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  irrecv.enableIRIn();
  brake();
}
void loop(){
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    digitalWrite(ledPin, HIGH);
   if (results.value == 4239130559)
      moveForward();
   if (results.value == 1034620592 || results.value == 1253111734)// 1253111734 is here because someties this shows up on serial monitor
      moveBackward();
  }
  delay(100);
  digitalWrite(ledPin, LOW);
}
