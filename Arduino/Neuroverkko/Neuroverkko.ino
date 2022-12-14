#include "accelerator.h"
#include "parametritNeuro.h"


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

  while (RotationDirection == 0)
  {
    if (Serial.available() > 0)
    {
      RotationDirection = Serial.parseInt();
    }
  }



  Serial.println("Give number how many measurements");
  int NumberOfMeasurements = 0;


  while (NumberOfMeasurements == 0)
  {
    if (Serial.available() > 0)
    {
      NumberOfMeasurements = Serial.parseInt();
    }
  }

  int idCounter = 0;
  int M = 0;
  double value;
  double value2;
  int j = 0;
  float minvalue = 500;
  int paikka = 0;
  for (int M = 0; M < NumberOfMeasurements;)
  {
    Aobject.makeMeasurement();
    Measurement foo = Aobject.getMeasurement();
    Aobject.makeMeasurement();
    Aobject.Print();
    Measurement m = Aobject.getMeasurement();
    uint8_t id = M;
    uint8_t flags = RotationDirection;
    float minvalue = 500;
    int y = 0;
      for (int y =0; y < 6;)
      {
        int z = 0;
        value = ((w[z][y]+w[z+1][y]+w[z+2][y]) + b[y]);
        value2 = max(0,value);
        // Serial.print("Value loop on: ");
        // Serial.println(value, 15);
        Serial.print("Value2 loop on: ");
        Serial.println(value2, 3);

        // Serial.print("w0 loop on: ");
        // Serial.println(w[z][y]);
        // Serial.print("w1 loop on: ");
        // Serial.println(w[z+1][y]);
        // Serial.print("w2 loop on: ");
        // Serial.println(w[z+2][y]);
        y++;
      }
      

    M++;
  } // end of for
}   // end of loop
