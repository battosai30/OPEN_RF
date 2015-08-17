
#include "OPEN_RF.h"

// CRC enable = true 
// Deviation = 5.157471 
// Address config = No address check 
// Packet length = 255 
// TX power = 0 
// Channel number = 0 
// Carrier frequency = 867.999939 
// RX filter BW = 58.035714 
// Base frequency = 867.999939 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// CRC autoflush = false 
// Device address = 0 
// Preamble count = 4 
// Channel spacing = 199.951172 
// Whitening = false 
// PA ramping = false 
// Data rate = 1.19948 
// Manchester enable = false 
// Modulation format = ASK/OOK 
// Data format = Normal mode 
// Sync word qualifier mode = 30/32 sync word bits detected 
// PA table 
static uint8_t PaTable[8]={0x00,0x8d,0x00,0x00,0x00,0x00,0x00,0x00,};

static const uint8_t RF_USERCONFIG[][2]={
{CC1101_IOCFG2,0x0E},
{CC1101_IOCFG1,0x8},
{CC1101_IOCFG0,0x0},
{CC1101_FIFOTHR,0x47},
{CC1101_SYNC1,0xD3},
{CC1101_SYNC0,0x91},
{CC1101_PKTLEN,0xFF},
{CC1101_PKTCTRL1,0x04},
{CC1101_PKTCTRL0,0x01},
{CC1101_ADDR,0x00},
{CC1101_CHANNR,0x00},
{CC1101_FSCTRL1,0x06},
{CC1101_FSCTRL0,0x00},
{CC1101_FREQ2,0x21},
{CC1101_FREQ1,0x62},
{CC1101_FREQ0,0x76},
{CC1101_MDMCFG4,0xF5},
{CC1101_MDMCFG3,0x83},
{CC1101_MDMCFG2,0x33},
{CC1101_MDMCFG1,0x22},
{CC1101_MDMCFG0,0xF8},
{CC1101_DEVIATN,0x15},
{CC1101_MCSM2,0x07},
{CC1101_MCSM1,0x30},
{CC1101_MCSM0,0x10},
{CC1101_FOCCFG,0x16},
{CC1101_BSCFG,0x6C},
{CC1101_AGCCTRL2,0x03},
{CC1101_AGCCTRL1,0x40},
{CC1101_AGCCTRL0,0x91},
{CC1101_WOREVT1,0x80},
{CC1101_WOREVT0,0x00},
{CC1101_WORCTRL,0xFB},
{CC1101_FREND1,0x56},
{CC1101_FREND0,0x11},
{CC1101_FSCAL3,0xE9},
{CC1101_FSCAL2,0x2A},
{CC1101_FSCAL1,0x00},
{CC1101_FSCAL0,0x1F},
};
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Whitening = false 
// Channel number = 0 
// Manchester enable = false 
// Data rate = 1.19948 
// Modulation format = 2-GFSK 
// Sync word qualifier mode = 30/32 sync word bits detected 
// Packet length = 255 
// Address config = No address check 
// Base frequency = 867.999939 
// TX power = 0 
// RX filter BW = 58.035714 
// Channel spacing = 199.951172 
// Deviation = 5.157471 
// PA ramping = false 
// Modulated = true 
// Carrier frequency = 867.999939 
// Device address = 0 
// CRC autoflush = false 
// CRC enable = true 
// Preamble count = 4 
// Data format = Normal mode 
//static uint8_t PaTable[8]= {0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60};
// static uint8_t PaTable[8]={0x8d,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
// static const uint8_t RF_USERCONFIG[][2]={
// {CC1101_IOCFG2,0x29},
// {CC1101_IOCFG1,0x2E},
// {CC1101_IOCFG0,0x06},
// {CC1101_FIFOTHR,0x47},
// {CC1101_SYNC1,0xD3},
// {CC1101_SYNC0,0x91},
// {CC1101_PKTLEN,0xFF},
// {CC1101_PKTCTRL1,0x04},
// {CC1101_PKTCTRL0,0x05},
// {CC1101_ADDR,0x00},
// {CC1101_CHANNR,0x00},
// {CC1101_FSCTRL1,0x06},
// {CC1101_FSCTRL0,0x00},
// {CC1101_FREQ2,0x21},
// {CC1101_FREQ1,0x62},
// {CC1101_FREQ0,0x76},
// {CC1101_MDMCFG4,0xF5},
// {CC1101_MDMCFG3,0x83},
// {CC1101_MDMCFG2,0x13},
// {CC1101_MDMCFG1,0x22},
// {CC1101_MDMCFG0,0xF8},
// {CC1101_DEVIATN,0x15},
// {CC1101_MCSM2,0x07},
// {CC1101_MCSM1,0x30},
// {CC1101_MCSM0,0x10},
// {CC1101_FOCCFG,0x16},
// {CC1101_BSCFG,0x6C},
// {CC1101_AGCCTRL2,0x03},
// {CC1101_AGCCTRL1,0x40},
// {CC1101_AGCCTRL0,0x91},
// {CC1101_WOREVT1,0x80},
// {CC1101_WOREVT0,0x00},
// {CC1101_WORCTRL,0xFB},
// {CC1101_FREND1,0x56},
// {CC1101_FREND0,0x10},
// {CC1101_FSCAL3,0xE9},
// {CC1101_FSCAL2,0x2A},
// {CC1101_FSCAL1,0x00},
// {CC1101_FSCAL0,0x1F},
// };

