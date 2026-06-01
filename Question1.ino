#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define Arduino pins for HC-SR04 sensor
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

// Define variables for calculation
long duration;
float distance_cm;

// Initialize the LCD library with I2C address 0x27 and size 16x2
// Note: If 0x27 doesn't work, try 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize Serial Monitor for debugging purposes
  Serial.begin(9600);
  
  // Define pin modes for the ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize the I2C LCD display
  lcd.init();
  lcd.backlight();
  
  // Display a professional welcome screen on boot
  lcd.setCursor(0, 0);
  lcd.print("Distance System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000); 
  lcd.clear();
}

void loop() {
  // Clear the TRIG_PIN by setting it LOW first
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by sending a 10-microsecond HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read the echo pulse duration in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate distance in centimeters
  // Speed of sound = 343 m/s = 0.0343 cm/microsecond
  // Distance = (Time * Speed) / 2 (accounting for round trip)
  distance_cm = (duration * 0.0343) / 2;
  
  // Display results via Serial Monitor for verification
  Serial.print("Measured Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  // Update the LCD display with formatted output
  lcd.setCursor(0, 0);
  lcd.print("Status: Active  ");
  
  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  
  // Handle out-of-range readings gracefully
  if (distance_cm >= 400 || distance_cm <= 2) {
    lcd.print("Out of Range");
  } else {
    lcd.print(distance_cm, 1); // Display distance with 1 decimal place
    lcd.print(" cm        ");   // Extra spaces to clear trailing digits
  }
  
  // Add a small delay to avoid screen flickering and stabilize readings
  delay(500);
}
