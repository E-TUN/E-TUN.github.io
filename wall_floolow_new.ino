// Follow Wall - Updated Logic
// Motor pins
int m_r1 = 12;  // Right motor forward
int m_r2 = 13;  // Right motor reverse
int m_l1 = 8;   // Left motor forward
int m_l2 = 9;   // Left motor reverse

int r_speed = 11;
int l_speed = 10;

// Ultrasonic sensor pins
int ecR = 5;
int triR = 6;

int ecF = 3;
int triF = 4;

void setup() {
  pinMode(m_r1, OUTPUT);
  pinMode(m_r2, OUTPUT);
  pinMode(m_l1, OUTPUT);
  pinMode(m_l2, OUTPUT);
  pinMode(r_speed, OUTPUT);
  pinMode(l_speed, OUTPUT);

  pinMode(triF, OUTPUT);
  pinMode(ecF, INPUT);
  pinMode(triR, OUTPUT);
  pinMode(ecR, INPUT);

  Serial.begin(9600);
}

void loop() {
  double distanceR = measureDistance(triR, ecR);
  double distanceF = measureDistance(triF, ecF);

  Serial.print("Forward Distance: ");
  Serial.println(distanceF);
  Serial.print("Right Distance: ");
  Serial.println(distanceR);

  if (distanceF > 20) {
    if (distanceR < 20) {
      Serial.println("Too close, turning left!");
      left(1500);
      left(750); // Slight adjustment
    } else if (distanceR > 40) {
      Serial.println("Too far, turning right!");
      right(3000);
      left(750); // Slight adjustment to move forward
    } else {
      Serial.println("Moving Forward");
      fwd();
    }
  } else {
    Serial.println("Obstacle ahead, stopping");
    stop();
  }
  delay(10);
}

double measureDistance(int trigPinNo, int echoPinNo) {
  digitalWrite(trigPinNo, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinNo, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinNo, LOW);

  long duration = pulseIn(echoPinNo, HIGH, 30000);
  return (duration == 0) ? -1 : duration * 0.034 / 2;
}

void fwd() {
  digitalWrite(m_r1, LOW);
  digitalWrite(m_r2, HIGH);
  analogWrite(r_speed, 95);
  
  digitalWrite(m_l1, LOW);
  digitalWrite(m_l2, HIGH);
  analogWrite(l_speed, 116);
}

void left(int duration) {
  digitalWrite(m_r1, HIGH);
  digitalWrite(m_r2, LOW);
  analogWrite(r_speed, 255);
  
  digitalWrite(m_l1, LOW); // ULTA
  digitalWrite(m_l2, LOW);
  analogWrite(l_speed, 0);
  delay(duration);
  stop();
}

void right(int duration) {
  digitalWrite(m_r1, LOW); // ULTA
  digitalWrite(m_r2, LOW);
  analogWrite(r_speed, 0);
  
  digitalWrite(m_l1, HIGH);
  digitalWrite(m_l2, LOW);
  analogWrite(l_speed, 255);
  delay(duration);
  stop();
}

void stop() {
  digitalWrite(m_r1, LOW);
  digitalWrite(m_r2, LOW);
  digitalWrite(m_l1, LOW);
  digitalWrite(m_l2, LOW);
  analogWrite(r_speed, 0);
  analogWrite(l_speed, 0);
}
