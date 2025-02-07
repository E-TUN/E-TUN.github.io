int value = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    value = Serial.read();
    if(value == 1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
  }
}
