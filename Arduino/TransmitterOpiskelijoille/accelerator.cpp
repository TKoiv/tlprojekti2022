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

}
Measurement Accelerator::getMeasurement()
{
 
}
