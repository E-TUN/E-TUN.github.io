#include <Servo.h>

Servo s1;
double distance;
long duration;
int trigPin = 10;
int echo = 11;
bool isFollowing = false;
String lastDirection = "CENTER"; // Tracks the last direction

// Constants for servo angle ranges
const int SERVO_CENTER = 90; // Center position
const int SERVO_LEFT = 0;    // Far left
const int SERVO_RIGHT = 180; // Far right



// motor code
int a = 2;
int b = 3;
int c = 4;
int d = 5;

void setup() {
  pinMode(echo, INPUT);
  pinMode(trigPin, OUTPUT);

  s1.attach(9);
  s1.write(SERVO_CENTER); // Start with the servo at the center position
  Serial.begin(9600);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
}



void loop() {
  distance = measureDistance();

  if (distance > 15 && distance < 100) {
    followObjectNormal(); // Follow the object at normal speed
  } else if (distance > 100 && distance < 205) {
    moveForwardSlow(); // Move forward slowly
  } else if (distance < 15) {
    stopAndNod(); // Stop and nod
  } else {
    stopRobot(); // Stop in other cases
  }
}

// Function to measure the distance using the ultrasonic sensor
double measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echo, HIGH);
  double distance = duration * 0.034 / 2; // Calculate distance in cm
  return distance;
}

// Function to follow the object at normal speed
void followObjectNormal() {
  if (!isFollowing) {
    Serial.println("Following the object at normal speed...");
    isFollowing = true;
  }

  // Check if the detected object requires turning
  if (lastDirection == "RIGHT") {
    Serial.println("Object on the right. Moving forward after turning right...");
    // Add motor right turn code here
    lastDirection = "FORWARD"; // Update direction to forward
  } else if (lastDirection == "LEFT") {
    Serial.println("Object on the left. Moving forward after turning left...");
    // Add motor left turn code here
    lastDirection = "FORWARD"; // Update direction to forward
  } else {
    Serial.println("Object straight ahead. Moving forward...");
    // Add motor forward code here
  }
}

// Function to move forward slowly
void moveForwardSlow() {
  Serial.println("Object slightly far. Moving forward slowly...");
  nodHead();//repair
  // Add motor forward movement code here for slow speed
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);

  digitalWrite(c,HIGH);
  digitalWrite(d,LOW);
  
}

// Function to stop and nod
void stopAndNod() {
  Serial.println("Stopping and nodding...");
  stopRobot();
  nodHead();
}

// Function to nod the servo head
void nodHead() {
  for (int i = 0; i <= 180; i++) {
    s1.write(i);
    delay(10);
    checkObjectDuringNod(i); // Check for object during nod
  }
  for (int i = 180; i >= 0; i--) {
    s1.write(i);
    delay(10);
    checkObjectDuringNod(i); // Check for object during nod
  }
  // Return to the center after nodding
  s1.write(SERVO_CENTER);
}

// Function to check object during servo motion
void checkObjectDuringNod(int servoAngle) {
  double currentDistance = measureDistance();

  if (currentDistance > 150 && currentDistance < 300) {
    // Adjust direction and motion based on servo angle
    if (servoAngle > SERVO_CENTER && lastDirection != "RIGHT") {
      Serial.println("Object detected on the right. Turning right...");
      s1.write(SERVO_CENTER); // Return to center after detection
      lastDirection = "RIGHT"; // Update direction
      // Add motor right turn code here


    } else if (servoAngle < SERVO_CENTER && lastDirection != "LEFT") {
      Serial.println("Object detected on the left. Turning left...");
      s1.write(SERVO_CENTER); // Return to center after detection
      lastDirection = "LEFT"; // Update direction
      // Add motor left turn code here


    } else if (servoAngle == SERVO_CENTER && lastDirection != "FORWARD") {
      Serial.println("Object detected straight ahead. Moving forward...");
      lastDirection = "FORWARD"; // Update direction
      // Add motor forward code here
      digitalWrite(a,HIGH);
      digitalWrite(b,LOW);

      digitalWrite(c,HIGH);
      digitalWrite(d,LOW);
  

    }
  }
}

// Function to stop the robot
void stopRobot() {
  if (isFollowing) {
    Serial.println("Stopping the robot...");
    isFollowing = false;

    // Add motor stop code here
     digitalWrite(a,LOW);
    digitalWrite(b,LOW);

    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
  
  }
  s1.write(SERVO_CENTER); // Always return the servo to the center after stopping
}
