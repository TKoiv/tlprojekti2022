#include "messaging.h"
#include "accelerator.h"
#include <arduino.h>

Messaging::Messaging()
{
  Serial.println("messaging created!");
  pmanager = new RHReliableDatagram(driver, TRANSMITTER_ADDRESS);
 
  if (!pmanager->init())
    Serial.println("Radiohead manager init failed");

}

Messaging::~Messaging()
{
  Serial.println("Messaging deleted!");
  Serial.flush();
  delete pmanager;
}
void Messaging::createMessage(Measurement m)
{

  Data[0] = (m.x>>8);
  Data[1] = (m.x & 0x00ff);
  Data[2] = (m.y>>8);
  Data[3] = (m.y & 0x00ff);
  Data[4] = (m.z>>8);
  Data[5] = (m.z & 0x00ff);

  
  Serial.println(Data[0]);
  Serial.println(Data[1]);
  Serial.println(Data[2]);
  Serial.println(Data[3]);
  Serial.println(Data[4]);
  Serial.println(Data[5]);

}
bool Messaging::sendMessage(uint8_t id, uint8_t flags)
{
     unsigned long start = millis(); 
     unsigned long timeout = millis()-start;
     while(timeout<500)
     {
      timeout = millis()-start; 
     }
     driver.setModeTx();
     uint8_t to = RECEIVER_ADDRESS;
     uint8_t from = 73;  //TRANSMITTER_ADDRESS;
     
     pmanager->setHeaderTo(to);
     pmanager->setHeaderFrom(from);
     pmanager->setHeaderId(id);
     pmanager->setHeaderFlags(flags);
     
     bool returnValue = false;
  
     if (pmanager->sendto(Data, messageLength, RECEIVER_ADDRESS))
     {
        returnValue = true;
     }
     pmanager->waitPacketSent();   
     return returnValue;

}
bool Messaging::receiveACK()
{
    driver.setModeRx();
    unsigned long start = millis(); 
    unsigned long timeout = millis()-start;
    bool receiverResult = false;
    uint8_t to;
    uint8_t from;
    uint8_t len;
    uint8_t id;
    uint8_t flags;
    while((timeout<1500) && (!pmanager->available()))
    {
      timeout = millis()-start;       
    }

    // Jos while luupista päästään, niin on saatu ACK tai on kulunut 1s
    receiverResult = pmanager->recvfrom(buf,&len,&from,&to,&id,&flags);
    if(receiverResult)
    {
      Serial.println("ACK received");
      Serial.println((char *)buf);
      Serial.print("Lähetettiin osoitteesta = ");
      Serial.println(from);
      Serial.print("ID = ");
      Serial.println(id);
      Serial.print("flags = ");
      Serial.println(flags);
      return true;
    }
    else
    {
      Serial.println("ACK not received, retransmit");
      return false;
    }

}
