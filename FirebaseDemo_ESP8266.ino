#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "Redmi K50i"                 // Replace with your Wi-Fi SSID
#define WIFI_PASSWORD "sp#2003jul"         // Replace with your Wi-Fi password
#define FIREBASE_HOST "node-mcu-iot-ad136-default-rtdb.asia-southeast1.firebasedatabase.app"

#define FIREBASE_AUTH ""                      // Leave blank for test mode

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Attempt to write data
  if (Firebase.pushString(firebaseData, "/test", "Hello World")) {
    Serial.println("Data written successfully!");
  } else {
    Serial.print("Error writing data: ");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {}
