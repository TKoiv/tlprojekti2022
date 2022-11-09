#include "accelerator.h"
#include <arduino.h>

Accelerator::Accelerator()
{
  Serial.println("Accelerator created!");
}


Accelerator::~Accelerator()
{
  Serial.println("Accelerator deleted!");
}

void Accelerator::makeMeasurement()
{
  m.x = analogRead(A1);
  m.y = analogRead(A2);
  m.z = analogRead(A3);

  //m.x = 258*2;
  //m.y = 259;
  //m.z = 240;

}
Measurement Accelerator::getMeasurement()
{
  return m;
}

void Accelerator::Print()
{

  delay(500); // Annetaan aikaa käynnistelylle
  Serial.print("Sens_x");
  Serial.print("\t");
  Serial.print("Sens_y");
  Serial.print("\t");
  Serial.println("Sens_z"); // Tulostus ja rivinvaihto

  // print the results to the serial monitor:
  Serial.print(m.x);
  Serial.print("\t");
  Serial.print(m.y);
  Serial.print("\t");
  Serial.println(m.z);

}
