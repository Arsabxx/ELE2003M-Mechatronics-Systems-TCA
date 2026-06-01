#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define Analog Input Pins
const int VOLTAGE_PIN_1 = A0; // Measures raw input voltage (V1)
const int VOLTAGE_PIN_2 = A1; // Measures voltage after shunt resistor (V2)

// Known resistance of the shunt resistor in Ohms
const float SHUNT_RESISTANCE = 220.0; 

// Initialize the LCD library with I2C address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize Serial Monitor for engineering calibration data
  Serial.begin(9600);
  Serial.println("--- Arduino UNO R3 Volt/Current Meter Booting ---");
  
  // Initialize the I2C LCD
  lcd.init();
  lcd.backlight();
  
  // Professional boot sequence screen
  lcd.setCursor(0, 0);
  lcd.print("Digital Multimtr");
  lcd.setCursor(0, 1);
  lcd.print("Status: Calibrat");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read raw 10-bit ADC values (0 to 1023)
  int adc1 = analogRead(VOLTAGE_PIN_1);
  int adc2 = analogRead(VOLTAGE_PIN_2);
  
  // Convert ADC values back to actual physical voltage magnitudes (0.0V - 5.0V)
  float v1 = (adc1 * 5.0) / 1023.0;
  float v2 = (adc2 * 5.0) / 1023.0;
  
  // Calculate the voltage drop across the shunt resistor
  float voltageDrop = v1 - v2;
  
  // Avoid negative noise fluctuations due to ADC indexing offsets
  if (voltageDrop < 0.0) {
    voltageDrop = 0.0;
  }
  
  // Apply Ohm's Law (I = V / R) to derive current in Amperes
  float current_A = voltageDrop / SHUNT_RESISTANCE;
  
  // Convert Amperes to Milliamperes (mA) for human-readable precision on LCD
  float current_mA = current_A * 1000.0;
  
  // Output diagnostic telemetry data to Serial Monitor
  Serial.print("V1: "); Serial.print(v1, 2); Serial.print("V | ");
  Serial.print("V2: "); Serial.print(v2, 2); Serial.print("V | ");
  Serial.print("Current: "); Serial.print(current_mA, 1); Serial.println(" mA");
  
  // Update the LCD display screen interface
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(v1, 2); // Display voltage with 2 decimal points precision
  lcd.print(" V   ");
  
  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(current_mA, 1); // Display current with 1 decimal point precision
  lcd.print(" mA  ");
  
  // 300ms delay window to stabilize data refresh on liquid crystal matrix
  delay(300);
}
