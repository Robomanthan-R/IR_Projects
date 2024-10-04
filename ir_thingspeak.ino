#include <WiFi.h>
#include <ThingSpeak.h>

// IR sensor pin
const int irPin = 13;  // Pin connected to the IR sensor output

WiFiClient client;
long myChannelNumber = 2656460;
const char myWriteAPIKey[] = "8OSM2N4AMWH1D3U5";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set the IR sensor pin as input
  pinMode(irPin, INPUT);

  // Connect to WiFi
  WiFi.begin("Robomanthan4g", "12345678");

  int timeout = 10000;  // 10-second timeout
  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    delay(200);
    Serial.print("..");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("ESP32 is connected!");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("Failed to connect to WiFi");
  }

  ThingSpeak.begin(client);
}

void loop() {
  // Read the IR sensor's digital output (HIGH or LOW)
  int irValue = digitalRead(irPin);

  // Convert IR sensor reading to a distance-like value (optional)
  // If the sensor detects something, set distance to 0 (detected) or 100 (not detected)
  float distance = (irValue == HIGH) ? 0 : 100;  // Modify based on your IR sensor behavior

  // Display the sensor status
  if (irValue == HIGH) {
    Serial.println("Object detected.");
  } else {
    Serial.println("No object detected.");
  }

  // Send the distance value to ThingSpeak
  ThingSpeak.setField(1, distance);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  // No error message

  // Delay for 2 seconds
  delay(2000);
}
