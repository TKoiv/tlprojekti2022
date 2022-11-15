#include "messaging.h"
#include "accelerator.h"

// Kiihtvyys-anturin napojen määrittely:
const int VccPin2        = A0;  // Käyttöjännite
const int GNDPin2        = A4;  // laitteen maa-napa
int RotationDirection = 0;
int idCounter = 0;


void setup() 
{
  Serial.begin(9600);
  

  // Kiihtvyys-anturin napojen määrittely:
  pinMode(VccPin2, OUTPUT);     // Kiihtyvyysanturin käyttöjännite Vcc
  pinMode(GNDPin2, OUTPUT);     // Kiihtyvyysanturin GND

  // Asetetaan syöttöjännite (5V UNO-BOARDILLA, 3.3V Genuino 101:llä) ja maa-arvot (0V):
  digitalWrite(VccPin2, HIGH);
  delayMicroseconds(2);
  digitalWrite(GNDPin2, LOW);
  delayMicroseconds(2);
  
}

void loop()
{
  Accelerator Aobject;
  Messaging Mobject;

  /*
     1 = Z-aksel up 
     2 = Z-aksel down

     3 = y-aksel up 
     4 = y-aksel down

     5 = x-aksel up 
     6 = x-aksel down
     
  */
  
  Serial.println("Give rotation of arduino");
  int RotationDirection = 0;

  while(RotationDirection==0)
  {
    if(Serial.available()>0)
    {
       RotationDirection = Serial.parseInt();
    }
  }

  
  
  Serial.println("Give number how many measurements");
  int NumberOfMeasurements = 0;

  
  while(NumberOfMeasurements==0)
  {
    if(Serial.available()>0)
    {
       NumberOfMeasurements = Serial.parseInt();
    }
  }

  int idCounter = 0;
  for(int M = 0;M<NumberOfMeasurements;M++)
  {
     Aobject.makeMeasurement();
     Measurement foo = Aobject.getMeasurement();
     Aobject.makeMeasurement();
     Aobject.Print();
     Measurement m = Aobject.getMeasurement();
     uint8_t id = M;
     uint8_t flags = RotationDirection;
     Mobject.createMessage(m);
     if(Mobject.sendMessage(id,flags))
     {
       Serial.println("Successfull transmission");
     }
     else
     {
       Serial.println("Transmission fails");
     }
     if(Mobject.receiveACK())
     {
       Serial.println("Receiver got message, going to next measurement");
     }
     else
     {
       Serial.println("Reciver did not get the message. Need to resend it");
       M--;  // Let's just revind for loop 
     }
  } // end of for
}   // end of loop
