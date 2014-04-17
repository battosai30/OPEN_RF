
#include "OPEN_RF.h"

/****************************************************************/

 
// Whitening = false 
// Manchester enable = false 
// Address config = No address check 
// PA ramping = false 
// Deviation = 5.157471 
// Channel number = 0 
// CRC autoflush = false 
// RX filter BW = 58.035714 
// Modulation format = GFSK 
// Base frequency = 432.999817 
// Modulated = true 
// Channel spacing = 49.987793 
// Carrier frequency = 432.999817 
// TX power = 0 
// Sync word qualifier mode = 30/32 sync word bits detected 
// Device address = 0 
// CRC enable = true 
// Data format = Normal mode 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Preamble count = 4 
// Data rate = 1.19948 
// Packet length = 255 
// PA table 

static uint8_t PaTable[8] = {0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

 static const uint8_t RF_USERCONFIG[][2]={
{CC1101_IOCFG2,0x29},
{CC1101_IOCFG1,0x2E},
{CC1101_IOCFG0,0x06},
{CC1101_FIFOTHR,0x47},
{CC1101_SYNC1,0xD3},
{CC1101_SYNC0,0x91},
{CC1101_PKTLEN,0xFF},
{CC1101_PKTCTRL1,0x04},
{CC1101_PKTCTRL0,0x05},
{CC1101_ADDR,0x00},
{CC1101_CHANNR,0x00},
{CC1101_FSCTRL1,0x06},
{CC1101_FSCTRL0,0x00},
{CC1101_FREQ2,0x10},
{CC1101_FREQ1,0xA7},
{CC1101_FREQ0,0x62},
{CC1101_MDMCFG4,0xF5},
{CC1101_MDMCFG3,0x83},
{CC1101_MDMCFG2,0x13},
{CC1101_MDMCFG1,0x20},
{CC1101_MDMCFG0,0xF8},
{CC1101_DEVIATN,0x15},
{CC1101_MCSM2,0x07},
{CC1101_MCSM1,0x30},
{CC1101_MCSM0,0x18},
{CC1101_FOCCFG,0x16},
{CC1101_BSCFG,0x6C},
{CC1101_AGCCTRL2,0x03},
{CC1101_AGCCTRL1,0x40},
{CC1101_AGCCTRL0,0x91},
{CC1101_WOREVT1,0x87},
{CC1101_WOREVT0,0x6B},
{CC1101_WORCTRL,0xFB},
{CC1101_FREND1,0x56},
{CC1101_FREND0,0x10},
{CC1101_FSCAL3,0xE9},
{CC1101_FSCAL2,0x2A},
{CC1101_FSCAL1,0x00},
{CC1101_FSCAL0,0x1F},
{CC1101_RCCTRL1,0x41},
{CC1101_RCCTRL0,0x00},
{CC1101_FSTEST,0x59},
{CC1101_PTEST,0x7F},
{CC1101_AGCTEST,0x3F},
{CC1101_TEST2,0x81},
{CC1101_TEST1,0x35},
{CC1101_TEST0,0x09},
};

/* byte PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};

const byte CC1101_USERCONFIG[][2]={
{CC1101_IOCFG0,0x13},
{CC1101_MCSM0,0x18} ,
{CC1101_FIFOTHR,0x47},
{CC1101_PKTCTRL1,0x06},
{CC1101_PKTCTRL0,0x05},
{CC1101_ADDR,0x30},
{CC1101_FREQ2,0x10},
{CC1101_FREQ1,0xA7},
{CC1101_FREQ0,0x62}, 
{CC1101_MDMCFG4,0xF5},
{CC1101_MDMCFG3,0x83},
{CC1101_MDMCFG2,0x10},
{CC1101_DEVIATN,0x15},
{CC1101_FOCCFG,0x16},
{CC1101_WORCTRL,0xFB},
{CC1101_FSCAL3,0xE9},
{CC1101_FSCAL2,0x2A},
{CC1101_FSCAL1,0x00},
{CC1101_FSCAL0,0x1F},
{CC1101_TEST2,0x81},
{CC1101_TEST1,0x35},
{CC1101_TEST0,0x09}    
};


/* SpiWriteReg(CC1101_FSCTRL1,  0x08);
    SpiWriteReg(CC1101_FSCTRL0,  0x00);
    SpiWriteReg(CC1101_FREQ2,    0x10);
    SpiWriteReg(CC1101_FREQ1,    0xA7);
    SpiWriteReg(CC1101_FREQ0,    0x62);
    SpiWriteReg(CC1101_MDMCFG4,  0x5B);
    SpiWriteReg(CC1101_MDMCFG3,  0xF8);
    SpiWriteReg(CC1101_MDMCFG2,  0x03);
    SpiWriteReg(CC1101_MDMCFG1,  0x22);
    SpiWriteReg(CC1101_MDMCFG0,  0xF8);
    SpiWriteReg(CC1101_CHANNR,   0x00);
    SpiWriteReg(CC1101_DEVIATN,  0x47);
    SpiWriteReg(CC1101_FREND1,   0xB6);
    SpiWriteReg(CC1101_FREND0,   0x10);
    SpiWriteReg(CC1101_MCSM0 ,   0x18);
    SpiWriteReg(CC1101_FOCCFG,   0x1D);
    SpiWriteReg(CC1101_BSCFG,    0x1C);
    SpiWriteReg(CC1101_AGCCTRL2, 0xC7);
	SpiWriteReg(CC1101_AGCCTRL1, 0x00);
    SpiWriteReg(CC1101_AGCCTRL0, 0xB2);
    SpiWriteReg(CC1101_FSCAL3,   0xEA);
	SpiWriteReg(CC1101_FSCAL2,   0x2A);
	SpiWriteReg(CC1101_FSCAL1,   0x00);
    SpiWriteReg(CC1101_FSCAL0,   0x11);
    SpiWriteReg(CC1101_FSTEST,   0x59);
    SpiWriteReg(CC1101_TEST2,    0x81);
    SpiWriteReg(CC1101_TEST1,    0x35);
    SpiWriteReg(CC1101_TEST0,    0x09);
    SpiWriteReg(CC1101_IOCFG2,   0x0B); 	
    SpiWriteReg(CC1101_IOCFG0,   0x06);  	
    SpiWriteReg(CC1101_PKTCTRL1, 0x04);		
											
    SpiWriteReg(CC1101_PKTCTRL0, 0x05);		
    SpiWriteReg(CC1101_ADDR,     0x00);		
    SpiWriteReg(CC1101_PKTLEN,   0x3D); 	
} */
