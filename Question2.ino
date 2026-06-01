#include <Servo.h>

// Create a servo object to control the SG90 motor
Servo myServo;

// Define Arduino pins
const int POT_PIN = A0;
const int SERVO_PIN = 5;

// Variables to store analog readings and calculated metrics
int potValue = 0;
int targetAngle = 0;
int previousAngle = 90; // Start at midpoint

void setup() {
  // Initialize Serial Monitor for system validation
  Serial.begin(9600);
  Serial.println("--- Arduino UNO R3 Servo Control System Booting ---");

  // Attach the servo object to digital pin 5
  myServo.attach(SERVO_PIN);
  
  // Move servo to initial center position (90 degrees)
  myServo.write(90);
  delay(500);
}

void loop() {
  // Read analog value from the potentiometer (Range: 0 to 1023)
  potValue = analogRead(POT_PIN);

  // Map the 10-bit ADC value into physical angular displacement (0 to 180 degrees)
  targetAngle = map(potValue, 0, 1023, 0, 180);


  // Write the precise position command to the servo motor
  myServo.write(targetAngle);

  // Determine dynamic directional displacement for diagnostics
  Serial.print("Potentiometer ADC: ");
  Serial.print(potValue);
  Serial.print(" | Target Angular Position: ");
  Serial.print(targetAngle);
  Serial.print(" deg | Status: ");

  if (targetAngle > previousAngle + 1) {
    Serial.println("Moving CLOCKWISE");
  } else if (targetAngle < previousAngle - 1) {
    Serial.println("Moving COUNTER-CLOCKWISE");
  } else {
    Serial.println("POSITION HOLD");
  }

  // Update history buffer for directional calculation
  previousAngle = targetAngle;

  // Small delay to prevent jitter and stabilize mechanical linkage
  delay(50);
}
