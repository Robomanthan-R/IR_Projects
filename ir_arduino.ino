// Define pin for IR sensor
#define irSensorPin 7  // Connect the OUT pin of the IR sensor to digital pin 7
#define ledPin 13      // Built-in LED for indication (optional)

// Variable to store the sensor state
int sensorState = 0;

void setup() {
  // Initialize the serial monitor
  Serial.begin(9600);

  // Set up the IR sensor pin as input
  pinMode(irSensorPin, INPUT);

  // Optional: Set up the built-in LED as output to indicate object detection
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read the sensor state (HIGH or LOW)
  sensorState = digitalRead(irSensorPin);

  // Check if the sensor detects an object
  if (sensorState == LOW) {  // Assuming LOW means an object is detected
    Serial.println("Object detected!");
    
    // Turn on the LED (optional indication)
    digitalWrite(ledPin, HIGH);
  } 
  else {
    Serial.println("No object detected.");
    
    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }

  // Small delay to prevent flooding the serial monitor
  delay(200);
}
