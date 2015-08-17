
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

ReadBurstReg(CC1101_RXFIFO,Data,Count);

}

void OPEN_RF::SetAppendStatus(uint8_t mode){

byte ActualReg = ReadReg(CC1101_PKTCTRL1) & ~0x08;
WriteReg(CC1101_PKTCTRL1, ActualReg | (mode & 1)<<2);
_AppendStatus = mode & 1;

}

void OPEN_RF::SetRX(void){
Strobe(CC1101_SIDLE);
Strobe(CC1101_SFRX);
Strobe(CC1101_SRX);

}

void OPEN_RF::SetTX(void){
Strobe(CC1101_STX);
}

void OPEN_RF::SetIdle(void){
Strobe(CC1101_SIDLE);
while(GetState()!=1);
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
InitInternalVariables();
FlushTX();
FlushRX();
}

void OPEN_RF::Powerdown(void) {

Strobe(CC1101_SIDLE);
Strobe(CC1101_SXOFF);

}

uint8_t OPEN_RF::ReadRegister(uint8_t addr){

return ReadReg(addr);

}

void OPEN_RF::ConfigureSyncWord(uint16_t SyncWord){

 WriteReg(CC1101_SYNC0, SyncWord & 0xFF);
 WriteReg(CC1101_SYNC1, SyncWord>>8);

}

void OPEN_RF::RXModeOff(uint16_t Mode){

byte ActualReg = ReadReg(CC1101_MCSM1) & 0xF3;

WriteReg(CC1101_MCSM1, ActualReg | ((Mode & 0x3)<<2));

}

void OPEN_RF::TXModeOff(uint16_t Mode){

byte ActualReg = ReadReg(CC1101_MCSM1) & 0xFC;

WriteReg(CC1101_MCSM1, ActualReg | (Mode & 0x3));
}

void OPEN_RF::SetModulation(uint8_t Modulation){

byte ActualReg = ReadReg(CC1101_MDMCFG2) & 0x8F;

WriteReg(CC1101_MDMCFG2, ActualReg | ((Modulation & 0x7)<<4));

}

void OPEN_RF::SetRate(uint32_t Rate){



}

void OPEN_RF::SetSyncMode(uint8_t SyncMode){

byte ActualReg = ReadReg(CC1101_MDMCFG2) & 0xF8;

WriteReg(CC1101_MDMCFG2, ActualReg | (SyncMode & 0x07));

}

void OPEN_RF::EnableManchesterEnc(uint8_t Enable){

byte ActualReg = ReadReg(CC1101_MDMCFG2);

if(Enable) WriteReg(CC1101_MDMCFG2, ActualReg | 0x08);
else WriteReg(CC1101_MDMCFG2, ActualReg & ~0x08);

}

void OPEN_RF::SetDeviation(uint8_t Deviation){


}

void OPEN_RF::EnableAdressCheck(uint8_t Mode){

byte ActualReg = ReadReg(CC1101_PKTCTRL1) & 0xFC;

WriteReg(CC1101_PKTCTRL1, ActualReg | (Mode & 0x3));
 
_AdressCheck = Mode & 0x3;


}

void OPEN_RF::SetPacketLenght(uint8_t Length){
WriteReg(CC1101_PKTLEN,Length);
}

void OPEN_RF::PacketLenghtMode(uint8_t Mode){

byte ActualReg = ReadReg(CC1101_PKTCTRL0) & 0xFC;

WriteReg(CC1101_PKTCTRL0, ActualReg | (Mode & 0x03));


}

void OPEN_RF::EnableDataWhitening(uint8_t Enable){

byte ActualReg = ReadReg(CC1101_PKTCTRL0);

if(Enable) WriteReg(CC1101_PKTCTRL0, ActualReg | 0x40);
else WriteReg(CC1101_PKTCTRL0, ActualReg & ~0x40);

}

