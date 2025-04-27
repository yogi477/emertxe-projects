#ifndef EEPROM_H
#define EEPROM_H

#define COUNT_ADDR 0x00
void write_internal_eeprom(unsigned char address, unsigned char data); 
unsigned char read_internal_eeprom(unsigned char address);

#endif