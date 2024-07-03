@Author Arij Saleh

#include <Wire.h>

// Pin definitions
#define SCL_PIN 22
#define SDA_PIN 21
#define FUSB_INT_PIN 23

// FUSB302 I2C address
#define FUSB302_I2C_ADDR 0x22 // Change if different

void setup() {
  Serial.begin(115200);

  // Initialize I2C
  Wire.begin(SDA_PIN, SCL_PIN);
  
  // Initialize FUSB302
  initializeFUSB302();

  // Attach interrupt for dynamic power handling
  pinMode(FUSB_INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FUSB_INT_PIN), handlePowerChange, FALLING);

  // Start initial power negotiation
  negotiatePower(3000, 5000); // 3A/5V
}

void loop() {
  
}

void initializeFUSB302() {
  // Basic initialization for FUSB302
  Wire.beginTransmission(FUSB302_I2C_ADDR);
  //Must configure registers ( see datasheet of FUSB302)
  // Write initialization registers
  Wire.write(0x01); //  register
  Wire.write(0x03); //  value
  Wire.endTransmission();

  Serial.println("FUSB302 initialized");
}

void negotiatePower(uint16_t current_mA, uint16_t voltage_mV) {
  // Send power negotiation request to FUSB302
  Wire.beginTransmission(FUSB302_I2C_ADDR);
  //  register and values for power negotiation
  Wire.write(0x05); //  register for power request
  Wire.write(current_mA / 10); //  value for current
  Wire.write(voltage_mV / 50); //  value for voltage
  Wire.endTransmission();

  Serial.print("Requested power: ");
  Serial.print(current_mA);
  Serial.print("mA, ");
  Serial.print(voltage_mV);
  Serial.println("mV");
}

void handlePowerChange() {
  // Handle power capability change interrupt
  Serial.println("Power source capability changed");

  // Read new power capabilities
  Wire.beginTransmission(FUSB302_I2C_ADDR);
  Wire.write(0x07); // register for reading capabilities
  Wire.endTransmission();
  
  Wire.requestFrom(FUSB302_I2C_ADDR, 2);
  uint16_t maxCurrent = Wire.read() * 10; // conversion
  uint16_t maxVoltage = Wire.read() * 50; //conversion

  Serial.print("New capabilities: ");
  Serial.print(maxCurrent);
  Serial.print("mA, ");
  Serial.print(maxVoltage);
  Serial.println("mV");

  // Negotiate for new power
  negotiatePower(maxCurrent, maxVoltage);
}
