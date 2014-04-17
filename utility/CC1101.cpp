#include "RF_DRIVER.h"

#ifndef __MSP430_HAS_CC1101__

#include <SPI.h>

static uint16_t SS_PIN,GDO0,GDO1,GDO2;

void Initialisation(uint16_t pin){

    SS_PIN = pin;
	pinMode(SS_PIN,OUTPUT);
	SPI.begin();  
	SPI.setBitOrder(MSBFIRST);
	SPI.setClockDivider(SPI_CLOCK_DIV8);
	SPI.setDataMode(SPI_MODE0);
    reset();

}

void reset (void)
{

	Strobe(CC1101_SRES);
	digitalWrite(SS_PIN,HIGH);
	delay(1);
	digitalWrite(SS_PIN, LOW);
	while(READMISOPIN); 
	digitalWrite(SS_PIN,HIGH);
		
}

void configGDOPins(uint16_t GDO0_PIN, uint8_t GDO0_cfg, uint8_t GDO0_INV, uint16_t GDO1_PIN, uint8_t GDO1_cfg, uint8_t GDO1_INV, uint16_t GDO2_PIN, uint8_t GDO2_cfg, uint8_t GDO2_INV, uint8_t DS, uint8_t TEMP_SENSOR_ENABLE)
{

if(GDO0_PIN) pinMode(GDO0_PIN, INPUT);
if(GDO1_PIN) pinMode(GDO1_PIN, INPUT);
if(GDO2_PIN) pinMode(GDO2_PIN, INPUT);

if(TEMP_SENSOR_ENABLE) WriteReg(CC1101_IOCFG0, 128);
else WriteReg(CC1101_IOCFG0, (GDO0_cfg & 0b00111111) | ((GDO0_INV & 1)<<6));

WriteReg(CC1101_IOCFG1, ((DS & 1) << 7 )| (GDO1_cfg & 0b00111111) | ((GDO1_INV & 1)<<6));

WriteReg(CC1101_IOCFG2, (GDO2_cfg & 0b00111111) | ((GDO2_INV & 1)<<6));

}


void WritePATable(uint8_t* PaTab, uint8_t Size){

WriteBurstReg(CC1101_PATABLE,PaTab,Size);

}


void Initialisation(void)
{
    Initialisation(SS_PIN_DEFAULT);
}


void WriteReg(uint8_t addr, uint8_t value)
{
    if (addr<=0x2F || addr >=0x3E) {
	
	digitalWrite(SS_PIN, LOW);
	while(READMISOPIN);
	SPI.transfer(addr);
	SPI.transfer(value);
	digitalWrite(SS_PIN, HIGH);
	}
	
}


void WriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num)
{
	if (addr<=0x2F || addr >=0x3E) {	
    digitalWrite(SS_PIN, LOW);
	
    while(READMISOPIN);
	SPI.transfer(addr | WRITE_BURST);
    for (uint16_t i = 0; i < num; i++)
 	{
        SPI.transfer(buffer[i]);
		delayMicroseconds(1);
    }
	
    digitalWrite(SS_PIN, HIGH);
	
	}
}



uint8_t Strobe(uint8_t strobe)
{
	digitalWrite(SS_PIN, LOW);
	
    while(READMISOPIN);
	uint8_t value=SPI.transfer(strobe);
	
	digitalWrite(SS_PIN, HIGH);
	
	return value;
}



uint8_t ReadReg(uint8_t addr) 
{
    if(addr>=0x30 && addr<=0x3D) addr |= READ_BURST;
	else addr|= READ_SINGLE;
	
	digitalWrite(SS_PIN,LOW);
	
	while(READMISOPIN);
	SPI.transfer(addr);
	uint8_t value=SPI.transfer(0);
	
	digitalWrite(SS_PIN,HIGH);
   
   return value;
}


void ReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num)
{
	uint8_t i;
	
	digitalWrite(SS_PIN, LOW);
	
	while(READMISOPIN);
	
	SPI.transfer(addr | READ_BURST);
	
	for(i=0;i<num;i++)
	{
	    buffer[i]=SPI.transfer(0);
	}
	
	digitalWrite(SS_PIN, HIGH);
}

#endif