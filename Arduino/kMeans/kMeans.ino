#include "accelerator.h"
#include "keskipisteet.h"


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
  float value;
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
    //     Serial.println(w[1][1]);
    //     Serial.println((w[0][0]-m.x));
    float minvalue = 500;
    for (int j = 0; j < 6;)
    {
      value = abs(sqrt(pow((w[j][0] - m.x), 2) + pow((w[j][1] - m.y), 2) + pow((w[j][2] - m.z), 2)));
//      Serial.print("Value loop on: ");
//      Serial.println(value);
      //values[j] = value
      if (value < minvalue) {
        minvalue = value;
        paikka = w[j][3];
//        Serial.print("Min on: ");
//        Serial.println(minvalue);
//        Serial.print("Paikka on: ");
//        Serial.println(paikka);
      }
      j++;
    }

    Serial.print(flags);
    Serial.print(",");
    Serial.println(paikka);

    M++;
  } // end of for
}   // end of loop
