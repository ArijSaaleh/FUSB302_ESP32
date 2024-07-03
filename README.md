Setup I2C Communication: The Wire.begin(SDA_PIN, SCL_PIN) sets up the I2C communication on the specified pins.
Initialize FUSB302: The initializeFUSB302() function sets up the FUSB302 with basic settings. This would need to be expanded based on the specific registers and initialization sequence required by the FUSB302.
Power Negotiation: The negotiatePower() function sends a power negotiation request to the FUSB302.
Interrupt Handling: The handlePowerChange() function handles the interrupt for power capability changes and re-negotiates power based on the new capabilities.
