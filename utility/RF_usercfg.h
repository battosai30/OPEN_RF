
#include "OPEN_RF.h"

/****************************************************************/
// CRC enable = true 
// Manchester enable = false 
// Data format = Normal mode 
// Modulation format = ASK/OOK 
// Channel spacing = 199.951172 
// Preamble count = 4 
// TX power = 0 
// Channel number = 0 
// Carrier frequency = 432.999817 
// Whitening = false 
// Data rate = 19.9852 
// Address config = No address check 
// Base frequency = 432.999817 
// Packet length = 62 
// Deviation = 5.157471 
// PA ramping = false 
// Device address = 0 
// Sync word qualifier mode = 30/32 sync word bits detected 
// CRC autoflush = false 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// RX filter BW = 162.500000 
// PA table 

static uint8_t PaTable[8]= {0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60};

static const uint8_t RF_USERCONFIG[][2]={
{CC1101_IOCFG0,0x06},
{CC1101_IOCFG2,0x00},
{CC1101_FIFOTHR,0x0},
{CC1101_PKTLEN,0x3E},
{CC1101_SYNC1,0x81},
{CC1101_SYNC0,0x81},
{CC1101_PKTCTRL0,0x05},
{CC1101_FSCTRL1,0x06},
{CC1101_FREQ2,0x10},
{CC1101_FREQ1,0xA7},
{CC1101_FREQ0,0x62},
{CC1101_MDMCFG4,0x99},
{CC1101_MDMCFG3,0x93},
{CC1101_MDMCFG2,0x33},
{CC1101_DEVIATN,0x15},
{CC1101_MCSM0,0x18},
{CC1101_FOCCFG,0x16},
{CC1101_WORCTRL,0xFB},
{CC1101_FREND0,0x11},
{CC1101_FSCAL3,0xE9},
{CC1101_FSCAL2,0x2A},
{CC1101_FSCAL1,0x00},
{CC1101_FSCAL0,0x1F},
{CC1101_TEST2,0x81},
{CC1101_TEST1,0x35},
{CC1101_TEST0,0x09},
};

