
/*
	OPEN_CC1101.h - CC1101 module library - V1.0
	
  	Author: B@tto battomicro.wordpress.com
	
	This library is designed to use CC1101/CC1100 module on Arduino and Energia platforms.
	
	This library is an updated version of Elechouse's CC1101 library : http://www.elechouse.com/elechouse/index.php?main_page=product_info&products_id=802
	
	Sea readme.txt for more informations and how to use this library
	
*/

#include "OPEN_RF.h"


OPEN_RF OPEN_rf;

void OPEN_RF::Reset(void) {

reset();

}

void OPEN_RF::FillTXFIFO(uint8_t* Data, uint8_t Count){

}

void OPEN_RF::GetRXFIFO(uint8_t* Data, uint8_t Count){

}

void OPEN_RF::SetRX(void){
Strobe(CC1101_SRX);
}

void OPEN_RF::SetTX(void){
Strobe(CC1101_STX);
}

void OPEN_RF::SetIdle(void){
Strobe(CC1101_SIDLE);
}

void OPEN_RF::Init(void) {

Init(SS_PIN_DEFAULT);

}

void OPEN_RF::Init(uint16_t pin){

#ifdef __MSP430_HAS_CC1101__  
Initialisation();
#else
Initialisation(pin);
#endif
	
LoadConfigSettings(RF_USERCONFIG,sizeof(RF_USERCONFIG)); // load user config in RF_usercfg.h
WritePATable(PaTable,8);   //CC1101 PATABLE config in RF_usercfg.h

}

void OPEN_RF::Powerdown(void) {

Strobe(CC1101_SIDLE);
Strobe(CC1101_SXOFF);

}

uint8_t OPEN_RF::ReadRegister(uint8_t addr){

return ReadReg(addr);

}

void OPEN_RF::WriteRegister(uint8_t addr, uint8_t value){

return WriteReg(addr, value);

}

void OPEN_RF::SetAdress(uint8_t _Adress, uint8_t Broadcat){

WriteReg(CC1101_ADDR,_Adress);

}

uint32_t OPEN_RF::GetFreq(void){

uint32_t Freq=0;
uint8_t Freq_array[3];
ReadBurstReg(CC1101_FREQ2,Freq_array,3);

return (long(Freq_array[0])<<16 | long(Freq_array[1])<<8 | long(Freq_array[2])) * FOSC / 65536;

}

void OPEN_RF::SetFreq(uint32_t Frequency){

Strobe(CC1101_SIDLE);
uint32_t FREQ = Frequency * 65536 / FOSC; 
uint8_t Freq_array[]={FREQ & 0xFF0000 >> 15,FREQ & 0xFF00 >> 7,FREQ & 0xFF};
WriteBurstReg(CC1101_FREQ2,Freq_array,3);

}

void OPEN_RF::SetChannel(uint8_t Channel){

WriteReg(CC1101_CHANNR,Channel);

}

void OPEN_RF::SetPower(uint8_t Power){

}

void OPEN_RF::ConfigurePacket(uint8_t Preambule, uint8_t CRC_ENABLE, uint8_t LENGH_CONFIG, uint8_t PacketLenght, uint16_t SYNCWORD, uint8_t Adress_Check){

}

uint8_t OPEN_RF::GetRSSI(){

return ReadReg(CC1101_RSSI);

}

uint8_t OPEN_RF::GetLQI(){

return ReadReg(CC1101_LQI) & 0x7F;

}

uint8_t OPEN_RF::BytesAvailableInTXFIFO(){

return Strobe(CC1101_SNOP) & 0xF;

}

uint8_t OPEN_RF::BytesAvailableInRXFIFO(){

return Strobe(CC1101_SNOP | READ_SINGLE) & 0xF;
}


uint8_t OPEN_RF::GetState() {

uint8_t value1,value2;
value1 = ReadReg(CC1101_MARCSTATE) & 0x1F;

while(value1!=value2) {
value2 = ReadReg(CC1101_MARCSTATE) & 0x1F;
value1 = ReadReg(CC1101_MARCSTATE) & 0x1F;
}

return value1;

}


void OPEN_RF::FlushTX(void){
Strobe(CC1101_SFTX);
}

void OPEN_RF::FlushRX(void){
Strobe(CC1101_SFRX);
}


void OPEN_RF::LoadConfigSettings(const uint8_t ConfigArray[][2], uint8_t Size) 
{
uint8_t i = Size / (2*sizeof(uint8_t));

for(uint8_t y=0;y<i;y++) {
WriteReg(ConfigArray[y][0], ConfigArray[y][1]);
}

}


void OPEN_RF::SendData(uint8_t *txBuffer,uint8_t size)
{
	
	WriteReg(CC1101_TXFIFO,size);
	WriteBurstReg(CC1101_TXFIFO,txBuffer,size);			//write data to send
	Strobe(CC1101_STX);									//start send
    while (GetState()>1);	// whileSending

}


void OPEN_RF::SetReceive(void)
{
	Strobe(CC1101_SRX);
}


uint8_t OPEN_RF::CheckReceiveFlag(void)
{
	/* if(digitalRead(GDO0))			//receive data
	{
		while (digitalRead(GDO0));
		return 1;
	}
	else							// no data
	{
		return 0;
	} */
}


uint8_t OPEN_RF::ReceiveData(uint8_t *rxBuffer)
{
	uint8_t size;
	uint8_t status[2];

	//if(SpiReadStatus(CC1101_RXBYTES) & BYTES_IN_RXFIFO)
	if(1)
	{
		size=ReadReg(CC1101_RXFIFO);
		ReadBurstReg(CC1101_RXFIFO,rxBuffer,size);
		ReadBurstReg(CC1101_RXFIFO,status,2);
		Strobe(CC1101_SFRX);
		return size;
	}
	else
	{
		Strobe(CC1101_SFRX);
		return 0;
	}
	
}






