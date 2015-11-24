#ifndef _PIN_H
#define _PIN_H
#include "common_defines.h"

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1



class Pin
{
public:
  Pin();
  ~Pin();
  void startup(int _num, string _name, int _wpi_num);
  int getWpiNum() {return wpi_num;}
  string getName() {return name;}
  void serializeJson(Writer<StringBuffer>* writer);
  void setDirection(int dir) { direction = dir; }
  void setOutputState(int os) { outputState = os; }
private:
  string name;
  int num, wpi_num;
  int direction;
  int outputState;
};

#endif
