/*
** ds18b20.h
** by Pedro Ferreira
*/

#ifndef   	DS18B20_H_
# define   	DS18B20_H_

#include "OneWire.h"

class DS18B20 {
 private:
  OneWire wire;
  uint8_t* addr_table;
  uint8_t data[9];
  uint8_t ndev;
 public:
  DS18B20(uint8_t, uint8_t);
  ~DS18B20();
  int initialize();
  void start_conversion(uint8_t);
  int read_scratchpad(uint8_t);
  float read_temperature();
};

#endif 	    /* !DS18B20_H_ */
