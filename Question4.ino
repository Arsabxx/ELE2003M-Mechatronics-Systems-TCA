// Define PWM Pins for RGB Channels
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Define the display duration for each color (in milliseconds)
const int COLOR_DELAY = 1500; 

void setup() {
  // Initialize Serial Monitor for engineering calibration verification
  Serial.begin(9600);
  Serial.println("--- Arduino UNO R3 Rainbow Display Booting ---");

  // Configure RGB pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // 1. Red (#FF0000 -> 255, 0, 0)
  setRGB(255, 0, 0, "Red");
  
  // 2. Orange (#FF7F00 -> 255, 127, 0)
  setRGB(255, 127, 0, "Orange");
  
  // 3. Yellow (#FFFF00 -> 255, 255, 0)
  setRGB(255, 255, 0, "Yellow");
  
  // 4. Green (#00FF00 -> 0, 255, 0)
  setRGB(0, 255, 0, "Green");
  
  // 5. Turquoise (#00CED1 -> 0, 206, 209)
  setRGB(0, 206, 209, "Turquoise");
  
  // 6. Blue (#0000FF -> 0, 0, 255)
  setRGB(0, 0, 255, "Blue");
  
  // 7. Indigo (#4B0082 -> 75, 0, 130)
  setRGB(75, 0, 130, "Indigo");
  
  // 8. Violet (#9400D3 -> 148, 0, 211)
  setRGB(148, 0, 211, "Violet");
  
  // 9. Pink (#FF1493 -> 255, 20, 147)
  setRGB(255, 20, 147, "Pink");
}

/**
 * Helper function to update the PWM duty cycle for the RGB LED channels
 * Note: Assumes a Common Cathode RGB LED configuration.
 */
void setRGB(int rValue, int gValue, int bValue, String colorName) {
  // Write the 8-bit color intensities to the corresponding PWM channels
  analogWrite(RED_PIN, rValue);
  analogWrite(GREEN_PIN, gValue);
  analogWrite(BLUE_PIN, bValue);
  
  // Output status telemetry to the Serial Monitor
  Serial.print("Active Color: ");
  Serial.print(colorName);
  Serial.print(" | R:"); Serial.print(rValue);
  Serial.print(" G:"); Serial.print(gValue);
  Serial.print(" B:"); Serial.println(bValue);
  
  // Maintain the color state for the specified observation window
  delay(COLOR_DELAY);
}