void OPEN_RF::EnableCRC(uint8_t Enable){

byte ActualReg = ReadReg(CC1101_PKTCTRL0);

if(Enable) WriteReg(CC1101_PKTCTRL0, ActualReg | 0x04);
else WriteReg(CC1101_PKTCTRL0, ActualReg & ~0x04);

}

void OPEN_RF::SetAdress(uint8_t _Adress){

//Strobe(CC1101_SIDLE);
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
Strobe(CC1101_SIDLE);
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

return ReadReg(CC1101_LQI) ;//& 0x7F;

}

uint8_t OPEN_RF::BytesAvailableInTXFIFO(){

return ReadReg(CC1101_TXBYTES) & 0x7F;

}

uint8_t OPEN_RF::BytesAvailableInRXFIFO(){

return ReadReg(CC1101_RXBYTES) & 0x7F;

}

uint8_t OPEN_RF::GetState(void) {

uint8_t value1,value2;
value1 = ReadReg(CC1101_MARCSTATE) & 0x1F;

while(value1!=value2) {
value2 = ReadReg(CC1101_MARCSTATE) & 0x1F;
value1 = ReadReg(CC1101_MARCSTATE) & 0x1F;
}

return value1;

}

void OPEN_RF::FlushTX(void){
Strobe(CC1101_SIDLE);
Strobe(CC1101_SFTX);
}

void OPEN_RF::FlushRX(void){
Strobe(CC1101_SIDLE);
Strobe(CC1101_SFRX);
}

void OPEN_RF::LoadConfigSettings(const uint8_t ConfigArray[][2], uint8_t Size){
uint8_t i = Size / (2*sizeof(uint8_t));

for(uint8_t y=0;y<i;y++) {
WriteReg(ConfigArray[y][0], ConfigArray[y][1]);
}

}

void OPEN_RF::SendData(uint8_t _txBuffer[],uint8_t size_){

    Strobe(CC1101_SIDLE);	
	WriteReg(CC1101_TXFIFO,size_);
	WriteBurstReg(CC1101_TXFIFO,_txBuffer,size_);			//write data to send
	Strobe(CC1101_STX);									//start send
    while (GetState()>1);	// whileSending

}

void OPEN_RF::SendDataTo(uint8_t Addr, uint8_t *_txBuffer,uint8_t size_){

    Strobe(CC1101_SIDLE);	
	WriteReg(CC1101_TXFIFO,size_+1);
	WriteReg(CC1101_TXFIFO,Addr);
	WriteBurstReg(CC1101_TXFIFO,_txBuffer,size_);			//write data to send
	Strobe(CC1101_STX);									//start send
    while (GetState()>1);	// whileSending

}

uint8_t OPEN_RF::StrobeCmd(uint8_t cmd){

   return Strobe(cmd);	
	
}

void OPEN_RF::WriteBurstRegister(uint8_t _addr, uint8_t _buffer[], uint8_t _size) {
	WriteBurstReg(_addr,_buffer,_size);
}

void OPEN_RF::ReadBurstRegister(uint8_t _addr, uint8_t _buffer[], uint8_t _size) {
	ReadBurstReg(_addr,_buffer,_size);
}

uint8_t OPEN_RF::ReceiveData(uint8_t* rxBuffer){
	
	uint8_t size;
	uint8_t status[2];

	if(BytesAvailableInRXFIFO())
	{
		size=ReadReg(CC1101_RXFIFO);
		
		   if(_AdressCheck) {
		byte Addr = ReadReg(CC1101_RXFIFO); 
		size--;
		} 
		
		 ReadBurstReg(CC1101_RXFIFO,rxBuffer,size);
		 
		 if(_AppendStatus) {
		 ReadBurstReg(CC1101_RXFIFO,status,2);
		 } 
		 
		return size;
	}
	else
	{
		return 0;
	}
	
}

void OPEN_RF::InitInternalVariables(void) {

_AdressCheck = ReadReg(CC1101_PKTCTRL1) & 0x03 ;
_AppendStatus = (ReadReg(CC1101_PKTCTRL1) & 0x04)>>2 ;

}




