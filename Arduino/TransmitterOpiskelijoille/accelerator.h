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
  void Print();
  void makeMeasurement();
  Measurement getMeasurement();
  int sisaanmeno = 0;

private:
  Measurement m;
 
};

#endif // ACCELERATOR_H
