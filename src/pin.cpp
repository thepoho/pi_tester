#include "pin.h"
#include <string>

Pin::Pin()
{

}
Pin::~Pin()
{

}

void Pin::startup(int _num, string _name, int _wpi_num)
{
  num = _num;
  name = _name;
  wpi_num = _wpi_num;
  cout << "Starting pin " << num << " name: " << name << " wpi: " << wpi_num << endl;
}
