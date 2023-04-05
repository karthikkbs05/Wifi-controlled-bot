#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Replace with your app's IP address and port number
IPAddress server(192, 168, 0, 100);
int port = 80;

// Define the pins for the motor driver
const int motor1Pin1 = 5;
const int motor1Pin2 = 4;
const int motor2Pin1 = 0;
const int motor2Pin2 = 2;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Set the motor pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Debugging: print IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if the client is connected to the server
  if (!client.connected()) {
    // Connect to the server
    Serial.print("Connecting to server ");
    Serial.print(server);
    Serial.print(":");
    Serial.println(port);
    if (client.connect(server, port)) {
      Serial.println("Connected to server");
    } else {
      Serial.println("Connection failed");
    }
  }
  
  // Check if data is available from the client
  if (client.available()) {
    // Read data from the client
    String data = client.readStringUntil('\n');
    
    // Debugging: print received data
    Serial.println(data);
    
    // Process received data
    if (data == "F") {
      // Move forward
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(1000);  // Move for one second
      // Stop
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    } else if (data == "B") {
      // Move backward
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      delay(1000);  // Move for one second
      // Stop
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    } else if (data == "L") {
      // Turn left
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(500);  // Turn for half a second
      // Stop
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
