#include <OPEN_RF.h>
#include <SPI.h>

void setup()
{

  Serial.begin(9600);
  Serial.println("Launching");
  
  pinMode(5,INPUT); // GD0 pin

  OPEN_rf.Init(10); // chip select on pin 10

  OPEN_rf.SetModulation(MODULATION_ASK_OOK);
  OPEN_rf.RXModeOff(RXOFF_MODE_STAYINRX); 
  OPEN_rf.EnableAdressCheck(TRUE);
  OPEN_rf.SetAdress(23);
  OPEN_rf.EnableCRC(FALSE);

  OPEN_rf.SetRX();

  Serial.println("RX Enabled");

}

void loop() {

  if(digitalRead(5)) {

    if(OPEN_rf.BytesAvailableInRXFIFO()){

      delay(20);

      byte Buffer[20];

      Serial.print("Bytes in RX = ");
      Serial.println(OPEN_rf.BytesAvailableInRXFIFO());

      int y = OPEN_rf.ReceiveData(Buffer);

      Serial.print("Received : ");
      for (int i=0;i<y;i++) Serial.print(Buffer[i]);

      Serial.println("");

    }
  }

}

















