#include <Servo.h>

Servo s1;

int trigPin = 10;
int echo = 11;

long distance;
bool isFound = false;

// Constants for servo angle ranges
const int SERVO_CENTER = 90; // Center position
const int SERVO_LEFT = 0;    // Far left
const int SERVO_RIGHT = 180; // Far right

void setup() {

  // ultrasonic pins
  pinMode(trigPin, OUTPUT);
  pinMode(echo, INPUT);

  // Right side motor
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  // Left side motor
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  s1.attach(6);

  Serial.begin(9600);
  s1.write(SERVO_CENTER);
}

void loop() {
  distance = measureDistance();
  movFind();
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.034 / 2; // Calculate distance in cm
  return distance;
}

void movFind() {
  if (distance > 20 && distance < 100) {
    Serial.println(distance);
    Serial.println("Moving forward Toward you.... Found you");
    isFound = true;

    //motor Control
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);


    delay(1000);
  } else if (distance < 15) {
    isFound = false;
    Serial.println(distance);
    Serial.println("Stopping and nodding...");

    //motor Control
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);

    nodHead();
    delay(1000);
  } else {
    isFound = false;
    Serial.println(distance);
    Serial.println("Too far... Stopping and nodding...");
    nodHead();

   
    //motor Control
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);


    

    delay(1000);
  }
}
void nodHead() {
  if (!isFound) {
    delay(1000); // Initial delay before nodding starts

    // Sweep from left to right
    for (int angle = SERVO_LEFT; angle <= SERVO_RIGHT; angle += 10) {
      s1.write(angle);
      delay(100); // Allow servo to reach the position

      // Measure distance at the current servo angle
      distance = measureDistance();

      if (distance > 20 && distance < 100) {
        Serial.print("Object found at angle: ");
        Serial.println(angle);

        if (angle < (SERVO_CENTER - 10)) {
          Serial.println("Object found on the left, turning right... 0 - 180");

          //motor Control TURN LEFT
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);

          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);

        } else if (angle > (SERVO_CENTER + 10)) {
          Serial.println("Object found on the right, turning left... 0 - 180");

          //motor Control TURN RIGHT
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);

        } else {
          Serial.println("Object found at the center.");
          Serial.println(distance);

          //motor Control FORWARD
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);

        }

        isFound = true;

        // Allow time for actions like turning before resetting to center
        delay(500);
        break; // Exit the sweep as the object is found
      }
    }

    // Ensure the servo completes the sweep if no object was detected
    if (!isFound) {
      for (int angle = SERVO_RIGHT; angle >= SERVO_LEFT; angle -= 10) {
        s1.write(angle);
        delay(100); // Allow servo to move

        distance = measureDistance();

        if (distance > 20 && distance < 100) {
          Serial.print("Object found at angle: ");
          Serial.println(angle);

          if (angle < (SERVO_CENTER - 10)) {
            Serial.println("Object found on the left, turning left... 180 - 0");

            //motor Control TURN LEFT
            digitalWrite(2, LOW);
            digitalWrite(3, LOW);

            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);



          } else if (angle > (SERVO_CENTER + 10)) {
            Serial.println("Object found on the right, turning right... 180 - 0");

            //motor Control TURN RIGHT
            digitalWrite(2, HIGH);
            digitalWrite(3, LOW);
            
            digitalWrite(4, LOW);
            digitalWrite(5, LOW); 

          } else {
            Serial.println("Object found at the center.");
            //motor Control FORWARD
            digitalWrite(2, HIGH);
            digitalWrite(3, LOW);
            
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);


          }

          isFound = true;

          // Allow time for actions like turning before resetting to center
          delay(1000);
          break; // Exit the sweep as the object is found
        }
      }
    }

    // Reset servo to the center position after the sweep
    s1.write(SERVO_CENTER);
    delay(500); // Allow servo to settle at the center
  }
}
