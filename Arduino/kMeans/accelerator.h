#ifndef ACCELERATOR_H
#define ACCELERATOR_H


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
  void Keskipisteet();
  void makeMeasurement();
  Measurement getMeasurement();
  int sisaanmeno = 0;
  int kp1 = 0;

private:
  Measurement m;
 
};

#endif // ACCELERATOR_H
