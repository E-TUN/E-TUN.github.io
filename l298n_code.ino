 

void setup() {
  // put your setup code here, to run once:

  //4 5,7 8
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);

  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

  Serial.begin(9600);

  // START Set
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);

  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);


}

void loop() {

//   Serial.println("Starting ... in 3 sec");

//   delay(3000);
//   // forward
//   digitalWrite(2,HIGH);
//   digitalWrite(3,LOW);

//   digitalWrite(4,HIGH);
//   digitalWrite(5,LOW);

//   delay(3000);

//   Serial.println("Turning Right ...");
//   //right
//   digitalWrite(2,HIGH);
//   digitalWrite(3,LOW);

//   digitalWrite(4,LOW);
//   digitalWrite(5,LOW);

//   delay(3000);


//   Serial.println("Turning left ...");

//   //left
//   digitalWrite(2,LOW);
//   digitalWrite(3,LOW);

//   digitalWrite(4,HIGH);
//   digitalWrite(5,LOW);

//   delay(3000);


//   Serial.println("Stopping ...");
//   //stop
//   digitalWrite(2,LOW);
//   digitalWrite(3,LOW);

//   digitalWrite(4,LOW);
//   digitalWrite(5,LOW);

}
