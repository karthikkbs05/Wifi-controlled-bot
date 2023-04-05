#include <ESP8266WiFi.h>
int D0 = 1, D1= 3, D2= 4,D3=5;
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your app's IP address and port number
IPAddress server(192, 168, 0, 100);
int port = 80;

WiFiClient client;

// Motor driver pins
#define IN1 D0
#define IN2 D1
#define IN3 D2
#define IN4 D3

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  
  // Set motor driver pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Check if the client is connected to the server
  if (!client.connected()) {
    // Connect to the server
    if (client.connect(server, port)) {
    } else {
    }
  }
  
  // Check if data is available from the client
  if (client.available()) {
    // Read data from the client
    String data = client.readStringUntil('\n');
    
    // Process received data
    if (data == "F") {
      // Move forward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (data == "B") {
      // Move backward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (data == "L") {
      // Turn left
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (data == "R") {
      // Turn right
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (data == "S") {
      // Stop
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}

