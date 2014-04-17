#ifndef _RF_DRIVER_H
#define _RF_DRIVER_H

#include "OPEN_RF.h"
		
uint8_t ReadReg(uint8_t addr); // Read a single register
void Initialisation(void); // module initialisation
void Initialisation(uint16_t pin); // module initialisation with a different Slave Select pin
void configGDOPins(uint16_t GDO0_PIN, uint8_t GDO0_cfg, uint8_t GDO0_INV, uint16_t GDO1_PIN, uint8_t GDO1_cfg, uint8_t GDO1_INV, uint16_t GDO2_PIN, uint8_t GDO2_cfg, uint8_t GDO2_INV, uint8_t DS, uint8_t TEMP_SENSOR_ENABLE); // configuration of CC1101's I/O pins
void reset (void); // reset module
void WriteReg(uint8_t addr, uint8_t value); // write a single register
void WriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num); // write consecutive registers
uint8_t Strobe(uint8_t strobe); // send a strobe command
void ReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num); // read several consecutive registers
void WritePATable(uint8_t* PaTab, uint8_t Size);		
		
#endif
