#include <Servo.h>          // Servo motor library for controlling the servo motor
#include <NewPing.h>         // Ultrasonic sensor library for distance measurement

// Define motor control pins for L298N motor driver
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// LED pins for direction indication
const int ForwardLED = 8;
const int BackwardLED = 9;
const int LeftLED = 11;
const int RightLED = 12;
const int LeftSensorLED = 13;
const int RightSensorLED = 3;

// Ultrasonic sensor pins
#define trig_pin A1 // Trigger pin for ultrasonic sensor
#define echo_pin A2 // Echo pin for ultrasonic sensor
#define maximum_distance 200

// Global variables
boolean goesForward = false;
int distance = 100;
NewPing sonar(trig_pin, echo_pin, maximum_distance); // Create an object to control the ultrasonic sensor
Servo servo_motor; // Servo motor object

void setup() {
  Serial.begin(9600); // Start serial monitor for debugging

  // Set motor pins as outputs
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Set LED pins as outputs
  pinMode(ForwardLED, OUTPUT);
  pinMode(BackwardLED, OUTPUT);
  pinMode(LeftLED, OUTPUT);
  pinMode(RightLED, OUTPUT);
  pinMode(LeftSensorLED, OUTPUT);
  pinMode(RightSensorLED, OUTPUT);

  // Attach and center the servo motor
  servo_motor.attach(10); // Attach the servo to pin 10
  servo_motor.write(115); // Center position
  delay(2000);

  // Initial distance measurement
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 45) { // Obstacle detected within 45 cm
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);

    // Check distances on right and left
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    // Decide direction based on sensor readings
    if (distanceRight >= distanceLeft) {
      turnRight();
    } else {
      turnLeft();
    }
    moveStop();
  } else {
    moveForward();
  }

  distance = readPing(); // Update distance reading
}

int lookRight() {
  digitalWrite(RightSensorLED, HIGH); // Turn on right indicator LED
  delay(200);
  digitalWrite(RightSensorLED, LOW);

  servo_motor.write(50); // Rotate servo to the right
  delay(500);

  int distance = readPing(); // Read distance on the right
  delay(100);

  servo_motor.write(115); // Reset servo to center
  return distance;
}

int lookLeft() {
  digitalWrite(LeftSensorLED, HIGH); // Turn on left indicator LED
  delay(500);
  digitalWrite(LeftSensorLED, LOW);

  servo_motor.write(170); // Rotate servo to the left
  delay(500);

  int distance = readPing(); // Read distance on the left
  delay(100);

  servo_motor.write(115); // Reset servo to center
  return distance;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm(); // Get distance in cm
  if (cm == 0) {
    cm = 250; // Set max value if no object detected
  }
  Serial.print("Distance: ");
  Serial.println(cm);
  return cm;
}

void moveStop() {
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);

  digitalWrite(ForwardLED, LOW);
  digitalWrite(BackwardLED, LOW);
  digitalWrite(LeftLED, LOW);
  digitalWrite(RightLED, LOW);
  digitalWrite(LeftSensorLED, LOW);
  digitalWrite(RightSensorLED, LOW);
}

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);

    digitalWrite(ForwardLED, HIGH); // Turn on forward indicator LED
  }
}

void moveBackward() {
  goesForward = false;
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

  digitalWrite(BackwardLED, HIGH); // Turn on backward indicator LED
}

void turnRight() {
  digitalWrite(RightLED, HIGH); // Turn on right indicator LED
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(250);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void turnLeft() {
  digitalWrite(LeftLED, HIGH); // Turn on left indicator LED
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(250);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
