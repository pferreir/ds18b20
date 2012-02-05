#include "ds18b20.h"

// Supports up to 8 devices connected to the OneWire bus
DS18B20 ds18(10, 8);

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  // initialize() scans the bus for sensors
  ds18.initialize();
  // ask for a temperature conversion from sensor 0
  ds18.start_conversion(0);
  // read the scratchpad on the other side
  ds18.read_scratchpad(0);
  // print the temperature in celsius
  Serial.println(ds18.read_temperature());
}
