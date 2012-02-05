/*
** ds18b20.cpp
** by Pedro Ferreira
*/


#include "ds18b20.h"

DS18B20::DS18B20(uint8_t pin, uint8_t max_dev) : wire(pin){
  addr_table = (uint8_t*)malloc(max_dev * 8);
}

DS18B20::~DS18B20() {
  free(addr_table);
}

int DS18B20::initialize() {

  ndev = 0;
  uint8_t* ptr;

  while(1) {
    ptr = &addr_table[ndev * 8];
    if (!wire.search(ptr)) {
      wire.reset_search();
      return ndev;
    }

    if (OneWire::crc8(ptr, 7) != ptr[7]) {
      return -1;
    }

    if (ptr[0] != 0x10 && ptr[0] != 0x28) {
      return -1;
    }

    ndev++;
  }

}

void DS18B20::start_conversion(uint8_t dev_n) {
  wire.reset();
  wire.select(addr_table + dev_n * 8);
  wire.write(0x44,1); // start conversion!
  delay(1000);
}

int DS18B20::read_scratchpad(uint8_t dev_n) {
  wire.reset();
  wire.select(addr_table + dev_n * 8);
  wire.write(0xBE); // read scratchpad

  for (uint8_t i = 0; i < 9; i++) {
    data[i] = wire.read();
  }
  return OneWire::crc8(data, 8) == data[8];
}

float DS18B20::read_temperature() {
  return ((data[1] << 8) + data[0]) * 0.0625;
}