// Deviation = 5.157471 
// Preamble count = 4 
// Modulated = true 
// Sync word qualifier mode = 30/32 sync word bits detected 
// Packet length = 255 
// Channel number = 0 
// RX filter BW = 58.035714 
// Address config = No address check 
// Manchester enable = false 
// Modulation format = 2-GFSK 
// Channel spacing = 199.951172 
// PA ramping = false 
// Base frequency = 432.999817 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Whitening = false 
// Data format = Normal mode 
// Data rate = 249.939 
// CRC autoflush = false 
// CRC enable = true 
// Carrier frequency = 432.999817 
// TX power = 10 
// Device address = 0 
// PA table 
/* static uint8_t PaTable[8]= {0xc6,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

static const uint8_t RF_USERCONFIG[][2]={
{CC1101_IOCFG2,0x08},
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
{CC1101_MDMCFG4,0xFD},
{CC1101_MDMCFG3,0x3B},
{CC1101_MDMCFG2,0x13},
{CC1101_MDMCFG1,0x22},
{CC1101_MDMCFG0,0xF8},
{CC1101_DEVIATN,0x15},
{CC1101_MCSM2,0x07},
{CC1101_MCSM1,0x30},
{CC1101_MCSM0,0x10},
{CC1101_FOCCFG,0x16},
{CC1101_BSCFG,0x6C},
{CC1101_AGCCTRL2,0x03},
{CC1101_AGCCTRL1,0x40},
{CC1101_AGCCTRL0,0x91},
{CC1101_WOREVT1,0x80},
{CC1101_WOREVT0,0x00},
{CC1101_WORCTRL,0xFB},
{CC1101_FREND1,0x56},
{CC1101_FREND0,0x10},
{CC1101_FSCAL3,0xEA},
{CC1101_FSCAL2,0x2A},
{CC1101_FSCAL1,0x00},
{CC1101_FSCAL0,0x1F},
{CC1101_TEST2,0x81},
{CC1101_TEST1,0x35},
{CC1101_TEST0,0x09},
}; */



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
//static uint8_t PaTable[8]= {0x0,0x6c,0x00,0x00,0x00,0x00,0x00,0x00};
//static uint8_t PaTable[8]= {0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60};

// static const uint8_t RF_USERCONFIG[][2]={
// {CC1101_IOCFG0,0x06},
// {CC1101_IOCFG2,0x08},
 // {CC1101_FIFOTHR,0x07}, 
// {CC1101_PKTLEN,0x3D},
// {CC1101_SYNC1,0x81},
// {CC1101_SYNC0,0x81},
  // {CC1101_PKTCTRL1,0x06},
 // {CC1101_PKTCTRL0,0x45},
// {CC1101_FSCTRL1,0x08},
// {CC1101_FSCTRL0,0x00},
// {CC1101_FREQ2,0x10},
// {CC1101_FREQ1,0xA7},
// {CC1101_FREQ0,0x62},
 // {CC1101_MDMCFG4,0xCA},
 // {CC1101_MDMCFG3,0x83},
 // {CC1101_MDMCFG2,0x93},
  // {CC1101_MDMCFG1,0x22},
   // {CC1101_MDMCFG0,0xF8},
 // {CC1101_DEVIATN,0x35},
 // {CC1101_MCSM2,0x07},
 // {CC1101_MCSM1,0x30},
 // {CC1101_MCSM0,0x18},
// {CC1101_FOCCFG,0x16},
// {CC1101_BSCFG,0X6C},
// {CC1101_AGCCTRL2,0x43},
// {CC1101_AGCCTRL1,0x40},
// {CC1101_AGCCTRL0,0x91},
// {CC1101_WORCTRL,0xFB},
// {CC1101_FREND0,0x56},
// {CC1101_FREND0,0x10},
// {CC1101_FSCAL3,0xE9},
// {CC1101_FSCAL2,0x2A},
// {CC1101_FSCAL1,0x00},
// {CC1101_FSCAL0,0x1F},
// {CC1101_RCCTRL0,0x41},
// {CC1101_TEST2,0x81},
// {CC1101_TEST1,0x35},
// {CC1101_TEST0,0x09},
// };

