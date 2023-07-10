#include <ESP8266WiFi.h>

const char* ssid = "YourWiFiSSID";      
const char* password = "YourWiFiPassword";  

const int ledPin = D3;
const int pirPin = D1;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  Serial.begin(9600);
  delay(100);
  Serial.println("Cubicle Vacancy Indicator");

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to Wi-Fi network with IP address: ");
  Serial.println(WiFi.localIP());
}

void sendNotification(const char* motionStatus) {
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect("yourwebsite.com", httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  // Send HTTP POST request
  client.print("POST /notification.php HTTP/1.1\r\n");
  client.print("Host: yourwebsite.com\r\n");
  client.print("Content-Type: application/x-www-form-urlencoded\r\n");
  client.print("Content-Length: ");
  client.print(strlen(motionStatus));
  client.print("\r\n\r\n");
  client.print(motionStatus);

  delay(10);
  client.stop();
}

void loop() {
  int motion = digitalRead(pirPin);
  if (motion == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion detected!");
    sendNotification("Motion detected!");
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(100);
}
