#include <Servo.h>

// Setup servo
const int rightServoPin = 10;
Servo rightServo;
int servoPosition = 0;

// Setup ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;

// For calculating distance
long duration;
int distance;

// Filter to check when to start the servo.
int filterCount = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  rightServo.attach(rightServoPin);
  Serial.begin(9600);
  rightServo.write(0);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance= duration*0.034/2;
    
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    // Exception handling.
    if(distance == 0) return;

    // Only increasing when hand is within 10cm
    if (distance < 10 && distance > 0){
      filterCount++;
    }
    
    if(filterCount == 50){
       rightServo.write(0);
       delay(200);
       rightServo.write(80);
       delay(400);
       rightServo.write(160);
       delay(1000);
       rightServo.write(0); // Reset the servo to 0 Degrees
       delay(3000);
       filterCount = 0;
    } 
}
