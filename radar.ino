#include <Servo.h>  // Include the Servo library

// Pin definitions for Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;
#define servoPin 6

// Create a servo object
Servo myServo;

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);
  
  // Set the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach the servo motor to pin 6
  myServo.attach(servoPin);
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 1) {
    myServo.write(angle);  // Move the servo to the current angle
    delay(20);  // Wait for the servo to reach the position
    int distance = getDistance();  // Get the distance from the ultrasonic sensor

    // Print the angle and distance to the Serial Monitor
    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
    delay(100);  // Add a delay between readings
  }

  // Sweep the servo back from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 1) {
    myServo.write(angle);
    delay(20);
    int distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);


    delay(100);
  }
}

// Function to calculate the distance using the ultrasonic sensor
int getDistance() {
  long duration;
  int distance;

  // Clear the trigPin by setting it LOW for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, return the duration in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  return distance;  // Return the distance in cm
}
