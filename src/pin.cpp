#include "pin.h"
#include <string>

Pin::Pin()
{

}
Pin::~Pin()
{

}

void Pin::startup(int _num, string _name)
{
  num = _num;
  name = _name;
}