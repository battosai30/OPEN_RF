/*
	OPEN_CC1101.h - CC1101 module library - V1.0
	
  	Author: B@tto battomicro.wordpress.com
	
	This library is designed to use CC1101/CC1100 module on Arduino and Energia platforms.
	
	It's an updated version of Elechouse's CC1101 library : http://www.elechouse.com/elechouse/index.php?main_page=product_info&products_id=802
	
	See readme.txt for more informations and how to use this library
	
*/

#ifndef OPEN_CC1101_h
#define OPEN_CC1101_h

#include <msp430.h>

#include <Arduino.h> 


#include "utility/RF_DEFINES.h"
#include "utility/RF_usercfg.h"
#include "utility/RF_DRIVER.h"


class OPEN_RF
{
	private:

	uint8_t _AppendStatus;
	uint8_t _AdressCheck;
	uint8_t _LengthConfig;
	
	void InitInternalVariables(void);
	
	public:
	
		void Init(uint16_t pin); // initialisation with specification of SPI SS pin
		void Init(void); // initialisation
		void Reset(); // reset radio
	
	    void Powerdown(void); // powerdown the radio
		void SetRX(void); // set radio in reception mode
		void SetTX(void); // set radio in emission mode
		void SetIdle(void); // set radio in idle mode
		
		uint8_t BytesAvailableInTXFIFO(void); // get free space available TXFIFO
		uint8_t BytesAvailableInRXFIFO(void); // get number of bytes received
		uint8_t GetRSSI(); // get RSSI level
		uint8_t GetLQI(); // get LQI level
		uint8_t GetState(); // get MARC_STATE
		void FlushTX(); // Flush TX FIFO
		void FlushRX(); // Flush RX FIFO
		void FillTXFIFO(uint8_t* Data, uint8_t Count); // fill TX FIFO without sending
        void GetRXFIFO(uint8_t* Data, uint8_t Count); // get RX FIFO content		
		void RXModeOff(uint16_t Mode);
		void TXModeOff(uint16_t Mode);
		
        void SetChannel(uint8_t Channel); // set radio channel
        void SetAdress(uint8_t _Adress); // Set radio address
		void EnableAdressCheck(uint8_t Mode);
		void SetDeviation(uint8_t Deviation);
		void SetModulation(uint8_t Modulation);
		void SetSyncMode(uint8_t SyncMode);
		void EnableManchesterEnc(uint8_t Enable);
		void EnableCRC(uint8_t Enable);
		void EnableDataWhitening(uint8_t Enable);
		void SetPacketLenght(uint8_t Length);
		void ConfigureSyncWord(uint16_t SyncWord);
		void PacketLenghtMode(uint8_t Mode);
		void SetRate(uint32_t Rate);
		void SetFreq(uint32_t Frequency); // set frequency
		void SetPower(uint8_t Power); // configure power
		void SetAdress(uint8_t _Adress, uint8_t Broadcat); // configure radio address and broadcast
		void ConfigurePacket(uint8_t Preambule, uint8_t CRC_ENABLE, uint8_t LENGH_CONFIG, uint8_t PacketLenght, uint16_t SYNCWORD, uint8_t Adress_Check); // configure packet format
		uint32_t  GetFreq(void); // get the programmed frequency 
		void SetAppendStatus(uint8_t mode);
		
		void SendDataTo(uint8_t Addr, uint8_t *_txBuffer,uint8_t size_); // send data to specific address
		void SendData(uint8_t *txBuffer, uint8_t size); // Send data
		uint8_t ReceiveData(uint8_t *rxBuffer); // receive data
		
		
		void LoadConfigSettings(const uint8_t ConfigArray[][2], uint8_t Size); // this function allow to configure CC1101 with a single array
		uint8_t StrobeCmd(uint8_t cmd); 
		uint8_t ReadRegister(uint8_t addr); // read a register
		void ReadBurstRegister(uint8_t addr, uint8_t* buffer, uint8_t size); 
		void WriteRegister(uint8_t addr, uint8_t value); // write a register
		void WriteBurstRegister(uint8_t addr, uint8_t* buffer, uint8_t size); 
		
		
};

extern OPEN_RF OPEN_rf;

#endif