#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include "messaging.h"

struct Measurement
{
  int x;
  int y;
  int z;
};

class Accelerator
{
public:
  Accelerator();
  ~Accelerator();
  void makeMeasurement();
  Measurement getMeasurement();

private:
  Measurement m;
 
};

#endif // ACCELERATOR_H
