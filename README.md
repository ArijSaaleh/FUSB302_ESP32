# USB-C Power Negotiation with ESP32 and FUSB302

## Overview
This project demonstrates how to implement USB-C power negotiation using the ESP32 microcontroller and the FUSB302 USB-C power delivery controller. The code handles initial power negotiation to achieve 3A/5V and dynamically adjusts if the power source's capability changes.

## Hardware Setup
- **ESP32-WROOM-32E**
- **FUSB302** with the following pin configurations:
  - **SCL:** IO22
  - **SDA:** IO21
  - **FUSB_INT:** IO23

## Software Environment
- **Arduino IDE 1.8**

## Functionality

### Setup I2C Communication
The `Wire.begin(SDA_PIN, SCL_PIN)` function sets up the I2C communication on the specified pins.

### Initialize FUSB302
The `initializeFUSB302()` function sets up the FUSB302 with basic settings. This would need to be expanded based on the specific registers and initialization sequence required by the FUSB302.

### Power Negotiation
The `negotiatePower()` function sends a power negotiation request to the FUSB302.

### Interrupt Handling
The `handlePowerChange()` function handles the interrupt for power capability changes and re-negotiates power based on the new capabilities.

