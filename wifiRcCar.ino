#define HTML_PAGE "<!DOCTYPE html>" \
"<html lang='en'>" \
"<head>" \
"<meta charset='UTF-8'>" \
"<meta name='viewport' content='width=device-width, initial-scale=1.0'>" \
"<title>ESP8266 RC Car Control</title>" \
"<style>" \
"body {font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f9; margin: 0; padding: 20px;}" \
"h1 {color: #333;}" \
"button {background-color: #007bff; color: white; padding: 15px 30px; margin: 10px; border: none; border-radius: 5px; font-size: 16px; cursor: pointer;}" \
"button:active {background-color: #0056b3;}" \
".stop {background-color: #dc3545;}" \
".stop:active {background-color: #a71d2a;}" \
"#slider {margin: 20px 0; width: 80%;}" \
".container {display: flex; flex-direction: column; align-items: center;}" \
".direction-controls {display: flex; justify-content: center; gap: 20px; flex-wrap: wrap;}" \
".direction-controls.vertical {flex-direction: column;}" \
"</style>" \
"</head>" \
"<body>" \
"<h1>ESP8266 RC Car Control</h1>" \
"<div class='container'>" \
"<div class='direction-controls'>" \
"<button onclick='sendCommand(\"forward/on\")'>Forward</button>" \
"<button class='stop' onclick='sendCommand(\"stop\")'>Stop</button>" \
"<button onclick='sendCommand(\"back/on\")'>Back</button>" \
"</div>" \
"<div class='direction-controls'>" \
"<button onclick='sendCommand(\"left/on\")'>Left</button>" \
"<button onclick='sendCommand(\"right/on\")'>Right</button>" \
"</div>" \
"<div>" \
"<label for='slider'>Speed Control</label><br>" \
"<input type='range' id='slider' min='0' max='255' value='128' oninput='setSpeed(this.value)'>" \
"</div>" \
"</div>" \
"<script>" \
"function sendCommand(command) {fetch('/' + command).then(response => console.log('Command sent:', command)).catch(error => console.error('Error:', error));}" \
"function setSpeed(speed) {fetch('/speed/' + speed).then(response => console.log('Speed set to:', speed)).catch(error => console.error('Error:', error));}" \
"</script>" \
"</body>" \
"</html>"


#include<ESP8266WiFi.h>

#define print(x) Serial.println(x)

const char* myHotspotName = "Redmi K50i";
const char* myHotspotPswd = "sp#2003jul";

WiFiServer server(80);

String header;

// var to store state of motors 
String rightMotorD1 =  "off"; // d1
String rightMotorD2 = "off"; // d2

String leftMotorD3 = "off"; // d3
String leftMotorD4 = "off"; // d4


// assigingng gpio
int rm_d1 = 5;
int rm_d2 = 4;

int lm_d3 = 0;
int lm_d4 = 2;

// car motion
bool forwardCar = false;
int speedPin = 14;

void setup(){

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  //right motor
  pinMode(rm_d1, OUTPUT);
  pinMode(rm_d2, OUTPUT);

  // left motor
  pinMode(lm_d3, OUTPUT);
  pinMode(lm_d4, OUTPUT);

  // Setting initial low 
  digitalWrite(rm_d1, LOW);
  digitalWrite(rm_d2, LOW);
  digitalWrite(lm_d3, LOW);
  digitalWrite(lm_d4, LOW);

  // connect to wifi using name, pswd
  print("Connecting to..");
  print(myHotspotName);

  WiFi.begin(myHotspotName, myHotspotPswd);
  print("Atempting to connect to WiFi...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    print(".");
  }
  print("Congrulations... Connect to (sabh i have got this ip) --"); // sabh i have got this ip
  print(WiFi.localIP());
  server.begin();

}
void loop() {
  WiFiClient client = server.available(); // Check if a client has connected

  if (client) {
    print("New Client Connected.");
    String currentLine = "";
    header = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // Read a byte
        Serial.write(c);        // Print it to the Serial Monitor
        header += c;            // Add to header string

        if (c == '\n') { // If the byte is a newline character
          // If the currentLine is empty, it means the HTTP header is complete
          if (currentLine.length() == 0) { // !! request pura ho gaya hai 
            // Send HTTP header
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Check for specific requests and perform actions
            if (header.indexOf("GET /forward/on") >= 0) {
              print("Motor Forward");
              digitalWrite(rm_d1, HIGH);
              digitalWrite(rm_d2, LOW);
              digitalWrite(lm_d3, HIGH);
              digitalWrite(lm_d4, LOW);
              forwardCar = true;
            } else if (header.indexOf("GET /stop") >= 0) {
              print("Motor Stop");
              digitalWrite(rm_d1, LOW);
              digitalWrite(rm_d2, LOW);
              digitalWrite(lm_d3, LOW);
              digitalWrite(lm_d4, LOW);
              forwardCar = false;
            } else if (header.indexOf("GET /back/on") >= 0) {
              print("Motor Backward");
              digitalWrite(rm_d1, LOW);
              digitalWrite(rm_d2, HIGH);
              digitalWrite(lm_d3, LOW);
              digitalWrite(lm_d4, HIGH);
              forwardCar = false;
            } else if (header.indexOf("GET /right/on") >= 0) {
              print("Turn Right");
              digitalWrite(rm_d1, HIGH);
              digitalWrite(rm_d2, LOW);
              digitalWrite(lm_d3, LOW);
              digitalWrite(lm_d4, LOW);
            } else if (header.indexOf("GET /left/on") >= 0) {
              print("Turn Left");
              digitalWrite(rm_d1, LOW);
              digitalWrite(rm_d2, LOW);
              digitalWrite(lm_d3, HIGH);
              digitalWrite(lm_d4, LOW);
            }
            if (header.indexOf("GET /speed/") >= 0) {
              int speedIndex = header.indexOf("GET /speed/") + 11; // Extract speed value
              String speedValue = header.substring(speedIndex, header.indexOf(" ", speedIndex));
              int pwmSpeed = speedValue.toInt(); // Convert to integer
              analogWrite(speedPin, pwmSpeed); // Set PWM to the motor
}


            // Send the HTML page
            client.println(HTML_PAGE);

            // Break out of the loop
            break;
          } else { // If the line is not empty, clear it
            currentLine = "";
          }
        } else if (c != '\r') { // !! abhi request is cooming 
          currentLine += c; // Add characters to the current line
        }
      }
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    print("Client Disconnected.");
  }
}
