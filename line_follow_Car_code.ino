// black -- 0
// white -- 1

#define print(x) Serial.println(x);
const int r_s = 3; // Right sensor pin
const int l_s = 5; // Left sensor pin

byte lsValue, rsValue;
// Motor pins
int m_r1 = 6;  // Right motor forward
int m_r2 = 7;  // Right motor reverse

int m_l1 = 12; // Left motor forward
int m_l2 = 11; // Left motor reverse

int r_speed = 9;
int l_speed = 10;

void setup() {
  // Initialize sensors
  pinMode(r_s, INPUT);
  pinMode(l_s, INPUT);

  // Initialize motors
  pinMode(m_r1, OUTPUT);
  pinMode(m_r2, OUTPUT);

  pinMode(m_l1, OUTPUT);
  pinMode(m_l2, OUTPUT);

  // speed controol 
  pinMode(r_speed, OUTPUT);
  pinMode(l_speed, OUTPUT);

  analogWrite(9, 80); // Right motor speed (0-255)
  analogWrite(10, 80); // Left motor speed (0-255)


  Serial.begin(9600);
}

void loop() {

  
  // Read sensor values
  lsValue = digitalRead(l_s);
  rsValue = digitalRead(r_s);

  // Right motor control (depends on left sensor)
  if (lsValue == 0) {
    print("Left sensor black - Stop right motor");
    digitalWrite(m_r1, HIGH);
    digitalWrite(m_r2, LOW); // REVERSE motor
    analogWrite(l_speed,100);
  } else {
    print("Left sensor white - Run right motor");
    digitalWrite(m_r1, LOW); // Move forward
    digitalWrite(m_r2, HIGH);
    analogWrite(r_speed, 80); // Right motor speed (0-255)
    

  }

  // Left motor control (depends on right sensor)
  if (rsValue == 0) {
    print("Right sensor black - Stop left motor");
    digitalWrite(m_l1, HIGH);
    digitalWrite(m_l2, LOW); // REVERSE motor
    analogWrite(r_speed, 100);
  } else {
    print("Right sensor white - Run left motor");
    digitalWrite(m_l1, LOW); // Move forward
    digitalWrite(m_l2, HIGH);
    analogWrite(l_speed, 80); // Left motor speed (0-255)

  }
}