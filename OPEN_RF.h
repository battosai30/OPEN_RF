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

	public:
	
	    void Powerdown(void); // powerdown the radio
		void FillTXFIFO(uint8_t* Data, uint8_t Count); // fill TX FIFO without sending
        void GetRXFIFO(uint8_t* Data, uint8_t Count); // get RX FIFO content		
		void SetRX(void); // set radio in reception mode
		void SetTX(void); // set radio in emission mode
		void SetIdle(void); // set radio in idle mode
        void SetChannel(uint8_t Channel); // set radio channel
        uint8_t BytesAvailableInTXFIFO(void); // get free space available TXFIFO
		uint8_t BytesAvailableInRXFIFO(void); // get number of bytes received
		uint8_t GetRSSI(); // get RSSI level
		uint8_t GetLQI(); // get RSSI level
		void Reset(); // reset radio
	    void FlushTX(); // Flush TX FIFO
		void FlushRX(); // Flush RX FIFO
		void SetAdress(uint8_t _Adress); // Set radio address
		void Init(void); // initialisation
		void Init(uint16_t pin); // initialisation with specification of SPI SS pin
		uint8_t ReadRegister(uint8_t addr); // read a register
		void WriteRegister(uint8_t addr, uint8_t value); // write a register
	    uint8_t ReceiveData(uint8_t *rxBuffer); // receive data
		void SetFreq(uint32_t Frequency); // set frequency
		void SetPower(uint8_t Power); // configure power
		void SetAdress(uint8_t _Adress, uint8_t Broadcat); // configure radio address and broadcast
		void ConfigurePacket(uint8_t Preambule, uint8_t CRC_ENABLE, uint8_t LENGH_CONFIG, uint8_t PacketLenght, uint16_t SYNCWORD, uint8_t Adress_Check); // configure packet format
	    uint8_t GetState(); // get MARC_STATE
		void SendData(uint8_t *txBuffer, uint8_t size); // Send data
		void SetReceive(void); // receive data
		uint8_t CheckReceiveFlag(void);
		uint32_t  GetFreq(void); // get the programmed frequency 
        void LoadConfigSettings(const uint8_t ConfigArray[][2], uint8_t Size); // this function allow to configure CC1101 with a single array
		
};

extern OPEN_RF OPEN_rf;

#endif